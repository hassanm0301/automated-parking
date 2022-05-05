#include "carsHistory.hpp"
#include "carsParking.hpp"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void clrScr(){
    for(int i=0; i<10; i++){
        cout<<"\n\n\n\n\n\n\n";
    }
}

string* lineToArr(string line)
{
    string* lineArray = new string[4];
    int lineArrayPosition = 0;
    string word = "";
    for (int i=0; i<line.length(); i++){
        char letter = line[i];
        if(letter == ',' || i == line.length()-1){
            lineArray[lineArrayPosition] = word;
            word = "";
            lineArrayPosition++;
            if(line[i+1] == ' '){
                i++;
            }
        }
        else{
            word += letter;
        }
    }
    return lineArray;
}

void importFile(CarsParking* object){
    clrScr();
    cout<<"Enter file name"<<endl;
    string filename;
    cin>>filename;
    ifstream myFile(filename);
    string myFileStr;
    while(getline(myFile, myFileStr)){
        if(myFileStr[0] == 'D'){
            continue;
        }
        object->append(lineToArr(myFileStr));
    };
    myFile.close();
    clrScr();
    return;
}

int main(){
    CarsParking* Parking = new CarsParking;
    while (true){
        cout<<"###_Automated Parking_####"<<endl;
        cout<<"1. Import File"<<endl;
        cout<<"2. Add data"<<endl;
        cout<<"3. Cars currently in parking"<<endl;
        cout<<"4. Remove a vehicle"<<endl;
        cout<<"5. History"<<endl;
        cout<<"6. Export to file"<<endl;

        int res;
        cin>>res;
        switch(res){
            case 1:
                importFile(Parking);
                break;
            case 3:
                clrScr();
                Parking->printList();
                cin.get();
                cin.get();
                clrScr();
                break;
        }
    }
    return 0;
}