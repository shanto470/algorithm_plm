#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

struct Position {
    int x, y, moves;
};

int dx[] = {2, 2, 1, 1, -1, -1, -2, -2};
int dy[] = {1, -1, 2, -2, 2, -2, 1, -1};

bool isValid(int x, int y) {
    return (x >= 0 && x < 8 && y >= 0 && y < 8);
}

int bfs(string start, string end) {
    if (start == end) return 0;

    bool visited[8][8];
    memset(visited, false, sizeof(visited));

    int startX = start[0] - 'a';
    int startY = start[1] - '1';
    int endX = end[0] - 'a';
    int endY = end[1] - '1';

    queue<Position> q;
    q.push({startX, startY, 0});
    visited[startX][startY] = true;

    while (!q.empty()) {
        Position current = q.front();
        q.pop();

        for (int i = 0; i < 8; i++) {
            int newX = current.x + dx[i];
            int newY = current.y + dy[i];

            if (isValid(newX, newY) && !visited[newX][newY]) {
                if (newX == endX && newY == endY) {
                    return current.moves + 1;
                }

                visited[newX][newY] = true;
                q.push({newX, newY, current.moves + 1});
            }
        }
    }

    return -1;
}

int main() {
    string start, end;

    while (cin >> start >> end) {
        int moves = bfs(start, end);
        cout << "To get from " << start << " to " << end << " takes " << moves << " knight moves." << endl;
    }

    return 0;
}
