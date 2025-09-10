#ifndef ALGO_FB1_H
#define ALGO_FB1_H

#include <vector>
#include <tuple>
#include <string>

using namespace std;

// Single-quantum feedback
void feedbackQ1(
    const vector<tuple<string,int,int>>& processes,
    int last_instant,
    vector<vector<char>>& timeline,
    vector<int>& finishTime,
    vector<int>& turnAroundTime,
    vector<float>& normTurn
);

#endif // ALGO_FB1_H
