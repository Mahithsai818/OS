
// void fillInWaitTime(){
//     for (int i = 0; i < process_count; i++)
//     {
//         int arrivalTime = getArrivalTime(processes[i]);
//         for (int k = arrivalTime; k < finishTime[i]; k++)
//         {
//             if (timeline[k][i] != '*')
//                 timeline[k][i] = '.';
//         }
//     }
// }

// void firstComeFirstServe()
// {
//     int time = getArrivalTime(processes[0]);
//     for (int i = 0; i < process_count; i++)
//     {
//         int processIndex = i;
//         int arrivalTime = getArrivalTime(processes[i]);
//         int serviceTime = getServiceTime(processes[i]);

//         finishTime[processIndex] = (time + serviceTime);
//         turnAroundTime[processIndex] = (finishTime[processIndex] - arrivalTime);
//         normTurn[processIndex] = (turnAroundTime[processIndex] * 1.0 / serviceTime);

//         for (int j = time; j < finishTime[processIndex]; j++)
//             timeline[j][processIndex] = '*';
//         for (int j = arrivalTime; j < time; j++)
//             timeline[j][processIndex] = '.';
//         time += serviceTime;
//     }
// }

// void roundRobin(int originalQuantum)
// {
//     queue<pair<int,int>>q;
//     int j=0;
//     if(getArrivalTime(processes[j])==0){
//         q.push(make_pair(j,getServiceTime(processes[j])));
//         j++;
//     }
//     int currentQuantum = originalQuantum;
//     for(int time =0;time<last_instant;time++){
//         if(!q.empty()){
//             int processIndex = q.front().first;
//             q.front().second = q.front().second-1;
//             int remainingServiceTime = q.front().second;
//             int arrivalTime = getArrivalTime(processes[processIndex]);
//             int serviceTime = getServiceTime(processes[processIndex]);
//             currentQuantum--;
//             timeline[time][processIndex]='*';
//             while(j<process_count && getArrivalTime(processes[j])==time+1){
//                 q.push(make_pair(j,getServiceTime(processes[j])));
//                 j++;
//             }

//             if(currentQuantum==0 && remainingServiceTime==0){
//                 finishTime[processIndex]=time+1;
//                 turnAroundTime[processIndex] = (finishTime[processIndex] - arrivalTime);
//                 normTurn[processIndex] = (turnAroundTime[processIndex] * 1.0 / serviceTime);
//                 currentQuantum=originalQuantum;
//                 q.pop();
//             }else if(currentQuantum==0 && remainingServiceTime!=0){
//                 q.pop();
//                 q.push(make_pair(processIndex,remainingServiceTime));
//                 currentQuantum=originalQuantum;
//             }else if(currentQuantum!=0 && remainingServiceTime==0){
//                 finishTime[processIndex]=time+1;
//                 turnAroundTime[processIndex] = (finishTime[processIndex] - arrivalTime);
//                 normTurn[processIndex] = (turnAroundTime[processIndex] * 1.0 / serviceTime);
//                 q.pop();
//                 currentQuantum=originalQuantum;
//             }
//         }
//         while(j<process_count && getArrivalTime(processes[j])==time+1){
//             q.push(make_pair(j,getServiceTime(processes[j])));
//             j++;
//         }
//     }
//     fillInWaitTime();
// }

// void shortestProcessNext()
// {
//     priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // pair of service time and index
//     int j = 0;
//     for (int i = 0; i < last_instant; i++)
//     {
//         while(j<process_count && getArrivalTime(processes[j]) <= i){
//             pq.push(make_pair(getServiceTime(processes[j]), j));
//             j++;
//         }
//         if (!pq.empty())
//         {
//             int processIndex = pq.top().second;
//             int arrivalTime = getArrivalTime(processes[processIndex]);
//             int serviceTime = getServiceTime(processes[processIndex]);
//             pq.pop();

//             int temp = arrivalTime;
//             for (; temp < i; temp++)
//                 timeline[temp][processIndex] = '.';

//             temp = i;
//             for (; temp < i + serviceTime; temp++)
//                 timeline[temp][processIndex] = '*';

