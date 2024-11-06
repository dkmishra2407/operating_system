#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define DISK_SIZE 199

// SSTF Algorithm
void sstf(vector<int>& requests, int head) {
    vector<int> visited(requests.size(), false);
    int total_movement = 0;
    int count = 0;

    while (count < requests.size()) {
        int min_index = -1;
        int min_distance = INT_MAX;

        // Find the closest unvisited request
        for (int i = 0; i < requests.size(); i++) {
            if (!visited[i]) {
                int distance = abs(requests[i] - head);
                if (distance < min_distance) {
                    min_distance = distance;
                    min_index = i;
                }
            }
        }

        count++;
        visited[min_index] = true;
        head = requests[min_index];
        total_movement += min_distance;
    }

    cout << "Total head movement for SSTF: " << total_movement << endl;
}

// SCAN Algorithm
void scan(vector<int>& requests, int head, string direction) {
    vector<int> right, left;
    int total_movement = 0;

    // Separate requests to the left and right of head
    for (int req : requests) {
        if (req >= head) {
            right.push_back(req);
        } else {
            left.push_back(req);
        }
    }
    
        sort(left.begin(), left.end(),greater<int>());
        sort(right.begin(), right.end());
    // Process requests based on scan direction
    if (direction == "right") {
        // Move to the right first
        for (int req : right) {
            total_movement += abs(head - req);
            head = req;
        }

        // Move to the end of the disk and back to the start
        total_movement += abs(head - DISK_SIZE);
        head = DISK_SIZE;

        for (int req : left) {
            total_movement += abs(head - req);
            head = req;
        }
        
    } else {
        // Move to the left first
        for (int req : left) {
            total_movement += abs(head - req);
            head = req;
        }

        // Move to the start of the disk and back to the end
        total_movement += abs(head - 0);
        head = 0;

        for (int req : right) {
            total_movement += abs(head - req);
            head = req;
        }
    }

    cout << "Total head movement for SCAN: " << total_movement << endl;
}

// C-LOOK Algorithm
void clook(vector<int>& requests, int head) {
    vector<int> right, left;
    int total_movement = 0;

    // Separate requests to the left and right of head
    for (int req : requests) {
        if (req >= head) {
            right.push_back(req);
        } else {
            left.push_back(req);
        }
    }

    // Sort requests in both directions for C-LOOK movement
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    // Process requests on the right side
    for (auto req : right) {
        total_movement += abs(req - head);
        head = req;
    }

    // Jump back to the lowest request on the left side if needed
    total_movement += abs(left[0] - head);
    head = left[0];
    if (!left.empty()) {
        for (int request : left) {
            total_movement += abs(head - request);
            head = request;
        }
    }

    cout << "Total head movement for C-LOOK: " << total_movement << endl;
}

int main() {
    int n;
    cout << "Enter the number of requests: ";
    cin >> n;

    vector<int> requests(n);
    cout << "Enter the requests: ";
    for (int i = 0; i < n; i++) {
        cin >> requests[i];
    }

    int head;
    cout << "Enter the initial head position: ";
    cin >> head;

    cout << "\nSSTF Algorithm" << endl;
    sstf(requests, head);

    cout << "\nSCAN Algorithm (right direction)" << endl;
    scan(requests, head, "right");

    cout << "\nC-LOOK Algorithm" << endl;
    clook(requests, head);

    return 0;
}
