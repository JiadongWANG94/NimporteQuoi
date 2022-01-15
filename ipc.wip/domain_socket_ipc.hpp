#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <string>
#include <functional>
#include <thread>
#include <vector>

#include "log.hpp"

#define DOMAIN_SOCKET_ROOT std::string("./")

class DomainSocketPublisher;
class DomainSocketSubscriber;

// class IPCContext {
//  public:
//     IPCContext *GetInstance() {
//         static IPCContext instance;
//         return &instance;
//     }
//  public:
//     DomainSocketPublisher *createDomainSocketPublisher(const std::string
//     &topic); DomainSocketSubscriber *createDomainSocketSubscriber(const
//     std::string &topic);
//  private:
//     IPCContext() = default;
//     IPCContext(const IPCContext &) = default;
//     IPCContext &operator=(const IPCContext &) = default;
// };

// DomainSocketPublisher *IPCContext::createDomainSocketPublisher(const
// std::string &topic) {
//     std::string socket_path = DOMAIN_SOCKET_ROOT + "/" + topic;

//     int listenfd, connfd;
//     pid_t childpid;
//     socklen_t clilen;
//     struct sockaddr_un cliaddr, servaddr;

//     listenfd = socket(AF_LOCAL, SOCK_STREAM, 0);
//     unlink(socket_path);
//     bzero(&servaddr, sizeof(servaddr));
//     servaddr.sun_family = AF_LOCAL;
//     strcpy(servaddr.sun_path, socket_path.c_str());

//     bind(listenfd, (sockaddr *) &servaddr, sizeof(servaddr));
// }

class DomainSocketPublisher {
 public:
    bool Init(const std::string &topic);

    template <typename T>
    bool Publish(const T &);

 private:
    std::vector<int> listenfd_list_;
    int listenfd_;
    std::mutex list_mtx_;
    std::atomic<bool> alive_{false};
};

bool DomainSocketPublisher::Init(const std::string &topic) {
    std::string socket_path = DOMAIN_SOCKET_ROOT + "/" + topic;
    std::cout << "topic " << topic << std::endl;

    std::cout << "socket_path " << socket_path << std::endl;
    alive_.store(true);
    struct sockaddr_un servaddr;

    listenfd_ = socket(AF_LOCAL, SOCK_STREAM, 0);
    LOG(DomainSocketPublisher) << "listen fd is " << listenfd_ << std::endl;

    unlink(socket_path.c_str());
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sun_family = AF_LOCAL;
    strcpy(servaddr.sun_path, socket_path.c_str());
    LOG(DomainSocketPublisher) << "socket path " << socket_path << std::endl;

    if (bind(listenfd_, (sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        LOG(DomainSocketPublisher)
            << "Error failed bind to socket" << std::endl;
        return false;
    } else {
        LOG(DomainSocketPublisher) << "Bind success." << std::endl;
    }

    if (listen(listenfd_, SOMAXCONN) < 0) {
        LOG(DomainSocketPublisher)
            << "Error failed to listen socket" << std::endl;
        return false;
    } else {
        LOG(DomainSocketPublisher) << "Listen success." << std::endl;
    }

    std::function<void()> worker_fn = [this]() {
        while (this->alive_.load()) {
            struct sockaddr_un cliaddr;
            socklen_t clientlen = sizeof(cliaddr);
            int connfd =
                accept(this->listenfd_, (sockaddr *)&cliaddr, &clientlen);
            if (connfd < 0) {
                LOG(DomainSocketPublisher)
                    << "Error accept return code < 0" << std::endl;
                continue;
            } else {
                LOG(DomainSocketPublisher) << "Accept success." << std::endl;
            }
            {
                std::lock_guard<std::mutex> guard(list_mtx_);
                LOG(DomainSocketPublisher)
                    << "Register client fd " << connfd << std::endl;
                this->listenfd_list_.push_back(connfd);
            }
            sleep(1);
        }
    };
    std::thread worker_thread(worker_fn);
    worker_thread.detach();
    return true;
}

template <typename T>
bool DomainSocketPublisher::Publish(const T &data) {
    std::lock_guard<std::mutex> guard(list_mtx_);
    LOG(DomainSocketPublisher) << "Number to client subscribed to publisher : "
                               << this->listenfd_list_.size() << std::endl;
    for (auto &connfd : listenfd_list_) {
        LOG(DomainSocketPublisher)
            << "Publish to connection fd " << connfd << std::endl;
        write(connfd, &data, sizeof(T));
    }
    return true;
}

class DomainSocketSubscriber {
 public:
    bool Init(const std::string &topic);

    template <typename T>
    bool Receive(T *);

 private:
    int sockfd_;
};

bool DomainSocketSubscriber::Init(const std::string &topic) {
    std::string socket_path = DOMAIN_SOCKET_ROOT + "/" + topic;
    struct sockaddr_un servaddr;
    sockfd_ = socket(AF_LOCAL, SOCK_STREAM, 0);
    if (sockfd_ == 0) {
        LOG(DomainSocketSubscriber)
            << "Error failed to get socket fd." << std::endl;
        return false;
    }
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sun_family = AF_LOCAL;
    strcpy(servaddr.sun_path, socket_path.c_str());
    if (connect(sockfd_, (sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        LOG(DomainSocketSubscriber)
            << "Error failed to connect server." << std::endl;
        return false;
    }
    return true;
}

template <typename T>
bool DomainSocketSubscriber::Receive(T *buffer) {
    if (nullptr == buffer) {
        LOG(DomainSocketSubscriber) << "Error nullptr" << std::endl;
        return false;
    }
    int count = read(sockfd_, buffer, sizeof(T));
    LOG(DomainSocketSubscriber)
        << "Number of bytes received " << count << std::endl;
    return true;
}
