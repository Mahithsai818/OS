#include "mlfq.h"
#include <queue>
#include <vector>
#include <tuple>
#include <cmath>

// Helper: mark waiting slots with '.'
static void fillInWaitTime(
    const vector<tuple<string,int,int>>& processes,
    vector<vector<char>>& timeline,
    const vector<int>& finishTime
) {
    int n = processes.size();
    for (int i = 0; i < n; ++i) {
        int arrival = get<1>(processes[i]);
        int finish  = finishTime[i];
        for (int t = arrival; t < finish; ++t) {
            if (timeline[t][i] != '*')
                timeline[t][i] = '.';
        }
    }
}

void mlfqScheduling(
    const vector<tuple<string,int,int>>& processes,
    int last_instant,
    vector<vector<char>>& timeline,
    vector<int>& finishTime,
    vector<int>& turnAroundTime,
    vector<float>& normTurn
) {
    int levels=3;
    int n = processes.size(), j = 0;
    vector<int> rem(n);
    for (int i = 0; i < n; ++i)
        rem[i] = get<2>(processes[i]);

    vector<queue<int>> queues(levels);

    for (int t = 0; t < last_instant; ++t) {
        // Enqueue new arrivals at level 0
        while (j < n && get<1>(processes[j]) == t) {
            queues[0].push(j);
            ++j;
        }

        // Find first non-empty queue
        int lvl = 0;
        while (lvl < levels && queues[lvl].empty()) ++lvl;
        if (lvl == levels) continue;  // CPU idle

        int idx = queues[lvl].front();
        queues[lvl].pop();

        int quantum = 1 << lvl;             // 2^lvl
        int run     = min(rem[idx], quantum);
        for (int u = 0; u < run && t < last_instant; ++u, ++t) {
            timeline[t][idx] = '*';
            --rem[idx];
        }

        if (rem[idx] > 0) {
            // Demote to next level (or keep at last)
            int next = min(lvl + 1, levels - 1);
            queues[next].push(idx);
        } else {
            finishTime[idx]     = t;
            turnAroundTime[idx] = finishTime[idx] - get<1>(processes[idx]);
            normTurn[idx]       = turnAroundTime[idx] * 1.0f / get<2>(processes[idx]);
        }

        // Step back one time unit (outer loop will ++t)
        --t;
    }

    fillInWaitTime(processes, timeline, finishTime);
}
