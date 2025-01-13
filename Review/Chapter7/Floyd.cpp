#include <iostream>
#include <vector>
#include <climits>

using namespace std;
const int INF = 0x3f3f3f3f;

void floydWarshall(vector<vector<int>>& graph, int n) {
    // 初始化距离矩阵
    vector<vector<int>> dist(n, vector<int>(n));

    // 复制图的邻接矩阵到距离矩阵
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dist[i][j] = graph[i][j];
        }
    }

    // Floyd-Warshall算法核心部分
    // T(n) = O(n^3)
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                // 如果通过k节点可以找到更短的路径
                // D_k[i][j] > D_(k-1)[i][k] + D_(k-1)[k][j]
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // 输出最短路径矩阵
    cout << "Shortest distances between every pair of vertices:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == INF) {
                cout << "INF\t";
            } else {
                cout << dist[i][j] << "\t";
            }
        }
        cout << endl;
    }
}

int main() {
    int n;  
    cout << "Enter the number of vertices: ";
    cin >> n;

    // 初始化图的邻接矩阵
    // graph[n][n]
    vector<vector<int>> graph(n, vector<int>(n, INF)); 

    // 设置节点到自身的距离为0
    for (int i = 0; i < n; i++) {
        graph[i][i] = 0;
    }

    // 输入图的边
    int m;  // 边的数量
    cout << "Enter the number of edges: ";
    cin >> m;

    cout << "Enter the edges (u, v, weight):\n";
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u][v] = w;
        // 如果是无向图，取消下面这行注释
        graph[v][u] = w;
    }

    // 调用Floyd-Warshall算法
    floydWarshall(graph, n);

    return 0;
}