#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>

using namespace std;

void merge(vector<int>& arr, int l, int mid, int h) {
    vector<int> temp(h - l + 1);
    int i = l;
    int j = mid + 1;
    int k = 0;

    while (i <= mid && j <= h) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    while (j <= h) {
        temp[k++] = arr[j++];
    }

    for (int x = l; x <= h; x++) {
        arr[x] = temp[x - l];
    }
}

void mergeSort(vector<int>& arr, int l, int h) {
    if (l >= h) return;

    int mid = (l + h) / 2;
    mergeSort(arr, l, mid);
    mergeSort(arr, mid + 1, h);
    merge(arr, l, mid, h);
}

int main() {
    int choice;

    cout << "\n**********MENU**********\n";
    cout << "1. Normal Execution (Sorting) \n";
    cout << "2. Demonstrate Zombie State \n";
    cout << "3. Demonstrate Orphan State \n";
    cout << "\nEnter Your Choice: ";
    cin >> choice;

    switch (choice) {
        case 1: {
            vector<int> arr(5);
            cout << "\nEnter Five Integers To Be Sorted \n";
            for (int i = 0; i < 5; i++) {
                cout << "Enter Integer " << i + 1 << ": ";
                cin >> arr[i];
            }

            pid_t pid = fork();
            if (pid == -1) {
                cout << "Error In Forking The Process! \n";
            } else if (pid == 0) {  // Child process
                cout << "\nInside Child Process \n";
                mergeSort(arr, 0, 4);
                cout << "Array Sorted By Child Process: ";
                for (int i : arr) {
                    cout << i << " ";
                }
                cout << endl;
                exit(0);
                // function call in the 
                // context of your C++ code serves a specific purpose, which is to terminate the current process. 
            } else {  // Parent process
                cout << "\nInside Parent Process \n";
                mergeSort(arr, 0, 4);
                cout << "Array Sorted By Parent Process: ";
                for (int i : arr) {
                    cout << i << " ";
                }
                cout << endl;
                cout << "Waiting For Child Process To Terminate...... \n\n";
                wait(NULL);   // waiting for the terminating the child
                cout << "Child Process Has Been Terminated \n";
                cout << "Terminating Parent Process Now \n";
            }
            break;
        }
        
        case 2: {  // Zombie process demonstration
            pid_t pid1 = fork();
            if (pid1 == -1) {
                cout << "Error In Forking The Process! \n";
            } else if (pid1 == 0) {  // Child process
                cout << "\nInside Child Process \n";
                cout << "My Process ID = " << getpid() << "\n";
                cout << "My Parent's Process ID = " << getppid() << "\n";
                exit(0);
            } else {  // Parent process
                sleep(5);    // DUE TO THIS CHILD FINISH EARLY BUT NOT PARENT
                cout << "\nInside Parent Process \n";
                cout << "My Process ID = " << getpid() << "\n";
                cout << "Demonstrating Zombie Process \n";
                system("ps | grep a.out");
                // The command system("ps | grep a.out"); is executed to list all running processes and
                // filter for the current program (a.out is typically the default name for compiled C/C++ programs). 
                // This shows that the child process has completed but has not yet been reaped by the parent.
                cout << "Child Process Is Dead And Has Become A Zombie (defunct) \n\n";
            }
            break;
        }

        case 3: {  // Orphan process demonstration
            pid_t pid2 = fork();
            if (pid2 == -1) {
                cout << "Error In Forking The Process! \n";
            } else if (pid2 == 0) {  // Child process
                sleep(2);
                cout << "\nInside Child Process \n";
                cout << "My Process ID = " << getpid() << "\n";
                cout << "My Parent's Process ID = " << getppid() << "\n";
                system("ps | grep a.out");
                cout << "This Process Has Been Adopted By Process " << getppid() << "\n";
                cout << "Its Original Parent Process Has Been Terminated \n";
                exit(0);
            } else {  // Parent process
                cout << "\nInside Parent Process \n";
                cout << "My Process ID = " << getpid() << "\n";
                system("ps | grep a.out");
                cout << "Process " << pid2 << " Is My Child Process \n\n";
            }
            break;
        }
        
        default:
            cout << "Invalid choice!\n";
            break;
    }
    return 0;
}
