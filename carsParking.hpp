#ifndef _CARSPARKING_HPP_
#define _CARSPARKING_HPP_

#include <iostream>

using namespace std;

// Class one node of the doubly linked list
class CarNode{
    public:
        string* data;
        CarNode* nextNode;
        CarNode* prevNode;
};

class CarsParking{
    private:
        CarNode* head;

    public:
        CarsParking();
        void append(string* data);
        void del(string plateNum);
        void printList();
};

#endif