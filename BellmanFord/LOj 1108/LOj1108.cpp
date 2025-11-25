#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cmath>

using namespace std;

const int INF = 1e9;

struct Edge {
    int u, v, w;
};

int main() {
    int caseNum = 1;
    int n;
    
    while (cin >> n) {
        vector<int> busyness(n + 1);
        for (int i = 1; i <= n; i++) {
            cin >> busyness[i];
        }
        
        int r;
        cin >> r;
        vector<Edge> edges(r);
        
        for (int i = 0; i < r; i++) {
            int u, v;
            cin >> u >> v;
            int w = pow(busyness[v] - busyness[u], 3);
            edges[i] = {u, v, w};
        }
        
        int q;
        cin >> q;
        vector<int> queries(q);
        for (int i = 0; i < q; i++) {
            cin >> queries[i];
        }
        
        vector<int> dist(n + 1, INF);
        dist[1] = 0;
        
        for (int i = 0; i < n - 1; i++) {
            for (const Edge& e : edges) {
                if (dist[e.u] != INF && dist[e.u] + e.w < dist[e.v]) {
                    dist[e.v] = dist[e.u] + e.w;
                }
            }
        }
        
        vector<bool> inCycle(n + 1, false);
        for (int i = 0; i < n - 1; i++) {
            for (const Edge& e : edges) {
                if (dist[e.u] != INF && dist[e.u] + e.w < dist[e.v]) {
                    dist[e.v] = dist[e.u] + e.w;
                    inCycle[e.v] = true;
                }
            }
        }
        
        vector<bool> visited(n + 1, false);
        for (int i = 1; i <= n; i++) {
            if (inCycle[i] && !visited[i]) {
                queue<int> q;
                q.push(i);
                visited[i] = true;
                while (!q.empty()) {
                    int u = q.front();
                    q.pop();
                    for (const Edge& e : edges) {
                        if (e.u == u && !visited[e.v]) {
                            visited[e.v] = true;
                            inCycle[e.v] = true;
                            q.push(e.v);
                        }
                    }
                }
            }
        }
        
        cout << "Set #" << caseNum++ << endl;
        for (int query : queries) {
            if (dist[query] < 3 || dist[query] == INF || inCycle[query]) {
                cout << "?" << endl;
            } else {
                cout << dist[query] << endl;
            }
        }
    }
    
    return 0;
}