//             finishTime[processIndex] = (i + serviceTime);
//             turnAroundTime[processIndex] = (finishTime[processIndex] - arrivalTime);
//             normTurn[processIndex] = (turnAroundTime[processIndex] * 1.0 / serviceTime);
//             i = temp - 1;
//         }
//     }
// }

// void shortestRemainingTime()
// {
//     priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
//     int j = 0;
//     for (int i = 0; i < last_instant; i++)
//     {
//         while(j<process_count &&getArrivalTime(processes[j]) == i){
//             pq.push(make_pair(getServiceTime(processes[j]), j));
//             j++;
//         }
//         if (!pq.empty())
//         {
//             int processIndex = pq.top().second;
//             int remainingTime = pq.top().first;
//             pq.pop();
//             int serviceTime = getServiceTime(processes[processIndex]);
//             int arrivalTime = getArrivalTime(processes[processIndex]);
//             timeline[i][processIndex] = '*';

//             if (remainingTime == 1) // process finished
//             {
//                 finishTime[processIndex] = i + 1;
//                 turnAroundTime[processIndex] = (finishTime[processIndex] - arrivalTime);
//                 normTurn[processIndex] = (turnAroundTime[processIndex] * 1.0 / serviceTime);
//             }
//             else
//             {
//                 pq.push(make_pair(remainingTime - 1, processIndex));
//             }
//         }
//     }
//     fillInWaitTime();
// }

// void highestResponseRatioNext()
// {

//     // Vector of tuple <process_name, process_response_ratio, time_in_service> for processes that are in the ready queue
//     vector<tuple<string, double, int>> present_processes;
//     int j=0;
//     for (int current_instant = 0; current_instant < last_instant; current_instant++)
//     {
//         while(j<process_count && getArrivalTime(processes[j])<=current_instant){
//             present_processes.push_back(make_tuple(getProcessName(processes[j]), 1.0, 0));
//             j++;
//         }
//         // Calculate response ratio for every process
//         for (auto &proc : present_processes)
//         {
//             string process_name = get<0>(proc);
//             int process_index = processToIndex[process_name];
//             int wait_time = current_instant - getArrivalTime(processes[process_index]);
//             int service_time = getServiceTime(processes[process_index]);
//             get<1>(proc) = calculate_response_ratio(wait_time, service_time);
//         }

//         // Sort present processes by highest to lowest response ratio
//         sort(all(present_processes), descendingly_by_response_ratio);

//         if (!present_processes.empty())
//         {
//             int process_index = processToIndex[get<0>(present_processes[0])];
//             while(current_instant<last_instant && get<2>(present_processes[0]) != getServiceTime(processes[process_index])){
//                 timeline[current_instant][process_index]='*';
//                 current_instant++;
//                 get<2>(present_processes[0])++;
//             }
//             current_instant--;
//             present_processes.erase(present_processes.begin());
//             finishTime[process_index] = current_instant + 1;
//             turnAroundTime[process_index] = finishTime[process_index] - getArrivalTime(processes[process_index]);
//             normTurn[process_index] = (turnAroundTime[process_index] * 1.0 / getServiceTime(processes[process_index]));
//         }
//     }
//     fillInWaitTime();
// }

// void feedbackQ1()
// {
//     priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; //pair of priority level and process index
//     unordered_map<int,int>remainingServiceTime; //map from process index to the remaining service time
//     int j=0;
//     if(getArrivalTime(processes[0])==0){
//         pq.push(make_pair(0,j));
//         remainingServiceTime[j]=getServiceTime(processes[j]);
//         j++;
//     }
//     for(int time =0;time<last_instant;time++){
//         if(!pq.empty()){
//             int priorityLevel = pq.top().first;
//             int processIndex =pq.top().second;
//             int arrivalTime = getArrivalTime(processes[processIndex]);
//             int serviceTime = getServiceTime(processes[processIndex]);
//             pq.pop();
//             while(j<process_count && getArrivalTime(processes[j])==time+1){
//                     pq.push(make_pair(0,j));
//                     remainingServiceTime[j]=getServiceTime(processes[j]);
//                     j++;
//             }
//             remainingServiceTime[processIndex]--;
//             timeline[time][processIndex]='*';
//             if(remainingServiceTime[processIndex]==0){
//                 finishTime[processIndex]=time+1;
//                 turnAroundTime[processIndex] = (finishTime[processIndex] - arrivalTime);
//                 normTurn[processIndex] = (turnAroundTime[processIndex] * 1.0 / serviceTime);
//             }else{
//                 if(pq.size()>=1)
//                     pq.push(make_pair(priorityLevel+1,processIndex));
//                 else
//                     pq.push(make_pair(priorityLevel,processIndex));
//             }
//         }
//         while(j<process_count && getArrivalTime(processes[j])==time+1){
//                 pq.push(make_pair(0,j));
//                 remainingServiceTime[j]=getServiceTime(processes[j]);
//                 j++;
//         }
//     }
//     fillInWaitTime();
// }

