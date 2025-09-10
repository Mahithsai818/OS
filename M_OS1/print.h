#ifndef PRINT_H
#define PRINT_H

#include <vector>
#include <tuple>
#include <string>

using namespace std;

// Symbols for operations
extern const string TRACE;
extern const string SHOW_STATISTICS;
extern const string ALGORITHMS[11];

// Print helpers
void clear_timeline(int last_instant, int process_count, vector<vector<char>>& timeline);

// Printing trace diagram
void printTimeline(
    const vector<tuple<string,int,int>>& processes,
    int last_instant,
    int process_count,
    const vector<vector<char>>& timeline,
    int algorithm_index
);

// Printing statistics
void printStats(
    const vector<pair<string,int>>& algorithmsList,
    int algorithm_index,
    const vector<tuple<string,int,int>>& processes,
    int process_count,
    const vector<int>& finishTime,
    const vector<int>& turnAroundTime,
    const vector<float>& normTurn
);

#endif // PRINT_H
