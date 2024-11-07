#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <climits>

using namespace std;

class PageReplacement {
public:
    void fcfs(int frames, const vector<int>& pages) {
        cout << "FCFS Page Replacement:\n";
        vector<int> frame(frames, -1);
        int pageFaults = 0;

        for (int page : pages) {
            bool found = false;
            for (int i = 0; i < frames; i++) {
                if (frame[i] == page) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                frame[pageFaults % frames] = page;
                pageFaults++;
            }
            printFrame(frame);
        }
        cout << "Total Page Faults: " << pageFaults << endl;
    }

    void lru(int frames, const vector<int>& pages) {
        cout << "LRU Page Replacement:\n";
        vector<int> frame(frames, -1);
        unordered_map<int, int> lastUsed;  
        int pageFaults = 0;
        int time = 0;

        for (int page : pages) {
            bool found = false;
            for (int i = 0; i < frames; i++) {
                if (frame[i] == page) {
                    found = true;
                    lastUsed[page] = time; // Update last used time
                    break;    
                }
            }
            if (!found) {
                // Find the least recently used page to replace
                int lruIndex = -1,lruTime = INT_MAX;
                for (int i = 0; i < frames; i++) {
                    if (frame[i] == -1) {
                        lruIndex = i;
                        break;
                    }
                    if (lruTime > lastUsed[frame[i]]) {
                        lruTime  = lastUsed[frame[i]];
                        lruIndex = i;
                    }
                }
                frame[lruIndex] = page;
                lastUsed[page] = time;
                pageFaults++;
            }
            printFrame(frame);
            time++;
        }
        cout << "Total Page Faults: " << pageFaults << endl;
    }

    void optimal(int frames, const vector<int>& pages) {
        cout << "Optimal Page Replacement:\n";
        vector<int> frame(frames, -1);
        int pageFaults = 0;

        for (int i = 0; i < pages.size(); i++) {
            bool found = false;
            for (int j = 0; j < frames; j++) {
                if (frame[j] == pages[i]) {
                    found = true; 
                    break;
                }
            }
            if (!found) {
                if (pageFaults < frames) {
                    frame[pageFaults++] = pages[i]; // Fill empty frames
                } else {
                    // Replace page using optimal strategy
                    int farthest = -1, index = -1;
                    for (int j = 0; j < frames; j++) {
                        int next = -1;
                        for (int k = i + 1; k < pages.size(); k++) {
                            if (frame[j] == pages[k]) {
                                next = k;
                                break;
                            }
                        }
                        if (next == -1) {
                            index = j; // Page not found in future, replace it
                            break;
                        }
                        if (next > farthest) {
                            farthest = next;
                            index = j;
                        }
                    }
                    frame[index] = pages[i];
                    pageFaults++;
                }
            }
            printFrame(frame);
        }
        cout << "Total Page Faults: " << pageFaults << endl;
    }

private:
    void printFrame(const vector<int>& frame) {
        cout << "Frames: ";
        for (int page : frame) {
            if (page != -1) {
                cout << page << " ";
            } else {
                cout << " - ";
            }
        }
        cout << endl;
    }
};

int main() {
    int frames;
    cout << "Enter number of frames (minimum 3): ";
    cin >> frames;

    if (frames < 3) {
        cout << "Frame size must be at least 3." << endl;
        return 1;
    }

    vector<int> pages;
    int page;
    cout << "Enter page reference string (terminate with -1): ";
    while (cin >> page && page != -1) {
        pages.push_back(page);
    }

    PageReplacement pr;
    pr.fcfs(frames, pages);
    cout << endl;
    pr.lru(frames, pages);
    cout << endl;
    pr.optimal(frames, pages);

    return 0;
}


// test case 

// 3
// 1 3 0 3 5 6 3

// 4
// 7 0 1 2 0 3 0 4 2 3 0 3 2 3
