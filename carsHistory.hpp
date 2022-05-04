#ifndef _CARSHISTORY_HPP_
#define _CARSHISTORY_HPP_
#include <iostream>

class CarHashNode{
    public:
        int header;
        CarNode* firstNode;
};

class CarNode{
    public:
        std::string* data;
        CarNode* nextNode;
        CarNode(std::string* data);
};

class CarsHistory{
    private:
        CarHashNode** bucket;
        int bucketSize;
        std::string hash(std::string);
    public:
        CarsHistory();
        void insert(std::string* data);
        void printList();
        int hashToInt(std::string date);
};

#endif