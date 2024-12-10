#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>

using namespace std;

int D = 0;
int M = 0, N = 0;
//int G[100005][100005] = {0};
//vector<set<int>> G[100005];
//int in[100005];
bool toposort(vector<set<int>>& G, vector<int>& in, int n);

int main(void) {
    cin >> D;
    while(D > 0) {
        cin >> N >> M;
        vector<set<int>>  graph(N + 1);
        vector<set<int>>  graph2(N + 1);
        vector<int>  deDegree(N + 1, 0);
    
        // why should I use inverse toposort?
        // because you need to decide which node as output firstly
        // depending on its next node(make it smaller) 
        for (int i = 0; i < M; i++)  {
          int  from, to;
          cin >> from >> to;
          graph[from].insert(to);
          graph2[to].insert(from);
          deDegree[from] = graph[from].size();
        }
        // for(int i = 0; i < M; i++) {
        //     cin >> u >> v;
        //     G[u][v]++;
        //     //G[v][u]++;
        //     in[v]++;
        // }

        if (!toposort(graph2, deDegree, N)) cout << "Impossible!" << endl;
        //G[100005] = {0};
        D--;
    }
    return 0;
}

bool toposort(vector<set<int>>& G, vector<int>& in, int n) {
  vector<int> L;
  //priority_queue<int, vector<int>, greater<int>> S;
  priority_queue<int> S; // maxheap
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
    reverse(L.begin(), L.end());
    for (auto i : L) cout << i << ' ';
    //for(int i = L.size() - 1; i >= 0; i--) cout << L[i] << ' ';
    cout << endl;
    return true;
  }
  return false;
}