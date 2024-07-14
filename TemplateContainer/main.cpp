#include "myvec.hpp"
#include <iostream>

template <typename T>
std::ostream& operator<<(std::ostream& os, const MyVec<T>& vec)
{
  os << "MyVec (size "<< vec.size() <<"): [";
  for (size_t i = 0; i < vec.size(); ++i) {
    if (i > 0) {
      os << ", ";
    }
    os << vec[i];
  }
  os << "]\n";
  return os;
}

int main()
{
  MyVec<int> vec_int;

  std::cout << vec_int;

  MyVec<int> vec_int2(5, 10);
  vec_int = vec_int2;

  std::cout << vec_int;
  // vec_int.push_back(1);
  // vec_int.push_back(2);
  // vec_int.push_back(3);

  return 0;
}
