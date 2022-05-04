#include "carsParking.hpp"
#include <iostream>

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
        return;
    }

    new_node->nextNode = head;
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

void CarsParking::del(string plateNum){
    CarNode* temp = head;
    if (temp->data[1] != plateNum){
        while((temp->nextNode)->data[1] != plateNum){
                temp = temp->nextNode;
            }
        if (temp == NULL){
            cout<<"No matches found for that plate number. \n";
            return;
        };
        temp->nextNode = temp->nextNode->nextNode;
        return;
    }
    head = temp->nextNode;
    temp->nextNode=NULL;
    return;
}