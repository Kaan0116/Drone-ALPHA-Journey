#include "RoutePlanner.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
// Array to help you out with name of the cities in order
const std::string cities[81] = { 
    "Adana", "Adiyaman", "Afyon", "Agri", "Amasya", "Ankara", "Antalya", "Artvin", "Aydin", "Balikesir", "Bilecik", 
    "Bingol", "Bitlis", "Bolu", "Burdur", "Bursa", "Canakkale", "Cankiri", "Corum", "Denizli", "Diyarbakir", "Edirne", 
    "Elazig", "Erzincan", "Erzurum", "Eskisehir", "Gaziantep", "Giresun", "Gumushane", "Hakkari", "Hatay", "Isparta", 
    "Mersin", "Istanbul", "Izmir", "Kars", "Kastamonu", "Kayseri", "Kirklareli", "Kirsehir", "Kocaeli", "Konya", "Kutahya", 
    "Malatya", "Manisa", "Kaharamanmaras", "Mardin", "Mugla", "Mus", "Nevsehir", "Nigde", "Ordu", "Rize", "Sakarya", 
    "Samsun", "Siirt", "Sinop", "Sivas", "Tekirdag", "Tokat", "Trabzon", "Tunceli", "Urfa", "Usak", "Van", "Yozgat", 
    "Zonguldak", "Aksaray", "Bayburt", "Karaman", "Kirikkale", "Batman", "Sirnak", "Bartin", "Ardahan", "Igdir", 
    "Yalova", "Karabuk", "Kilis", "Osmaniye", "Duzce" 
};

// Constructor to initialize and load constraints
RoutePlanner::RoutePlanner(const std::string& distance_data, const std::string& priority_data, const std::string& restricted_data, int maxDistance)
    : maxDistance(maxDistance), totalDistanceCovered(0), numPriorityProvinces(0), numWeatherRestrictedProvinces(0) {
    map.loadDistanceData(distance_data);
    map.resetVisited();
    loadPriorityProvinces(priority_data);
    loadWeatherRestrictedProvinces(restricted_data);
    
        
}

// Load priority provinces from txt file to an array of indices
void RoutePlanner::loadPriorityProvinces(const std::string& filename){
    ifstream file(filename);
    if (!file.is_open()){
        cerr<<"Error: Could not open priority file "<<filename<<endl;
        return;
    }
    
    string line;
    int number;
    int i=0;

    while(getline(file, line)) {
        stringstream ss(line);
        string city;
        char open, close;
        if(!(ss>>city>>open>>number>>close)||open!='('||close!=')'){
            cerr<<"Error: Invalid format in file."<<filename<<endl;
            continue;
        }

        if(i>=MAX_PRIORITY_PROVINCES){
            cerr<<"Limit exceeded, over-prioritized zone found!"<<endl;
            return;
        }

        this->priorityProvinces[i] = number;
        this->numPriorityProvinces++;
        i++;
    }

    file.close();
}


// Load weather-restricted provinces from txt file to an array of indices
void RoutePlanner::loadWeatherRestrictedProvinces(const std::string& filename){
    ifstream file(filename);
    if (!file.is_open()) {
        cerr<<"Error: Could not open weather-restricted file."<<filename<<endl;
        return;
    }

    string line;
    int number;
    int i=0;

    while(getline(file, line)) {
        stringstream ss(line);
        string city;
        char open,close;


        if(!(ss>>city>>open>>number>>close)||open!='('||close!=')'){
            cerr<<"Error: Invalid format in file."<<filename<<endl;
            continue;
        }

        if (i>=MAX_WEATHER_RESTRICTED_PROVINCES) {
            cerr<<"Limit exceeded, over-weather-restricted prioritized zones found!"<<endl;
            return;
        }
        this->weatherRestrictedProvinces[i]=number;
        this->numWeatherRestrictedProvinces++;
        i++;
    }

    file.close();
}


// Checks if a province is a priority province
bool RoutePlanner::isPriorityProvince(int province) const {
    for(int i=0;i<this->numPriorityProvinces;i++){
        if(this->priorityProvinces[i]==province){
            return true;
        }
    }
    
    return false;
}

