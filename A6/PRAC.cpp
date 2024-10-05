#include<bits/stdc++.h>
using namespace std;

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

void fcfs(int frame,vector<int> pages){
    vector<int> f(frame,-1);
    int pagefault = 0;

    for(int i=0;i<pages.size();i++){
        bool flag = false;

        for(int k=0;k<frame;k++){
            if(pages[i]==f[k]){
                flag = 1;
                break;
            }
        }
        if(!flag){
            f[pagefault % frame] = pages[i];
            pagefault++;
        }
        printFrame(f);
    }

    cout << pagefault << endl;
}

void lru(int frame,vector<int> pages){
     vector<int> f(frame,-1);
    int pagefault = 0;
    unordered_map<int, int> lastused;
    int time = 0;
    for(int i=0;i<pages.size();i++){
        bool flag = false;

        for(int k=0;k<frame;k++){
            if(pages[i]==f[k]){
                flag = 1;
                break;
            }
        }
        if(!flag){
            int lastIndex = -1;
            int lastTime = INT_MAX;

            for(int i=0;i<frame;i++){
                if(f[i]==-1){
                    lastIndex = i;
                    break;
                }
                if(lastused[f[i]] < lastTime){
                    lastTime = lastused[f[i]];
                    lastIndex = i;
                }
            }

            f[lastIndex] = pages[i];
            lastused[f[i]] = time;
            pagefault++;
        }
        time++;
        printFrame(f);
    }

    cout << pagefault << endl;
}

void optimal(int frame,vector<int> pages){
     vector<int> f(frame,-1);
    int pagefault = 0;
    for(int i=0;i<pages.size();i++){
        bool flag = false;

        for(int k=0;k<frame;k++){
            if(pages[i]==f[k]){
                flag = 1;
                break;
            }
        }
        if(!flag){
            if (pagefault < frame) {
                f[pagefault++] = pages[i]; // Fill empty frames
            }
            else{
                int index = -1;
                int furtherest = -1;
                for(int j=0;j<frame;j++){
                    int next = -1;
                    for(int k=i+1;k<pages.size();k++){
                        if(f[j] == pages[k]){
                            next = k;
                            break;
                        }
                    }
                    if(next==-1){
                        index = j;
                        break;
                    }
                    if(next > furtherest){
                        next = furtherest;
                        index = j;
                    }
                }

                f[index] = pages[i];
                 pagefault++;
            }
        }
        printFrame(f);
    }

    cout << pagefault << endl;
}

int main(){
    int frame;
    cin>>frame;
    int n;
    cin>>n;
    vector<int> pages(n);

    for(int i=0;i<n;i++){
        cin>>pages[i];
    }

    optimal(frame,pages);
    return 0;
}