#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
};

struct CompareBurstTime {
    bool operator()(const Process& p1, const Process& p2) {
        return p1.burstTime > p2.burstTime;
    }
};

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        cout << "Enter arrival time for Process " << i + 1 << ": ";
        cin >> processes[i].arrivalTime;
        cout << "Enter burst time for Process " << i + 1 << ": ";
        cin >> processes[i].burstTime;
        processes[i].remainingTime = processes[i].burstTime;
    }

    int currentTime = 0;
    priority_queue<Process, vector<Process>, CompareBurstTime> readyQueue;
    vector<int> completionTime(n);
    vector<int> waitingTime(n);

    int completed = 0;
    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0) {
                readyQueue.push(processes[i]);
            }
        }

        if (readyQueue.empty()) {
            currentTime++;
        } else {
            Process currentProcess = readyQueue.top();
            readyQueue.pop();

            currentProcess.remainingTime--;

            currentTime++;

            if (currentProcess.remainingTime == 0) {
                completed++;
                completionTime[currentProcess.id - 1] = currentTime;
                waitingTime[currentProcess.id - 1] = currentTime - currentProcess.arrivalTime - currentProcess.burstTime;
            } else {
                readyQueue.push(currentProcess);
            }
        }
    }

    // Calculate turnaround time
    vector<int> turnaroundTime(n);
    for (int i = 0; i < n; i++) {
        turnaroundTime[i] = completionTime[i] - processes[i].arrivalTime;
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
    cout << "Process\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time" << endl;
    for (int i = 0; i < n; i++) {
        cout << "P" << processes[i].id << "\t" << processes[i].arrivalTime << "\t\t" << processes[i].burstTime << "\t\t"
             << completionTime[i] << "\t\t" << waitingTime[i] << "\t\t" << turnaroundTime[i] << endl;
    }

    cout << "Average Waiting Time: " << averageWaitingTime << endl;
    cout << "Average Turnaround Time: " << averageTurnaroundTime << endl;

    return 0;
}
