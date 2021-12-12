/* program_4.cpp
    Divvy Bike Data Analysis program.
    Author: Keyur Patel
    Date: 10/7/2021
    Class: CS 141, Fall 2021, UIC
    System: Visual Studio 2019 IDE Windows
    Menu Option 5 Extra Credit URL: https://www.google.com/maps/d/u/0/edit?mid=1kEBEpX9wK7_L-cxFBnXy6ZYR_u0mVIs6&usp=sharing
    Coordinates for Home I would like to live in:  41.8645	-87.6292
*/

#include <iostream>   // For Input and Output
#include <iomanip>
#include <fstream>    // For file input and output
#include <cassert>    // For the assert statement
#include <cctype>     // access to tolower() or toupper() function
#include <vector>     // For vectors
#include <string>     // String operations
#include <algorithm>  // use of vector algorithms
#include <cmath>

using namespace std;

// Utility functions getting distant between two map points 
// Attribution: https://www.geeksforgeeks.org/program-distance-two-points-earth/  
// converting degrees to radians

class DivvyData//class that holds all the divy data
{
public:
    string rideId;//stores ID
    string rideType;// stores the ride type
    string startAt;//stores the start date and time
    string endAt;//stores the end date and time
    string startStationName;// stores start station name
    string endStationName;// stores end station name
    long double startLat;//stores start latitude
    long double startLong;//stores start longitude
    long double endLat;//stores end latitude
    long double endLong;//stores end longitude
    string memberCasual;// stores either member or casual

    DivvyData(string rideId,string rideType,string startAt,string endAt,string startStationName,string endStationName,long double startLat,
    long double startLong,long double endLat,long double endLong,string memberCasual);//Contructor

};


DivvyData::DivvyData(string rideId,string rideType,string startAt,string endAt,string startStationName,string endStationName,long double startLat,
 long double startLong,long double endLat,long double endLong,string memberCasual)// constructor with all the divvy data variables as parameters
{
    this->rideId=rideId;//sets the object variable equal to the parameter variable
    this-> rideType=rideType;
    this-> startAt=startAt;//sets the object variable equal to the parameter variable
    this-> endAt=endAt;
    this-> startStationName=startStationName;//sets the object variable equal to the parameter variable
    this-> endStationName=endStationName;
    this-> startLat=startLat;
    this-> startLong=startLong;//sets the object variable equal to the parameter variable
    this-> endLat=endLat;
    this-> endLong=endLong;
    this-> memberCasual=memberCasual;//sets the object variable equal to the parameter variable
}


long double toRadians(const long double degree){//converts to radians
    // cmath library in C++
    // defines the constant
    // M_PI as the value of
    // pi accurate to 1e-30
    long double one_deg = (3.14159265358979323846) / 180;
    return (one_deg * degree);
}


long double distance(long double lat1, long double long1,long double lat2, long double long2){// gets the total distance in miles from start location to end location
    // Convert the latitudes
    // and longitudes
    // from degree to radians.
    lat1 = toRadians(lat1);
    long1 = toRadians(long1);
    lat2 = toRadians(lat2);
    long2 = toRadians(long2);

    // Haversine Formula
    long double dlong = long2 - long1;
    long double dlat = lat2 - lat1;

    long double ans = pow(sin(dlat / 2), 2) +
        cos(lat1) * cos(lat2) *
        pow(sin(dlong / 2), 2);

    ans = 2 * asin(sqrt(ans));

    // Radius of Earth in
    // Kilometers, R = 6371
    // Use R = 3956 for miles
    long double R = 3956;

    // Calculate the result
    ans = ans * R;

    return ans;
}


