//Finding node in a tree which is closest to b, and lies on the path from a to c
#include <iostream>
#include <vector>
#include <cstring>
#include <math.h>
#include <map>
#include <algorithm>
#include <climits>
#define f first
#define s second
#define MAXN 100001
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
    xors[cur] = (prev==-1) ? popu[cur] : (popu[cur]^xors[prev]);
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

int get_distance(int u, int v){
    int lca = LCA(u,v);
    return depth[u]-depth[lca]+depth[v]-depth[lca];
}

//returns the node which is closest to b and lies on path from a to c
int findClosest(int a, int b, int c){

    return LCA(a, b)^LCA(b, c)^LCA(a, c);
    /*Explanation:
    int dab = get_distance(a,b);
    int dac = get_distance(a,c);
    int dbc = get_distance(b,c);
    
    if(dac == dab+dbc) return b;
    int lcaab = LCA(a,b);
    int lcaac = LCA(a,c);
    int lcabc = LCA(b,c);
    
    if(lcaab == lcaac){
        return lcabc;
    }
    if(lcaac == lcabc){
        return lcaab;
    }
    return lcaac;*/
}

int main()
{
    scanf("%d", &n);
    int q; scanf("%d", &q);
    for(int i=1; i<=n; i++){
        cin>>popu[i];
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
    
    while(q--){
        int a,b,c; scanf("%d%d%d", &a, &b, &c);        
        int ver = findClosest(a, b, c);
        cout<<ver<<endl;
    }
    
    return 0;
}
