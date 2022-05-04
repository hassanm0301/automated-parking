#ifndef _CARSPARKING_HPP_
#define _CARSPARKING_HPP_

#include <iostream>

using namespace std;

// Class one node of the doubly linked list
class DLLCarNode{
    public:
        string* data;
        DLLCarNode* nextNode;
};

class CarsParking{
    private:
        DLLCarNode* head;

    public:
        CarsParking();
        void append(string* data);
        void del(string plateNum);
        void printList();
};

#endif