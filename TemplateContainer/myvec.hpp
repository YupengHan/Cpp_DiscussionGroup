/**
 * @brief A simple implementation of a vector-like container.
 *
 * @details
 * The following class is a simple implementation of a vector-like container.
 * The order of the member function is the same as in the standard library for
 * cross reference. In addition, we also reuse the same names for the method
 * arguments to reduce ambiguity.
 *
 * You may refer to https://en.cppreference.com/w/cpp/container/vector for the
 * method order and the standard interface of the `std::vector` class.
 */

#ifndef MYVEC_HPP
#define MYVEC_HPP

#include <iostream>
#include <memory>
#include <stdexcept>

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

  // Member Functions

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

  // Element Access

  /**
   * @brief Returns a reference to the element at the specified position in this container.
   *
   * @param pos position of the element to return.
   * @return T& reference to the requested element.
   */
  T& operator[](size_type pos)
  {
    return m_data[pos];
  }

  /**
   * @brief Returns a const reference to the element at the specified position in this container.
   *
   * @param pos position of the element to return.
   * @return const T& reference to the requested element.
   */
  const T& operator[](size_type pos) const
  {
    return m_data[pos];
  }

  /**
   * @brief Returns a reference to the element at specified location `pos`, with bounds checking.
   *
   * @param pos position of the element to return.
   * @return T& reference to the requested element.
   */
  T& at(size_type pos)
  {
    if (pos >= m_size) {
      throw std::out_of_range("Index out of range");
    }
    return m_data[pos];
  }

  /**
   * @brief Returns a const reference to the element at specified location `pos`, with bounds checking.
   *
   * @param pos position of the element to return.
   * @return const T& reference to the requested element.
   */
  const T& at(size_type pos) const
  {
    if (pos >= m_size) {
      throw std::out_of_range("Index out of range");
    }
    return m_data[pos];
  }

  // Capacity

  /**
   * @brief Returns true if this container is empty, false otherwise.
   */
  bool empty() const
  {
    return m_size == 0;
  }

  /**
   * @brief Reserve space for at least `new_cap` elements.
   *
   * @details
   * If `new_cap` is greater than the current capacity, new memory is allocated. Otherwise, the method does nothing.
   * @param new_cap the new capacity to reserve.
   */
  void reserve(size_type new_cap)
  {
    if (new_cap <= m_capacity) {
      return;
    }
    if (new_cap > max_size()) {
      throw std::length_error("Requested capacity exceeds maximum size");
    }
    T* new_data = m_allocator.allocate(new_cap);
    for (size_type i = 0; i < m_size; ++i) {
      std::construct_at(new_data + i, std::move(m_data[i]));
      traits::destroy(m_allocator, m_data + i);
    }
    m_allocator.deallocate(m_data, m_capacity);
    m_capacity = new_cap;
    m_data = new_data;
  }

  /**
   * @brief Returns the number of elements in this container.
   */
  size_type size() const
  {
    return m_size;
  }

  /**
   * @brief Returns the maximum theoretically possible allocation size for the container.
   *
   * @return size_type the maximum size of the container.
   */
  size_type max_size() const
  {
    return traits::max_size(m_allocator);
  }

  size_type capacity() const
  {
    return m_capacity;
  }

  // Modifiers

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

  /**
   * @brief Appends the given element `value` to the end of this container.
   *
   * @param value the value to append to this container.
   */
  void push_back(const T& value)
  {
    if (m_size == m_capacity) {
      reserve(m_capacity == 0 ? 1 : m_capacity * 2);
    }
    m_data[m_size] = value;
    ++m_size;
  }

  /**
   * @brief Removes the last element of this container.
   * Calling this method on an empty container is undefined behavior.
   */
  void pop_back()
  {
    m_allocator.destroy(m_data + m_size - 1);
    --m_size;
  }


  // void resize();
  // void insert();

};

#endif // MYVEC_HPP
// template class MyVec<float>;
// template class MyVec<double>;
// template class MyVec<std::string>;
