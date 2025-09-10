#include "hrrn.h"
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

static double calculate_response_ratio(int w, int s) {
    return (w + s) * 1.0 / s;
}

void highestResponseRatioNext(
    const vector<tuple<string,int,int>>& processes,
    int last_instant,
    vector<vector<char>>& timeline,
    vector<int>& finishTime,
    vector<int>& turnAroundTime,
    vector<float>& normTurn
) {
    int n = processes.size(), j = 0;
    vector<tuple<string,double,int>> ready; // name, ratio, doneUnits

    for (int t = 0; t < last_instant; ++t) {
        // enqueue arrivals
        while (j < n && get<1>(processes[j]) <= t) {
            ready.emplace_back(get<0>(processes[j]), 1.0, 0);
            ++j;
        }
        // update ratios
        for (auto &pr : ready) {
            string name = get<0>(pr);
            int idx = -1;
            for (int k = 0; k < n; ++k)
                if (get<0>(processes[k]) == name) { idx = k; break; }
            int w = t - get<1>(processes[idx]);
            int s = get<2>(processes[idx]);
            get<1>(pr) = calculate_response_ratio(w, s);
        }
        // pick highest ratio
        sort(ready.begin(), ready.end(),
             [](auto &a, auto &b){ return get<1>(a) > get<1>(b); });
        if (ready.empty()) continue;

        // run selected to completion
        string sel = get<0>(ready[0]);
        int idx = -1;
        for (int k = 0; k < n; ++k)
            if (get<0>(processes[k]) == sel) { idx = k; break; }
        int run = get<2>(processes[idx]);
        int start = t;
        while (get<2>(ready[0]) < run && t < last_instant) {
            timeline[t][idx] = '*';
            get<2>(ready[0])++;
            ++t;
        }
        --t;  // adjust overflow
        finishTime[idx]     = t + 1;
        turnAroundTime[idx] = finishTime[idx] - get<1>(processes[idx]);
        normTurn[idx]       = turnAroundTime[idx] * 1.0f / get<2>(processes[idx]);
        ready.erase(ready.begin());
    }
    // fill waiting dots
    for (int i = 0; i < n; ++i) {
        int a = get<1>(processes[i]), f = finishTime[i];
        for (int x = a; x < f; ++x)
            if (timeline[x][i] != '*') timeline[x][i] = '.';
    }
}
