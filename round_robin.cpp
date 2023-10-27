#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Process {
    int id;
    int burstTime;
    int remainingTime;
};

int main() {
    int n, timeQuantum;
    cout << "Enter the number of processes: ";
    cin >> n;
    
    cout << "Enter the time quantum: ";
    cin >> timeQuantum;

    vector<Process> processes(n);
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        cout << "Enter burst time for Process " << i + 1 << ": ";
        cin >> processes[i].burstTime;
        processes[i].remainingTime = processes[i].burstTime;
    }

    queue<Process> readyQueue;
    int currentTime = 0;
    vector<int> turnaroundTime(n);
    vector<int> waitingTime(n);

    while (!readyQueue.empty() || currentTime < n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].remainingTime > 0 && processes[i].burstTime > timeQuantum) {
                processes[i].remainingTime -= timeQuantum;
                currentTime += timeQuantum;
                readyQueue.push(processes[i]);
            } else if (processes[i].remainingTime > 0) {
                currentTime += processes[i].remainingTime;
                processes[i].remainingTime = 0;
                turnaroundTime[i] = currentTime;
            }
        }

        while (!readyQueue.empty() && processes[currentTime % n].remainingTime == 0) {
            readyQueue.pop();
        }
        
        if (!readyQueue.empty()) {
            readyQueue.push(processes[currentTime % n]);
        }
    }

    // Calculate waiting time
    for (int i = 0; i < n; i++) {
        waitingTime[i] = turnaroundTime[i] - processes[i].burstTime;
    }

    // Calculate average waiting time and turnaround time
    double totalWaitingTime = 0;
    double totalTurnaroundTime = 0;
    for (int i = 0; i < n; i++) {
        totalWaitingTime += waitingTime[i];
        totalTurnaroundTime += turnaroundTime[i];
    }
    double averageWaitingTime = totalWaitingTime / n;
    double averageTurnaroundTime = totalTurnaroundTime / n;

    // Display results
    cout << "Process\tBurst Time\tWaiting Time\tTurnaround Time" << endl;
    for (int i = 0; i < n; i++) {
        cout << "P" << processes[i].id << "\t" << processes[i].burstTime << "\t\t" << waitingTime[i] << "\t\t" << turnaroundTime[i] << endl;
    }

    cout << "Average Waiting Time: " << averageWaitingTime << endl;
    cout << "Average Turnaround Time: " << averageTurnaroundTime << endl;

    return 0;
}