void readsampleDivvyDataIntoArray(vector<DivvyData>& alldivvyData,vector<DivvyData>& cleandivvyData,int option){
    //reads the divvy data type selectedd into the clean array and into all divvy data array.
    string rideId;//stores ID
    string rideType;// stores the ride type
    string startAt;//stores the start date and time
    string endAt;//stores the end date and time
    string startStationName;// stores start station name
    string endStationName;// stores end station name
    string memberCasual;//// stores either member or casual

    long double startLat,startLong,endLat,endLong;// stores start location and end location
    
    string tempstartLat;//temporary varible for start latitude
    string tempstartLong;//temporary varible for start longitude
    string tempendLat;//temporary varible for end latitude
    string tempendLong;//temporary varible for end longitude

    ifstream inStream;
    if(option==1){// if data type option is 1 then read the sample data
        inStream.open( "divvyridesampledata.csv");
    }
    else if(option==2){// if data type option is 2 then read the weekdayweekend data
        inStream.open( "weekdayweekend.csv");
    }
    else {// if data type option is 3 then read the september data
        inStream.open( "all_divvy_rides_september.csv");
    }
    inStream.ignore(500, '\n');//ignores the first line which contains the variable names
    while(inStream.good()){//goes through each line until the end//reads line by line andd stores each data seperated by commas into respective varibales

        getline(inStream,rideId,',');// stores the rideID of the current line and so one...
        getline(inStream,rideType,',');
        getline(inStream,startAt,',');
        getline(inStream,endAt,',');// stores the end time of the current line and so one...
        getline(inStream,startStationName,',');
        getline(inStream,endStationName,',');
        getline(inStream,tempstartLat,',');
        getline(inStream,tempstartLong,',');
        getline(inStream,tempendLat,',');
        getline(inStream,tempendLong,',');
        getline(inStream,memberCasual,'\n');
        if(!rideId.empty() && !rideType.empty() && !startAt.empty() && !endAt.empty() && !startStationName.empty() && !endStationName.empty() 
        &&!tempstartLat.empty() && !tempstartLong.empty()&!tempendLat.empty()&&!tempendLong.empty() && !memberCasual.empty() ) {// If the data is clean then convert the lats and longs to long doubles and then create object which call contructor and store the object into the clean object array
            startLat=stold(tempstartLat);
            startLong=stold(tempstartLong);
            endLat=stold(tempendLat);
            endLong=stold(tempendLong);
                
            DivvyData DV(rideId,rideType,startAt,endAt,startStationName,endStationName,startLat,startLong,endLat,endLong,memberCasual);  
            cleandivvyData.push_back(DV);
        }          
    
        DivvyData DV(rideId,rideType,startAt,endAt,startStationName,endStationName,startLat,startLong,endLat,endLong,memberCasual);  
        alldivvyData.push_back(DV) ; //create object which call contructor and store the object into the alldivvydata object array
        }
        alldivvyData.pop_back();//removes the last object because the last line in the CSV files is empty
}


