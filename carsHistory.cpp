#include "carsHistory.hpp"
#include <iostream>


CarsHistory::CarsHistory(){
    int bucketSize = 0;
    CarHashNode* bucket = new CarHashNode[30];
};

int CarsHistory::hashToInt(std::string date){
    int days;
    days += date[0]+date[1]-96;
    days += (date[3]+date[4]-96)*31;
    days += (date[6]+date[7]+date[8]+date[9]-192)*366;
    days -= 2228;
    return days;
}

void CarsHistory::insert(std::string* data){
    int header = hashToInt(data[0]);
    for(int i=0; i<bucketSize; i++){
        CarHashNode* currentHashNode = *(bucket+i);
        if(header == currentHashNode->header){
            CarNode* newNode;
            newNode->data = data;
            newNode->nextNode = currentHashNode->firstNode;
            currentHashNode->firstNode = newNode;
            return;
        }
    }

    int bucketMax = sizeof(bucket)/sizeof(bucket[0]);
    if((bucketSize+1)>(bucketMax*0.9)){
        CarHashNode** bucketTemp = new CarHashNode*[bucketSize*2];
        for(int i=0; i<bucketSize; i++){
            bucketTemp[i] = bucket[i];
        }
        bucket = bucketTemp;
        bucketSize = bucketSize*2;
    }

    CarHashNode* newHashNode;
    newHashNode->firstNode = NULL;
    newHashNode->header = header;
    bucket[bucketSize] = newHashNode;

}