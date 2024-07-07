#ifndef MYVEC_HPP
#define MYVEC_HPP

#include <vector> // For debugging usage
#include <iostream>

template <typename T>
class MyVec
{
private:
  T *data = nullptr;
  size_t data_size = 0;
  size_t data_length = 0;
  std::vector<T> debug_data = std::vector<T>();

public:
  // constructor
  MyVec();
  // MyVec(size_t size);
  // MyVec(size_t size, const T &value);
  // MyVec(const MyVec &rhs);
  // MyVec(MyVec &&rhs);
  // desctructor
  ~MyVec();
  // void clear();
  // void resize();
  // void push_back();
  // void pop_back();
  // void insert();
  // bool empty() const;
  // size_t size() const;

  // operator
  // T &operator[](size_t index) const;
  // T &at(size_t index) const;
};

#include "myvec.hpp"

template <typename T>
MyVec<T>::MyVec()
{
  std::cout << "MyVec constructor" << std::endl;
  data_size = 0;
  data_length = 0;
  if (data != nullptr)
  {
    delete[] data;
    data = nullptr;
  }
};
template <typename T>
MyVec<T>::~MyVec()
{
  std::cout << "MyVec destructor" << std::endl;
  if (data != nullptr)
  {
    delete[] data;
  }
};

template class MyVec<int>;
#endif // MYVEC_HPP
// template class MyVec<float>;
// template class MyVec<double>;
// template class MyVec<std::string>;
