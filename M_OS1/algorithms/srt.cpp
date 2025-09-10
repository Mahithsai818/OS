#include "srt.h"
#include <queue>
#include <vector>
#include <tuple>
#include <functional>

using namespace std;

// Helper: fill in waiting time slots with '.'
static void fillInWaitTime(
    const vector<tuple<string,int,int> >& processes,
    vector<vector<char> >& timeline,
    const vector<int>& finishTime
) {
    int n = processes.size();
    for (int i = 0; i < n; ++i) {
        int arrival = get<1>(processes[i]);
        for (int t = arrival; t < finishTime[i]; ++t) {
            if (timeline[t][i] != '*')
                timeline[t][i] = '.';
        }
    }
}

void shortestRemainingTime(
    const vector<tuple<string,int,int> >& processes,
    int last_instant,
    vector<vector<char> >& timeline,
    vector<int>& finishTime,
    vector<int>& turnAroundTime,
    vector<float>& normTurn
) {
    int process_count = processes.size();

    // min-heap by (remainingTime, index)
    priority_queue<pair<int,int>,
                   vector<pair<int,int> >,
                   greater<pair<int,int> > > pq;

    int j = 0;
    for (int t = 0; t < last_instant; ++t) {
        // enqueue new arrivals
        while (j < process_count && get<1>(processes[j]) == t) {
            pq.push(make_pair(get<2>(processes[j]), j));
            ++j;
        }

        if (!pq.empty()) {
            pair<int,int> top = pq.top();
            pq.pop();
            int rem = top.first;
            int idx = top.second;

            int arrival = get<1>(processes[idx]);
            int service = get<2>(processes[idx]);

            // run one unit
            timeline[t][idx] = '*';

            if (rem == 1) {
                // finishes now
                finishTime[idx]     = t + 1;
                turnAroundTime[idx] = finishTime[idx] - arrival;
                normTurn[idx]       = turnAroundTime[idx] * 1.0f / service;
            } else {
                // re-enqueue with decremented remaining
                pq.push(make_pair(rem - 1, idx));
            }
        }
    }

    fillInWaitTime(processes, timeline, finishTime);
}
