#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

const int MAXN = 1005;

std::vector<int> adj[MAXN];  // 邻接表表示图
int dis[MAXN];               // 距离数组

void bfs(int start, int n) {
    std::queue<int> q;
    memset(dis, -1, sizeof(dis));  // 初始化距离为 -1，表示未访问
    dis[start] = 0;               // 起点距离为 0
    q.push(start);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (dis[v] == -1) {   // 未访问的节点
                dis[v] = dis[u] + 1;
                q.push(v);
            }
        }
    }
}

int main() {
    int N, M, C;
    std::cin >> N >> M >> C;

    for (int i = 0; i < M; i++) {
        int u, v;
        std::cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);  // 无向图需要双向连接
    }

    bfs(C, N);

    for (int i = 1; i <= N; i++) {
        std::cout << dis[i] << std::endl;  // 按编号输出每个地方的距离
    }

    return 0;
}
