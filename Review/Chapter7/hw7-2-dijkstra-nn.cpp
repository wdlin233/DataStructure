#include <bits/stdc++.h>
struct edge {
    int v, w;
};

std::vector<edge> e[10005];
int dis[10005], vis[10005];

void dijkstra(int n, int s) {
    memset(dis, 0x3f, (n + 1) * sizeof(int));
    memset(vis, 0, sizeof(vis)); // 或使用bool数组
    dis[s] = 0;

    for (int i = 1; i <= n; i++) {
        int u = 0, MIN_DIS = 0x3f3f3f3f;
        // 找到当前未访问的距离最小的节点
        // 与Prim找到最短路的策略是等价的
        // 区别在于，dis[j]是起点到j的最短距离；dist[v]是生成树到v的最短距离

        // 第二个区别是更新策略不同：
        // dis[v] = min(dis[v], dis[u] + w);
        // dist[v] = min(dist[v], graph[u][v]); 
        // dijkstra的更新策略是整条最短路的最小值，
        // 而prim算法的更新策略是相邻点的最小值
        for (int j = 1; j <= n; j++) {
            if (!vis[j] && dis[j] < MIN_DIS) {
                u = j;
                MIN_DIS = dis[j];
            }
        }

        // 如果没有找到合法的节点，提前退出
        if (MIN_DIS == 0x3f3f3f3f) break;

        vis[u] = true; // 找到u了

        // 更新邻接节点的最短路径
        for (auto ed : e[u]) {
            int v = ed.v, w = ed.w;
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
            }
        }
    }
}

int main() {
    int N, M, C;
    std::cin >> N >> M >> C; // N 为节点数，M 为边数，C 为起始节点

    for (int i = 1; i <= M; i++) {
        int u_tmp = 0, v_tmp = 0;
        std::cin >> u_tmp >> v_tmp;
        e[u_tmp].push_back({v_tmp, 1});  // 无向图
        e[v_tmp].push_back({u_tmp, 1});  // 注意此处，需要双向
    }

    dijkstra(N, C);

    for (int i = 1; i <= N; i++) {
        if (dis[i] == 0x3f3f3f3f)
            std::cout << "INF" << std::endl;  // 不可达
        else
            std::cout << dis[i] << std::endl;
    }

    return 0;
}
