//LCA USING DYNAMIC PROGRAMMING
//BUILDING PA[] ARRAY TAKES O(NlogN) time
//LCA() takes O(logH) time, worst case => H=N
#include <iostream>
#include <vector>
#include <cstring>
#include <math.h>
#include <map>
#include <algorithm>
#include <climits>
#define f first
#define s second
#define MAXN 10001
#define LN 14
#define ll long long
#define INF -1e+16
#define MOD 1000000007
using namespace std;

vector<int> adj[MAXN];
int pa[MAXN][LN];
int n;
int depth[MAXN];

void dfs(int cur, int prev){
    pa[cur][0] = prev;
    depth[cur] = (prev==-1) ? 0 : depth[prev]+1;
    for(int i=0; i<adj[cur].size(); i++){
        if(adj[cur][i] != prev){
            dfs(adj[cur][i], cur);
        }
    }
}

int LCA(int u, int v){
    if(depth[u] < depth[v]) return LCA(v, u);
    int diff = depth[u] - depth[v];
    for(int i=0; i<LN; i++){
        if((diff>>i)&1) u=pa[u][i];
    }
    if(u!=v){
        for(int i=LN-1; i>=0; i--){
            if(pa[u][i] != pa[v][i]){
                u = pa[u][i];
                v = pa[v][i];
            }
        }
        u = pa[u][0];
    }    
    return u;
}

int main()
{
    int t; cin>>t;
    while(t--){
        scanf("%d", &n);
        for(int i=1; i<=n; i++){
            adj[i].clear(); 
        }
        memset(pa, -1, sizeof pa);
        
        for(int i=1; i<n; i++){
            int a, b; scanf("%d%d", &a, &b);
            adj[a].push_back(b);
            adj[b].push_back(a);
        }

        dfs(1, -1);
        for(int j=0; j<LN-1; j++){
            for(int i=1; i<=n; i++){
                if(pa[i][j] != -1) pa[i][j+1] = pa[pa[i][j]][j];
            }
        }
        int q; scanf("%d", &q);
        while(q--){
            int u, v; scanf("%d%d", &u, &v);
            printf("%d\n", LCA(u, v));
        }
     
    }
    return 0;
}
