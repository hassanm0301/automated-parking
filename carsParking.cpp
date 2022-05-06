#include "carsParking.hpp"
#include <iostream>
#include <fstream>

using namespace std;

CarsParking::CarsParking(){
    head = NULL;
};

void CarsParking::append(std::string* data){
    DLLCarNode* new_node = new DLLCarNode;
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
    DLLCarNode* temp = head;
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

void CarsParking::fileData(ofstream* file){
    DLLCarNode* temp = head;
    while (true){
        for (int i=0; i<3; i++){
            *file<<temp->data[i]<<", ";
        }
        *file<<"\n";
        if (temp->nextNode == NULL){
            return;
        }
        temp = temp->nextNode;
    };
};

void CarsParking::del(std::string vrn){
    DLLCarNode* temp = head;
    if (temp->data[1] != vrn){
        while((temp->nextNode)->data[1] != vrn){
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

string* CarsParking::getData(string vrn){
    DLLCarNode* temp = new DLLCarNode;
    temp = head;
    if (temp->data[1] != vrn){
        while((temp->nextNode)->data[1] != vrn && temp->nextNode != NULL){
                temp = temp->nextNode;
            }
        if (temp->nextNode == NULL){
            cout<<"No matches found for that plate number. \n";
            return NULL;
        };
        return temp->nextNode->data;
    }
    return temp->data;
}