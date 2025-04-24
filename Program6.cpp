#include <iostream>
#include <vector>
#include <climits>
using namespace std;

void firstFit(vector<int> blockSize, vector<int>& processSize, int m, int n) {
    vector<int> allocation(n, -1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }
    cout << "\nFirst Fit Allocation:\n";
    for (int i = 0; i < n; i++)
        if (allocation[i] != -1)
            cout << "Process " << i + 1 << " is allocated to Block " << allocation[i] + 1 << endl;
        else
            cout << "Process " << i + 1 << " is not allocated\n";
}

void bestFit(vector<int> blockSize, vector<int>& processSize, int m, int n) {
    vector<int> allocation(n, -1);
    for (int i = 0; i < n; i++) {
        int bestIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (bestIdx == -1 || blockSize[bestIdx] > blockSize[j])
                    bestIdx = j;
            }
        }
        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
        }
    }
    cout << "\nBest Fit Allocation:\n";
    for (int i = 0; i < n; i++)
        if (allocation[i] != -1)
            cout << "Process " << i + 1 << " is allocated to Block " << allocation[i] + 1 << endl;
        else
            cout << "Process " << i + 1 << " is not allocated\n";
}

void nextFit(vector<int> blockSize, vector<int>& processSize, int m, int n) {
    vector<int> allocation(n, -1);
    int j = 0;
    for (int i = 0; i < n; i++) {
        int count = 0;
        while (count < m) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
            j = (j + 1) % m;
            count++;
        }
    }
    cout << "\nNext Fit Allocation:\n";
    for (int i = 0; i < n; i++)
        if (allocation[i] != -1)
            cout << "Process " << i + 1 << " is allocated to Block " << allocation[i] + 1 << endl;
        else
            cout << "Process " << i + 1 << " is not allocated\n";
}

void worstFit(vector<int> blockSize, vector<int>& processSize, int m, int n) {
    vector<int> allocation(n, -1);
    for (int i = 0; i < n; i++) {
        int worstIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (worstIdx == -1 || blockSize[worstIdx] < blockSize[j])
                    worstIdx = j;
            }
        }
        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            blockSize[worstIdx] -= processSize[i];
        }
    }
    cout << "\nWorst Fit Allocation:\n";
    for (int i = 0; i < n; i++)
        if (allocation[i] != -1)
            cout << "Process " << i + 1 << " is allocated to Block " << allocation[i] + 1 << endl;
        else
            cout << "Process " << i + 1 << " is not allocated\n";
}

int main() {
    int m, n, choice;
    
    cout << "Enter number of memory blocks and processes: ";
    cin >> m >> n;

    vector<int> originalBlockSize(m), processSize(n);

    cout << "Enter memory block sizes:\n";
    for (int i = 0; i < m; i++)
        cin >> originalBlockSize[i];

    cout << "Enter process sizes:\n";
    for (int i = 0; i < n; i++)
        cin >> processSize[i];

    do {
        cout << "\nMenu:\n";
        cout << "1. First Fit Allocation\n";
        cout << "2. Best Fit Allocation\n";
        cout << "3. Next Fit Allocation\n";
        cout << "4. Worst Fit Allocation\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Always use a fresh copy of the original block sizes
        vector<int> blockSize = originalBlockSize;

        switch(choice) {
            case 1:
                firstFit(blockSize, processSize, m, n);
                break;
            case 2:
                bestFit(blockSize, processSize, m, n);
                break;
            case 3:
                nextFit(blockSize, processSize, m, n);
                break;
            case 4:
                worstFit(blockSize, processSize, m, n);
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }

    } while(choice != 5);

    return 0;
}
