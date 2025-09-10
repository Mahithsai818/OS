#include "fb2i.h"
#include <queue>
#include <unordered_map>
#include <cmath>

using namespace std;

void feedbackQ2i(
    const vector<tuple<string,int,int>>& processes,
    int last_instant,
    vector<vector<char>>& timeline,
    vector<int>& finishTime,
    vector<int>& turnAroundTime,
    vector<float>& normTurn
) {
    int n = processes.size(), j = 0;
    priority_queue<pair<int,int>,
                   vector<pair<int,int> >,
                   greater<pair<int,int> > > pq;
    unordered_map<int,int> rem;

    // initial enqueue
    if (get<1>(processes[0]) == 0) {
        pq.push(make_pair(0, 0));
        rem[j] = get<2>(processes[0]);
        ++j;
    }

    for (int t = 0; t < last_instant; ++t) {
        if (!pq.empty()) {
            pair<int,int> top = pq.top();
            pq.pop();
            int pl = top.first;
            int idx = top.second;

            if (j < n && get<1>(processes[j]) <= t + 1) {
                pq.push(make_pair(0, j));
                rem[j] = get<2>(processes[j]);
                ++j;
            }

            int q = 1 << pl;   // quantum = 2^pl
            int timeSlot = 0;

            while (timeSlot < q && rem[idx] > 0 && t < last_instant) {
                timeline[t][idx] = '*';
                --rem[idx];
                ++timeSlot;
                ++t;
            }

            if (rem[idx] == 0) {
                finishTime[idx]     = t;
                turnAroundTime[idx] = finishTime[idx] - get<1>(processes[idx]);
                normTurn[idx]       = turnAroundTime[idx] * 1.0f / get<2>(processes[idx]);
            } else {
                int nxt = pq.empty() ? pl : pl + 1;
                pq.push(make_pair(nxt, idx));
            }

            --t;  // adjust overshoot (since last loop increments t)
        }

        // enqueue arrivals at time t+1
        while (j < n && get<1>(processes[j]) <= t + 1) {
            pq.push(make_pair(0, j));
            rem[j] = get<2>(processes[j]);
            ++j;
        }
    }

    // fill waiting slots with '.'
    for (int i = 0; i < n; ++i) {
        int a = get<1>(processes[i]);
        int f = finishTime[i];
        for (int x = a; x < f; ++x) {
            if (timeline[x][i] != '*')
                timeline[x][i] = '.';
        }
    }
}
