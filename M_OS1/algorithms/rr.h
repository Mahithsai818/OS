#ifndef ALGO_RR_H
#define ALGO_RR_H
using namespace std;
#include <vector>
#include <tuple>
#include <string>

void roundRobin(
    const vector<tuple<string,int,int>>&processes,
    int last_instant,
    vector<vector<char>>& timeline,
    vector<int>& finishTime,
    vector<int>& turnAroundTime,
    vector<float>& normTurn,
    int originalQuantum
);

#endif 