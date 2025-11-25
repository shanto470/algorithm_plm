#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

typedef long long ll;
typedef pair<ll, int> pli;

const ll INF = 1e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> graph(n + 1);

    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        graph[a].push_back({b, w});
        graph[b].push_back({a, w});
    }

    vector<ll> dist(n + 1, INF);
    vector<int> parent(n + 1, -1);
    vector<bool> visited(n + 1, false);

    priority_queue<pli, vector<pli>, greater<pli>> pq;

    dist[1] = 0;
    pq.push({0, 1});

    while (!pq.empty()) {
        ll current_dist = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;

        if (u == n) break;

        for (auto &edge : graph[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (!visited[v] && current_dist + weight < dist[v]) {
                dist[v] = current_dist + weight;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    if (dist[n] == INF) {
        cout << -1 << endl;
    } else {
        vector<int> path;
        for (int v = n; v != -1; v = parent[v]) {
            path.push_back(v);
        }
        reverse(path.begin(), path.end());

        for (int i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i < path.size() - 1) cout << " ";
        }
        cout << endl;
    }

    return 0;
}

