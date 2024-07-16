
#include <iostream>
#include <stdexcept>
#include "SortedList.h"

template<typename T>
Node<T>::Node(const T val) : value(val), next(nullptr) {};

template<typename T>
Node<T>::Node(const T val, Node<T> next) : value(val), next(next) {};

template<typename T>
Node<T>::~Node() {
    if (next != nullptr) {
        delete next;
    }
}


