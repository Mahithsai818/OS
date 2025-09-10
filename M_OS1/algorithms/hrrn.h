#ifndef ALGO_HRRN_H
#define ALGO_HRRN_H

#include <vector>
#include <tuple>
#include <string>

using namespace std;

// Highest Response‐Ratio Next (non-preemptive)
void highestResponseRatioNext(
    const vector<tuple<string,int,int>>& processes,
    int last_instant,
    vector<vector<char>>& timeline,
    vector<int>& finishTime,
    vector<int>& turnAroundTime,
    vector<float>& normTurn
);

#endif // ALGO_HRRN_H
