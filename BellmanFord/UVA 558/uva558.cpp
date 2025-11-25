#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct Edge {
    int u, v, w;
};

int main() {
    int c;
    cin >> c;

    while (c--) {
        int n, m;
        cin >> n >> m;

        vector<Edge> edges(m);

        for (int i = 0; i < m; i++) {
            cin >> edges[i].u >> edges[i].v >> edges[i].w;
        }

        vector<int> dist(n, INT_MAX);
        dist[0] = 0;

        for (int i = 0; i < n; i++) {
            for (const Edge& e : edges) {
                if (dist[e.u] != INT_MAX && dist[e.u] + e.w < dist[e.v]) {
                    dist[e.v] = dist[e.u] + e.w;
                }
            }
        }

        bool hasNegativeCycle = false;
        for (const Edge& e : edges) {
            if (dist[e.u] != INT_MAX && dist[e.u] + e.w < dist[e.v]) {
                hasNegativeCycle = true;
                break;
            }
        }

        cout << (hasNegativeCycle ? "possible" : "not possible") << endl;
    }

    return 0;
}

