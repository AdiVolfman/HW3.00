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
void Node<T>::insertNext(T &val) {
    Node<T> *node = new Node<T>(value, this->next);
    this->next = node;
}

template<typename T>
void Node<T>::removeNext(Node<T> *node) {
    this->next = node->next;
    node->next = nullptr;
    delete node;
}


using namespace mtm;

template<typename T>
SortedList<T>::SortedList(const SortedList<T> &list):
        head(new Node<T>(list.head)), size(0) {}

template<typename T>
SortedList<T> &SortedList<T>::operator=(const SortedList<T> &list) {
    if (this == &list) {
        return *this;
    }
    delete this->head;
    size = list.size;
    head = new Node<T>(*list.head);
    return *this;
}


template<typename T>
SortedList<T>::~SortedList() {
    if (head != nullptr) {
        delete head;
    }
}


template<typename T>
void SortedList<T>::insert(T newValue) {
    if (newValue > this->value) {
        head = new Node<T>(newValue, head);
    }
    Node<T> *ptr = this;
    while (ptr->next != nullptr && ptr->next->value > newValue) {
        ptr = ptr->next;
    }
    ptr->insertNext(newValue);
    size++;
}

template<typename T>
void SortedList<T>::remove(ConstIterator iterator) {
    ConstIterator currPtr = this->head;
    if (currPtr != iterator) {
        ++currPtr;
        ConstIterator prevPtr = this->head;
        while (currPtr != iterator) {
            ++currPtr;
            ++prevPtr;
        }
        prevPtr->removeNext();
    } else {
        Node<T> *temp = head;
        this->head = head->next;
        delete head;
    }
}


template<typename T>
int SortedList<T>::length() {
    return this->size;
}

template<typename T>
SortedList<T>::ConstIterator SortedList<T>::begin() const {
    return SortedList<T>::ConstIterator(head);
}

template<typename T>
SortedList<T>::ConstIterator SortedList<T>::end() const {
    return SortedList<T>::ConstIterator(nullptr);
}

template<class T>
SortedList<T>::ConstIterator &SortedList<T>::ConstIterator::operator++() {
    ptr = ptr->next;
    return this;
}

template<typename T>
bool SortedList<T>::ConstIterator::operator!=(
        const SortedList<T>::ConstIterator &other) const {
    return ptr != other.ptr;
}

template<class T>
const T &SortedList<T>::ConstIterator::operator*() {
    return this->value;
}
