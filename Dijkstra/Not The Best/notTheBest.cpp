#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

typedef pair<int, int> pii;

const int INF = INT_MAX;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    for (int tc = 1; tc <= T; tc++) {
        int N, R;
        cin >> N >> R;

        vector<vector<pii>> graph(N + 1);

        for (int i = 0; i < R; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            graph[u].push_back({v, w});
            graph[v].push_back({u, w});
        }

        vector<int> dist1(N + 1, INF);
        vector<int> dist2(N + 1, INF);

        priority_queue<pii, vector<pii>, greater<pii>> pq;

        dist1[1] = 0;
        pq.push({0, 1});

        while (!pq.empty()) {
            int d = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            if (d > dist2[u]) continue;

            for (auto &edge : graph[u]) {
                int v = edge.first;
                int w = edge.second;
                int nd = d + w;

                if (nd < dist1[v]) {
                    dist2[v] = dist1[v];
                    dist1[v] = nd;
                    pq.push({nd, v});
                } 
                else if (nd > dist1[v] && nd < dist2[v]) {
                    dist2[v] = nd;
                    pq.push({nd, v});
                }
            }
        }

        cout << "Case " << tc << ": " << dist2[N] << "\n";
    }

    return 0;
}

