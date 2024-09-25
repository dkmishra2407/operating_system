#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>

using namespace std;

void SSTF(vector<int> requests, int head) {
    vector<bool> visited(requests.size(), false);
    int total_head_movement = 0;
    int count = 0;

    while (count < requests.size()) {
        int min_distance = numeric_limits<int>::max();
        int index = -1;

        // Find the closest unvisited request
        for (int i = 0; i < requests.size(); i++) {
            if (!visited[i]) {
                int distance = abs(requests[i] - head);
                // Check for minimum distance and resolve ties by index
                if (distance < min_distance) {
                    min_distance = distance;
                    index = i;
                } else if (distance == min_distance && index != -1) {
                    // Tie-breaking: choose the one that appears first in the original list
                    if (i < index) {
                        index = i;
                    }
                }
            }
        }

        // Mark the selected request as visited
        visited[index] = true;
        total_head_movement += min_distance;
        head = requests[index]; // Move head to the selected request
        count++;
    }

    cout << "Total head movement (SSTF): " << total_head_movement << endl;
}

void SCAN(vector<int> requests, int head, string direction) {
    vector<int> left, right;
    int total_head_movement = 0;

    for (int request : requests) {
        if (request < head) left.push_back(request);
        else right.push_back(request);
    }

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    // Move towards the end in the specified direction
    if (direction == "right") {
        for (int request : right) {
            total_head_movement += abs(head - request);
            head = request;
        }
        // Move to the end of the disk
        total_head_movement += abs(head - 199); // Assuming disk size is 200
        head = 0; // Move to start
        for (int request : left) {
            total_head_movement += abs(head - request);
            head = request;
        }
    } else { // direction == "left"
        for (int i = left.size() - 1; i >= 0; i--) {
            total_head_movement += abs(head - left[i]);
            head = left[i];
        }
        // Move to the start of the disk
        total_head_movement += abs(head - 0);
        head = 199; // Move to end
        for (int i = right.size() - 1; i >= 0; i--) {
            total_head_movement += abs(head - right[i]);
            head = right[i];
        }
    }

    cout << "Total head movement (SCAN): " << total_head_movement << endl;
}

void CLOOK(vector<int> requests, int head) {
    vector<int> left, right;
    int total_head_movement = 0;

    for (int request : requests) {
        if (request < head) left.push_back(request);
        else right.push_back(request);
    }

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    // Service requests on the right side of the head
    for (int request : right) {
        total_head_movement += abs(head - request);
        head = request;
    }

    // Jump back to the first request on the left side
    if (!left.empty()) {
        total_head_movement += abs(head - left[0]);
        head = left[0];
        
        for (int request : left) {
            total_head_movement += abs(head - request);
            head = request;
        }
    }

    cout << "Total head movement (C-Look): " << total_head_movement << endl;
}

int main() {
    vector<int> sstf_requests = {98, 183, 41, 122, 14, 124, 65, 67};
    int sstf_head = 53; // Initial head position for SSTF

    vector<int> scan_requests = {176, 79, 34, 60, 92, 11, 41, 114};
    int scan_head = 50; // Initial head position for SCAN
    string scan_direction = "right"; // or "left"

    vector<int> clook_requests = {176, 79, 34, 60, 92, 11, 41, 114};
    int clook_head = 50; // Initial head position for C-Look

    // Call SSTF function
    SSTF(sstf_requests, sstf_head);

    // Call SCAN function
    SCAN(scan_requests, scan_head, scan_direction);

    // Call C-Look function
    CLOOK(clook_requests, clook_head);

    return 0;
}