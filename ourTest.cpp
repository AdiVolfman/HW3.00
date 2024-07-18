
#include <iostream>
#include "SortedList.h"


using std::cout;
using std::endl;

using namespace mtm;

int main(void) {
    SortedList<int> list;
    cout << list.length() << endl;
    list.insert(3);
    list.insert(7);
    list.insert(2);
    list.insert(1);
    cout << list << endl;
    cout << list.length() << endl;
    SortedList<int>::ConstIterator it = list.begin();
    ++it;
    list.remove(it);
    cout << list << endl;
    cout << list.length() << endl;
    SortedList<int> list2 = list.filter([](int i) { return (i % 2 == 0); });
    cout << list2;
    SortedList<int> list3 = list.apply([](int i) { return (i * 2); });
    cout << list3;
}
