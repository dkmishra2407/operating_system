#include <bits/stdc++.h>
using namespace std;

// Function to check if the process can be safely allocated resources
bool check(int row, int m, const vector<vector<int>>& need, const vector<int>& available) {
    for (int i = 0; i < m; i++) {
        if (need[row][i] > available[i]) {
            return false;
        }
    }
    return true;
}

// Function to update the available resources after allocation
void update(int row, int m, vector<int>& available, const vector<vector<int>>& allocation) {
    for (int i = 0; i < m; i++) {
        available[i] += allocation[row][i];
    }
}

int main() {
    int n;  
    int m = 3;
   
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<vector<int>> allocation(n, vector<int>(m));
    vector<vector<int>> max(n, vector<int>(m));
    vector<int> available(m);
    vector<vector<int>> need(n, vector<int>(m));

    cout << "Enter the allocation matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> allocation[i][j];
        }
    }

    cout << "Enter the max matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> max[i][j];
        }
    }

    cout << "Enter the available resources:\n";
    for (int i = 0; i < m; i++) {
        cin >> available[i];
    }

    // Calculate the need matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    vector<int> ans; // To store the safe sequence
    vector<bool> finish(n, false);

    // Find the safe sequence
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (!finish[i] && check(i, m, need, available)) {
                ans.push_back(i);
                update(i, m, available, allocation);
                finish[i] = true;
            }
        }
    }

    cout << "System is in a safe state.\nSafe sequence is: ";
    for (int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;

    return 0;
}