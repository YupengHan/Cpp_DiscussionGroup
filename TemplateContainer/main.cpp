#include "myvec.hpp"
#include <iostream>
#include <algorithm>

template <typename T, typename A>
std::ostream& operator<<(std::ostream& os, const MyVec<T, A>& vec)
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

// minimal allocator with debug output
template<class Tp>
struct DebugAllocator
{
    typedef Tp value_type;

    DebugAllocator() = default;
    template<class T>
    DebugAllocator(const DebugAllocator<T>&) {}

    Tp* allocate(std::size_t n)
    {
        n *= sizeof(Tp);
        Tp* p = static_cast<Tp*>(::operator new(n));
        std::cout << "allocating " << n << " bytes @ " << p << '\n';
        return p;
    }

    void deallocate(Tp* p, std::size_t n)
    {
        std::cout << "deallocating " << n * sizeof *p << " bytes @ " << p << "\n\n";
        ::operator delete(p);
    }

    size_t max_size() const { return size_t(-1) / sizeof(Tp); }
};

void test_reserve()
{
    constexpr int max_elements = 32;

    std::cout << "using reserve: \n";
    {
        MyVec<int, DebugAllocator<int>> v1;
        v1.reserve(max_elements); // reserves at least max_elements * sizeof(int) bytes

        for (int n = 0; n < max_elements; ++n)
            v1.push_back(n);
    }

    std::cout << "not using reserve: \n";
    {
        MyVec<int, DebugAllocator<int>> v1;

        for (int n = 0; n < max_elements; ++n)
        {
            if (v1.size() == v1.capacity())
                std::cout << "size() == capacity() == " << v1.size() << '\n';
            v1.push_back(n);
        }
    }
}

void test_copy()
{
  MyVec<int> vec_int;
  std::cout << "Before copy:\n";
  std::cout << vec_int;
  MyVec<int> vec_int2(5, 10);
  vec_int = vec_int2;
  std::cout << "After copy:\n";
  std::cout << vec_int;
}


void test_move()
{
  MyVec<int> vec_int;
  std::cout << "vec Before move:\n";
  std::cout << vec_int;
  MyVec<int> vec_int2(5, 10);
  vec_int = std::move(vec_int2);
  std::cout << "vec After move:\n";
  std::cout << vec_int;
  std::cout << "vec2 After move:\n";
  std::cout << vec_int2;

}

void test_resize()
{
  MyVec<int> vec_int;
  std::cout << "Before resize:\n";
  std::cout << vec_int;
  vec_int.resize(5, 10);
  std::cout << "After resize up:\n";
  std::cout << vec_int;
  vec_int.resize(2);
  std::cout << "After resize down:\n";
  std::cout << vec_int;
}

void test_iterators()
{
  MyVec<int> vec_int;
  vec_int.push_back(2);
  vec_int.push_back(4);
  vec_int.push_back(8);
  vec_int.push_back(3);
  vec_int.push_back(1);
  vec_int.push_back(5);
  vec_int.push_back(6);
  vec_int.push_back(7);

  std::cout << "Accessing vector via iterator:\n";
  for (auto it = vec_int.begin(); it != vec_int.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;

  std::cout << "After sorting:\n";
  std::sort(vec_int.begin(), vec_int.end());
  std::cout << vec_int;
}

void test_insert()
{
  MyVec<int> vec_int;
  vec_int.push_back(2);
  vec_int.push_back(4);
  vec_int.push_back(8);
  vec_int.push_back(3);
  vec_int.push_back(1);
  vec_int.push_back(5);
  vec_int.push_back(6);
  vec_int.push_back(7);

  std::cout << "Before insert:\n";
  std::cout << vec_int;
  vec_int.insert(vec_int.begin() + 2, 10);
  vec_int.insert(vec_int.end(), 11);
  vec_int.insert(vec_int.begin(), 12);
  std::cout << "After insert:\n";
  std::cout << vec_int;
}

int main()
{
  test_reserve();
  test_copy();
  test_move();
  test_resize();
  test_iterators();
  test_insert();

  // vec_int.push_back(1);
  // vec_int.push_back(2);
  // vec_int.push_back(3);

  return 0;
}
