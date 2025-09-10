#ifndef ALGO_FB2I_H
#define ALGO_FB2I_H

#include <vector>
#include <tuple>
#include <string>

using namespace std;

// Exponential feedback quantum
void feedbackQ2i(
    const vector<tuple<string,int,int>>& processes,
    int last_instant,
    vector<vector<char>>& timeline,
    vector<int>& finishTime,
    vector<int>& turnAroundTime,
    vector<float>& normTurn
);

#endif // ALGO_FB2I_H
