#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
using namespace std;

void simulate_cp() {
    char source[100], destination[100];
    cout << "Enter source file: ";
    cin >> source;
    cout << "Enter destination file: ";
    cin >> destination;

    pid_t pid = fork();
    if (pid == 0) {
        cout << "Child (cp) PID: " << getpid() << endl;
        execl("/bin/cp", "cp", source, destination, NULL);
        perror("execl failed");
        exit(1);
    } else {
        wait(NULL);
        cout << "Parent (cp): Copy operation complete\n";
    }
}



void simulate_grep() {
    char word[100], file[100];
    cout << "Enter word to search: ";
    cin >> word;
    cout << "Enter file to search in: ";
    cin >> file;

    pid_t pid = fork();
    if (pid == 0) {
        cout << "Child (grep) PID: " << getpid() << endl;

        // FIXED: use execlp so it finds grep in PATH
        execlp("grep", "grep", word, file, NULL);

        // Only runs if exec fails
        perror("execlp failed");
        exit(1);
    } else {
        wait(NULL);
        cout << "Parent (grep): Grep operation complete\n";
    }
}

int main() {
    int choice;
    do {
        cout << "\nLinux Command Simulation Menu:\n";
        cout << "1. Simulate cp command\n";
        cout << "2. Simulate grep command\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: simulate_cp(); break;
            case 2: simulate_grep(); break;
            case 3: cout << "Exiting...\n"; exit(0);
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 3);

    return 0;
}