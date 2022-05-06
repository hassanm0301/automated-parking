#ifndef _CARSHISTORY_HPP_
#define _CARSHISTORY_HPP_
#include <iostream>

using namespace std;

class HTCarNode{
    public:
        std::string* data;
        HTCarNode* nextNode;
        HTCarNode(nullptr_t);
};

class CarsHistory{
    private:
        HTCarNode** bucket;
        int bucketSize;
        std::string hash(std::string);
    public:
        CarsHistory();
        void insert(std::string* data);
        void printDay(std::string);
        int hashToInt(std::string date);
        void fileDay(string filename, string day);
};

#endif