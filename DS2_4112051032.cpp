#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;


struct Process{
    int ID;
    int atime;//arrival
    int etime;//execution
    int priority;
    int remain;
    int complete;
};

bool compareprocesses(const Process& p1, const Process& p2) {
    if (p1.priority != p2.priority) {
        return p1.priority > p2.priority;
    }
    return p1.atime < p2.atime;
}

int main() {
    ifstream inFile("testcase2.txt");
    ofstream outFile("ans2.txt");
    
    int testCases;
    inFile >> testCases;
    
    for (int t = 0; t < testCases; t++) {
        int n;
        inFile >> n;  // process數量
        vector<Process> processes(n);

        for (int i = 0; i < n; i++) {
            inFile >> processes[i].ID >> processes[i].atime 
                     >> processes[i].etime >> processes[i].priority;
            processes[i].remain = processes[i].etime;
            processes[i].complete = 0;
        }

        int time=0;
        int runningIndex = -1;
        int counter=0;

        while(counter<n){
            vector<int> readyIndices;//排隊執行

            for (int i = 0; i < n; i++){
                if(processes[i].atime <= time && processes[i].remain > 0){
                    readyIndices.push_back(i);
                }
            }

            if(readyIndices.empty()){
                time++;
                continue;
            }


            if(runningIndex != -1 && processes[runningIndex].remain > 0 && processes[runningIndex].atime <= time) {
                int candidate = runningIndex;
                bool preempt = false;
                for (int i = 0; i < readyIndices.size(); i++){
                    int idx = readyIndices[i];
                    if(processes[idx].priority > processes[runningIndex].priority){
                        if(processes[idx].priority > processes[candidate].priority)
                            candidate = idx;
                        preempt = true;
                    }
                }
                if(preempt)
                    runningIndex = candidate;
            } else {
                int candidate = readyIndices[0];//candidate的功能在於儲存另一優先級，並比較原本的優先級是不是比較高
                for (int i = 0; i < readyIndices.size(); i++){
                    int idx = readyIndices[i];
                    if(processes[idx].priority > processes[candidate].priority){
                        candidate = idx;
                    } else if(processes[idx].priority == processes[candidate].priority){
                        if(processes[idx].atime < processes[candidate].atime)
                            candidate = idx;
                    }
                }
                runningIndex = candidate;
            }

            processes[runningIndex].remain--;//執行1秒

            if(processes[runningIndex].remain == 0){//停止
                processes[runningIndex].complete = time + 1;
                counter++;
                runningIndex = -1; 
            }
            time++;
        }

        vector<Process> finished = processes;
        sort(finished.begin(), finished.end(), [](const Process &a, const Process &b){
            return a.complete < b.complete;
        });

        for (int i = 0; i < finished.size(); i++){
            outFile << finished[i].ID << " " << finished[i].complete << "\n";
        }
    }

    inFile.close();
    outFile.close();
    return 0;
}