void overallTripInformation(vector<DivvyData> cleandivvyData){// displays trip information
    double totalMiles=0;//stores all the miles combined
    int longesttripIndex=0; //stores the index of the longest ride
    double longesttrip;// stores the current distance of the longest ride
    double currentTrip;//stores the distance of the current index ride of the array 
    double longesttripdistanceTraveled;//stores the distance of the longest ride
    for(int i=0;i<cleandivvyData.size();i++){//goes through the clean data array
        currentTrip = distance(cleandivvyData.at(i).startLat,cleandivvyData.at(i).startLong,cleandivvyData.at(i).endLat,cleandivvyData.at(i).endLong);//
        //sets currentTrip equal to the distance of the trip that the array is on//Calls distance to get the location of the current trip the array is on

        totalMiles=totalMiles+currentTrip;//adds the current trip the array is on to the total miles
        if(currentTrip>longesttrip){// if the current trip the array is on is greater then the longest trip then set longesttrip to the current trip distance and index
            longesttrip=currentTrip;
            longesttripIndex=i;
        }
    }
    longesttripdistanceTraveled = distance(cleandivvyData.at(longesttripIndex).startLat,cleandivvyData.at(longesttripIndex).startLong,cleandivvyData.at(longesttripIndex).endLat,cleandivvyData.at(longesttripIndex).endLong);
    // sets longesttripdistanceTraveled equal to the distance of the longest trip index

    cout << endl;
    cout <<"   Total # of miles traveled: "<< round(totalMiles) <<endl;// displays total miles and rounds it
    cout <<"   Average length of trips in miles:  "<<(round((totalMiles/cleandivvyData.size())*10)) / 10.0 <<endl; // displays total miles and rounds it to the nrearest tenth
    cout << endl;
    cout << "   Longest trip information below:" <<  endl;
    cout << "   -------------------------------" <<  endl;
    cout << "   Trip ID: " << cleandivvyData.at(longesttripIndex).rideId <<  endl; // displays the longest trip ID
    cout << "   Trip start location: " << cleandivvyData.at(longesttripIndex).startStationName<<  endl;//diplays the start station name of the longest trip
    cout << "   Trip end location: " << cleandivvyData.at(longesttripIndex).endStationName<<  endl;//displays the end station name of the longest trip
    cout << "   Trip distance in miles: " << (round((longesttripdistanceTraveled)*10)) / 10.0 <<  endl; // displays the longest trip distance and rounds it to the nearest tenth
    cout << endl << endl;

}


void percentriderType(vector<DivvyData> cleandivvyData){//calculates the percent of the rider type and displays it// cleans data as the parameter
    double casualriderCount;//holds the count of the number of casual riders
    double casualriderPercent;//holds the percent casual riders
    double memberriderCount;//holds the count of the number of member riders
    double memberriderPercent;//holds the percent member riders
    double totalRiders = cleandivvyData.size();//holds the total number of riders or the size of cleandivvydata
    string casual = cleandivvyData.at(1).memberCasual; // sets casual rider equal to "casual"
    string member = cleandivvyData.at(0).memberCasual;// sets casual rider equal to "member"

    for(int i=0;i<cleandivvyData.size();i++){//goes through cleandata array
        if(cleandivvyData.at(i).memberCasual.compare("member")==1){//if the the rider type at index i is equal to "member" then increment member count
            memberriderCount++;
        }
        else{//increments causal rider when the rider type at index i is not "member"
            casualriderCount++;
        }
    }
    casualriderPercent = (casualriderCount/totalRiders)*100.0;//calculates the casual rider percent
    memberriderPercent = (memberriderCount/totalRiders)*100.0;//calculates the member rider percent

    cout << "   Casual Rider Percentage: " <<fixed << setprecision(1) << casualriderPercent << "%" <<  endl;//sets the corrent decimal length and displays the percecnt
    cout << "   Member Rider Percentage: " <<fixed << setprecision(1) << memberriderPercent << "%" <<  endl;
}


void getTripsPerHour(vector<DivvyData> cleandivvyData,vector<int>& weekdayData,vector<int>& weekendData,int& largestRidesPerHour){//sets the weekend and weekday array with the data
    //parameters are cleandata array, weekdayData array which is empty, weekendDData array which is empty and the largestRidesPerHour
    string time;// stores the hour of the current index
    int hourstringlength;//stores the length of the startAt string 
    int day;// stores the day number 
    for(int i=0;i<24;i++){//loops through 24 times
        weekdayData.push_back(0);//adds 0 to the vector because each index is the hour and 0 is the number of rides per hour without adding
        weekendData.push_back(0);//adds 0 to the vector
    }

    for(int index=0;index<cleandivvyData.size();index++){//loops through cleandivvydata
        string time = cleandivvyData.at(index).startAt;//sets the time equal to the start time string from the index of clean data
        if(time.substr(time.find('/')+1,1)=="1"){//if it is 1 which is weekday then increament the hour index in the weekday data by one
            int hourstringlength = time.find(':')-time.find(' ')-1;
            string hour=time.substr(time.find(' ')+1,hourstringlength);
            weekdayData.at(stoi(hour))++;
        }
        else{//if it is 4 which is weekend then increament the hour index in the weekend data by one
            int hourstringlength = time.find(':')-time.find(' ')-1;
            string hour=time.substr(time.find(' ')+1,hourstringlength);
            weekendData.at(stoi(hour))++;            
        }
    }
    for(int i=0;i<weekendData.size();i++){//loops through and get the hour with the largest amount of rides
        if(weekendData.at(i)>largestRidesPerHour){
            largestRidesPerHour = weekendData.at(i);
        }
        if(weekdayData.at(i)>largestRidesPerHour){
            largestRidesPerHour = weekdayData.at(i);
        }
    }
}


