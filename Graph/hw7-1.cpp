#include<bits/stdc++.h>
using namespace std;
//ctor<int> edge[1000];
int ans[1010];
bool rust[1010][1010];
int main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        if(!rust[u][v]){
            ans[u]--;
            ans[v]++;
            }
        rust[u][v]=true;
    }
    for(int i=0;i<n;i++){
    cout<<ans[i]<<endl;
    }
    return 0;
}
