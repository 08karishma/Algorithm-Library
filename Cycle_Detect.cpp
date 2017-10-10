//DETECT CYCLE IN A DIRECTED GRAPH
#include <iostream>
#include <vector>
#include <cstring>
#include <stack>
#include <algorithm>
#include  <queue>
#define MAX 5001
using namespace std;

vector<int> adj[MAX];
int vis[MAX];
int isRunning[MAX]; //to detect cycle

bool hasCycle(int u){
    vis[u]=1;
    isRunning[u]=1;
    for(int j=0; j<adj[u].size(); j++) {
        int v = adj[u][j];
        if(isRunning[v]) return true;
        if(!vis[v]){
            if(hasCycle(v)) return true;
        }
    }
    isRunning[u]=0;
    return false;
}

int main() {
    int n, m; scanf("%d%d", &n, &m);

    for(int i=0; i<m; i++){
        int u, v; scanf("%d%d", &u, &v);
        adj[u].push_back(v);
    } 

    int flag=0;
    memset(vis, 0, sizeof vis);
    for(int i=1; i<=n && !flag; i++) {
        if(!vis[i]) flag=hasCycle(i);
    }

    if(flag) printf("Sandro fails.\n");
    else printf("No cycle.\n");

    return 0;
}