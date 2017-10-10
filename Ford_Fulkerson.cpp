//FORD FULKERSON TO FIND MAXIMUM MATCHING IN A GRAPH
//TIME COMPLEXITY 
//with adj list bfs takes O(E) time
//with adj matrix (used in this) bfs take O(V^2) time
//overall time compl = O(f*(time for bfs)), where f is max flow, since on each bfs, flow increases by atleast 1
//note: when bfs is used for finding augmenting paths, it's edmond karp and it runs in O(V(E^2))
#include <iostream>
#include <climits>
#include <cstring>
#include <algorithm>
#include  <queue>
#define MAX 201
#define NINF INT_MIN
#define INF INT_MAX
#define ll long long
using namespace std;

int n;
ll cap[MAX][MAX];
int s, t;

ll bfs(){
    int vis[n+1];
    memset(vis, 0, sizeof vis);
    queue<int> q;
    int from[n+1];
    memset(from, -1, sizeof from);

    q.push(1);
    vis[1]=1;
    while(!q.empty()){
        int u = q.front(); q.pop();
        for(int v=1; v<=n; v++){
            if(cap[u][v]>0 && !vis[v]) {
                q.push(v);
                vis[v]=1; 
                from[v]=u;
            }
        }
    }
    ll path_cap=INF;
    int cur=t;
    while(from[cur]!=-1){
        path_cap = min(path_cap, cap[from[cur]][cur]);
        cur = from[cur];
    }
    cur=t;
    while(from[cur]!=-1){
        cap[from[cur]][cur] -= path_cap;
        cap[cur][from[cur]] += path_cap;
        cur = from[cur];
    }
    return path_cap;
}

ll ford_fulk(){
    ll ans = 0;
    while(1){
        ll x = bfs();
        if(x==INF) break;
        ans += x;
    }
    return ans;
}

int main() {
    int tc; scanf("%d", &tc);
    while(tc--){
        scanf("%d", &n);
        memset(cap, 0, sizeof cap);
        //  input capacities here
        // cap[u][v] is capacity of E(u, v)
        for(int i=1; i<n; i++){
            int k; scanf("%d", &k);
            while(k--){
                int j; scanf("%d", &j);
                if(i==1 || j==n) cap[i][j]=1;
                else cap[i][j]=INF;
            }
        }
        s=1; t=n;
        printf("%lld\n", ford_fulk());
    }

    return 0;
}