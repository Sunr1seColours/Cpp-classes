#ifndef VECTOR_H_
#define VECTOR_H_

#include <iostream>
#include <utility>
#include <vector>

template<class T>
class Vector {
 public:
  class Iterator {
   private:
    T *current_ = nullptr;
    
   public:
    Iterator() {
    }

    explicit Iterator(T *p_int) {
      current_ = p_int;
    }

    Iterator &operator=(const Iterator &iterator) {
      current_ = iterator.current_;
      return *this;
    }

    Iterator &operator+=(int step) {
      current_ += step;
      return *this;
    }

    Iterator &operator-=(int step) {
      current_ -= step;
      return *this;
    }

    Iterator operator+(int step) const {
      Iterator result = *this;
      result += step;
      return result;
    }

    Iterator operator-(int step) const {
      Iterator result = *this;
      return result -= step;
    }

    size_t operator-(const Iterator &iterator) {
      return current_ - iterator.current_;
    }

    size_t operator+(const Iterator &iterator) {
      return current_ + iterator.current_;
    }

    Iterator &operator++() {
      return *this += 1;
    }

    Iterator &operator--() {
      current_ -= 1;
      return *this;
    }

    Iterator operator++(int) {
      Iterator curr = *(this);
      ++(*this);
      return curr;
    }

    Iterator operator--(int) {
      Iterator curr = *(this);
      --(*this);
      return curr;
    }

    T operator*() {
      return *current_;
    }

    T *operator->() {
      return current_;
    }

    bool operator==(const Iterator &other) const {
      return current_ == other.current_;
    }

    bool operator!=(const Iterator &other) const {
      return current_ != other.current_;
    }
  };

  Vector() {
    Reserve(1);
  }

  explicit Vector(size_t size) {
    Realloc(size);
    for (size_t i = 0; i < size; ++i) {
      *(data_ + i) = 0;
    }
    size_ = size;
    capacity_ = size_;
  }

  Vector(std::initializer_list<int> list) {
    Realloc(list.size());
    for (size_t i = 0; i < list.size(); ++i) {
      *(data_ + i) = *(list.begin() + i);
    }
    size_ = list.size();
    capacity_ = size_;
  }

  Vector(const Vector &vector) {
    Reserve(vector.capacity_);
    for (size_t i = 0; i < vector.size_; ++i) {
      *(data_ + i) = *(vector.data_ + i);
    }
    size_ = vector.size_;
    capacity_ = vector.capacity_;
  }

  Vector(Vector &&vector) {
    data_ = vector.data_;
    capacity_ = vector.size_;
    size_ = vector.size_;
    vector.data_ = nullptr;
  }

  Vector &operator=(Vector vector) {
    Reserve(vector.capacity_);
    for (size_t i = 0; i < vector.size_; ++i) {
      *(data_ + i) = *(vector.data_ + i);
    }
    size_ = vector.size_;
    capacity_ = vector.capacity_;
    return *this;
  }

  ~Vector() {
    delete[] data_;
  }

  T &operator[](size_t index) {
    return *(data_ + index);
  }

  T operator[](size_t index) const {
    return *(data_ + index);
  }

  size_t Size() const {
    return size_;
  }

  size_t Capacity() const {
    return capacity_;
  }

  void Swap(Vector &vector) {
    std::swap(data_, vector.data_);
    std::swap(capacity_, vector.capacity_);
    std::swap(size_, vector.size_);
  }

  void PushBack(T element) {
    if (capacity_ >= size_ + 1) {
      *(data_ + size_) = element;
      ++size_;
    } else {
      Reserve(size_ * 2);
      *(data_ + size_) = element;
      ++size_;
    }
  }

  bool Empty() {
    return size_ == 0;
  }

  void PopBack() {
    if (!Empty()) {
      --size_;
    }
  }

  void Clear() {
    size_ = 0;
  }

  void Reserve(size_t size) {
    if (capacity_ < size) {
      Realloc(size);
      capacity_ = size;
    }
  }

  Iterator Begin() {
    return Iterator(data_);
  }

  Iterator End() {
    return Iterator(data_ + size_);
  }

  Iterator begin() {// NOLINT
    return Iterator(data_);
  }

  Iterator end() {// NOLINT
    return Iterator(data_ + size_);
  }

  private:
  T *data_ = nullptr;
  size_t size_ = 0;
  size_t capacity_ = 0;

  void Realloc(size_t new_size) {
    if (capacity_ == 0) {
      data_ = new T[new_size];
      capacity_ = new_size;
    } else {
      auto copy = new T[new_size];

      std::move(data_, data_ + size_, copy);
      delete[] data_;

      data_ = copy;
      capacity_ = new_size;
    }
  }
};

#endif