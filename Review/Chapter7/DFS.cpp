#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int n, m;
vector<bool> vis; // visited
vector<vector<int>> adj;

// Stack implementation of DFS
void dfs_stack(int s) {
    stack<int> st;
    st.push(s);
    vis[s] = true;

    while(!st.empty()) {
        int u = st.top();
        st.pop();
        for (int i = 0; i < adj[u].size(); ++i) {
            int v = adj[u][i];
            if (!vis[v]) {
                st.push(v);
                vis[v] = true;
            }
        }
    }
}

void dfs_call_stack1(int u) {
    if (vis[u]) return;
    vis[u] = true;
    for (int i = 0; i < adj[u].size(); ++i) {
        dfs(adj[u][i]);
    }
}

void dfs_call_stack2(const int u) {
    vis[u] = true;
    for (int v: adj[u]) {
        if (!vis[v]) dfs(v);
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