#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int D = 0;
int M = 0, N = 0;
//int G[100005][100005] = {0};
vector<int> G[100005];
int in[100005];
bool toposort(int n);

int main(void) {
    cin >> D;
    while(D > 0) {
        cin >> N >> M;
        int u, v;
        for (int i = 1; i <= N; i++) {
            G[i].clear();
            in[i] = 0;
        }
        for(int i = 0; i < M; i++) {
            cin >> u >> v;
            if (u == v) continue;
            else {
                G[u].push_back(v);
                in[v]++;
            }
        }
        // for(int i = 0; i < M; i++) {
        //     cin >> u >> v;
        //     G[u][v]++;
        //     //G[v][u]++;
        //     in[v]++;
        // }
        if (!toposort(N)) cout << "Impossible!" << endl;
        //G[100005] = {0};
        D--;
    }
    return 0;
}

bool toposort(int n) {
  vector<int> L;
  //queue<int> S;
  priority_queue<int, vector<int>, greater<int>> S;
  //priority_queue<int> S;
  for (int i = 1; i <= n; i++)
    if (in[i] == 0) S.push(i);
  while (!S.empty()) {
    //int u = S.front();
    int u = S.top();
    S.pop();
    L.push_back(u);
    for (auto v : G[u]) {
      if (--in[v] == 0) {
        S.push(v);
      }
    }
  }
  if (L.size() == n) {
    for (auto i : L) cout << i << ' ';
    cout << endl;
    return true;
  }
  return false;
}