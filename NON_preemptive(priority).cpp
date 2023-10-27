#include <iostream>
#include <algorithm>
using namespace std;

class NonPreemptivePriorityCPUSchedulingAlgorithm
{
    int *burstTime;
    int *priority;
    int *arrivalTime;
    string *processId;
    int numberOfProcess;

public:
    void getProcessData()
    {
        cout << "Enter the number of Processes for Scheduling: ";
        cin >> numberOfProcess;
        burstTime = new int[numberOfProcess];
        priority = new int[numberOfProcess];
        arrivalTime = new int[numberOfProcess];
        processId = new string[numberOfProcess];
        string st = "P";
        for (int i = 0; i < numberOfProcess; i++)
        {
            processId[i] = st + to_string(i);
            cout << "Enter the burst time for Process - " << i << ": ";
            cin >> burstTime[i];
            cout << "Enter the arrival time for Process - " << i << ": ";
            cin >> arrivalTime[i];
            cout << "Enter the priority for Process - " << i << ": ";
            cin >> priority[i];
        }
    }

    void sortAccordingArrivalTimeAndPriority(int *at, int *bt, int *prt, string *pid)
    {
        int temp;
        string stemp;
        for (int i = 0; i < numberOfProcess; i++)
        {
            for (int j = 0; j < numberOfProcess - i - 1; j++)
            {
                if (at[j] > at[j + 1])
                {
                    temp = at[j];
                    at[j] = at[j + 1];
                    at[j + 1] = temp;

                    temp = bt[j];
                    bt[j] = bt[j + 1];
                    bt[j + 1] = temp;

                    temp = prt[j];
                    prt[j] = prt[j + 1];
                    prt[j + 1] = temp;

                    stemp = pid[j];
                    pid[j] = pid[j + 1];
                    pid[j + 1] = stemp;
                }
                if (at[j] == at[j + 1])
                {
                    if (prt[j] > prt[j + 1])
                    {
                        temp = at[j];
                        at[j] = at[j + 1];
                        at[j + 1] = temp;

                        temp = bt[j];
                        bt[j] = bt[j + 1];
                        bt[j + 1] = temp;

                        temp = prt[j];
                        prt[j] = prt[j + 1];
                        prt[j + 1] = temp;

                        stemp = pid[j];
                        pid[j] = pid[j + 1];
                        pid[j + 1] = stemp;
                    }
                }
            }
        }
    }

    void priorityNonPreemptiveAlgorithm()
    {
        int *finishTime = new int[numberOfProcess];
        int *bt = new int[numberOfProcess];
        int *at = new int[numberOfProcess];
        int *prt = new int[numberOfProcess];
        string *pid = new string[numberOfProcess];
        int *waitingTime = new int[numberOfProcess];
        int *turnAroundTime = new int[numberOfProcess];

        copy(burstTime, burstTime + numberOfProcess, bt);
        copy(arrivalTime, arrivalTime + numberOfProcess, at);
        copy(priority, priority + numberOfProcess, prt);
        copy(processId, processId + numberOfProcess, pid);

        sortAccordingArrivalTimeAndPriority(at, bt, prt, pid);

        finishTime[0] = at[0] + bt[0];
        turnAroundTime[0] = finishTime[0] - at[0];
        waitingTime[0] = turnAroundTime[0] - bt[0];

        for (int i = 1; i < numberOfProcess; i++)
        {
            finishTime[i] = bt[i] + finishTime[i - 1];
            turnAroundTime[i] = finishTime[i] - at[i];
            waitingTime[i] = turnAroundTime[i] - bt[i];
        }

        float sum = 0;
        for (int i = 0; i < numberOfProcess; i++)
        {
            sum += waitingTime[i];
        }
        float averageWaitingTime = sum / numberOfProcess;

        sum = 0;
        for (int i = 0; i < numberOfProcess; i++)
        {
            sum += turnAroundTime[i];
        }
        float averageTurnAroundTime = sum / numberOfProcess;

        cout << "Priority Scheduling Algorithm : " << endl;
        cout << "ProcessId   BurstTime   ArrivalTime   Priority   FinishTime   WaitingTime   TurnAroundTime" << endl;
        for (int i = 0; i < numberOfProcess; i++)
        {
            cout << processId[i] << "          " << bt[i] << "           " << at[i] << "             " << prt[i] << "          " << finishTime[i] << "           " << waitingTime[i] << "            " << turnAroundTime[i] << endl;
        }

        cout << "Average               " << averageWaitingTime << "           " << averageTurnAroundTime << endl;

        delete[] bt;
        delete[] at;
        delete[] prt;
        delete[] pid;
        delete[] finishTime;
        delete[] waitingTime;
        delete[] turnAroundTime;
    }
};

int main()
{
    NonPreemptivePriorityCPUSchedulingAlgorithm obj;
    obj.getProcessData();
    obj.priorityNonPreemptiveAlgorithm();
    return 0;
}














#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Process {
    int id;
    int burstTime;
    int priority;

    // Define comparison operator for priority queue
    bool operator<(const Process& other) const {
        return priority > other.priority; // Higher priority processes come first
    }
};

void priorityScheduling(vector<Process>& processes) {
    priority_queue<Process> pq;

    // Push processes into the priority queue
    for (const auto& process : processes) {
        pq.push(process);
    }

    float totalWaitingTime = 0, totalTurnaroundTime = 0;
    cout << "Process Execution Order: ";

    while (!pq.empty()) {
        Process currentProcess = pq.top();
        pq.pop();

        cout << currentProcess.id << " ";

        totalWaitingTime += totalTurnaroundTime;
        totalTurnaroundTime += currentProcess.burstTime;
    }

    cout << endl;

    float averageWaitingTime = totalWaitingTime / processes.size();
    float averageTurnaroundTime = totalTurnaroundTime / processes.size();

    cout << "Average Waiting Time: " << averageWaitingTime << endl;
    cout << "Average Turnaround Time: " << averageTurnaroundTime << endl;
}

int main() {
    int numProcesses;
    cout << "Enter the number of processes: ";
    cin >> numProcesses;

    vector<Process> processes(numProcesses);

    for (int i = 0; i < numProcesses; ++i) {
        processes[i].id = i + 1;
        cout << "Enter Burst Time for Process " << processes[i].id << ": ";
        cin >> processes[i].burstTime;
        cout << "Enter Priority for Process " << processes[i].id << ": ";
        cin >> processes[i].priority;
    }

    priorityScheduling(processes);

    return 0;
}