void displayTripsPerHourData(vector<int>& weekdayData,vector<int>& weekendData,int& largestRides){//displays the weekend and weekday data
    cout << "   LargestNumberOfRides is: "  << largestRides << endl;
    cout << "   Rides per hour for weekday and weekend:" << endl;

    for(int i=0;i<weekdayData.size();i++){//loops through 24 times and displays the corresponding data for each hour
        cout << setw(5)  << i <<":"<< setw(7) <<weekdayData.at(i) << setw(7) << weekendData.at(i)<< endl;
    }
}


void displayTripsPerHourGraph(vector<DivvyData> cleandivvyData,vector<int> weekdayData,vector<int> weekendData,int largestRides){//diplays the graph of trips per hour of weekend and weekday data
    double graphWeekDay; // stores the number of @s for weekday
    double graphWeekEnd;// stores the number of +s for weekends

    cout << endl;
    for(int index=0;index<weekdayData.size();index++){// loops through 24 times
        graphWeekDay = double(weekdayData.at(index))/double(largestRides)*50;//calculates the number of @s for each weekday hours
        graphWeekEnd = double(weekendData.at(index))/double(largestRides)*50;//calculates the number of +s for each weekend hours

        cout << setw(5) << index << ": ";//diplays the hour index

        for(int j=0;j<int(graphWeekDay);j++){//diplays the @ grapWeekDay times
            cout << '@';
        }
        cout << endl <<endl;
        cout << setw(8);
        for(int j=0;j<int(graphWeekEnd);j++){//diplays the + grapWeekEnd times
            cout << '+';
        }
        cout <<  endl;
    }
}


void findClosestStation(vector<DivvyData> cleandivvyData){//finds the closest station and the distance 
    double long latInput;//stores the latitude input
    double long longInput;//stores the longitude input
    double closestStation= 999999999999.0;//stores the distace of the closest distance
    int closestStationIndex;//stores the index of the closest station

    cout << "   Input latitude and longitude of the home: ";
    cin >> latInput >> longInput;//takes in the latInput and longInput
    cout <<  endl;
    cout << "   You entered: " << ((int)((latInput)*10)) / 10.0  << " for latitude and " << ((int)((longInput)*10)) / 10.0 << " for longitude" <<  endl;//displays the rounded inputs

    for(int i=0;i<cleandivvyData.size();i++){//loops the clean data
        double currDistance = distance(latInput,longInput,cleandivvyData.at(i).endLat,cleandivvyData.at(i).endLong); //sets currDistace equal to the distance of input to the end cordinates at current index
        if(currDistance<closestStation){//if the current distance is less then the distance of the closest station then
            closestStation=currDistance;//set closeststation equal to the current distance
            closestStationIndex=i;// set the index equal to i
        }
    }
    
    cout << "   Closest Divvy station is: " << cleandivvyData.at(closestStationIndex).endStationName << 
    " at "<<cleandivvyData.at(closestStationIndex).endLat<<", "<<cleandivvyData.at(closestStationIndex).endLong <<", "<<
     round(10*closestStation)/10 <<" miles"<<endl;//displays the closest station and the distance away from it
}


