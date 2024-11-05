#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
void non_premption(vector<vector<int>> &matrix) {
    int n = matrix.size();

    int count = 0;
    int curr_time = 0;
    vector<int> waiting_time(n, 0);
    vector<int> completion_time(n, 0);

    while (count < n) {
        int min_brust = -1; // Index of the process with the minimum burst time
        int brust = INT_MAX; // Placeholder for the smallest burst time

        // Find the process with the minimum burst time that has arrived and is not completed
        for (int i = 0; i < n; i++) {
            if (matrix[i][1] <= curr_time && matrix[i][2] < brust && completion_time[i] == 0) { 
                // Changed `waiting_time[i] == 0` to `completion_time[i] == 0` to check if the process is completed
                brust = matrix[i][2];
                min_brust = i;
            }
        }

        // If no process is available, increment the current time and continue to the next iteration
        if (min_brust == -1) {
            curr_time++;
            continue; // Changed `break` to `continue` to avoid premature termination of the loop
        }

        // Calculate waiting time and completion time for the selected process
        waiting_time[min_brust] = curr_time - matrix[min_brust][1] ;
        completion_time[min_brust] = curr_time + matrix[min_brust][2]; // Corrected completion time calculation
        curr_time += matrix[min_brust][2];
        count++;
    }

    // Output process details for verification
    for (int i = 0; i < n; i++) {
        cout << matrix[i][0] << " " << matrix[i][1] << " " << matrix[i][2] << endl;
    }
    cout << "Waiting Time" << endl;
    for (int i = 0; i < n; i++) {
        cout << waiting_time[i] << endl;
    }
}

void premption(vector<vector<int>> &matrix) {
    int n = matrix.size();
     // Sorting processes based on arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (matrix[j][1] > matrix[j + 1][1]) {
                for (int k = 0; k < 3; k++) {
                    swap(&matrix[j][k], &matrix[j + 1][k]);
                }
            }
        }
    }
    int count = 0;
    int curr_time = 0;
    vector<int> waiting_time(n, 0);
    vector<int> completion_time(n, 0);
    vector<int> remaining_time(n);
    for(int i=0;i<n;i++){
        remaining_time[i] = matrix[i][2];
    }
    while (count < n) {
        int min_brust = -1; // Index of the process with the minimum burst time
        int brust = INT_MAX; // Placeholder for the smallest burst time

        // Find the process with the minimum burst time that has matrixived and is not completed
        for (int i = 0; i < n; i++) {
            if (matrix[i][1] <= curr_time && remaining_time[i] < brust && remaining_time[i] > 0) { 
                // Changed `waiting_time[i] == 0` to `completion_time[i] == 0` to check if the process is completed
                brust = remaining_time[i];
                min_brust = i;
            }
        }

        if (min_brust == -1) {
            curr_time++;
            continue; 
        }
        
       remaining_time[min_brust]--;

       if(remaining_time[min_brust] == 0){
         waiting_time[min_brust] = curr_time - matrix[min_brust][1]- (matrix[min_brust][2] - 1) ;
         completion_time[min_brust] = curr_time + matrix[min_brust][2];
         count++; 
       }
        curr_time ++;
        
    }

    // Output process details for verification
    for (int i = 0; i < n; i++) {
        cout << matrix[i][0] << " " << matrix[i][1] << " " << matrix[i][2] << endl;
    }
    cout << "Waiting Time" << endl;
    for (int i = 0; i < n; i++) {
        cout << waiting_time[i] << endl;
    }
    cout << "Completion Time" << endl;
    for (int i = 0; i < n; i++) {
        cout << completion_time[i] << endl;
    }
}
void round_robin(vector<vector<int>> &matrix){
    int n = matrix.size();

    // Sorting processes based on arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (matrix[j][1] > matrix[j + 1][1]) {
                for (int k = 0; k < 3; k++) {
                    swap(&matrix[j][k], &matrix[j + 1][k]);
                }
            }
        }
    }

    int count = 0;
    int curr_time = 0;
    vector<int> waiting_time(n, 0);
    vector<int> completion_time(n, 0);
    vector<int> remaining_time(n);

    for(int i = 0; i < n; i++) {
        remaining_time[i] = matrix[i][2];
    }

    int tq = 2;

    // Vector to store Gantt chart sequence
    vector<pair<int, int>> gantt_chart;  // Stores (Process ID, time spent in that slice)

    while (count < n) {
        bool found = false;  // Reset flag for each round

        for (int i = 0; i < n; i++) {
            if (matrix[i][1] <= curr_time && remaining_time[i] > 0) {
                found = true;  // Process is available to run

                if (remaining_time[i] > tq) {
                    remaining_time[i] -= tq;
                    gantt_chart.push_back({matrix[i][0], tq});
                    curr_time += tq;
                } else {
                    gantt_chart.push_back({matrix[i][0], remaining_time[i]});
                    curr_time += remaining_time[i];
                    remaining_time[i] = 0;
                    count++;
                    completion_time[i] = curr_time;
                    waiting_time[i] = curr_time - matrix[i][1] - matrix[i][2];
                }
            }
        }

        // Only increment curr_time if no process was found in this round
        if (!found) {
            curr_time++;
        }
    }

    // Output Gantt Chart
    cout << "Gantt Chart:\n";
    for (auto &entry : gantt_chart) {
        cout << "| P" << entry.first << " ";
    }
    cout << "|\n";

    curr_time = 0;
    for (auto &entry : gantt_chart) {
        cout << curr_time << "    ";
        curr_time += entry.second;
    }
    cout << curr_time << endl;

    // Output process details for verification
    cout << "\nProcess Details:\n";
    for (int i = 0; i < n; i++) {
        cout << "Process " << matrix[i][0] << " - Arrival Time: " << matrix[i][1] 
             << ", Burst Time: " << matrix[i][2] << endl;
    }
    
    cout << "\nWaiting Time:\n";
    for (int i = 0; i < n; i++) {
        cout << "Process " << matrix[i][0] << ": " << waiting_time[i] << endl;
    }

    cout << "\nCompletion Time:\n";
    for (int i = 0; i < n; i++) {
        cout << "Process " << matrix[i][0] << ": " << completion_time[i] << endl;
    }
}

int main() {
    int n;
    cin >> n;
    vector<vector<int>> matrix(n, vector<int>(3));
    cout << "Enter Process No, Arrival Time, & Burst Time:" << endl;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> matrix[i][j];
        }
    }

    round_robin(matrix);
    return 0;
}