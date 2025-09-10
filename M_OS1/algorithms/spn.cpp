#include "spn.h"
#include <queue>
#include <vector>
#include <tuple>
#include <functional>

using namespace std;

void shortestProcessNext(
    const vector<tuple<string,int,int> >& processes,
    int last_instant,
    vector<vector<char> >& timeline,
    vector<int>& finishTime,
    vector<int>& turnAroundTime,
    vector<float>& normTurn
) {
    int process_count = processes.size();

    // min-heap by (serviceTime, index)
    priority_queue<pair<int,int>,
                   vector<pair<int,int> >,
                   greater<pair<int,int> > > pq;

    int j = 0;
    for (int t = 0; t < last_instant; ++t) {
        // enqueue all arrived
        while (j < process_count && get<1>(processes[j]) <= t) {
            pq.push(make_pair(get<2>(processes[j]), j));
            ++j;
        }

        if (!pq.empty()) {
            pair<int,int> top = pq.top();
            pq.pop();
            int svc = top.first;
            int idx = top.second;

            int arrival = get<1>(processes[idx]);

            // mark wait before start
            for (int w = arrival; w < t; ++w)
                timeline[w][idx] = '.';

            // run to completion
            for (int u = t; u < t + svc; ++u)
                timeline[u][idx] = '*';

            finishTime[idx]     = t + svc;
            turnAroundTime[idx] = finishTime[idx] - arrival;
            normTurn[idx]       = turnAroundTime[idx] * 1.0f / svc;

            t += svc - 1;  // jump time
        }
    }
}
