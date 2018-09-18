// TOPOLOGICAL SORTING USING BFS O(V+E)
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

    //use priority queue when an ordering between independent nodes is required
    //for ex, here we want the lexicographically smallest topological sort order to be printed
    priority_queue<int> q;
    for(int i=1; i<=n; i++){
        if(indeg[i] == 0) q.push(-i);
    }    

    vector<int> res;
    while(!q.empty()){
        int u = -q.top();
        q.pop();
        res.push_back(u);
        for(int i=0; i<adj[u].size(); i++){
            int v = adj[u][i];
            indeg[v]--;
            if(indeg[v]==0) q.push(-v);
        }
    }

    if(res.size()!=n) {
        //cycle is detected
        printf("Sandro fails.\n");
    }
    else{
        for(int i=0; i<res.size(); i++) printf("%d ", res[i]);
        printf("\n");
    }

    return 0;
}
