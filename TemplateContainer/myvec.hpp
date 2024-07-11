#ifndef MYVEC_HPP
#define MYVEC_HPP

#include <vector> // debug usage
#include <iostream>
#include <cassert>

template <typename T>
class MyVec {
public:
    MyVec();
    MyVec(int size); // Design Q: use int or size_t as constructor input, which can avoid undesired cast?
    ~MyVec();   

// private:
    T* _data = nullptr;
    size_t _size = 0;
    size_t _capacity = 0;
};


template <typename T> MyVec<T>::MyVec() {
    if (_data != nullptr) {
        delete[] _data; // Design Q use delete[], how does code know the capacity?
        _data = nullptr;
    }
    _size = 0;
    _capacity = 0;
    std::cout << "costructor done\n";
}

template <typename T> MyVec<T>::MyVec(int size) {
    assert(size > 0);
    if (_data != nullptr) {
        delete[] _data; // Design Q use delete[], how does code know the capacity?
        _data = nullptr;
    }
    
    _capacity = 1; // Design Q, what is benefit of kiping capacity 2^k?
    while (_capacity < size) {
        _capacity *= 2;
    }

    _data = new T[_capacity];
    _size = size;
    std::cout << "costructor size:" << size << " done\n";
}

template <typename T> MyVec<T>::~MyVec() {
    if (_data != nullptr) {
        delete[] _data; // Design Q use delete[], how does code know the capacity?
        _data = nullptr; // No needed, since this object is going to be deleted
    }
    std::cout << "destructor size:" << _size << " close to done\n";
    _size = 0;
    _capacity = 0;
    
}


template class MyVec<int>; // Desgin Q: should this before the endif or after endif
#endif // MYVEC_HPP

