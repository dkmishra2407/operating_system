#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

void heapify(vector<int> &ans,int n,int i){
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if(left < n && ans[largest] < ans[left]){
        largest = left;
    }

    if(right < n && ans[largest] < ans[right]){
        largest = right;
    }

    if(largest != i){
        swap(ans[largest],ans[i]);
        heapify(ans,n,largest);
    }
}

void heapsort(vector<int> &ans){
    int n = ans.size();

    for(int i=n/2-1;i>=0;i--){
        heapify(ans,n,i);
    }

    for(int i=n-1;i>=0;i--){
        heapify(ans,i,0);
    }
}
int main() {
    vector<int> ans{ 60 ,20 ,40 ,70, 30, 10};
    heapsort(ans);

    for (int i = 0; i < ans.size(); ++i)
        cout << ans[i] << " ";
    return 0;
}