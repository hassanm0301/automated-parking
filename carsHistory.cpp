#include "carsHistory.hpp"
#include <iostream>
#include <fstream>

using namespace std;

// default constructor assigns null to values
HTCarNode::HTCarNode(nullptr_t ptr){
    this->data = ptr;
    this->nextNode = ptr;
}

// default constructor assigns large bucket size
// also gives all pointers in bucket null HTCarNode
CarsHistory::CarsHistory(){
    int bucketSize = 237886;
    HTCarNode** bucket = new HTCarNode*[bucketSize]; // bucket stores headers for singly linked list
    for(int i=0; i<bucketSize; i++){
        delete bucket[i];
        HTCarNode* nullNode = new HTCarNode(nullptr);
        bucket[i] = nullNode;
    };
};

// hashing function
// converts a date to number of days from 01/01/2022
// assumes all months have 31 days and all years have 366 days for no unnecessary collision
int CarsHistory::hashToInt(std::string date){
    int days = 0;
    days += date[0]+date[1]-96;
    days += (date[3]+date[4]-96)*31;
    days += (date[6]+date[7]+date[8]+date[9]-192)*366;
    days -= 2228;
    return days;
};

// inserts a new node to hash table
void CarsHistory::insert(std::string* data){
    int header = hashToInt(data[0]);
    
    // doubles bucket size if header is larger than bucket size
    while(header>bucketSize){
        HTCarNode** tempBucket = new HTCarNode*[bucketSize*2];

        for(int i=0; i<bucketSize; i++){
            tempBucket[i] = bucket[i];
        }
        bucket = tempBucket;
        delete tempBucket;
        bucketSize *= 2;
    }

    // header points to new node and new node points to old node
    HTCarNode* newNode = new HTCarNode(nullptr);
    newNode->data = data;
    newNode->nextNode = bucket[header];
    bucket[header] = newNode;
    return;

}

// prints details of paritcular day
void CarsHistory::printDay(std::string day){
    int header = hashToInt(day);
    if(bucket[header] == nullptr){ //checks if dy is null
        std::cout<<"Error! No entry found on that date.";
        return;
    }

    HTCarNode* head = bucket[header];
    // do while loop so that data still prints if there is only one node
    do{
        for(int i=0; i<4; i++){
            std::cout<<head->data[i]<<", ";
        }
        if(!(head->nextNode)){
            break;
        }
        head = head->nextNode;
        std::cout<<std::endl;
    }while(head->nextNode != nullptr);
};

// appends data of particular day to a file
void CarsHistory::fileDay(string filename, string day){
    ofstream file;
    file.open(filename, fstream::app);
    int header = hashToInt(day);
    if(bucket[header] == nullptr){
        std::cout<<"Error! No entry found on that date.";
        return;
    }
    HTCarNode* head = bucket[header];
    do{
        for(int i=0; i<4; i++){
            file<<head->data[i]<<", ";
        }
        if(!(head->nextNode)){
            break;
        }
        head = head->nextNode;
        file<<endl;
    }while(head->nextNode != nullptr);
    file.close();
};
