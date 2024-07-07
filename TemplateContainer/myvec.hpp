#ifndef MYVEC_HPP
#define MYVEC_HPP

#include <vector> // For debugging usage
#include <iostream>

template <typename T>
MyVec
{
private:
public:
  // constructor
  MyVec();
  // MyVec(size_t size);
  // MyVec(size_t size, const T &value);
  // MyVec(const MyVec &rhs);
  // MyVec(MyVec &&rhs);
  // desctructor
  ~MyVec();
  void clear();
  void resize();
  void push_back();
  void pop_back();
  void insert();
  bool empty() const;
  size_t size() const;

  // operator
  T &operator[](size_t index) const;
  T &at(size_t index) const;
};

#endif // MYVEC_HPP
template MyVec<int>;
