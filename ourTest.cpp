
#include <iostream>
#include "SortedList.h"


using std::cout;
using std::endl;

using namespace mtm;

int main(void) {
    SortedList<int> list;
    cout << list.length() << endl;
    int n = 3;
    list.insert(n);
    n = 7;
    list.insert(n);
    n = 5;
    list.insert(n);
    n = 1;
    list.insert(n);
    cout << list << endl;
    SortedList<int>::ConstIterator it = list.begin();
    ++it;
    list.remove(it);
    cout << list << endl;

}
