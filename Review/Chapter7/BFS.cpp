#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n, m;
vector<bool> vis; // visited
vector<vector<int>> adj;

void bfs(int u) {
    queue<int> q;
    q.push(u);
    vis[u] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = 0; i < adj[u].size(); ++i) {
            int v = adj[u][i];
            if (!vis[v]) {
                q.push(v);
                vis[v] = true;
            }
        }
    }
}

int main() {
    cin >> n >> m;
    vis.resize(n + 1, false);
    adj.resize(n + 1);
    for (int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }
    return 0;
}