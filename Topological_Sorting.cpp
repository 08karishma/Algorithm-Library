// TOPOLOGICAL SORTING KAHN'S ALGORITHM O(V+E)
#include <iostream>
#include <vector>
#include <cstring>
#include <stack>
#include <algorithm>
#include  <queue>
#define MAX 5001
using namespace std;

int main() {
    int n, m; scanf("%d%d", &n, &m);

    vector<int> adj[n+1];
    int vis[n+1];
    int indeg[n+1];
    memset(indeg, 0, sizeof indeg);
    memset(vis, 0, sizeof vis);

    for(int i=0; i<m; i++){
        int u, v; scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        indeg[v]++;
    } 

    vector<int> q;
    int level=0;
    int flag=1;
    while(flag){
        flag=0;
        for(int i=1; i<=n; i++){
            if(vis[i]==0 && indeg[i] == 0) {
                flag=1;
                q.push_back(i); vis[i]=1;
                cout<<level<<" "<<i<<endl;
                for(int j=0; j<adj[i].size(); j++) indeg[adj[i][j]]--;
            }
        }
        level++;
    }

    flag=1;
    for(int i=1; i<=n && flag; i++) {
        if(!vis[i]) flag=0;
    }
    if(!flag) printf("ERROR\n"); //cycle detected
    else{
        for(int i=0; i<q.size(); i++){
            printf("%d ", q[i]);
        }
        printf("\n");
    }
    return 0;
}