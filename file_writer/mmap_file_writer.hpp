#pragma once

#include <string>

class MmapFileWriter {
 public:
    ~MmapFileWriter();
    bool Init(const std::string &file_path);
    bool Write(const std::string &);
    bool Write(const char *);
    MmapFileWriter &operator<<(const std::string&);
    MmapFileWriter &operator<<(const char *);
 private:
    bool is_initiated_;
    char* cursor_;
    char* start_;
    char* end_;
    std::string file_path_;
    int fd_;
    size_t epoch_size_pg_ = 1;  // pages
    int32_t offset_;
 private:
    bool allocate_new_epoch();
};