#include <iostream>
#include <vector>
using namespace std;
// Prim O(n^2) 稠密图
// 从一个节点开始，不断加点

const int INF = 0x3f3f3f3f;

void prim(vector<vector<int>>& graph, int start) {
    int n = graph.size();
    vector<int> dist(n, INF); // 存储每个节点到生成树的最小距离
    vector<bool> visited(n, false); // 标记节点是否已经加入生成树
    vector<int> parent(n, -1); // 存储生成树的父节点

    dist[start] = 0; // 起始节点的距离为0，此时其他都是INF

    for (int i = 0; i < n - 1; ++i) { // 对建树的n - 1个节点进行循环，除去start起始节点
        int u = -1; // u is current node which is wait for operating, v is auxiliary node 
        for (int v = 0; v < n; ++v) {
            if (!visited[v] && (u == -1 || dist[v] < dist[u])) {
                u = v; // 找到未加入生成树的节点中，距离最小的节点
            }
        }
        visited[u] = true; // 将该节点加入生成树

        // 更新生成树到其他节点的距离
        for (int v = 0; v < n; ++v) {
            if (graph[u][v] != 0 && !visited[v] && graph[u][v] < dist[v]) {
                // 若其他节点到生成树距离变小，则更新
                dist[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }

    // 输出最小生成树的边
    cout << "Edge \tWeight\n";
    for (int i = 1; i < n; ++i) {
        cout << parent[i] << " - " << i << " \t" << graph[i][parent[i]] << "\n";
    }
}

int main() {
    int n, m; // n 是节点数，m 是边数
    cout << "Enter the number of nodes (n) and edges (m): ";
    cin >> n >> m;
    // 初始化邻接矩阵，所有边的权重初始化为0
    vector<vector<int>> graph(n, vector<int>(n, 0));

    cout << "Enter the edges (u, v, weight):" << endl;
    for (int i = 0; i < m; ++i) {
        int u, v, weight;
        cin >> u >> v >> weight;
        graph[u][v] = weight;
        graph[v][u] = weight; // 无向图，双向赋值
    }

    int start;
    cout << "Enter the starting node: ";
    cin >> start;

    prim(graph, start); 

    return 0;
}