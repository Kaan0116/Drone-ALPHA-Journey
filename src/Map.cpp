#include "Map.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <limits>
using namespace std;
Map::Map() {
    // TODO: Your code here
    // Initialize all distances to a value representing no direct connection
    // Initialize all provinces as unvisited
    for (int i=0;i<MAX_SIZE;i++){
        for(int j=0;j<MAX_SIZE;j++){
            this->distanceMatrix[i][j]=numeric_limits<int>::max();
        }
    }
    for (int i = 0; i < MAX_SIZE; i++) {
        this->visited[i] = false;
    }
}

// Loads distance data from a file and fills the distanceMatrix
void Map::loadDistanceData(const std::string& filename) {
    // TODO: Your code here
    // Read each line in the CSV file
    // Read each cell separated by a comma
    // Convert cell to an integer and store in distanceMatrix

    ifstream file(filename);
    string line;
    int row=0;
    while(getline(file,line)){
        stringstream ss(line);
        string cell;
        int col=0;
        while(getline(ss,cell,',')){
            if(!cell.empty()){
                this->distanceMatrix[row][col]=stoi(cell);
            }
            col++;
        }
        row++;
    }
    file.close();
}

// Checks if the distance between two provinces is within the allowed maxDistance
bool Map::isWithinRange(int provinceA, int provinceB, int maxDistance) const {
    return (this->getDistance(provinceA,provinceB)<=maxDistance);
     
}

// Marks a province as visited
void Map::markAsVisited(int province) {
    this->visited[province]=true;
}

// Checks if a province has already been visited
bool Map::isVisited(int province) const {
    return this->visited[province];
}

// Resets all provinces to unvisited
void Map::resetVisited() {
    for(int i=0;i<MAX_SIZE;i++){
        this->visited[i]=false;
    }
}

// Function to count the number of visited provinces
int Map::countVisitedProvinces() const {
    int c=0;
    for(int i=0;i<MAX_SIZE;i++){
        if(this->visited[i]){
            c++;
        }
    }
    return c;
}

// Function to get the distance between two provinces
int Map::getDistance(int provinceA, int provinceB) const {
    int result=this->distanceMatrix[provinceA][provinceB];
    return result;
}