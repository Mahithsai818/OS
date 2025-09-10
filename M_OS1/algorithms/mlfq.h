#ifndef ALGO_MLFQ_H
#define ALGO_MLFQ_H

#include <vector>
#include <tuple>
#include <string>

using namespace std;

// Multi-Level Feedback Queue scheduling:
// processes: (name, arrival, service)
// levels: number of feedback levels
// last_instant: simulation length
// timeline: 2D grid for '*' and '.'  
// finishTime, turnAroundTime, normTurn: outputs
void mlfqScheduling(
    const vector<tuple<string,int,int>>& processes,
    int last_instant,
    vector<vector<char>>& timeline,
    vector<int>& finishTime,
    vector<int>& turnAroundTime,
    vector<float>& normTurn
);

#endif // ALGO_MLFQ_H
