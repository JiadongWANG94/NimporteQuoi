#include <memory>
#include <string>

#include "managed_shared_memory.hpp"
#include "domain_socket_ipc.hpp"

#define CHANNEL_BUFFER_SIZE 10

// template <typename T>
// class MessageChannel;

// class MessageChannelManager {
//  public:
//     MessageChannelManager *GetInstance();
//     template <typename T>
//     MessageChannel<T> *FindChannel(const std::string &);
// };

struct DataBlockHeader {
    uint8_t ref_count = 0;
    uint32_t timestamp = 0;
    pthread_rwlock_t rwlock;
};

template <typename T>
struct DataBlock {
    DataBlockHeader header;
    T payload;
};

class SharedMutex {
 public:
    explicit SharedMutex(pthread_rwlock_t *lock, bool initiative = false)
        : lock_(lock), initiative_(initiative) {
        if (initiative_) {
            // pthread_rwlock_init()
        }
    }
    ~SharedMutex() {
        if (initiative_) {
            // pthread_rwlock_destroy()
        }
    }
    bool Lock() { return pthread_rwlock_wrlock(lock_) == 0; }
    bool TryLock() { return pthread_rwlock_trywrlock(lock_) == 0; }
    bool Unlock() { return pthread_rwlock_unlock(lock_) == 0; }
    bool LockShared() { return pthread_rwlock_rdlock(lock_) == 0; }
    bool TryLockShared() { return pthread_rwlock_tryrdlock(lock_) == 0; }
    bool UnlockShared() { return pthread_rwlock_unlock(lock_) == 0; }

 private:
    pthread_rwlock_t *lock_;
    bool initiative_;
};

// class IpcConditionVariable {
//  public:
//     bool Wait();
//     bool NotifyAll();
// };

template <typename T>
class DataVisitor;

enum class MessageChannelAccessType { OPEN_ONLY = 0, CREATE_ONLY = 1 };

template <typename T>
class MessageChannel {
    typedef void DestroyHandleFunc(T *);
    struct MessageChannelHeader {
        unsigned int capacity = CHANNEL_BUFFER_SIZE;
        unsigned int head_idx = 0;
        unsigned int tail_idx = 0;
        bool is_empty = true;
        unsigned int block_size = 0;
        pthread_rwlock_t rwlock;
    };

 public:
    MessageChannel() {}

    bool Init(MessageChannelAccessType type,
              const std::string &name,
              unsigned int capacity);
    bool Reset();

    // std::string GetName();
    int TryPush(const T &,
                uint32_t timestamp,
                DestroyHandleFunc *destroy_handle = nullptr);
    int Push(const T &,
             uint32_t timestamp,
             DestroyHandleFunc *destroy_handle = nullptr);
    bool TryPop();
    bool Pop();
    DataVisitor<T> &GetLatest();
    const T *GetLatestConstPtr();
    DataVisitor<T> &GetLatestWithTimestamp(uint32_t timestamp);

 private:
    MessageChannelHeader *GetHeader() {
        return static_cast<MessageChannelHeader *>(
            shared_memory_->GetAddress());
    }

    DataBlock *GetBlock(unsigned int idx) {
        return reinterpret_cast<DataBlock *>(
                   static_cast<char *>(shared_memory_->GetAddress()) +
                   sizeof(MessageChannelHeader)) +
               idx;
    }

    unsigned int &Capacity() { return GetHeader()->capacity; }
    unsigned int &HeadIdx() { return GetHeader()->head_idx; }
    unsigned int &TailIdx() { return GetHeader()->tail_idx; }
    unsigned int Size();
    bool &IsEmpty() { return GetHeader()->is_empty; }

 private:
    // std::string name_;
    // std::shared_ptr<DomainSocketPublisher> publisher_;
    // std::shared_ptr<DomainSocketSubscriber> subscriber_;
    std::shared_ptr<ManagedSharedMemory> shared_memory_;
};

