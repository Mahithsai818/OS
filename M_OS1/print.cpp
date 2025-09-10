#include "print.h"
#include <iostream>
#include <iomanip>
#include <cstdio>

using namespace std;

// Only declare functions and use extern for globals
// Globals are defined in main.cpp
// extern const string TRACE;
// extern const string SHOW_STATISTICS;
// extern const string ALGORITHMS[11];

// Clear timeline grid
void clear_timeline(int last_instant, int process_count, vector<vector<char>>& timeline) {
    for (int t = 0; t < last_instant; ++t) {
        for (int p = 0; p < process_count; ++p) {
            timeline[t][p] = ' ';
        }
    }
}

// Print the trace diagram
void printTimeline(
    const vector<tuple<string,int,int>>& processes,
    int last_instant,
    int process_count,
    const vector<vector<char>>& timeline,
    int algorithm_index
) {
    // Print time indices
    for (int t = 0; t <= last_instant; ++t) cout << (t % 10) << " ";
    cout << "\n" << string(4 * last_instant + 2, '-') << "\n";

    // One row per process
    for (int p = 0; p < process_count; ++p) {
        cout << setw(6) << get<0>(processes[p]) << " |";
        for (int t = 0; t < last_instant; ++t) {
            cout << timeline[t][p] << "|";
        }
        cout << "\n";
    }
    cout << string(4 * last_instant + 2, '-') << "\n";
}

// Print the statistics table
void printStats(
    const vector<pair<string,int>>& algorithmsList,
    int algorithm_index,
    const vector<tuple<string,int,int>>& processes,
    int process_count,
    const vector<int>& finishTime,
    const vector<int>& turnAroundTime,
    const vector<float>& normTurn
) {
    const string &id = algorithmsList[algorithm_index].first;
    int quantum = algorithmsList[algorithm_index].second;
    int alg = atoi(id.c_str());
    
    extern const string ALGORITHMS[11];
    cout << ALGORITHMS[alg];
    if (alg == 2) cout << quantum;
    cout << "\n";

    cout << "Process    ";
    for (int p = 0; p < process_count; ++p)
        cout << "|  " << setw(2) << get<0>(processes[p]) << " ";
    cout << "|\n";

    cout << "Arrival    ";
    for (int p = 0; p < process_count; ++p)
        cout << "|" << setw(3) << get<1>(processes[p]) << "  ";
    cout << "|\n";

    cout << "Service    |";
    for (int p = 0; p < process_count; ++p)
        cout << setw(3) << get<2>(processes[p]) << "  |";
    cout << " Mean|\n";

    cout << "Finish     ";
    for (int p = 0; p < process_count; ++p)
        cout << "|" << setw(3) << finishTime[p] << "  ";
    cout << "|-----|\n";

    cout << "Turnaround |";
    double sumT = 0;
    for (int p = 0; p < process_count; ++p) {
        cout << setw(3) << turnAroundTime[p] << "  |";
        sumT += turnAroundTime[p];
    }
    double meanT = sumT / process_count;
    cout << (meanT >= 10.0 ? setw(5) : setw(6)) << fixed << setprecision(2) << meanT << "|\n";

    cout << "NormTurn   |";
    double sumN = 0;
    for (int p = 0; p < process_count; ++p) {
        cout << setw(5) << fixed << setprecision(2) << normTurn[p] << "|";
        sumN += normTurn[p];
    }
    double meanN = sumN / process_count;
    cout << (meanN >= 10.0 ? setw(5) : setw(6)) << fixed << setprecision(2) << meanN << "|\n";
}
