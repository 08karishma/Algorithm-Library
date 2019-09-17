//MAXIMUM BIPARTITE MATCHING USING FORD FULKERSON MAX FLOW WITH ADJACENCY LIST
//Solution to this problem https://www.hackerrank.com/challenges/real-estate-broker/problem
#include <bits/stdc++.h>
using namespace std;

int n, m, sink, source;
vector<int> adj[2005];
int cap[2005][2005];
bool vis[2005];
int from[2005];

int bfs(){
    for(int i=0; i<=sink; i++){
        vis[i] = false;
        from[i] = -1;
    }
    queue<int> bfsQueue;
    bfsQueue.push(source);
    vis[source] = true;
    while(!bfsQueue.empty()){
        int u = bfsQueue.front();
        bfsQueue.pop();
        if(u == sink) break;
        for(int i=0; i<adj[u].size(); i++){
            int v = adj[u][i];
            if(!vis[v] && cap[u][v]>0){
                bfsQueue.push(v);
                from[v] = u;
                vis[v] = true;
            }
        }
    }

    int v = sink;
    int path_cap = INT_MAX;
    while(from[v] != -1){
        int u = from[v];
        path_cap = min(path_cap, cap[u][v]);
        v = u;
    }

    v = sink;
    while(from[v] != -1){
        int u = from[v];
        cap[u][v] -= path_cap;
        cap[v][u] += path_cap;
        v = u;
    }
    return path_cap;
}

int maxFlow(){
    int flow = 0;
    while(1){
        int augFlow = bfs();
        if(augFlow == INT_MAX){
            break;
        }
        flow += augFlow;
    }
    return flow;
}

int realEstateBroker(vector<vector<int>> clients, vector<vector<int>> houses) {
    n = clients.size();
    m = houses.size();    

    source = 0;
    sink = n+m+1;

    for(int i=source; i<=sink; i++){
        for(int j = source; j<=sink; j++){
            cap[i][j] = 0;
        }
    }

    for(int i=1; i<=n; i++){
        cap[source][i] = 1;
        adj[source].push_back(i);
        adj[i].push_back(source);
    }
    for(int j=1; j<=m; j++){
        cap[j+n][sink] = 1;
        adj[j+n].push_back(sink);
        adj[sink].push_back(j+n);
    }
    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            if(clients[i-1][0]<houses[j-1][0] && clients[i-1][1]>=houses[j-1][1]){
                cap[i][j+n] = 1;
                adj[i].push_back(j+n);
                adj[j+n].push_back(i);
            }
        }
    }
    return maxFlow();
}