template <typename T>
bool MessageChannel<T>::Init(MessageChannelAccessType type,
                             const std::string &name,
                             unsigned int capacity) {
    if (MessageChannelAccessType::OPEN_ONLY == type && capacity != 0) {
        LINFO(MessageChannel)
            << "Capacity should be zero when open an existing channel."
            << std::endl;
        return false;
    }
    if (MessageChannelAccessType::OPEN_ONLY == type) {
        subscriber_.reset(new DomainSocketSubscriber());
        if (!subscriber_->Init(name + ".socket")) {
            LINFO(MessageChannel) << "Failed to init subscriber." << std::endl;
            this->Reset();
            return false;
        } else {
            LINFO(MessageChannel) << "Subscriber initiated." << std::endl;
        }
        shared_memory_.reset(new ManagedSharedMemory());
        if (!shared_memory_->Init(name + ".shm",
                                  SharedMemoryAccessType::OPEN_ONLY,
                                  sizeof(MessageChannelHeader))) {
            LINFO(MessageChannel)
                << "Failed to init shared memory." << std::endl;
            this->Reset();
            return false;
        } else {
            LINFO(MessageChannel) << "Shared memory initiated." << std::endl;
        }
        shared_memory_->Allocate(this->GetHeader()->capacity * sizeof(T));
    } else if (MessageChannelAccessType::CREATE_ONLY == type) {
        publisher_.reset(new DomainSocketPublisher());
        if (!publisher_->Init(name + ".socket")) {
            LINFO(MessageChannel) << "Failed to init publisher." << std::endl;
            this->Reset();
            return false;
        } else {
            LINFO(MessageChannel) << "Publisher initiated." << std::endl;
        }
        shared_memory_.reset(new ManagedSharedMemory());
        if (!shared_memory_->Init(
                name + ".shm", SharedMemoryAccessType::CREATE_ONLY,
                sizeof(MessageChannelHeader) + capacity * sizeof(T))) {
            LINFO(MessageChannel)
                << "Failed to init shared memory." << std::endl;
            this->Reset();
            return false;
        } else {
            LINFO(MessageChannel) << "Shared memory initiated." << std::endl;
        }
        this->GetHeader()->capacity = capacity;
        this->GetHeader()->block_size = sizeof(DataBlock);
    }
    return true;
}

template <typename T>
bool MessageChannel<T>::Reset() {
    publisher_.reset();
    subscriber_.reset();
    shared_memory_.reset();
    return true;
}

template <typename T>
bool MessageChannel<T>::TryPush(const T &element, uint32_t timestamp) {
    if (Size() >= Capacity()) {
        return false;
    }
    memcpy(&(GetBlock(HeadIdx())->payload), &element, sizeof(T));
    GetBlock(HeadIdx())->timestamp = timestamp;
    HeadIdx() = (HeadIdx() + 1) % Capacity();
    IsEmpty() = false;
    return true;
}

template <typename T>
bool MessageChannel<T>::Pop() {
    if (IsEmpty()) {
        ;
    } else {
        TailIdx() = (TailIdx() + 1) % Capacity();
        if (TailIdx() == HeadIdx()) {
            IsEmpty() = true;
        }
    }
    return true;
}

template <typename T>
bool MessageChannel<T>::TryPop() {
    if (IsEmpty()) {
        ;
    } else {
        TailIdx() = (TailIdx() + 1) % Capacity();
        if (TailIdx() == HeadIdx()) {
            IsEmpty() = true;
        }
    }
    return true;
}

template <typename T>
unsigned int MessageChannel<T>::Size() {
    if (IsEmpty()) {
        return 0;
    }
    if (HeadIdx() > TailIdx()) {
        return HeadIdx() - TailIdx();
    } else {
        return HeadIdx() + (Capacity() - TailIdx());
    }
}

template <typename T>
class DataVisitor {
    friend class MessageChannel<T>;

 public:
    DataVisitor();
    ~DataVisitor() {
        sem_wait(sem_);
        ref_count_--;
        sem_post(sem_);
    }
    DataVisitor(const DataVisitor &);
    DataVisitor &operator=(const DataVisitor &);
    DataVisitor(DataVisitor &&);
    T &GetData();

 private:
    T *address_;
    uint8_t *ref_count_;
    sem_t sem_;
};
