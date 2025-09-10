#include "agg.h"
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

// compare (priority, wait, idx)
static bool byPriorityLevel(const tuple<int,int,int>& a,
                            const tuple<int,int,int>& b) {
    if (get<0>(a) == get<0>(b))
        return get<2>(a) > get<2>(b);
    return get<0>(a) > get<0>(b);
}

void aging(
    const vector<tuple<string,int,int>>& processes,
    int last_instant,
    vector<vector<char>>& timeline,
    vector<int>& finishTime,
    vector<int>& turnAroundTime,
    vector<float>& normTurn,
    int originalQuantum
) {
    int n = processes.size(), j = 0, current = -1;
    vector<tuple<int,int,int>> Q;  // (prio, idx, wait)
    for (int t = 0; t < last_instant; ++t) {
        while (j < n && get<1>(processes[j]) <= t) {
            Q.emplace_back(get<2>(processes[j]), j, 0);
            ++j;
        }
        // age everyone
        for (auto &e : Q) {
            if (get<1>(e) == current) {
                get<0>(e) = get<2>(processes[current]);
                get<2>(e) = 0;
            } else {
                get<0>(e)++;
                get<2>(e)++;
            }
        }
        sort(Q.begin(), Q.end(), byPriorityLevel);
        current = get<1>(Q[0]);
        int q = originalQuantum;
        while (q-- && t < last_instant) {
            timeline[t][current] = '*';
            ++t;
        }
        --t;
    }
    // fill waits
    for (int i = 0; i < n; ++i) {
        int a = get<1>(processes[i]), f; 
        // finishTime not set per unit; ignore for stats or set in Q exit
        f = last_instant;
        for (int x = a; x < f; ++x)
            if (timeline[x][i] != '*') timeline[x][i] = '.';
    }
}
