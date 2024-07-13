# MyVec - Template Container

## Description
MyVec is a repository for the development of a template class called MyVec, which is similar to the standard vector container in C++. This repository aims to provide a customizable and efficient container for storing and manipulating elements.

## Features
The following features are planned to be supported by MyVec:

1. Dynamic resizing: MyVec will automatically resize itself to accommodate a varying number of elements.
    - clear
    - resize
    - push_back
    - pop_back
2. Element access: MyVec will provide methods to access individual elements by their index.
    - operator[]
    - at
3. Insertion and deletion: MyVec will support efficient insertion and deletion of elements at various positions.
    - insert
    - erase

4. Iteration: MyVec will allow for easy iteration over its elements using iterators.
5. Memory management: MyVec will handle memory allocation and deallocation efficiently.
    - empty
    - size
## Design Structure

1. 数据结构设计
    我们可以使用一个动态数组来存储元素，并跟踪当前元素个数和容量。我们需要以下几个成员变量：

    T* data：指向动态分配的数组。
    size_t size：当前存储的元素个数。
    size_t capacity：当前分配的数组容量。
## License
This project is licensed under the [MIT License](LICENSE).