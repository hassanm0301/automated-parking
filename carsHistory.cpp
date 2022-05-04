#include "carsHistory.hpp"
#include <iostream>

CarNode::CarNode(){
    this->data = NULL;
    this->nextNode = NULL;
}


CarsHistory::CarsHistory(){
    int bucketSize = 30;
    CarNode** bucket = new CarNode*[bucketSize];
};

int CarsHistory::hashToInt(std::string date){
    int days = 0;
    days += date[0]+date[1]-96;
    days += (date[3]+date[4]-96)*31;
    days += (date[6]+date[7]+date[8]+date[9]-192)*366;
    days -= 2228;
    return days;
};

void CarsHistory::insert(std::string* data){
    int header = hashToInt(data[0]);

    while(header>bucketSize){
        CarNode** tempBucket = new CarNode*[bucketSize*2];
        for(int i=0; i<bucketSize; i++){
            tempBucket[i] = bucket[i];
        }
        bucket = tempBucket;
        delete tempBucket;
        bucketSize *= 2;
    }

    CarNode* newNode = new CarNode;
    newNode->data = data;
    newNode->nextNode = bucket[header];
    bucket[header] = newNode;
    return;

}

void CarsHistory::printDay(std::string day){
    int header = hashToInt(day);
    if(bucket[header] == NULL){
        std::cout<<"Error! No entry found on that date.";
        return;
    }
    CarNode* head = bucket[header];
    while(head != NULL){
        for(int i=0; i<4; i++){
            std::cout<<bucket[header]->data[i]<<", ";
        }
        head = head->nextNode;
        std::cout<<std::endl;
    }
};
