#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// AOV
// 拓扑排序函数
vector<int> topologicalSort(int n, vector<vector<int>>& adj) {
    vector<int> inDegree(n, 0);  // 存储每个节点的入度
    vector<int> result;          // 存储拓扑排序的结果
    queue<int> q;                // 用于存储入度为0的节点

    // 计算每个节点的入度
    for (int u = 0; u < n; u++) {
        for (int v : adj[u]) { // 对 u -> v 的每个v节点计算入度
            inDegree[v]++;
        }
    }

    // 将所有入度为0的节点加入队列
    for (int u = 0; u < n; u++) {
        if (inDegree[u] == 0) {
            q.push(u);
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        result.push_back(u);  

        for (int v : adj[u]) { // 对于 u -> v 的每个v节点
            inDegree[v]--;  // 减少邻接节点的入度
            if (inDegree[v] == 0) {
                q.push(v);  // 如果入度为0，加入队列
            }
        }
    }

    // 如果结果中的节点数量不等于n，说明图中有环
    if (result.size() != n) {
        cout << "Graph has a cycle, topological sort not possible!" << endl;
        return {};
    }

    return result;
}

int main() {
    int n, m;  // n: 节点数量, m: 边数量
    cout << "Enter the number of vertices: ";
    cin >> n;
    cout << "Enter the number of edges: ";
    cin >> m;

    // 邻接表表示图
    vector<vector<int>> adj(n);

    // 输入图的边
    cout << "Enter the edges (u, v):\n";
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);  // 添加有向边 u -> v
    }

    // 调用拓扑排序函数
    vector<int> result = topologicalSort(n, adj);

    // 输出拓扑排序结果
    if (!result.empty()) {
        cout << "Topological Sort Order:\n";
        for (int u : result) {
            cout << u << " ";
        }
        cout << endl;
    }

    return 0;
}

/*
1. 项目的最早完成时间取决于 最长的路径（即关键路径）。只有所有前置活动都完成后，事件 ( j ) 才能发生。
2. 项目的最晚完成时间取决于 最短的路径。如果事件 ( i ) 的最晚发生时间超过了某个后继事件 ( j ) 
   的最晚发生时间减去活动 ( (i, j) ) 的持续时间，那么整个项目的完成时间将会被推迟。
*/ 3304542560