// Checks if a province is weather-restricted
bool RoutePlanner::isWeatherRestricted(int province) const {
    for(int i=0;i<this->numWeatherRestrictedProvinces;i++){
        if(this->weatherRestrictedProvinces[i]==province){
            return true;
        }
    }
    return false;
}

// Begins the route exploration from the starting point
void RoutePlanner::exploreRoute(int startingCity) {

    if(!isWeatherRestricted(startingCity)){
        map.markAsVisited(startingCity);
        route.push_back(startingCity);
        stack.push(startingCity);
        exploreFromProvince(startingCity);
    }
    displayResults();
}

// Helper function to explore from a specific province
void RoutePlanner::exploreFromProvince(int province) {
    enqueueNeighbors(province);
    while (!queue.isEmpty()) {
        int next = queue.dequeue();
        if (map.isVisited(next) || isWeatherRestricted(next)) {

            continue;
        }
        map.markAsVisited(next);
        stack.push(next);
        route.push_back(next);
        totalDistanceCovered += map.getDistance(province, next);
        exploreFromProvince(next);
    }
    backtrack();
    backtrack();
}

void RoutePlanner::enqueueNeighbors(int province) {
    for(int i=0;i<81;i++){
        if(!map.isVisited(i)&&map.isWithinRange(province,i,maxDistance)&&!isWeatherRestricted(i)){
            if(isPriorityProvince(i)){
                queue.enqueuePriority(i);
            }
            else{
                queue.enqueue(i);
            }
        }
        else if(!map.isVisited(i)&&map.isWithinRange(province,i,maxDistance)&&isWeatherRestricted(i)){
            skip_city.push_back(i);
        }
    }
}

void RoutePlanner::backtrack() {
    while (!stack.isEmpty()){
        int last=stack.pop();
        if(!queue.isEmpty()){
            exploreFromProvince(last);
            return;
        }
    }

}

bool RoutePlanner::isExplorationComplete() const {
    return stack.isEmpty() && queue.isEmpty();
}

void RoutePlanner::displayResults() const {


    for(int i=0;i<skip_city.size();i++){
        cout<<"Province "<<cities[skip_city[i]]<<" is weather-restricted. Skipping."<<endl;
    }
    cout<<"----------------------------\nJourney Completed!\n----------------------------"<<endl;
    cout<<"Total Number of Provinces Visited: "<<this->route.size()<<endl;
    cout<<"Total Distance Covered:"<<this->totalDistanceCovered<<" km"<<endl;
    cout<<"Route Taken:"<<endl;
    for(int i=0;i<this->route.size();i++){
        if(i==this->route.size()-1){
            cout<<cities[this->route[i]]<<endl;
        }
        else{
            cout<<cities[this->route[i]]<<" -> ";
        }
    }
    cout<<"Priority Provinces Status:"<<endl;;
    int travel_pri_city=0;
    for(int i=0;i<this->numPriorityProvinces;i++){
        if(i==this->numPriorityProvinces-1){
            if(map.isVisited(this->priorityProvinces[i])){
                cout<<"- "<<cities[this->priorityProvinces[i]]<<" (Visited)";
                travel_pri_city++;
            }
            else{
                cout<<"- "<<cities[this->priorityProvinces[i]]<<" (Not Visited)";
            }
        }
        else{
            if(map.isVisited(this->priorityProvinces[i])){
                cout<<"- "<<cities[this->priorityProvinces[i]]<<" (Visited)"<<endl;
                travel_pri_city++;
            }
            else{
                cout<<"- "<<cities[this->priorityProvinces[i]]<<" (Not Visited)"<<endl;
            }
        }
    }

    cout<<"\nTotal Priority Provinces Visited: "<<travel_pri_city<<" out of "<<numPriorityProvinces<<endl;
    if(travel_pri_city!=numPriorityProvinces){
        cout<<"Warning: Not all priority provinces were visited."<<endl;
    }
    else{
        cout<<"Success: All priority provinces were visited."<<endl;
    }
}


