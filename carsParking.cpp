#include "carsParking.hpp"
#include <iostream>
#include <typeinfo>

using namespace std;

CarsParking::CarsParking(){
    head = NULL;
};

void CarsParking::append(string* data){
    CarNode* new_node = new CarNode;
    new_node->data = data;
    if (head == NULL){
        head = new_node;
        new_node -> nextNode = NULL;
        new_node -> prevNode = NULL;
        return;
    }

    new_node->nextNode = head;
    new_node->prevNode = NULL;
    head = new_node;
    return;

};

void CarsParking::printList(){
    CarNode* temp = head;
    while (true){
        for (int i=0; i<3; i++){
            cout<<temp->data[i]<<", ";
        }
        cout<<"\n";
        if (temp->nextNode == NULL){
            return;
        }
        temp = temp->nextNode;
    };
};