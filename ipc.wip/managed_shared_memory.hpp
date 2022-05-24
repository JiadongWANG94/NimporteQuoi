#include <string>
#include <unistd.h>
#include <sys/mman.h>
#include <iostream>

#include "log.hpp"

#define SHARED_MEMORY_ROOT std::string("./")

enum class SharedMemoryAccessType { OPEN_ONLY = 0, CREATE_ONLY = 1 };

class ManagedSharedMemory {
 public:
    ManagedSharedMemory() {}
    ~ManagedSharedMemory();

    bool Init(const std::string &name,
              SharedMemoryAccessType type,
              unsigned int size);
    bool Allocate(unsigned int size);
    bool Deallocate(unsigned int size);
    void *GetAddress() { return address_; }

    unsigned int Size() { return size_; }

 private:
    unsigned int size_ = 0;
    int fd_ = 0;
    FILE *fp_ = nullptr;
    std::string name_;
    void *address_ = nullptr;
    bool initiated_ = false;
    SharedMemoryAccessType type_;
};

bool ManagedSharedMemory::Init(const std::string &name,
                               SharedMemoryAccessType type,
                               unsigned int size) {
    if (initiated_) {
        return true;
    }
    size_ = size;
    std::string file_name = SHARED_MEMORY_ROOT + "/" + name;
    if (SharedMemoryAccessType::CREATE_ONLY == type) {
        int protection = PROT_WRITE;
        int visibility = MAP_SHARED;
        if (0 == access(file_name.c_str(), F_OK)) {
            // check
            LINFO(ManagedSharedMemory) << "File exists." << std::endl;
            if (0 != unlink(file_name.c_str())) {
                LINFO(ManagedSharedMemory) << "Failed to unlink." << std::endl;
                return false;
            }
        }
        fp_ = fopen((SHARED_MEMORY_ROOT + "/" + name).c_str(), "w+");
        if (nullptr != fp_) {
            fd_ = fileno(fp_);
        } else {
            LINFO(ManagedSharedMemory) << "Failed to create file." << std::endl;
            return false;
        }

        if (ftruncate(fd_, size) < 0) {
            LINFO(ManagedSharedMemory) << "Failed to ftruncate." << std::endl;
            return false;
        }

        address_ = mmap(NULL, size, protection, visibility, fd_, 0);
        if (nullptr == address_) {
            LINFO(ManagedSharedMemory) << "Failed mmap." << std::endl;
            return false;
        } else {
            LINFO(ManagedSharedMemory)
                << "Mmap succeed to address " << address_ << std::endl;
        }
        return true;
    } else {
        int protection = PROT_READ;
        int visibility = MAP_SHARED;
        fp_ = fopen(file_name.c_str(), "r");
        if (nullptr != fp_) {
            fd_ = fileno(fp_);
        } else {
            LINFO(ManagedSharedMemory) << "Failed to create file." << std::endl;
            return false;
        }
        address_ = mmap(NULL, size, protection, visibility, fd_, 0);
        if (nullptr == address_) {
            LINFO(ManagedSharedMemory) << "Failed mmap." << std::endl;
            return false;
        }
        return true;
    }
    initiated_ = true;
}

ManagedSharedMemory::~ManagedSharedMemory() {
    if (initiated_) {
        munmap(address_, size_);
        close(fd_);
    }
}

bool ManagedSharedMemory::Allocate(unsigned int size) { return true; }

bool ManagedSharedMemory::Deallocate(unsigned int size) { return true; }