#include "fb1.h"
#include <queue>
#include <unordered_map>

using namespace std;

void feedbackQ1(
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

    // init
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

            if (j < n && get<1>(processes[j]) == t + 1) {
                pq.push(make_pair(0, j));
                rem[j] = get<2>(processes[j]);
                ++j;
            }

            // run one unit
            timeline[t][idx] = '*';
            if (--rem[idx] == 0) {
                finishTime[idx]     = t + 1;
                turnAroundTime[idx] = finishTime[idx] - get<1>(processes[idx]);
                normTurn[idx]       = turnAroundTime[idx] * 1.0f / get<2>(processes[idx]);
            } else {
                // demote priority if others waiting
                int nxt = pq.empty() ? pl : pl + 1;
                pq.push(make_pair(nxt, idx));
            }
        }

        // enqueue arrivals
        while (j < n && get<1>(processes[j]) == t + 1) {
            pq.push(make_pair(0, j));
            rem[j] = get<2>(processes[j]);
            ++j;
        }
    }

    // fill waiting
    for (int i = 0; i < n; ++i) {
        int a = get<1>(processes[i]), f = finishTime[i];
        for (int x = a; x < f; ++x) {
            if (timeline[x][i] != '*')
                timeline[x][i] = '.';
        }
    }
}
