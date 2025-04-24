#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

void fifo(vector<int> req, int head) {
    int seek = 0;
    for (int r : req) {
        seek += abs(head - r);
        head = r;
    }
    cout << "Total Seek Time (FIFO): " << seek << endl;
}

void sstf(vector<int> req, int head) {
    int seek = 0;
    vector<bool> visited(req.size(), false);
    for (int i = 0; i < req.size(); i++) {
        int minDist = 1e9, index = -1;
        for (int j = 0; j < req.size(); j++) {
            if (!visited[j] && abs(head - req[j]) < minDist) {
                minDist = abs(head - req[j]);
                index = j;
            }
        }
        seek += minDist;
        head = req[index];
        visited[index] = true;
    }
    cout << "Total Seek Time (SSTF): " << seek << endl;
}

void scan(vector<int> req, int head, int diskSize) {
    int seek = 0;
    vector<int> left, right;
    for (int r : req) {
        if (r < head) left.push_back(r);
        else right.push_back(r);
    }
    sort(left.begin(), left.end(), greater<int>());
    sort(right.begin(), right.end());

    for (int r : right) {
        seek += abs(head - r);
        head = r;
    }
    if (!left.empty()) {
        seek += abs(head - (diskSize - 1));
        head = diskSize - 1;
        for (int r : left) {
            seek += abs(head - r);
            head = r;
        }
    }
    cout << "Total Seek Time (SCAN): " << seek << endl;
}

void cscan(vector<int> req, int head, int diskSize) {
    int seek = 0;
    vector<int> left, right;
    for (int r : req) {
        if (r < head) left.push_back(r);
        else right.push_back(r);
    }
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    for (int r : right) {
        seek += abs(head - r);
        head = r;
    }
    if (!left.empty()) {
        seek += abs(head - (diskSize - 1)); // go to end
        seek += diskSize - 1;               // wrap to beginning
        head = 0;
        for (int r : left) {
            seek += abs(head - r);
            head = r;
        }
    }
    cout << "Total Seek Time (C-SCAN): " << seek << endl;
}

int main() {
    int n, head, diskSize, choice;
    vector<int> requests;

    cout << "Enter number of disk requests: ";
    cin >> n;
    requests.resize(n);

    cout << "Enter disk request queue:\n";
    for (int i = 0; i < n; i++) cin >> requests[i];

    cout << "Enter initial head position: ";
    cin >> head;

    cout << "Enter disk size (e.g., 200): ";
    cin >> diskSize;

    do {
        cout << "\nMenu:\n";
        cout << "1. FIFO\n2. SSTF\n3. SCAN\n4. C-SCAN\n5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: fifo(requests, head); break;
            case 2: sstf(requests, head); break;
            case 3: scan(requests, head, diskSize); break;
            case 4: cscan(requests, head, diskSize); break;
            case 5: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 5);

    return 0;
}
