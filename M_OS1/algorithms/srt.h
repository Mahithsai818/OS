#ifndef ALGO_SRT_H
#define ALGO_SRT_H

#include <vector>
#include <tuple>
#include <string>

using namespace std;

// Preemptive shortest remaining time first
void shortestRemainingTime(
    const vector<tuple<string,int,int>>& processes,
    int last_instant,
    vector<vector<char>>& timeline,
    vector<int>& finishTime,
    vector<int>& turnAroundTime,
    vector<float>& normTurn
);

#endif // ALGO_SRT_H
