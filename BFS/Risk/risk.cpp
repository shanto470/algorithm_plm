#include <iostream>
#include <vector>
#include <queue>
#include <sstream>
#include <string>
#include <cstring>

using namespace std;

const int MAX_COUNTRIES = 21;

vector<int> graph[MAX_COUNTRIES];
bool visited[MAX_COUNTRIES];
int dist[MAX_COUNTRIES];

int bfs(int start, int destination) {
    if (start == destination) return 0;

    memset(visited, false, sizeof(visited));
    memset(dist, 0, sizeof(dist));

    queue<int> q;
    q.push(start);
    visited[start] = true;
    dist[start] = 0;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (int neighbor : graph[current]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                dist[neighbor] = dist[current] + 1;

                if (neighbor == destination) {
                    return dist[neighbor];
                }

                q.push(neighbor);
            }
        }
    }

    return -1;
}

int main() {
    int testSet = 1;
    string line;

    while (true) {
        for (int i = 0; i < MAX_COUNTRIES; i++) {
            graph[i].clear();
        }

        for (int country = 1; country <= 19; country++) {
            if (!getline(cin, line)) return 0;

            stringstream ss(line);
            int numConnections;
            ss >> numConnections;

            for (int j = 0; j < numConnections; j++) {
                int neighbor;
                ss >> neighbor;
                graph[country].push_back(neighbor);
                graph[neighbor].push_back(country);
            }
        }

        int numQueries;
        if (!getline(cin, line)) return 0;
        stringstream ss(line);
        ss >> numQueries;

        cout << "Test Set #" << testSet << endl;

        for (int i = 0; i < numQueries; i++) {
            if (!getline(cin, line)) return 0;
            stringstream query_ss(line);
            int start, destination;
            query_ss >> start >> destination;

            int result = bfs(start, destination);

            if (start < 10) cout << " ";
            cout << start << " to ";
            if (destination < 10) cout << " ";
            cout << destination << ": " << result << endl;
        }

        cout << endl;
        testSet++;

        while (getline(cin, line) && line.empty()) {}
        if (!cin) break;

        if (!line.empty()) {
            for (int i = line.size(); i >= 0; i--) {
                cin.putback(line[i]);
            }
        }
    }

    return 0;
}
