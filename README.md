# Drone ALPHA Journey

This project implements an autonomous drone route planning system across Türkiye’s provinces using stack and queue data structures. The program simulates exploration under realistic constraints such as limited fuel range, priority locations, and weather-restricted provinces.

## ✈️ Project Overview

- The drone starts from Ankara and attempts to visit the maximum number of provinces.
- Stack (LIFO) is used for backtracking when no forward moves are available.
- Queue (FIFO) is used to manage exploration of neighboring provinces.
- Each leg of the journey is limited to 250 km (fuel constraint).
- Some provinces are marked as high-priority, while others are weather-restricted and must be skipped.
- Outputs include the full route, total distance, and summary of priority province visits.

## 📁 File Structure

```
input/
├── distance_data.csv                 # Distance matrix between provinces
├── priority_provinces.txt           # List of high-priority provinces
├── weather_restricted_provinces.txt# List of inaccessible provinces

src/
├── Map.h / Map.cpp
├── Stack.h / Stack.cpp
├── Queue.h / Queue.cpp
├── RoutePlanner.h / RoutePlanner.cpp
```

> `.h` files contain class declarations and function prototypes,  
> `.cpp` files include implementations of corresponding modules.

## ▶️ Compilation and Execution

```bash
g++ -std=c++11 *.cpp *.h -o DroneALPHA
./DroneALPHA 250 5 distance_data.csv priority_provinces.txt weather_restricted_provinces.txt
```

### Arguments:
- `250`: Maximum allowed distance per move (fuel constraint)
- `5`: Index of starting province (Ankara)
- Input files: distance matrix, priority list, and restricted list

## 📦 Features

- Custom stack and circular queue structures using static arrays
- CSV-based map loading and dynamic exploration logic
- Skips restricted provinces and prioritizes critical regions
- Tracks visited provinces and prevents revisits
- Structured output: route, visited count, distance, and priority status

## 📌 Notes

- All memory management is handled statically (no dynamic allocation).
- Outputs are written to the console with summaries at the end.
- Input files must be in the correct format and order as per usage.

