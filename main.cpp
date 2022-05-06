#include "carsHistory.hpp"
#include "carsParking.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;


//clears screen
void clrScr(){
    for(int i=0; i<10; i++){
        cout<<"\n\n\n\n\n\n\n";
    }
}


// Calculates fee
string calcFee(string arrival, string departure){
    int duration = 0;
    int hours = stoi(departure.substr(0,2)) - stoi(arrival.substr(0,2));
    int min = stoi(departure.substr(3,2)) - stoi(arrival.substr(3,2));
    int sec = stoi(departure.substr(6,2)) - stoi(arrival.substr(6,2));

    duration = sec + (min*60) + (hours*60*60);

    cout<<"Parking charge is: ";
    if(duration<(30*60)){
        return "FREE";
    }
    else if(duration<=(1*60*60)){
        return "$1.50";
    }
    else if(duration<=(2*60*60)){
        return "$3.00";
    }
    else if(duration<=(4*60*60)){
        return "$5.00";
    }
    else if(duration<=(8*60*60)){
        return "$15.00";
    }
    return "$30.00";

}

// makes integer to 2 digits by adding zero in front if <10
string twoIntegers(int oneInteger){
    if(oneInteger < 10){
        return to_string(0)+to_string(oneInteger);
    }
    return to_string(oneInteger);
}

// gets current date to format DD/MM/YYY
string getCurrentDate(){
    time_t now = time(0);
    tm *ltm = localtime(&now);

    string day = twoIntegers(ltm->tm_mday);
    string month = twoIntegers(1 + ltm->tm_mon);
    string year = to_string(1900 + ltm->tm_year);

    string arrivalDate = day + "/" + month + "/" + year;

    return arrivalDate;
}

// gets current time to format HH:MM:SS
string getCurrentTime(){
    time_t now = time(0);
    tm *ltm = localtime(&now);

    string hour = twoIntegers(ltm->tm_hour);
    string min = twoIntegers(ltm->tm_min);
    string sec = twoIntegers(ltm->tm_sec);

    string arrivalTime = hour + ":" + min + ":" + sec;

    return arrivalTime;
}

// converts a line of string to array with "," as delimiter 
// also removes whitespace after any ","
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
            if(line[i+1] == ' '){ // skips whitespace
                i++;
            }
        }
        else{
            word += letter;
        }
    }
    return lineArray;
}

// adds a vehicle to parking
// takes current time as arrival time
void addVehicle(CarsParking* parking){
    string vrn1, vrn2, vrn;
    cout<<"Enter the the first part of the VRN: ";
    cin>>vrn1;
    cout<<endl<<"Enter the the second part of the VRN: ";
    cin>>vrn2;

    vrn = vrn1 + " " + vrn2;

    string arrivalDate = getCurrentDate();
    string arrivalTime = getCurrentTime();

    string* data = new string[4];

    data[0] = arrivalDate;
    data[1] = vrn;
    data[2] = arrivalTime;
    data[3] = "-";

    parking->append(data);

    delete data;

    return;
}

// removes a vehicle from parking and adds it to history
// deaprture time is current time
void removeVehicle(CarsParking* parking, CarsHistory* history){
    string vrn1, vrn2, vrn;
    cout<<"Enter the first part of the VRN: ";
    cin>>vrn1;
    cout<<"Enter the second part of the VRN: ";
    cin>>vrn2;

    vrn = vrn1 + " " + vrn2;
    string* data = new string[4];
    data = parking->getData(vrn);
    data[0] = getCurrentDate();
    data[3] = getCurrentTime();
    history->insert(data);
    cout<<calcFee(data[2], data[3]);
    cin.get();
    cin.get();
    parking->del(vrn);
}

// imports details from a txt file
void importFile(CarsParking* carsParking, CarsHistory* carsHistory){
    clrScr();
    cout<<"Enter file name"<<endl;
    string filename;
    cin>>filename;
    ifstream myFile(filename);
    string myFileStr;
    while(getline(myFile, myFileStr)){
        if(myFileStr[0] == 'D'){ // removes column headers
            continue;
        }
        string* lineArr = lineToArr(myFileStr);
        if(lineArr[3] == "-"){
            carsParking->append(lineArr);
        }
        else{
            carsHistory->insert(lineArr);
        }

    };
    myFile.close();

    clrScr();
    return;
}

// Creates file to store details of history of a particular day
// if day is today, stores cars in parking too
void exportFile(CarsHistory* History, CarsParking* Parking){
    string date, fileName;
    cout<<"Enter the date to export:";
    cin>>date;
    cout<<endl<<"Enter the file name:";
    cin>>fileName;

    ofstream file(fileName);
    ofstream* fileptr = &file;
    if(date == getCurrentDate()){ // puts cars in parking to file if date is today
        Parking->fileData(fileptr);
    }
    History->fileDay(fileptr, date);
    *fileptr<<"\n";
}

// main driver function
int main(){
    CarsParking* Parking = new CarsParking;
    CarsHistory* History = new CarsHistory;
    int res = 0;
    while (true){
        cout<<"###_Automated Parking_####"<<endl;
        cout<<"1. Import File"<<endl;
        cout<<"2. Add vehicle"<<endl;
        cout<<"3. Cars currently in parking"<<endl;
        cout<<"4. Remove a vehicle"<<endl;
        cout<<"5. History"<<endl;
        cout<<"6. Export to file"<<endl;
        cout<<"7. Exit"<<endl;
        cin>>res;
        switch(res){
            {
            case 1:
                importFile(Parking, History);
                break;
            }
            {
            case 2:
                clrScr();
                addVehicle(Parking);
                clrScr();
                break;
            }
            {
            case 3:
                clrScr();
                Parking->printList();
                cin.get();
                cin.get();
                clrScr();
                break;
            }
            {
            case 4:
                clrScr();
                removeVehicle(Parking, History);
                clrScr();
                break;
            }
            {
            case 5:
                clrScr();
                string date;
                cout<<"Enter a date in the format DD/MM/YYYY"<<endl;
                cin>>date;
                clrScr();
                History->printDay(date);
                break;
            }
            case 6:
                clrScr();
                exportFile(History, Parking);
                clrScr();
                break;
            {
            case 7:
                return 0;
            }
        }
    }
}