// void feedbackQ2i()
// {
//     priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; //pair of priority level and process index
//     unordered_map<int,int>remainingServiceTime; //map from process index to the remaining service time
//     int j=0;
//     if(getArrivalTime(processes[0])==0){
//         pq.push(make_pair(0,j));
//         remainingServiceTime[j]=getServiceTime(processes[j]);
//         j++;
//     }
//     for(int time =0;time<last_instant;time++){
//         if(!pq.empty()){
//             int priorityLevel = pq.top().first;
//             int processIndex =pq.top().second;
//             int arrivalTime = getArrivalTime(processes[processIndex]);
//             int serviceTime = getServiceTime(processes[processIndex]);
//             pq.pop();
//             while(j<process_count && getArrivalTime(processes[j])<=time+1){
//                     pq.push(make_pair(0,j));
//                     remainingServiceTime[j]=getServiceTime(processes[j]);
//                     j++;
//             }

//             int currentQuantum = pow(2,priorityLevel);
//             int temp = time;
//             while(currentQuantum && remainingServiceTime[processIndex]){
//                 currentQuantum--;
//                 remainingServiceTime[processIndex]--;
//                 timeline[temp++][processIndex]='*';
//             }

//             if(remainingServiceTime[processIndex]==0){
//                 finishTime[processIndex]=temp;
//                 turnAroundTime[processIndex] = (finishTime[processIndex] - arrivalTime);
//                 normTurn[processIndex] = (turnAroundTime[processIndex] * 1.0 / serviceTime);
//             }else{
//                 if(pq.size()>=1)
//                     pq.push(make_pair(priorityLevel+1,processIndex));
//                 else
//                     pq.push(make_pair(priorityLevel,processIndex));
//             }
//             time = temp-1;
//         }
//         while(j<process_count && getArrivalTime(processes[j])<=time+1){
//                 pq.push(make_pair(0,j));
//                 remainingServiceTime[j]=getServiceTime(processes[j]);
//                 j++;
//         }
//     }
//     fillInWaitTime();
// }

// void aging(int originalQuantum)
// {
//     vector<tuple<int,int,int>>v; //tuple of priority level, process index and total waiting time
//     int j=0,currentProcess=-1;
//     for(int time =0;time<last_instant;time++){
//         while(j<process_count && getArrivalTime(processes[j])<=time){
//             v.push_back(make_tuple(getPriorityLevel(processes[j]),j,0));
//             j++;
//         }

//         for(int i=0;i<v.size();i++){
//             if(get<1>(v[i])==currentProcess){
//                 get<2>(v[i])=0;
//                 get<0>(v[i])=getPriorityLevel(processes[currentProcess]);
//             }
//             else{
//                 get<0>(v[i])++;
//                 get<2>(v[i])++;
//             }
//         }
//         sort(v.begin(),v.end(),byPriorityLevel);
//         currentProcess=get<1>(v[0]);
//         int currentQuantum = originalQuantum;
//         while(currentQuantum-- && time<last_instant){
//             timeline[time][currentProcess]='*';
//             time++;
//         }
//         time--;
//     }
//     fillInWaitTime();
// }

