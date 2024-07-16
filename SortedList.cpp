#include "SortedList.h"

template<typename T>
Node<T>::Node(const T val) : value(T(val)), next(nullptr) {
}

template<typename T>
Node<T>::Node(const T val, Node<T> *nextPtr) :value(new T(val)), next(nextPtr) {
}

template<typename T>
Node<T>::~Node() {
    if (next != nullptr) {
        delete *next;
    }
}

