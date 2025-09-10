#ifndef ALGO_FCFS_H
#define ALGO_FCFS_H
using namespace std;
#include <vector>
#include <tuple>
#include <string>

// Must match signatures in main.cpp
void firstComeFirstServe(
    const vector<tuple<string,int,int>>&processes,
    int last_instant,
    vector<vector<char>>& timeline,
    vector<int>& finishTime,
    vector<int>& turnAroundTime,
    vector<float>& normTurn
);

#endif 
