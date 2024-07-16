#include "SortedList.h"

template<typename T>
Node<T>::Node(const T &val) : value(T(val)), next(nullptr) {
}

template<typename T>
Node<T>::Node(const T &val, Node<T> *nextPtr) :value(new T(val)),
                                               next(nextPtr) {
}

template<typename T>
Node<T>::Node(const Node<T> &node): value(node.value), next(nullptr) {
    if (node.next != nullptr) {
        next = new Node(*(node.next));
    }
}

template<typename T>
Node<T>::~Node() {
    if (next != nullptr) {
        delete *next;
    }
}

template<typename T>
void Node<T>::insertNext(Node<T> *node) {
    node->next = this->next;
    this->next = node;
}

template<typename T>
void Node<T>::removeNext(Node<T> *node) {
    this->next = node->next;
    node->next = nullptr;
    delete node;
}

