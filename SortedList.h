#pragma once

#include <iostream>
#include <stdexcept>


namespace mtm {
/**
 * @brief Class managing a sorted list structure.
 */
    template<typename T>
    class SortedList {
    private:
        /**
        * @brief Class managing Node memory structure.
        */
        class Node {
        private:
            T value; // value of each node, according to type of <typename>
            Node *next; // pointer to next chain in node.
            Node(const T &val);
            Node(const T &val, SortedList::Node *nextPtr);
            Node(const SortedList<T>::Node &node);
            ~Node();
            friend SortedList<T>;
        };

        SortedList<T>::Node *head; //pointer to the head of the list
    public:
        /**
        * @brief empty constructor.
        */
        SortedList();

        /**
        * @brief copy constructor.
        */
        SortedList(const SortedList &list);

        /**
        * @brief assignment operator.
        */
        SortedList<T> &operator=(const SortedList &list);

        /**
        * @brief destructor
        */
        ~SortedList();


        class ConstIterator;

        /**
        * @brief inserts T in a sorted manner, considering the operator > of <typename T> .
        */
        void insert(const T &newValue);

        /**
        * @brief removes a specific node from sortedlist.
        */
        void remove(const SortedList::ConstIterator &iterator);

        /**
        * @brief returns amount of nodes are in sorted list
        */
        int length() const;

        /**
        * @brief returns a new list of elements matching "Predict" condition .
        */
        template<class Predict>
        SortedList<T> filter(Predict p) const;

        /**
        * @brief returns a new list of elements after applying "Operation" command on each value.
        */
        template<class Operation>
        SortedList<T> apply(Operation op) const;

        /**
        * @brief returns iterator to the start of the list.
        */
        ConstIterator begin() const;

        /**
        * @brief returns iterator to the end of the list.
        */
        ConstIterator end() const;
    };

    /**
    * @brief Class that allows us to go threw all data in list in order.
    */
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

        /**
        * @brief moves iterator to next value.
        */
        ConstIterator &operator++();

        /**
        * @brief compares between two iterators returns true iff different.
        */
        bool operator!=(const ConstIterator &other) const;

        /**
        * @brief returns reference to current element of the list.
        */
        const T &operator*();
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
                //got in here if the recursive allocate is not succeed.
                // free the memory and throw exception.
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
    SortedList<T>::SortedList():head(nullptr) {}

    template<typename T>
    SortedList<T>::SortedList(const SortedList<T> &list):
            head(new SortedList<T>::Node(*list.head)) {}

    template<typename T>
    SortedList<T> &SortedList<T>::operator=(const SortedList<T> &list) {
        if (this == &list) {
            return *this;
        }
        if (list.head == nullptr) {
            delete this->head;
            this->head = nullptr;
        } else {
            SortedList<T>::Node *temp = new Node(*list.head);
            if (head != nullptr) {
                delete this->head;
            }
            head = temp;
        }
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
            //case the new value should be first in the list
            head = new Node(newValue, head);
        } else {
            SortedList<T>::Node *ptr = this->head;
            //finding the elements the new value need to be between.
            while (ptr->next != nullptr && ptr->next->value > newValue) {
                ptr = ptr->next;
            }
            ptr->next = new Node(newValue, ptr->next);
        }
    }

    template<typename T>
    void SortedList<T>::remove(const SortedList::ConstIterator &iterator) {
        ConstIterator currPtr = this->head;
        if (currPtr != iterator) {
            //case the iterator is not the beginning of the list
            ++currPtr;
            ConstIterator prevPtr = this->head;
            //finding iterator to the element before the removable item
            while (currPtr != nullptr && currPtr != iterator) {
                ++currPtr;
                ++prevPtr;
            }
            if (currPtr.ptr != nullptr && currPtr.ptr == iterator.ptr) {
                prevPtr.ptr->next = currPtr.ptr->next;
                currPtr.ptr->next = nullptr;
                delete currPtr.ptr;
            }
            //else {
            //     throw std::out_of_range("Iterator do not exist");
            //}
        } else {
            //case that we remove the head
            if (currPtr.ptr != nullptr) {
                Node *temp = head->next;
                this->head->next = nullptr;
                delete head;
                this->head = temp;
            }
        }
    }


    template<typename T>
    int SortedList<T>::length() const {
        int count = 0;
        Node *temp = head;
        while (temp != nullptr) {
            temp = temp->next;
            count++;
        }
        return count;
    }

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


