#include <iostream>
#include <vector>

using namespace std;

/*
邻接矩阵

邻接矩阵只适用于没有重边（或重边可以忽略）的情况。
其最显著的优点是可以 O(1) 查询一条边是否存在。
由于邻接矩阵在稀疏图上效率很低（尤其是在点数较多的图上，空间无法承受），

稠密图
*/

int n, m;
vector<bool> vis;
vector<vector<bool>> adj;

bool find_edge(int u, int v) { return adj[u][v]; }

void dfs(int u) {
  if (vis[u]) return;
  vis[u] = true;
  for (int v = 1; v <= n; ++v) {
    if (adj[u][v]) {
      dfs(v);
    }
  }
}

int main() {
  cin >> n >> m;

  vis.resize(n + 1);
  adj.resize(n + 1, vector<bool>(n + 1));

  for (int i = 1; i <= m; ++i) {
    int u, v;
    cin >> u >> v;
    adj[u][v] = true;
  }

  return 0;
}