#include <iostream>
#include <vector>
#include <algorithm>
// Kruskal O(mlogm) 稀疏图
// 从小到大加入边

const int MAXN = 100005;

// 直接存边
struct Edge {
    int x, y, t;
};

int parent[MAXN], size[MAXN];

// 初始化并查集
void init(int n) {
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        size[i] = 1;
    }
}

// 查找集合代表
int find(int x) {
    if (x != parent[x]) {
        parent[x] = find(parent[x]);  // 路径压缩
    }
    return parent[x];
}

// 合并两个集合
bool unite(int x, int y) {
    int px = find(x), py = find(y);
    if (px == py) return false; // 已经在同一个集合

    if (size[px] < size[py]) std::swap(px, py); // 选择size大的作为根
    parent[py] = px; // py的父节点是px，size大的为根
    size[px] += size[py];
    return true;
}

int main() {
    int N, M;
    std::cin >> N >> M;

    std::vector<Edge> edges(M);
    for (int i = 0; i < M; i++) {
        std::cin >> edges[i].x >> edges[i].y >> edges[i].t;
    }

    // 按修复时间排序
    std::sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
        return a.t < b.t;
    });

    init(N);
    int mst_edges = 0;
    int result = -1;

    for (const auto &edge : edges) { // 遍历边
        if (unite(edge.x, edge.y)) {
            mst_edges++;
            result = edge.t; // 若求MST权值，result += edge.t.
            if (mst_edges == N - 1) break;  // 最小生成树完成
        }
    }

    if (mst_edges == N - 1)
        std::cout << result << std::endl;
    else
        std::cout << -1 << std::endl;

    return 0;
}
