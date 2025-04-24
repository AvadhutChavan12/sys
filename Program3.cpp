#include <iostream>
#include <unistd.h>
#include <cstring>
using namespace std;

int main() {
    int pipe1[2]; // Parent to Child
    int pipe2[2]; // Child to Parent
    char buffer[100];

    pipe(pipe1);
    pipe(pipe2);

    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        close(pipe1[1]); // Close write end of pipe1 (Parent → Child)
        close(pipe2[0]); // Close read end of pipe2 (Child → Parent)

        // Redirect stdin to read from pipe1, stdout to write to pipe2
        dup2(pipe1[0], STDIN_FILENO);
        dup2(pipe2[1], STDOUT_FILENO);

        close(pipe1[0]);
        close(pipe2[1]);

        // Read message from parent (via redirected stdin)
        string msg;
        getline(cin, msg);
        cout << "Child received: " << msg << endl;
        cout << "Hello Parent" << endl;
        cout.flush(); // Ensure the output is flushed to the pipe

    } else {
        // Parent process
        close(pipe1[0]); // Close read end of pipe1
        close(pipe2[1]); // Close write end of pipe2

        // Redirect stdout to write to pipe1, stdin to read from pipe2
        dup2(pipe1[1], STDOUT_FILENO);
        dup2(pipe2[0], STDIN_FILENO);

        close(pipe1[1]);
        close(pipe2[0]);

        // Send message to child
        cout << "Hi Child" << endl;
        cout.flush();

        // Read child's response
        string response1, response2;
        getline(cin, response1); // Child's "Child received: Hi Child"
        getline(cin, response2); // Child's "Hello Parent"

        cerr << response1 << endl;
        cerr << "Parent received: " << response2 << endl;
    }

    return 0;
}
