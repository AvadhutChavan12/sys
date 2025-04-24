#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

void printFrames(const vector<int>& frames) {
    for (int f : frames) cout << f << " ";
    cout << endl;
}

void fcfs(const vector<int>& pages, int capacity) {
    vector<int> frames;
    int faults = 0;
    for (int p : pages) {
        if (find(frames.begin(), frames.end(), p) == frames.end()) {
            if (frames.size() == capacity) frames.erase(frames.begin());
            frames.push_back(p);
            faults++;
        }
    }
    cout << "FCFS Page Faults: " << faults << endl;
}

void lru(const vector<int>& pages, int capacity) {
    vector<int> frames;
    unordered_map<int, int> lastUsed;
    int faults = 0;
    for (int i = 0; i < pages.size(); i++) {
        int p = pages[i];
        if (find(frames.begin(), frames.end(), p) == frames.end()) {
            if (frames.size() == capacity) {
                int lruIndex = 0, minTime = i;
                for (int j = 0; j < frames.size(); j++) {
                    if (lastUsed[frames[j]] < minTime) {
                        minTime = lastUsed[frames[j]];
                        lruIndex = j;
                    }
                }
                frames[lruIndex] = p;
            } else {
                frames.push_back(p);
            }
            faults++;
        }
        lastUsed[p] = i;
    }
    cout << "LRU Page Faults: " << faults << endl;
}

void optimal(const vector<int>& pages, int capacity) {
    vector<int> frames;
    int faults = 0;
    for (int i = 0; i < pages.size(); i++) {
        int p = pages[i];
        if (find(frames.begin(), frames.end(), p) == frames.end()) {
            if (frames.size() == capacity) {
                int farthest = i + 1, idx = -1;
                for (int j = 0; j < frames.size(); j++) {
                    int k;
                    for (k = i + 1; k < pages.size(); k++)
                        if (pages[k] == frames[j]) break;
                    if (k > farthest) {
                        farthest = k;
                        idx = j;
                    }
                }
                if (idx == -1) idx = 0;
                frames[idx] = p;
            } else {
                frames.push_back(p);
            }
            faults++;
        }
    }
    cout << "Optimal Page Faults: " << faults << endl;
}

int main() {
    int n, cap, choice;
    cout << "Enter number of pages: ";
    cin >> n;

    vector<int> pages(n);
    cout << "Enter page reference string:\n";
    for (int i = 0; i < n; i++) cin >> pages[i];

    cout << "Enter number of frames: ";
    cin >> cap;

    do {
        cout << "\nMenu:\n1. FCFS\n2. LRU\n3. Optimal\n4. Exit\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: fcfs(pages, cap); break;
            case 2: lru(pages, cap); break;
            case 3: optimal(pages, cap); break;
            case 4: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 4);

    return 0;
}
