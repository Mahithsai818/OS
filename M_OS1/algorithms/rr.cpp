#include "rr.h"
#include <queue>
#include <tuple>
#include <string>
using namespace std;

static void fillInWaitTime(
    const vector<tuple<string,int,int>>& processes,
    vector<vector<char>>& timeline,
    const vector<int>& finishTime
) {
    int process_count = processes.size();
    for (int i = 0; i < process_count; ++i) {
        int arrivalTime = get<1>(processes[i]);
        for (int k = arrivalTime; k < finishTime[i]; ++k) {
            if (timeline[k][i] != '*')
                timeline[k][i] = '.';
        }
    }
}

void roundRobin(
    const vector<tuple<string,int,int>>& processes,
    int last_instant,
    vector<vector<char>>& timeline,
    vector<int>& finishTime,
    vector<int>& turnAroundTime,
    vector<float>& normTurn,
    int originalQuantum
) {
    int process_count = processes.size();
    queue<pair<int,int>> q;
    int j = 0;
    if (get<1>(processes[j]) == 0) {
        q.push({ j, get<2>(processes[j]) });
        ++j;
    }

    int currentQuantum = originalQuantum;
    for (int time = 0; time < last_instant; ++time) {
        if (!q.empty()) {
            int processIndex = q.front().first;
            q.front().second -= 1;
            int remainingServiceTime = q.front().second;

            int arrivalTime = get<1>(processes[processIndex]);
            int serviceTime = get<2>(processes[processIndex]);

            currentQuantum--;
            timeline[time][processIndex] = '*';
            while (j < process_count && get<1>(processes[j]) == time + 1) {
                q.push({ j, get<2>(processes[j]) });
                ++j;
            }

            if (currentQuantum == 0 && remainingServiceTime == 0) {
                finishTime[processIndex] = time + 1;
                turnAroundTime[processIndex] = finishTime[processIndex] - arrivalTime;
                normTurn[processIndex] = turnAroundTime[processIndex] * 1.0f / serviceTime;
                currentQuantum = originalQuantum;
                q.pop();
            }
            else if (currentQuantum == 0 && remainingServiceTime != 0) {
                q.pop();
                q.push({ processIndex, remainingServiceTime });
                currentQuantum = originalQuantum;
            }
            else if (currentQuantum != 0 && remainingServiceTime == 0) {
                finishTime[processIndex] = time + 1;
                turnAroundTime[processIndex] = finishTime[processIndex] - arrivalTime;
                normTurn[processIndex] = turnAroundTime[processIndex] * 1.0f / serviceTime;
                q.pop();
                currentQuantum = originalQuantum;
            }
        }

        while (j < process_count && get<1>(processes[j]) == time + 1) {
            q.push({ j, get<2>(processes[j]) });
            ++j;
        }
    }

    fillInWaitTime(processes, timeline, finishTime);
}
