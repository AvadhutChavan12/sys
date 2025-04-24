#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct Process {
    int pid;
    int bt;    // Burst Time
    int at;    // Arrival Time
    int priority;
    int wt;    // Waiting Time
    int tat;   // Turnaround Time
};

// Function to display process details
void display(vector<Process> &p) {
    float totalWT = 0, totalTAT = 0;
    cout << "\nPID\tAT\tBT\tWT\tTAT\n";
    for (auto &pr : p) {
        cout << pr.pid << "\t" << pr.at << "\t" << pr.bt << "\t" << pr.wt << "\t" << pr.tat << endl;
        totalWT += pr.wt;
        totalTAT += pr.tat;
    }
    cout << "Average Waiting Time: " << totalWT / p.size() << endl;
    cout << "Average Turnaround Time: " << totalTAT / p.size() << endl;
}

// FCFS Scheduling
void FCFS(vector<Process> p) {
    sort(p.begin(), p.end(), [](Process a, Process b) {
        return a.at < b.at;
    });

    int time = 0;
    for (int i = 0; i < p.size(); i++) {
        if (time < p[i].at)
            time = p[i].at;
        p[i].wt = time - p[i].at;
        time += p[i].bt;
        p[i].tat = p[i].wt + p[i].bt;
    }
    display(p);
}

// SJF Scheduling (Non-Preemptive)
void SJF(vector<Process> p) {
    int n = p.size();
    int complete = 0, time = 0;
    vector<bool> done(n, false);

    while (complete < n) {
        int idx = -1;
        int minBT = 1e9;
        for (int i = 0; i < n; i++) {
            if (!done[i] && p[i].at <= time && p[i].bt < minBT) {
                minBT = p[i].bt;
                idx = i;
            }
        }
        if (idx != -1) {
            p[idx].wt = time - p[idx].at;
            time += p[idx].bt;
            p[idx].tat = p[idx].wt + p[idx].bt;
            done[idx] = true;
            complete++;
        } else {
            time++;
        }
    }
    display(p);
}

// Round Robin Scheduling
void RoundRobin(vector<Process> p, int quantum) {
    int n = p.size();
    vector<int> remBT(n), wt(n, 0), tat(n, 0);
    for (int i = 0; i < n; i++) remBT[i] = p[i].bt;

    int time = 0;
    bool done;
    do {
        done = true;
        for (int i = 0; i < n; i++) {
            if (remBT[i] > 0) {
                done = false;
                if (remBT[i] > quantum) {
                    time += quantum;
                    remBT[i] -= quantum;
                } else {
                    time += remBT[i];
                    wt[i] = time - p[i].bt - p[i].at;
                    remBT[i] = 0;
                }
            }
        }
    } while (!done);

    for (int i = 0; i < n; i++) {
        p[i].wt = wt[i];
        p[i].tat = p[i].wt + p[i].bt;
    }
    display(p);
}

// Priority Scheduling (Non-Preemptive)
void PriorityScheduling(vector<Process> p) {
    sort(p.begin(), p.end(), [](Process a, Process b) {
        return (a.priority == b.priority) ? a.at < b.at : a.priority < b.priority;
    });

    int time = 0;
    for (int i = 0; i < p.size(); i++) {
        if (time < p[i].at)
            time = p[i].at;
        p[i].wt = time - p[i].at;
        time += p[i].bt;
        p[i].tat = p[i].wt + p[i].bt;
    }
    display(p);
}

// Input process data
vector<Process> inputProcesses(bool withPriority = false) {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    vector<Process> p(n);
    for (int i = 0; i < n; i++) {
        cout << "Process " << i + 1 << ":\n";
        p[i].pid = i + 1;
        cout << "Arrival Time: ";
        cin >> p[i].at;
        cout << "Burst Time: ";
        cin >> p[i].bt;
        if (withPriority) {
            cout << "Priority (Lower value = Higher priority): ";
            cin >> p[i].priority;
        }
    }
    return p;
}

// Main menu
int main() {
    int choice, quantum;
    while (true) {
        cout << "\nCPU Scheduling Algorithms:\n";
        cout << "1. FCFS\n2. SJF (Non-Preemptive)\n3. Round Robin\n4. Priority Scheduling\n5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 5) break;

        vector<Process> processes;
        switch (choice) {
            case 1:
                processes = inputProcesses();
                FCFS(processes);
                break;
            case 2:
                processes = inputProcesses();
                SJF(processes);
                break;
            case 3:
                processes = inputProcesses();
                cout << "Enter Time Quantum: ";
                cin >> quantum;
                RoundRobin(processes, quantum);
                break;
            case 4:
                processes = inputProcesses(true);
                PriorityScheduling(processes);
                break;
            default:
                cout << "Invalid choice.\n";
        }
    }
    return 0;
}

// SJF Scheduling (Preemptive - Shortest Remaining Time First)
struct Process {
    int pid;
    int at;   // Arrival Time
    int bt;   // Burst Time
    int rt;   // Remaining Time
    int wt;   // Waiting Time
    int tat;  // Turnaround Time
};

void display(const vector<Process>& p) {
    cout << "\nPID\tAT\tBT\tWT\tTAT\n";
    for (const auto& proc : p) {
        cout << proc.pid << "\t" << proc.at << "\t" << proc.bt
             << "\t" << proc.wt << "\t" << proc.tat << endl;
    }
}

void SJF_Preemptive(vector<Process> p) {
    int n = p.size();
    for (int i = 0; i < n; i++) {
        p[i].rt = p[i].bt;  // Initialize remaining time
    }

    int complete = 0, time = 0;
    int minRT = 1e9, idx = -1;
    bool found = false;

    while (complete < n) {
        minRT = 1e9;
        idx = -1;

        // Find process with shortest remaining time at current time
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].rt > 0 && p[i].rt < minRT) {
                minRT = p[i].rt;
                idx = i;
                found = true;
            }
        }

        if (!found) {
            time++;
            continue;
        }

        // Execute the process for 1 unit of time
        p[idx].rt--;
        time++;

        // If process is completed
        if (p[idx].rt == 0) {
            complete++;
            int finish_time = time;
            p[idx].tat = finish_time - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
        }

        found = false; // Reset for next time unit
    }

    display(p);
}
