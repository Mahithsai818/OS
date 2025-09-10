#include "fcfs.h"
using namespace std;

void firstComeFirstServe(
    const vector<tuple<string,int,int>>& processes,
    int last_instant,
    vector<vector<char>>& timeline,
    vector<int>& finishTime,
    vector<int>& turnAroundTime,
    vector<float>& normTurn
) {
    int process_count = processes.size();
    int time = get<1>(processes[0]);
    for (int i = 0; i < process_count; ++i) {
        int arrival = get<1>(processes[i]);
        int service = get<2>(processes[i]);
        finishTime[i] = time + service;
        turnAroundTime[i] = finishTime[i] - arrival;
        normTurn[i] = turnAroundTime[i] * 1.0f / service;
        for (int t = time; t < finishTime[i]; ++t)
            timeline[t][i] = '*';
        for (int t = arrival; t < time; ++t)
            timeline[t][i] = '.';
        time += service;
    }
}
