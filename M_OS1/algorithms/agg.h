#ifndef ALGO_AGING_H
#define ALGO_AGING_H

#include <vector>
#include <tuple>
#include <string>

using namespace std;

// Priority aging with fixed quantum
void aging(
    const vector<tuple<string,int,int>>& processes,
    int last_instant,
    vector<vector<char>>& timeline,
    vector<int>& finishTime,
    vector<int>& turnAroundTime,
    vector<float>& normTurn,
    int originalQuantum
);

#endif // ALGO_AGING_H
