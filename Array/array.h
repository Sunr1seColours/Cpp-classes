#ifndef ARRAY_H_
#define ARRAY_H_

#define ARRAY_TRAITS_IMPLEMENTED

#include <stdexcept>

class ArrayOutOfRange : public std::out_of_range {
 public:
  ArrayOutOfRange() : std::out_of_range("ArrayOutOfRange") {
  }
};

template<class T, size_t N>
class Array {
 public:
  T array[N];

  T &operator[](size_t i) {
    return array[i];
  }

  const T &operator[](size_t i) const {
    return array[i];
  }

  T &At(size_t idx) {
    if (idx >= N) {
      throw ArrayOutOfRange();
    }
    return array[idx];
  }

  const T &At(size_t idx) const {
    if (idx >= N) {
      throw ArrayOutOfRange();
    }
    return array[idx];
  }
  
  T &Front() {
    return array[0];
  }

  const T &Front() const {
    return array[0];
  }

  T &Back() {
    return array[N - 1];
  }

  const T &Back() const {
    return array[N - 1];
  }

  T *Data() {
    return array;
  }

  const T *Data() const {
    return array;
  }

  size_t Size() const {
    return N;
  }

  bool Empty() const {
    return N == 0;
  }

  void Fill(const T &value) {
    for (size_t i = 0; i < N; ++i) {
      array[i] = value;
    }
  }

  void Swap(Array<T, N> &other) {
    for (size_t i = 0; i < N; ++i) {
      std::swap(array[i], other[i]);
    }
  }
};

template<class T>
size_t GetSize(const T) {
  return 0;
}

template<class T, size_t N>
size_t GetSize(const T(&)[N]) {
  return N;
}

template<class T>
size_t GetRank(T) {
  return 0;
}

template<class T, size_t N>
size_t GetRank(const T(&arr)[N]) {
  return 1 + GetRank(arr[0]);
}

template<class T>
size_t GetNumElements(const T) {
  return 1;
}

template<class T, size_t N>
size_t GetNumElements(const T(&array)[N]) {
  return N * GetNumElements(array[0]);
}

#endif