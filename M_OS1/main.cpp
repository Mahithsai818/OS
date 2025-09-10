#include <bits/stdc++.h>
#include "parser.h"
#include "print.h"
#include "algorithms/fcfs.h"
#include "algorithms/rr.h"
#include "algorithms/srt.h"
#include "algorithms/spn.h"
#include "algorithms/agg.h"
#include "algorithms/hrrn.h"
#include "algorithms/fb1.h"
#include "algorithms/fb2i.h"
#include "algorithms/prio.h"
#include "algorithms/mlfq.h"

#define all(v) v.begin(), v.end()

using namespace std;

/** Global Constants **/
const string TRACE = "trace";
const string SHOW_STATISTICS = "stats";
const string ALGORITHMS[11] = {
    "", "FCFS", "RR-", "SPN", "SRT",
    "HRRN", "FB-1", "FB-2i", "AGING",
    "PRIO", "MLFQ"
};

void clear_timeline()
{
    for (int i = 0; i < last_instant; i++)
        for (int j = 0; j < process_count; j++)
            timeline[i][j] = ' ';
}

void execute_algorithm(string algorithm_id, int quantum, string operation)
{
    if (algorithm_id == "1") {
        if (operation == TRACE) cout << "FCFS  ";
        firstComeFirstServe(processes, last_instant, timeline, finishTime, turnAroundTime, normTurn);
    }
    else if (algorithm_id == "2") {
        if (operation == TRACE) cout << "RR-" << quantum << "  ";
        roundRobin(processes, last_instant, timeline, finishTime, turnAroundTime, normTurn, quantum);
    }
    else if (algorithm_id == "3") {
        if (operation == TRACE) cout << "SPN   ";
        shortestProcessNext(processes, last_instant, timeline, finishTime, turnAroundTime, normTurn);
    }
    else if (algorithm_id == "4") {
        if (operation == TRACE) cout << "SRT   ";
        shortestRemainingTime(processes, last_instant, timeline, finishTime, turnAroundTime, normTurn);
    }
    else if (algorithm_id == "5") {
        if (operation == TRACE) cout << "HRRN  ";
        highestResponseRatioNext(processes, last_instant, timeline, finishTime, turnAroundTime, normTurn);
    }
    else if (algorithm_id == "6") {
        if (operation == TRACE) cout << "FB-1  ";
        feedbackQ1(processes, last_instant, timeline, finishTime, turnAroundTime, normTurn);
    }
    else if (algorithm_id == "7") {
        if (operation == TRACE) cout << "FB-2i ";
        feedbackQ2i(processes, last_instant, timeline, finishTime, turnAroundTime, normTurn);
    }
    else if (algorithm_id == "8") {
        if (operation == TRACE) cout << "Aging ";
        aging(processes, last_instant, timeline, finishTime, turnAroundTime, normTurn, quantum);
    }
    else if (algorithm_id == "9") {
        if (operation == TRACE) cout << "PRIO  ";
        priorityScheduling(processes, last_instant, timeline, finishTime, turnAroundTime, normTurn);
    }
    else if (algorithm_id == "10") {
        if (operation == TRACE) cout << "MLFQ  ";
        mlfqScheduling(processes, last_instant, timeline, finishTime, turnAroundTime, normTurn);
    }
}

int main()
{
    parse();
    for (size_t idx = 0; idx < algorithms.size(); idx++) {
        clear_timeline();
        string algorithm_id = algorithms[idx].first;
        int quantum = algorithms[idx].second;

        execute_algorithm(algorithm_id, quantum, operation);

        if (operation == TRACE)
            printTimeline(processes, last_instant, process_count, timeline, (int)idx);
        else if (operation == SHOW_STATISTICS)
            printStats(algorithms, (int)idx, processes, process_count,
                       finishTime, turnAroundTime, normTurn);

        cout << "\n";
    }
    return 0;
}
