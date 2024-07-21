#pragma once

#include <iostream>
#include <stdexcept>


namespace mtm {

    template<typename T>
    class SortedList {
    private:
        class Node {
        private:
            T value;
            Node *next;
            Node(const T &val);
            Node(const T &val, SortedList::Node *nextPtr);
            Node(const SortedList<T>::Node &node);
            ~Node();
            friend SortedList<T>;
        };

        SortedList<T>::Node *head;
        int size;
    public:
        SortedList();
        SortedList(const SortedList &list);
        SortedList<T> &operator=(const SortedList &list);
        ~SortedList();

        class ConstIterator;

        void insert(const T &newValue);
        void remove(const SortedList::ConstIterator &iterator);
        int length() const;
        template<typename U>
        friend std::ostream &
        operator<<(std::ostream &output, const SortedList<U> &list);
        template<class Predict>
        SortedList<T> filter(Predict p) const;
        template<class Operation>
        SortedList<T> apply(Operation op) const;

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

    template<typename T>
    template<class Operation>
    SortedList<T> SortedList<T>::apply(Operation op) const {
        SortedList<T> newS;
        for (T val: *this) {
            newS.insert(op(val));
        }
        return newS;
    }

    template<typename T>
    template<class Predict>
    SortedList<T> SortedList<T>::filter(Predict p) const {
        SortedList<T> newS;
        for (T val: (*this)) {
            if (p(val)) {
                newS.insert(val);
            }
        }
        return newS;
    }


    template<class T>
    class SortedList<T>::ConstIterator {
    private:
        SortedList<T>::Node *ptr;

        ConstIterator(SortedList<T>::Node *node) : ptr(node) {};
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

namespace mtm {
    template<typename T>
    SortedList<T>::Node::Node(const T &val) : value(T(val)), next(nullptr) {
    }

    template<typename T>
    SortedList<T>::Node::Node(const T &val, SortedList::Node *nextPtr) :value(
            T(val)), next(nextPtr) {}

    template<typename T>
    SortedList<T>::Node::Node(const SortedList::Node &node): value(node.value),
                                                             next(nullptr) {
        if (node.next != nullptr) {
            try {
                next = new Node(*(node.next));
            } catch (const std::bad_alloc &error) {
                delete this;
                throw;
            }
        }
    }

    template<typename T>
    SortedList<T>::Node::~Node() {
        if (next != nullptr) {
            delete next;
        }
    }


    template<typename T>
    SortedList<T>::SortedList():head(nullptr), size(0) {}

    template<typename T>
    SortedList<T>::SortedList(const SortedList<T> &list):
            head(new SortedList<T>::Node(*list.head)), size(list.size) {}

    template<typename T>
    SortedList<T> &SortedList<T>::operator=(const SortedList<T> &list) {
        if (this == &list) {
            return *this;
        }
        SortedList<T>::Node *temp = new Node(*list.head);
        delete this->head;
        size = list.size;
        head = temp;
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
            head = new SortedList<T>::Node(newValue, head);
        } else {
            SortedList<T>::Node *ptr = this->head;
            while (ptr->next != nullptr && ptr->next->value > newValue) {
                ptr = ptr->next;
            }
            SortedList<T>::Node *node = new Node(newValue, ptr->next);
            ptr->next = node;
        }
        size++;
    }

    template<typename T>
    void SortedList<T>::remove(const SortedList::ConstIterator &iterator) {
        ConstIterator currPtr = this->head;
        if (currPtr != iterator) {
            ++currPtr;
            ConstIterator prevPtr = this->head;
            while (currPtr != nullptr && currPtr != iterator) {
                ++currPtr;
                ++prevPtr;
            }
            if (currPtr.ptr == iterator.ptr) {
                prevPtr.ptr->next = currPtr.ptr->next;
                currPtr.ptr->next = nullptr;
                delete currPtr.ptr;
            } else {
                throw std::out_of_range("Iterator do not exist");
            }
        } else {
            SortedList<T>::Node *temp = head->next;
            this->head->next = nullptr;
            delete head;
            this->head = temp;
        }
        size--;
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
        if (!ptr) {
            throw std::out_of_range("Iterator out of range");
        } else {
            ptr = ptr->next;
            return *this;
        }
    }

    template<typename T>
    bool SortedList<T>::ConstIterator::operator!=(
            const SortedList<T>::ConstIterator &other) const {
        return ptr != other.ptr;
    }


    template<class T>
    const T &SortedList<T>::ConstIterator::operator*() {
        if (!ptr) {
            throw std::out_of_range("Iterator out of range");
        }
        return this->ptr->value;
    }
}


