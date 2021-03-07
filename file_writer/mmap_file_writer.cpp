/**
 * Wang Jiadong <jiadong.wang.94@outlook.com>
 */

#include "mmap_file_writer.hpp"

#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include <cstring>
#include <string>
#include <cstdio>

MmapFileWriter::~MmapFileWriter() {
    munmap(static_cast<void*>(start_), epoch_size_pg_ * getpagesize());
}

bool MmapFileWriter::Init(const std::string& file_path) {
    if (this->is_initiated_) return true;
    this->is_initiated_ = true;
    fd_ = open(file_path.c_str(), O_CREAT | O_RDWR,
               S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH | S_IWGRP);
    if (-1 == fd_) {
        perror("failed to open file");
        return false;
    }
    cursor_ = 0;
    end_ = 0;
    offset_ = 0;
    return true;
}

bool MmapFileWriter::Write(const char* msg) {
    size_t offset = 0;
    if (0 == end_ - cursor_) {
        int ret = allocate_new_epoch();
        if (0 != ret) {
            perror("failed to allocate new epoch");
            return false;
        }
    }
    while (strlen(msg) - offset > size_t(end_ - cursor_)) {
        memcpy(cursor_, msg + offset, sizeof(char) * (end_ - cursor_));
        offset += (end_ - cursor_);
        cursor_ += (end_ - cursor_);
        if (!allocate_new_epoch()) {
            perror("failed to allocate new epoch");
            return false;
        }
    }
    memcpy(cursor_, msg + offset, sizeof(char) * (strlen(msg) - offset));
    cursor_ += strlen(msg) - offset;
    return true;
}

MmapFileWriter& MmapFileWriter::operator<<(const char* msg) {
    Write(msg);
    return *this;
}

bool MmapFileWriter::allocate_new_epoch() {
    if (0 !=
        munmap(static_cast<void*>(start_), epoch_size_pg_ * getpagesize())) {
        perror("failed to munmap");
        return false;
    }
    if (0 != ftruncate(fd_, offset_ + epoch_size_pg_ * getpagesize())) {
        perror("failed in ftruncate");
        return false;
    }

    void* ret =
        mmap(NULL, epoch_size_pg_ * getpagesize(),
             PROT_EXEC | PROT_READ | PROT_WRITE, MAP_SHARED, fd_, offset_);
    if (NULL == ret) {
        perror("failed in creating mmap");
        return false;
    }
    offset_ += epoch_size_pg_ * getpagesize();
    start_ = static_cast<char*>(ret);
    cursor_ = static_cast<char*>(ret);
    end_ = static_cast<char*>(ret) + epoch_size_pg_ * getpagesize();
    return true;
}