#include "domain_socket_ipc.hpp"

#include "test.hpp"
#include "log.hpp"

#include <string>

REGISTER_TEST(test_domain_socket_ipc) {
    std::string domain_socket_name = "test.socket";
    DomainSocketPublisher pub;
    pub.Init(domain_socket_name);

    int content = 1;
    pub.Publish(content);
    std::thread t([=]() {
        DomainSocketSubscriber sub;
        sub.Init(domain_socket_name);
        while (1) {
            int receive = 0;
            sub.Receive(&receive);
            LOG(test_domain_socket_ipc) << receive << std::endl;
        }
    });
    t.detach();
    sleep(5);
    pub.Publish(int(2));
    pub.Publish(int(3));
    pub.Publish(int(4));
    pub.Publish(int(5));

    sleep(10);
    return true;
}

int main() {
    InitFailureHandle();
    RunTests();
    return 0;
}