void menuoptionSelection(vector<DivvyData>& alldivvyData,vector<DivvyData>& cleandivvyData,vector<int> weekdaydata,vector<int> weekenddata,int& largestRides,int& userInput){//function for selecting menu options
    if(userInput==1){//if 1 then read in the data into the resepective arrays
        int datafileInput;//stores the option of the type of datafile
        cout << "   Select datafile:"<< endl;
        cout << "      1. Small subset of data with 14 rides to help create your program" << endl;
        cout << "      2. Week day vs weekend rides" <<  endl;
        cout << "      3. All September 2021 data (not tested in Zybooks)" << endl;
        cout << "   Your selection--> ";
        cin >> datafileInput;//reads in input for the type of datafile
        readsampleDivvyDataIntoArray(alldivvyData,cleandivvyData,datafileInput);//calls function to read data into clean and all divvy data arrays
        cout << "   Total # of trips found in datafile:  " << alldivvyData.size() << endl;
        cout << "   Total # of trips in clean data:  " << cleandivvyData.size() << endl;
        cout << endl;

    }
    else if((userInput==2 || userInput==3 ||userInput==4 ||userInput==5) && cleandivvyData.size()==0){//if the user selects 2,3,4, or 5 without selecting option one then display the warning message
        cout<<"   First read in data by selecting menu option 1" <<  endl;
    }
    else if(userInput==2){//if option 2 is selected then call overallTripInformation function
            overallTripInformation(cleandivvyData);//passes the clean data array
    }
    else if(userInput==3){//if option 3 is selected then call calculate percent function
        percentriderType(cleandivvyData);//passes the clean data array
    }
    else if (userInput==4){//if option 4 is slected then call the display hour data function
        int datadisplayType;
        cout << "   Select type of display:" << endl;
        cout << "      1. Counts of rides per hour in the day" <<  endl;
        cout << "      2. Proportional 50 column graph with @ for weekday and + for weekend" << endl;
        cout << "   Your selection--> ";
        cin >> datadisplayType;

        if(datadisplayType==1){//counts the rides in a day per hour and displays it in each line
            getTripsPerHour(cleandivvyData,weekdaydata,weekenddata,largestRides);
            displayTripsPerHourData(weekdaydata,weekenddata,largestRides);
        }
        else{//counts the rides in a day per hour and diplays the graph 
            getTripsPerHour(cleandivvyData,weekdaydata,weekenddata,largestRides);
            displayTripsPerHourGraph(cleandivvyData,weekdaydata,weekenddata,largestRides);
        }
    }
    else if(userInput==5){//if option 5 is selected then call the findClosestStation fuction
        findClosestStation(cleandivvyData);//passes the clean data array
    }
}


int main(){
    int userInput;   //stores the user input for menu option

    vector<DivvyData> alldivvyData;//stores all divvy data objects
    vector<DivvyData> cleandivvyData;//stores all clean data objects

    vector<int>weekdaydata;//stores the weekday rides per hour data
    vector<int>weekenddata;//stores the weekend rides per hour data
    int largestRides=0;//stores the largest number of rides in a hour

    cout << "Analyze Divvy bike ride information using September trip data." <<  endl;
    cout << "First select option 1 to read and clean the data." << endl;
    cout << endl;
    while (true){//keeps looping through until breaks

        cout << "Select a menu option: " << endl;
        cout << "   1. Select datafile, display rides totals and clean data" << endl;
        cout << "   2. Display overall trip information" << endl;
        cout << "   3. Display percentage of members vs. casual riders" << endl;
        cout << "   4. Display weekday vs weekend usage" << endl;
        cout << "   5. Extra Credit: find closest station" << endl;
        cout << "   6. Exit" << endl;
        cout << "Your choice --> ";
        cin >> userInput;//takes in user input

        if(userInput==6){
            break;//exits loop if option 6 is selected
        }
        else{//if the user input is not 6 then cacll the menutopionSlection function
            menuoptionSelection(alldivvyData,cleandivvyData,weekdaydata,weekenddata,largestRides,userInput);
        }
    }
    return 0;
}