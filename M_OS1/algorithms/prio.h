#ifndef ALGO_PRIORITY_H
#define ALGO_PRIORITY_H

#include <vector>
#include <tuple>
#include <string>

using namespace std;

// Fixed-priority, non-preemptive scheduling:
// processes: (name, arrival, service)
// priorities: per-process priority (lower value = higher priority)
// last_instant: simulation length
// timeline: 2D grid for '*' (running) and '.' (waiting)
// finishTime, turnAroundTime, normTurn: output metrics
void priorityScheduling(
    const vector<tuple<string,int,int>>& processes,
    int last_instant,
    vector<vector<char>>& timeline,
    vector<int>& finishTime,
    vector<int>& turnAroundTime,
    vector<float>& normTurn
);

#endif // ALGO_PRIORITY_H
