#ifndef ALGO_SPN_H
#define ALGO_SPN_H

#include <vector>
#include <tuple>
#include <string>

using namespace std;

void shortestProcessNext(
    const vector<tuple<string,int,int>>& processes,
    int last_instant,
    vector<vector<char>>& timeline,
    vector<int>& finishTime,
    vector<int>& turnAroundTime,
    vector<float>& normTurn
);

#endif 
