//KOSARAJU'S ALGORITHM TO FIND ALL STRONGLY CONNECTED COMPONENTS IN A DIRECTED GRAPH
//TIME COMPLEXITY O(V+E)

#include <iostream>
#include <vector>
#include <cstring>
#include <stack>
#include <algorithm>
#include  <unordered_map>
#define MAX 5001
using namespace std;

vector<int> graph[MAX], rev_graph[MAX];
stack<int> order;
int V, E;
int vis[MAX];

void dfs1(int u){
    vis[u]=1;
    for(int i=0; i<graph[u].size(); i++){
        int v =graph[u][i];
        if(!vis[v]) dfs1(v);
    }
    order.push(u);
}

void dfs2(int u){
    cout<<u<<" ";
    vis[u] = 1;
    for(int i=0; i<rev_graph[u].size(); i++){
        int v =rev_graph[u][i];
        if(!vis[v]) dfs2(v);
    }
}

int main() {

    scanf("%d%d", &V, &E);

    for(int i=1; i<=V; i++) {
        graph[i].clear();
        rev_graph[i].clear();
    }
    while(!order.empty()) order.pop();

    while(E--){
        int u,v; scanf("%d%d", &u, &v);
        graph[u].push_back(v);
        rev_graph[v].push_back(u);
    }

    memset(vis, 0, sizeof vis);
    for(int i=1; i<=V; i++){
        if(!vis[i]) dfs1(i);
    }

    memset(vis, 0, sizeof vis);
    while(!order.empty()){
        int i = order.top(); order.pop();
        if(!vis[i]) dfs2(i);
        cout<<endl;
    }

    return 0;
}