// void priorityScheduling() {
//   priority_queue<
//     tuple<int,int,int>,          
//     vector<tuple<int,int,int>>,
//     greater<tuple<int,int,int>>
//   > pq;
//   int j = 0;
//   for (int t = 0; t < last_instant; t++) {
//     while (j < process_count && getArrivalTime(processes[j]) == t)
//       pq.push(make_tuple(get<2>(processes[j]), getArrivalTime(processes[j]), j++));
//     if (!pq.empty()) {
//       auto top = pq.top(); pq.pop();
//         int prio = get<0>(top);
//         int at   = get<1>(top);
//         int idx  = get<2>(top);
//       timeline[t][idx] = '*';
//       for (int u = t+1; u < t + getServiceTime(processes[idx]); u++)
//         timeline[u][idx] = '*';
//       finishTime[idx] = t + getServiceTime(processes[idx]);
//       turnAroundTime[idx] = finishTime[idx] - at;
//       normTurn[idx] = turnAroundTime[idx] * 1.0 / getServiceTime(processes[idx]);
//       t += getServiceTime(processes[idx]) - 1;
//     }
//   }
//   fillInWaitTime();
// }





// void printAlgorithm(int algorithm_index)
// {
//     int algorithm_id = algorithms[algorithm_index].first - '0';
//     if(algorithm_id==2)
//         cout << ALGORITHMS[algorithm_id] <<algorithms[algorithm_index].second <<endl;
//     else
//         cout << ALGORITHMS[algorithm_id] << endl;
// }

// void printProcesses()
// {
//     cout << "Process    ";
//     for (int i = 0; i < process_count; i++)
//         cout << "|  " << get<0>(processes[i]) << "  ";
//     cout << "|\n";
// }
// void printArrivalTime()
// {
//     cout << "Arrival    ";
//     for (int i = 0; i < process_count; i++)
//         printf("|%3d  ",get<1>(processes[i]));
//     cout<<"|\n";
// }
// void printServiceTime()
// {
//     cout << "Service    |";
//     for (int i = 0; i < process_count; i++)
//         printf("%3d  |",get<2>(processes[i]));
//     cout << " Mean|\n";
// }
// void printFinishTime()
// {
//     cout << "Finish     ";
//     for (int i = 0; i < process_count; i++)
//         printf("|%3d  ",finishTime[i]);
//     cout << "|-----|\n";
// }
// void printTurnAroundTime()
// {
//     cout << "Turnaround |";
//     int sum = 0;
//     for (int i = 0; i < process_count; i++)
//     {
//         printf("%3d  |",turnAroundTime[i]);
//         sum += turnAroundTime[i];
//     }
//     if((1.0 * sum / turnAroundTime.size())>=10)
// 		printf("%2.2f|\n",(1.0 * sum / turnAroundTime.size()));
//     else
// 	 	printf(" %2.2f|\n",(1.0 * sum / turnAroundTime.size()));
// }

// void printNormTurn()
// {
//     cout << "NormTurn   |";
//     float sum = 0;
//     for (int i = 0; i < process_count; i++)
//     {
//         if( normTurn[i]>=10 )
//             printf("%2.2f|",normTurn[i]);
//         else
//             printf(" %2.2f|",normTurn[i]);
//         sum += normTurn[i];
//     }

//     if( (1.0 * sum / normTurn.size()) >=10 )
//         printf("%2.2f|\n",(1.0 * sum / normTurn.size()));
// 	else
//         printf(" %2.2f|\n",(1.0 * sum / normTurn.size()));
// }
// void printStats(int algorithm_index)
// {
//     printAlgorithm(algorithm_index);
//     printProcesses();
//     printArrivalTime();
//     printServiceTime();
//     printFinishTime();
//     printTurnAroundTime();
//     printNormTurn();
// }

// void printTimeline(int algorithm_index)
// {
//     for (int i = 0; i <= last_instant; i++)
//         cout << i % 10<<" ";
//     cout <<"\n";
//     cout << "------------------------------------------------\n";
//     for (int i = 0; i < process_count; i++)
//     {
//         cout << get<0>(processes[i]) << "     |";
//         for (int j = 0; j < last_instant; j++)
//         {
//             cout << timeline[j][i]<<"|";
//         }
//         cout << " \n";
//     }
//     cout << "------------------------------------------------\n";
// }