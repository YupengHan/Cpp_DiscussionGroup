#ifndef MYVEC_HPP
#define MYVEC_HPP

#include <vector> // For debugging usage
#include <iostream>
#include <memory>

template <typename T, typename Allocator = std::allocator<T>>
class MyVec
{
private:
  using size_type = std::size_t;
  using traits = std::allocator_traits<Allocator>;

  Allocator m_allocator { Allocator() };
  size_type m_capacity { 0 };
  size_type m_size { 0 };
  T* m_data { nullptr };

public:

  /**
   * @brief Constructs a new MyVec object.
   *
   * @param alloc The allocator object to be used for memory allocation.
   */
  explicit MyVec(const Allocator &alloc = Allocator())

    : m_allocator(alloc)
    , m_capacity(0)
    , m_size(0)
    , m_data(nullptr)
  {
    m_data = m_allocator.allocate(m_capacity);
  }

  /**
   * @brief Constructs a `MyVec` object with a specified size and initial value.
   *
   * @param count The number of elements to construct.
   * @param value The value to initialize the elements with (default is a default-constructed value of type `T`).
   * @param alloc The allocator object to use (default is the default allocator for type `T`).
   */
  explicit MyVec(size_type count, const T& value = T(), const Allocator& alloc = Allocator())
    : m_allocator(alloc)
    , m_capacity(count)
    , m_size(count)
    , m_data(nullptr)
  {
    m_data = m_allocator.allocate(m_capacity);
    for (size_type i = 0; i < count; ++i) {
      std::construct_at(m_data + i, value);
    }
  }

  /**
   * @brief Copy constructor of MyVec
   *
   * @param other the container to copy the contents from.
   */
  MyVec(const MyVec& other)
    : m_allocator(other.m_allocator)
    , m_capacity(other.m_size)
    , m_size(other.m_size)
    , m_data(nullptr)
  {
    m_data = m_allocator.allocate(m_capacity);
    for (size_type i = 0; i < m_size; ++i) {
      std::construct_at(m_data + i, other.m_data[i]);
    }
  }

  /**
   * @brief Move constructor of MyVec
   *
   * @param other the container to move the contents from. After the move operation, `other` is guaranteed to be empty.
   */
  MyVec(MyVec&& other)
    : m_allocator(other.m_allocator)
    , m_capacity(other.m_capacity)
    , m_size(other.m_size)
    , m_data(other.m_data)
  {
    other.m_capacity = 0;
    other.m_size = 0;
    other.m_data = nullptr;
  }

  /**
   * @brief Destructor for the MyVec class.
   *
   * This destructor clears the container and deallocates the memory used by the container.
   */
  ~MyVec()
  {
    clear();
    m_allocator.deallocate(m_data, m_capacity);
  }

  /**
   * @brief Copy assignment operator. Replaces the contents witht a copy of the contents of `other`.
   *
   * @param other other container to copy the contents from.
   */

  MyVec& operator=(const MyVec& other)
  {
    if (this == &other) {
      return *this;
    }
    if (m_capacity < other.m_size) {
      clear();
      m_allocator.deallocate(m_data, m_capacity);
      m_capacity = other.m_size;
      m_data = m_allocator.allocate(m_capacity);
    }
    m_size = other.m_size;
    for (size_type i = 0; i < m_size; ++i) {
      std::construct_at(m_data + i, other.m_data[i]);
    }
    return *this;
  }

  /**
   * @brief Move assignment operator. Replaces the contents with the contents of `other` using move semantics.
   *
   * @param other other container to move the contents from.
   */
  MyVec& operator=(MyVec&& other)
  {
    if (this == &other) {
      return *this;
    }
    clear();
    m_allocator.deallocate(m_data, m_capacity);
    m_allocator = other.m_allocator;
    m_capacity = other.m_capacity;
    m_size = other.m_size;
    m_data = other.m_data;
    other.m_capacity = 0;
    other.m_size = 0;
    other.m_data = nullptr;
    return *this;
  }





  /**
   * @brief Erases all elements from this container. After this call, size of this container should be zero.
   *
   * Note: this method keeps the container capacity unchanged.
   */
  void clear()
  {
    for(size_type i = 0; i < m_size; ++i) {
      traits::destroy(m_allocator, m_data + i);
    }
    m_size = 0;
  }

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

#endif // MYVEC_HPP
// template class MyVec<float>;
// template class MyVec<double>;
// template class MyVec<std::string>;
