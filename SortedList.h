#pragma once

#include <iostream>
#include <stdexcept>


template<typename T>
class Node {
public:
    T value;
    Node *next;
    Node(const T &val);
    Node(const T &val, Node<T> *nextPtr);
    Node(const Node<T> &node);
    ~Node();

};

namespace mtm {

    template<typename T>
    class SortedList {
    private:
        Node<T> *head;
        int size;
    public:
        SortedList();
        SortedList(const SortedList &list);
        SortedList<T> &operator=(const SortedList &list);
        ~SortedList();

        class ConstIterator;

        void insert(const T &newValue);
        void remove(SortedList::ConstIterator iterator);
        int length() const;
        template<typename U>
        friend std::ostream &
        operator<<(std::ostream &output, const SortedList<U> &list);

        ConstIterator begin() const;
        ConstIterator end() const;
        /**
         *
         * the class should support the following public interface:
         * if needed, use =defualt / =delete
         *
         * constructors and destructor:
         * 1. SortedList() - creates an empty list.
         * 2. copy constructor
         * 3. operator= - assignment operator
         * 4. ~SortedList() - destructor
         *
         * iterator:
         * 5. class ConstIterator;
         * 6. begin method
         * 7. end method
         *
         * functions:
         * 8. insert - inserts a new element to the list
         * 9. remove - removes an element from the list
         * 10. length - returns the number of elements in the list
         * 11. filter - returns a new list with elements that satisfy a given condition
         * 12. apply - returns a new list with elements that were modified by an operation
         */

    };


    template<class T>
    class SortedList<T>::ConstIterator {
    private:
        Node<T> *ptr;

        ConstIterator(Node<T> *node) : ptr(node) {};
    public:
        ConstIterator() = default;
        ConstIterator(const ConstIterator &iterator) = default;
        ~ConstIterator() = default;
        ConstIterator &operator=(const ConstIterator &list) = default;

        friend class SortedList<T>;

        ConstIterator &operator++();
        bool operator!=(const ConstIterator &other) const;
        const T &operator*();
        /**
         * the class should support the following public interface:
         * if needed, use =defualt / =delete
         *
         * constructors and destructor:
         * 1. a ctor(or ctors) your implementation needs
         * 2. copy constructor
         * 3. operator= - assignment operator
         * 4. ~ConstIterator() - destructor
         *
         * operators:
         * 5. operator* - returns the element the iterator points to
         * 6. operator++ - advances the iterator to the next element
         * 7. operator!= - returns true if the iterator points to a different element
         *
         */
    };


}


template<typename T>
Node<T>::Node(const T &val) : value(T(val)), next(nullptr) {
}

template<typename T>
Node<T>::Node(const T &val, Node<T> *nextPtr) :value(T(val)),
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
        delete next;
    }
}


namespace mtm {
    template<typename T>
    SortedList<T>::SortedList():head(nullptr), size(0) {}

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
    void SortedList<T>::insert(const T &newValue) {
        if (head == nullptr || newValue > this->head->value) {
            head = new Node<T>(newValue, head);
        } else {
            Node<T> *ptr = this->head;
            while (ptr->next != nullptr && ptr->next->value > newValue) {
                ptr = ptr->next;
            }
            Node<T> *node = new Node<T>(newValue, ptr->next);
            ptr->next = node;
        }
        size++;
    }

    template<typename T>
    void SortedList<T>::remove(SortedList::ConstIterator iterator) {
        ConstIterator currPtr = this->head;
        if (currPtr != iterator) {
            ++currPtr;
            ConstIterator prevPtr = this->head;
            while (currPtr != iterator) {
                ++currPtr;
                ++prevPtr;
            }
            prevPtr.ptr->next = currPtr.ptr->next;
            currPtr.ptr->next = nullptr;
            delete currPtr.ptr;
        } else {
            Node<T> *temp = head;
            this->head = head->next;
            delete temp;
        }
    }


    template<typename T>
    int SortedList<T>::length() const {
        return this->size;
    }

    template<typename T>
    std::ostream &operator<<(std::ostream &output, const SortedList<T> &list) {
        output << "start" << std::endl;
        for (T val: list) {
            output << val << std::endl;
        }
        output << "end!" << std::endl;
        return output;
    }

    template<typename T>
    typename SortedList<T>::ConstIterator SortedList<T>::begin() const {
        return SortedList<T>::ConstIterator(head);
    }

    template<typename T>
    typename SortedList<T>::ConstIterator SortedList<T>::end() const {
        return SortedList<T>::ConstIterator(nullptr);
    }

    template<class T>
    typename SortedList<T>::ConstIterator &
    SortedList<T>::ConstIterator::operator++() {
        if (ptr != nullptr) {
            ptr = ptr->next;
        }
        return *this;
    }

    template<typename T>
    bool SortedList<T>::ConstIterator::operator!=(
            const SortedList<T>::ConstIterator &other) const {
        return ptr != other.ptr;
    }


    //k=chek throw
    template<class T>
    const T &SortedList<T>::ConstIterator::operator*() {
        if (!ptr) {
            throw std::out_of_range("Iterator out of range");
        }
        return this->ptr->value;
    }
}


