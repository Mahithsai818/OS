#include "prio.h"
#include <queue>
#include <tuple>
#include <vector>
#include <functional>

// Copy of your fillInWaitTime helper
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

void priorityScheduling(
    const vector<tuple<string,int,int>>& processes,
    int last_instant,
    vector<vector<char>>& timeline,
    vector<int>& finishTime,
    vector<int>& turnAroundTime,
    vector<float>& normTurn
) {
    int n = processes.size(), j = 0;

    // Min-heap of (priority=serviceTime, arrivalTime, index)
    priority_queue<
      tuple<int,int,int>,
      vector<tuple<int,int,int>>,
      greater<tuple<int,int,int>>
    > pq;

    for (int t = 0; t < last_instant; ++t) {
        // enqueue arrivals at time t
        while (j < n && get<1>(processes[j]) == t) {
            // use serviceTime as priority
            pq.emplace(get<2>(processes[j]), get<1>(processes[j]), j);
            ++j;
        }
        if (pq.empty()) continue;

        // select highest-priority (smallest serviceTime)
        auto top = pq.top(); 
        pq.pop();
        int svc = get<0>(top);
        int at  = get<1>(top);
        int idx = get<2>(top);

        // mark running
        for (int u = t; u < t + svc && u < last_instant; ++u)
            timeline[u][idx] = '*';

        finishTime[idx]     = min(t + svc, last_instant);
        turnAroundTime[idx] = finishTime[idx] - at;
        normTurn[idx]       = turnAroundTime[idx] * 1.0f / svc;

        // advance time to end of this run
        t += svc - 1;
    }

    fillInWaitTime(processes, timeline, finishTime);
}
