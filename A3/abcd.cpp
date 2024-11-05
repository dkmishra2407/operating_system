#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    int t;
    cin >> t;
    while(t--) {
        vector<pair<pair<char, char>, int>> vec;
        char startvertex, endvertex;
        int weight, n;
        
        cout << "Enter the number of edges: ";
        cin >> n;
        
        for(int i = 0; i < n; i++) {
            cin >> startvertex >> endvertex >> weight;
            vec.push_back({{startvertex, endvertex}, weight});
        }

        unordered_map<char, int> dist;
        unordered_set<char> vertices;
        
        for (auto edge : vec) {
            vertices.insert(edge.first.first);
            vertices.insert(edge.first.second);
        }
        
        for (auto vertex : vertices) {
            dist[vertex] = INT_MAX;
        }

        char source;
        cout << "Enter the source vertex: ";
        cin >> source;
        dist[source] = 0;

        for (int i = 0; i < vertices.size() - 1; i++) {
            for (auto edge : vec) {
                char u = edge.first.first;
                char v = edge.first.second;
                int w = edge.second;
                
                if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                }
            }
        }

        bool isNegativeCycle = false;
        for (auto edge : vec) {
            char u = edge.first.first;
            char v = edge.first.second;
            int w = edge.second;
            
            if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                isNegativeCycle = true;
                break;
            }
        }
        
        if (isNegativeCycle) {
            cout << "Graph contains a negative-weight cycle" << endl;
        } else {
            cout << "Shortest distances from source " << source << ":" << endl;
            for (auto d : dist) {
                cout << "Vertex " << d.first << " -> " << d.second << endl;
            }
        }
    }
    return 0;
}
