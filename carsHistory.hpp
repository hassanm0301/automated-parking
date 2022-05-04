#ifndef _CARSHISTORY_HPP_
#define _CARSHISTORY_HPP_
#include <iostream>

class CarNode{
    public:
        std::string* data;
        CarNode* nextNode;
        CarNode();
};

class CarsHistory{
    private:
        CarNode** bucket;
        int bucketSize;
        std::string hash(std::string);
    public:
        CarsHistory();
        void insert(std::string* data);
        void printDay(std::string);
        int hashToInt(std::string date);
};

#endif