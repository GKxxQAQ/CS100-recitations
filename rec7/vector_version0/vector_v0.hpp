#ifndef CS100_VECTOR_HPP
#define CS100_VECTOR_HPP

#include <cstddef>
#include <algorithm>

// We do not separate the allocation of memory and the construction of object,
// which is fine because we only store some ints.
class Vector {
  size_t m_size, m_capacity;
  int *m_data;

 public:
  Vector() : m_size(0), m_capacity(0), m_data(nullptr) {}
  Vector(int *arr, size_t n) : m_size(n), m_capacity(n), m_data(new int[n]()) {
    std::copy(arr, arr + n, m_data);
  }
  Vector(size_t n)  // a Vector with n elements value-initialized.
      : m_size(n), m_capacity(n), m_data(new int[n]()) {}
  ~Vector() {
    delete[] m_data;
  }

  void push_back(int x) {
    check_and_realloc();
    m_data[m_size++] = x;
  }
  void pop_back() {
    --m_size;
  }
  
  void shrink_to_fit() {
    if (m_size)
      reallocate(m_size);
    else {
      delete[] m_data;
      m_data = nullptr;
      m_capacity = 0;
    }
  }
  void clear() {
    m_size = 0;
  }

  size_t size() const {
    return m_size;
  }
  size_t capacity() const {
    return m_capacity;
  }
  bool empty() const {
    return size() == 0;
  }

  int &front() {
    return m_data[0];
  }
  const int &front() const {
    return m_data[0];
  }
  int &back() {
    return m_data[m_size - 1];
  }
  const int &back() const {
    return m_data[m_size - 1];
  }

  int &at(size_t n) {
    return m_data[n];
  }
  const int &at(size_t n) const {
    return m_data[n];
  }

 private:
  void reallocate(size_t new_cap) {
    int *new_data = new int[new_cap];
    std::copy(m_data, m_data + m_size, new_data);
    delete[] m_data;
    m_capacity = new_cap;
    m_data = new_data;
  }

  void check_and_realloc() {
    if (m_size == m_capacity)
      reallocate(m_capacity ? m_capacity * 2 : 1);
  }

  friend bool operator==(const Vector &, const Vector &);
  friend bool operator<(const Vector &, const Vector &);
};

inline bool operator==(const Vector &lhs, const Vector &rhs) {
  if (lhs.m_size != rhs.m_size)
    return false;
  for (size_t i = 0; i < lhs.m_size; ++i)
    if (lhs.m_data[i] != rhs.m_data[i])
      return false;
  return true;
}

inline bool operator<(const Vector &lhs, const Vector &rhs) {
  size_t size = std::min(lhs.m_size, rhs.m_size);
  for (size_t i = 0; i < size; ++i) {
    if (lhs.m_data[i] < rhs.m_data[i])
      return true;
    if (rhs.m_data[i] < lhs.m_data[i])
      return false;
  }
  return lhs.m_size < rhs.m_size;
}

inline bool operator!=(const Vector &lhs, const Vector &rhs) {
  return !(lhs == rhs);
}

inline bool operator>(const Vector &lhs, const Vector &rhs) {
  return rhs < lhs;
}

inline bool operator<=(const Vector &lhs, const Vector &rhs) {
  return !(lhs > rhs);
}

inline bool operator>=(const Vector &lhs, const Vector &rhs) {
  return !(lhs < rhs);
}

void print_vector(std::ostream &os, const Vector &vec) {
  for (size_t i = 0; i + 1 < vec.size(); ++i)
    os << vec.at(i) << ' ';
  if (vec.size() > 1)
    os << vec.back();
}

#endif // CS100_VECTOR_HPP
