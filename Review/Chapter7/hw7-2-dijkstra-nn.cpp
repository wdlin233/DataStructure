#include <bits/stdc++.h>
struct edge {
    int v, w;
};

std::vector<edge> e[10005];
int dis[10005], vis[10005];

void dijkstra(int n, int s) {
    memset(dis, 0x3f, (n + 1) * sizeof(int));
    memset(vis, 0, sizeof(vis));
    dis[s] = 0;

    for (int i = 1; i <= n; i++) {
        int u = 0, mind = 0x3f3f3f3f;

        // 找到当前未访问的距离最小的节点
        for (int j = 1; j <= n; j++) {
            if (!vis[j] && dis[j] < mind) {
                u = j;
                mind = dis[j];
            }
        }

        // 如果没有找到合法的节点，提前退出
        if (mind == 0x3f3f3f3f) break;

        vis[u] = true;

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
    std::cin >> N >> M >> C;

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
