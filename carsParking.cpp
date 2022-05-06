#include "carsParking.hpp"
#include <iostream>
#include <fstream>

using namespace std;

// assigns head as null as singly linked list is empty
CarsParking::CarsParking(){
    head = NULL;
};

// adds node to list
void CarsParking::append(std::string* data){
    DLLCarNode* new_node = new DLLCarNode;
    new_node->data = data;
    if (head == NULL){ //checks if list is empty to assign null to nextNode
        head = new_node;
        new_node -> nextNode = NULL;
        return;
    }

    new_node->nextNode = head;
    head = new_node;
    return;

};

// prints details of all nodes in list
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

// appends all data to a file
void CarsParking::fileData(string filename){
    ofstream file;
    file.open(filename, fstream::app);
    DLLCarNode* temp = head;
    while (true){
        for (int i=0; i<3; i++){
            cout<<temp->data[i];
            file<<temp->data[i]<<", ";
        }
        file<<"\n";
        if (temp->nextNode == NULL){
            return;
        }
        temp = temp->nextNode;
    };
    file.close();
};

// removes a node by pointing it to null and deleting it
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

// gets data of particular vehicle based on vrn
// returns pointer to array
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