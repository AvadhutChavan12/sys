#include <iostream>
using namespace std;

int main() {
    int n, m;
    cout << "Enter number of processes and resources: ";
    cin >> n >> m;

    int alloc[n][m], max[n][m], avail[m], need[n][m];

    cout << "Enter Allocation Matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> alloc[i][j];

    cout << "Enter Maximum Matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> max[i][j];

    cout << "Enter Available Resources:\n";
    for (int j = 0; j < m; j++)
        cin >> avail[j];

    // Calculate need matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    int work[m], safe[n], count = 0;
    bool finish[n] = {false};

    for (int i = 0; i < m; i++)
        work[i] = avail[i];

    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < m; j++)
                    if (need[i][j] > work[j]) break;

                if (j == m) {
                    for (int k = 0; k < m; k++)
                        work[k] += alloc[i][k];

                    safe[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            cout << "System is not in a safe state.\n";
            return 0;
        }
    }

    cout << "System is in a safe state.\nSafe Sequence: ";
    for (int i = 0; i < n; i++)
        cout << "P" << safe[i] << (i == n - 1 ? "\n" : " -> ");

    return 0;
}
