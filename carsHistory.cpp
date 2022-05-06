#include "carsHistory.hpp"
#include <iostream>
#include <fstream>

using namespace std;

HTCarNode::HTCarNode(nullptr_t ptr){
    this->data = ptr;
    this->nextNode = ptr;
}

CarsHistory::CarsHistory(){
    int bucketSize = 237886;
    HTCarNode** bucket = new HTCarNode*[bucketSize];
    for(int i=0; i<bucketSize; i++){
        delete bucket[i];
        HTCarNode* nullNode = new HTCarNode(nullptr);
        bucket[i] = nullNode;
    };
    cout<<bucketSize;
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
        HTCarNode** tempBucket = new HTCarNode*[bucketSize*2];

        for(int i=0; i<bucketSize; i++){
            tempBucket[i] = bucket[i];
        }
        bucket = tempBucket;
        delete tempBucket;
        bucketSize *= 2;
    }

    HTCarNode* newNode = new HTCarNode(nullptr);
    newNode->data = data;
    newNode->nextNode = bucket[header];
    bucket[header] = newNode;
    return;

}

void CarsHistory::printDay(std::string day){
    int header = hashToInt(day);
    if(bucket[header] == nullptr){
        std::cout<<"Error! No entry found on that date.";
        return;
    }
    HTCarNode* head = bucket[header];
    do{
        for(int i=0; i<4; i++){
            std::cout<<head->data[i]<<", ";
        }
        std::cout<<head->nextNode;
        if(!(head->nextNode)){
            std::cout<<head->nextNode;
            break;
        }
        head = head->nextNode;
        std::cout<<std::endl;
    }while(head->nextNode != nullptr);
};

void CarsHistory::fileDay(ofstream* file, string day){
    int header = hashToInt(day);
    if(bucket[header] == nullptr){
        std::cout<<"Error! No entry found on that date.";
        return;
    }
    HTCarNode* head = bucket[header];
    do{
        for(int i=0; i<4; i++){
            *file<<head->data[i]<<", ";
        }
        *file<<head->nextNode;
        if(!(head->nextNode)){
            *file<<head->nextNode;
            break;
        }
        head = head->nextNode;
        *file<<endl;
    }while(head->nextNode != nullptr);
};
