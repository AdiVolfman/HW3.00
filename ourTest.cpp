
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
    list.insert(5);
    list.insert(1);
    cout << list << endl;
    cout << list.length() << endl;
    SortedList<int>::ConstIterator it = list.begin();
    ++it;
    list.remove(it);
    cout << list << endl;
    cout << list.length() << endl;

}
