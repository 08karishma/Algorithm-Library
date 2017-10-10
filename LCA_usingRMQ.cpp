//LCA TO RMQ REDUCTION USING EULER TOUR
//DFS() TAKES O(N) TIME, BUILDING SEGMENT TREE O(NLogN), EACH QUERY O(LogN)
//ref. https://www.topcoder.com/community/data-science/data-science-tutorials/range-minimum-query-and-lowest-common-ancestor
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
#define ll long long
#define INF -1e+16
#define MOD 1000000007
using namespace std;

vector<int> adj[MAXN];
int E[2*MAXN]; //nodes visited in Euler tour of the tree
int L[2*MAXN]; //L[i] = level of node at E[i]
int H[MAXN]; //first occurence of each node in E
int n, ptr;
int level[MAXN]; //depth of node in the tree
int tree[8*MAXN]; //segment tree to solve RMQ on E

void build_tree(int node, int s, int e){
    if(s==e){
        tree[node] = s;
        return;
    }
    int m=(s+e)/2;
    build_tree(2*node, s, m);
    build_tree(2*node+1, m+1, e);
    int i1=tree[2*node], i2=tree[2*node+1];
    if(L[i1] < L[i2]) tree[node] = i1;
    else tree[node] = i2;
}

int query_tree(int node, int s, int e, int l, int r){
    if(r<s || l>e) return -1;
    if(s>=l && e<=r) return tree[node];
    int m=(s+e)/2;
    int i1 = query_tree(2*node, s, m, l, r);
    int i2 = query_tree(2*node+1, m+1, e, l, r);
    if(i1==-1) return i2;
    if(i2==-1) return i1;
    if(L[i1] < L[i2]) return i1;
    else return i2;
}

void setLevels(int cur, int prev){
    level[cur] = (prev==-1) ? 0 : level[prev]+1;
    for(int i=0; i<adj[cur].size(); i++){
        if(adj[cur][i]!=prev) {
            setLevels(adj[cur][i], cur);
        }
    }
}

void dfs(int cur, int prev){
    E[ptr] = cur;
    L[ptr] = level[cur];
    H[cur] = ptr;
    ptr++;
    for(int i=0; i<adj[cur].size(); i++){
        if(adj[cur][i]!=prev) {
            dfs(adj[cur][i], cur);
            E[ptr] = cur;
            L[ptr] = level[cur];
            ptr++;
        }
    }
}

int main()
{
    int t; cin>>t;
    while(t--){
        scanf("%d", &n);
        for(int i=1; i<=n; i++){
            adj[i].clear(); 
        }
        
        for(int i=1; i<n; i++){
            int a, b; scanf("%d%d", &a, &b);
            adj[a].push_back(b);
            adj[b].push_back(a);
        }  

        ptr=0;
        setLevels(1, -1); dfs(1, -1);
        build_tree(1, 0, ptr-1);


        int q; scanf("%d", &q);
        while(q--){
            int u, v; scanf("%d%d", &u, &v);
            int l = min(H[u], H[v]), r = max(H[u], H[v]);
            int ans_ind = query_tree(1, 0, ptr-1, l, r);
            printf("%d\n", E[ans_ind]);
        }
    }
    return 0;
}
