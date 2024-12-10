#include <iostream>
#include <vector>
#include <algorithm>

const int MAXN = 100005;

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
    if (px == py) return false;

    if (size[px] < size[py]) std::swap(px, py); // 较大集合为根节点
    parent[py] = px;
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
    int connected_components = N; // 联通分量
    int result = -1;

    for (const auto &edge : edges) {
        if (unite(edge.x, edge.y)) {
            connected_components--;
            if (connected_components == 1) {
                result = edge.t;
                break;
            }
        }
    }

    std::cout << result << std::endl;
    return 0;
}
