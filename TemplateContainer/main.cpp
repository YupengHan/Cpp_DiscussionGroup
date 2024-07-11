#include "myvec.hpp"

int main()
{
  MyVec<int> vec_int;
  {
    MyVec<int> vec_int3(3);
  }
  MyVec<double> vec_double(10000);
  // vec_int.push_back(1);
  // vec_int.push_back(2);
  // vec_int.push_back(3);

  // for (size_t i = 0; i < vec_int.size(); ++i) {
  //   std::cout << vec_int[i] << std::endl;
  // }
  return 0;
}
