//FORD FULKERSON FOR MAX FLOW 
//O(E*f) where E is no of edges and f is maximum flow in the network
#include <iostream>
#include <cstring>
#include <queue>
#define f first
#define s second
#define MAX 201
#define INF 10000
using namespace std;

int source, sink;
int n; //no of nodes
int cap[MAX][MAX];
int vis[MAX];

int bfs(){
    memset(vis, 0, sizeof vis);
    queue<int> q;
    q.push(source);
    vis[source]=1;
    int from[n+1];
    memset(from, -1, sizeof from);
    int done=0;
    while(!q.empty() && !done){
        int t=q.front();
        q.pop();
        for(int v=1; v<=n; v++){
            if(!vis[v] && cap[t][v]>0){
                q.push(v);
                from[v]=t;
                vis[t]=1;
                if(v==sink) done=1;
            }
        } 
    }
    int path_cap=INF;
    int cur=sink;
    while(from[cur]>-1){
        int prev=from[cur];
        path_cap=min(path_cap, cap[prev][cur]);
        cur=prev;
    }
    cur=sink;
    while(from[cur]>-1){
        int prev=from[cur];
        cap[prev][cur]-=path_cap;
        cap[cur][prev]+=path_cap;
        cur=prev;
    }
    if(path_cap==INF) return 0;
    return path_cap;
}

int max_flow(){
    int res=0;
    while(1){
        int path_cap = bfs();
        if(path_cap==0) break;
        res+=path_cap;
    }
    return res;
}

int main()
{
    int t; scanf("%d", &t);
    while(t--){
        scanf("%d", &n);
        source=1; sink=n;
        memset(cap, 0, sizeof cap);
        for(int i=1; i<n; i++){
            int k; scanf("%d", &k);
            while(k--){
                int v; scanf("%d", &v);
                if(i==1 || v==n) cap[i][v]=1;
                else cap[i][v]=INF;
                cap[v][i]=0;
            }
        }
        printf("%d\n", max_flow());
    }   
    return 0;
}
