#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
void sjf_non_premptive(vector<vector<int>>&matrix){
    int n = matrix.size();
    vector<int>waiting_time(n,0);
    vector<int>completion_time(n,0);
    vector<int>tat(n,0);
    int count = 0;
    int currtime = 0;
    while (count < n)
    {
        /* code */
        int minindex = -1;
        int brust = INT_MAX;

        for(int i=0;i<n;i++){
            if(matrix[i][1] <= currtime && completion_time[i] == 0 && matrix[i][2] < brust){
                // completion_time[i] = currtime;
                minindex = i;
                brust = matrix[i][2];
            }
        }

        if(minindex == -1){
            currtime++;
            continue;
        }
        currtime += matrix[minindex][2];
        completion_time[minindex] = currtime;

        // Calculate turnaround time and waiting time
        tat[minindex] = completion_time[minindex] - matrix[minindex][1];
        waiting_time[minindex] = tat[minindex] - matrix[minindex][2];    
        count++;

    }

    for (int i = 0; i < n; i++)
    {
        /* code */
        cout << matrix[i][0] <<" " << matrix[i][1] <<" " << matrix[i][2] <<" " <<waiting_time[i] << " "<<  completion_time[i] << endl;
    }
}



void preemptive(vector<vector<int>>& matrix) {
    int n = matrix.size();

    // Sort processes based on arrival time
    sort(matrix.begin(), matrix.end(), [](const vector<int>& a, const vector<int>& b) {
        return a[1] < b[1]; // Sort by arrival time
    });

    vector<int> waiting_time(n, 0);
    vector<int> completion_time(n, 0);
    vector<int> tat(n, 0);
    vector<int> remaining(n);

    int count = 0;
    int currtime = 0;

    // Initialize remaining time for each process
    for (int i = 0; i < n; i++) {
        remaining[i] = matrix[i][2];
    }

    while (count < n) {
        int min_index = -1;
        int min_distance = INT_MAX;

        // Find the process with the shortest remaining time
        for (int i = 0; i < n; i++) {
            if (matrix[i][1] <= currtime && remaining[i] > 0 && remaining[i] < min_distance) {
                min_distance = remaining[i];
                min_index = i;
            }
        }

        if (min_index == -1) {
            currtime++;
            continue; // No process is ready, increment time
        }

        // Decrement the remaining time for the selected process
        remaining[min_index]--;

        // If the process is finished
        if (remaining[min_index] == 0) {
            count++;
            completion_time[min_index] = currtime + 1; // Current time + 1 since we are incrementing after this
            tat[min_index] = completion_time[min_index] - matrix[min_index][1];
            waiting_time[min_index] = tat[min_index] - matrix[min_index][2];
        }

        currtime++; // Increment current time
    }

    // Print the results
    for (int i = 0; i < n; i++) {
        cout << matrix[i][0] << " " << matrix[i][1] << " " << matrix[i][2] << " "
             << waiting_time[i] << " " << completion_time[i] << " " << tat[i] << endl;
    }
}


void roundRobin(vector<vector<int>>& matrix) {
    int n = matrix.size();

    // Sort processes based on arrival time
    sort(matrix.begin(), matrix.end(), [](const vector<int>& a, const vector<int>& b) {
        return a[1] < b[1]; // Sort by arrival time
    });

    vector<int> waiting_time(n, 0);
    vector<int> completion_time(n, 0);
    vector<int> tat(n, 0);
    vector<int> remaining(n);

    int count = 0;
    int currtime = 0;

    // Initialize remaining time for each process
    for (int i = 0; i < n; i++) {
        remaining[i] = matrix[i][2];
    }
    int tq;
    tq = 2;
    while (count < n) {
        int min_index = -1;
        int min_distance = INT_MAX;

        // Find the process with the shortest remaining time
        for (int i = 0; i < n; i++) {
            if (matrix[i][1] <= currtime && remaining[i] > 0 && remaining[i] < min_distance) {
                min_distance = remaining[i];
                min_index = i;
            }
        }


        // If the process is finished
        if (remaining[min_index] > tq) {
            remaining[min_index] -= tq;
            currtime += tq;
        }
        else{
            count++;
            currtime += remaining[min_index];
            completion_time[min_index] = currtime + 1; // Current time + 1 since we are incrementing after this
            tat[min_index] = completion_time[min_index] - matrix[min_index][1];
            waiting_time[min_index] = tat[min_index] - matrix[min_index][2];
        }

    }

    // Print the results
    for (int i = 0; i < n; i++) {
        cout << matrix[i][0] << " " << matrix[i][1] << " " << matrix[i][2] << " "
             << waiting_time[i] << " " << completion_time[i] << " " << tat[i] << endl;
    }
}

int main() {
    int n;
    cin>>n;
    vector<vector<int>> matrix(n, vector<int>(3));
    // cout << "Enter PNO , Arrival Time & Brust Time" << endl;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cin>>matrix[i][j];
        }
    }
    

    roundRobin(matrix);
    return 0;
}

