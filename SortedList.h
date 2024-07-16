#pragma once

#include <iostream>
#include <stdexcept>

template<typename T>
class Node {
private:
    friend SortedList<T>;
    friend SortedList<T>::ConstIterator;
    T value;
    Node *next;
    Node(const T &val);
    Node(const T &val, Node<T> *nextPtr);
    Node(const Node<T> &node);
    ~Node();
    void insertNext(T &va);
    void removeNext(Node<T> *node);
};


namespace mtm {

    template<typename T>
    class SortedList {
    public:
        Node<T> *head;
        int size;
        SortedList() = default;
        SortedList(const SortedList<T> &list);
        SortedList<T> &operator=(const SortedList<T> &list);
        ~SortedList();

        class ConstIterator;

        void insert(T newValue);
        void remove(ConstIterator iterator);
        int length();


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
        ~ConstIterator() = default;
        ConstIterator(ConstIterator &iterator) = default;
        ConstIterator &operator=(const ConstIterator &list) = default;

        SortedList<T> *list;
        friend SortedList<T>;
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



