#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

const int INF = 0x3f3f3f3f;
const int MAXN = 1005;

struct edge {
    int v, w;  // 邻接点和边权
};

std::vector<edge> adj[MAXN];  // 邻接表表示图
int dis[MAXN];                // 最短路径数组

// O(mlogm)
void dijkstra(int start, int n) {
    // std::priority_queue<T, Container, Compare>
    // 小根堆
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;

    std::fill(dis, dis + n + 1, INF);  // 初始化距离为无穷大
    dis[start] = 0;                    // 起点距离为 0
    pq.push({0, start});               // {距离, 节点编号}

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dis[u]) continue;  // 当前距离已不是最短，跳过

        for (auto &ed : adj[u]) {
            int v = ed.v, w = ed.w;
            if (dis[v] > dis[u] + w) {  // 更新最短路径
                dis[v] = dis[u] + w;
                pq.push({dis[v], v});
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
        adj[u].push_back({v, 1});  // 无向图，边权为 1
        adj[v].push_back({u, 1});
    }

    dijkstra(C, N);

    for (int i = 1; i <= N; i++) {
        std::cout << dis[i] << std::endl;
    }

    return 0;
}
