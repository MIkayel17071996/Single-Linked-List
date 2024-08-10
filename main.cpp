#include <iostream>
#include "SingleLinkedList.h"

int main() {
    SingleLinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);

    SingleLinkedList<int> list2;
    list2.push_back(1);
    list2.push_back(2);
    list2.push_back(3);
    list2.push_back(4);

   list.merge(list2);

    list.printList();


}
