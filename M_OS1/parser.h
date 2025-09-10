#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include <bits/stdc++.h>

using namespace std;

string operation;
int last_instant, process_count;
vector<tuple<string,int,int>> processes;
vector<vector<char>>timeline;
unordered_map<string,int>processToIndex;


//Results

vector<int>finishTime;
vector<int>turnAroundTime;
vector<float>normTurn;
vector<pair<string, int>> algorithms;


void parse_algorithms(string algorithm_chunk)
{
    stringstream stream(algorithm_chunk);
    while (stream.good())
    {
        string temp_str;
        getline(stream, temp_str, ',');
        stringstream ss(temp_str);
        getline(ss, temp_str, '-');
        string algorithm_id = temp_str;
        getline(ss, temp_str, '-');
        int quantum = temp_str.size() >= 1 ? stoi(temp_str) : -1;
        algorithms.emplace_back( algorithm_id, quantum );
    }
}

void parse_processes()
{
    string process_chunk, process_name;
    int process_arrival_time, process_service_time;
    for(int i=0; i<process_count; i++)
    {
        cin >> process_chunk;

        stringstream stream(process_chunk);
        string temp_str;
        getline(stream, temp_str, ',');
        process_name = temp_str;
        getline(stream, temp_str, ',');
        process_arrival_time = stoi(temp_str);
        getline(stream, temp_str, ',');
        process_service_time = stoi(temp_str);

        processes.push_back( make_tuple(process_name, process_arrival_time, process_service_time) );
        processToIndex[process_name] = i;
    }
}

void parse()
{
    string algorithm_chunk;
    cin >> operation >> algorithm_chunk >> last_instant >> process_count;
    parse_algorithms(algorithm_chunk);
    parse_processes();
    finishTime.assign(process_count,0);
    turnAroundTime.assign(process_count,0);
    normTurn.assign(process_count,0.0f);
    timeline.assign(last_instant,vector<char>(process_count,' '));
    for(int i=0; i<last_instant; i++)
        for(int j=0; j<process_count; j++)
            timeline[i].push_back(' ');
}


#endif // PARSER_H_INCLUDED