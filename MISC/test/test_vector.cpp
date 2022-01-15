#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

template <typename T>
class MyVector {
 public:
    MyVector();
    ~MyVector();
    bool push_back(const T &);
    bool pop_back();
    T &operator[](unsigned int idx);
    unsigned int size() { return size_; }
    unsigned int capacity() { return capacity_; }

 private:
    unsigned int size_ = 0;
    unsigned int capacity_ = 0;
    char *data_ = nullptr;
};

template <typename T>
MyVector<T>::MyVector() {
    data_ = static_cast<char *>(malloc(sizeof(T) * 10));
    capacity_ = 10;
}

template <typename T>
MyVector<T>::~MyVector() {
    if (data_ != nullptr) {
        free(data_);
    }
}

template <typename T>
bool MyVector<T>::push_back(const T &data) {
    if (size_ == capacity_) {
        capacity_ = capacity_ * 2;
        char *tmp = static_cast<char *>(malloc(sizeof(T) * capacity_));
        memcpy(tmp, data_, sizeof(T) * size_);
        free(data_);
        data_ = tmp;
    }
    memcpy(data_ + sizeof(T) * size_, &data, sizeof(T));
    size_++;
    return true;
}

template <typename T>
bool MyVector<T>::pop_back() {
    if (size_ > 0) {
        size_--;
        return true;
    } else {
        return false;
    }
}

template <typename T>
T &MyVector<T>::operator[](unsigned int idx) {
    return *reinterpret_cast<T *>(data_ + sizeof(T) * idx);
}

int main() {
    MyVector<int> vector;
    vector.push_back(2);
    vector.push_back(3);
    vector.pop_back();
    std::cout << vector.size() << std::endl;
    std::cout << vector.capacity() << std::endl;
    std::cout << vector[0] << std::endl;
    return 0;
}
