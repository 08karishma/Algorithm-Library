//KRUSKAL'S ALGORITHM TO FIND MINIMUM SPANNING TREE
//RUN TIME O(ElogV)
#include <iostream>
#include <climits>
#include <cstring>
#include <algorithm>
#include <vector>
#define MAX  100001  
#define NINF INT_MIN
#define INF INT_MAX
#define ll long long
#define si(n) scanf("%d", &n)
#define sll(n) scanf("%lld", &n)
#define pi(n) printf("%d", n)
#define pin(n) printf("%d\n", n)
#define pll(n) printf("%lld", n)
#define plln(n) printf("%lld\n",n)
using namespace std;

struct edge{
    ll len; int u, v;
    bool operator<(struct edge &e1) {
        return (this->len < e1.len);
    }
};

edge E[300001];
ll p;
int n,m;
int id[1001];

void initialize(){
    for(int i=1; i<=n; i++) id[i]=i;
}

int root(int x){
    while(id[x] != x){
        id[x] = id[id[x]];
        x =id[x];
    }
    return x;
}

void union_(int a, int b){
    int r1 = root(a);
    int r2 = root(b);
    id[r1] = r2;
}

int main() {
    int t; si(t);
    while(t--){
        sll(p); si(n); si(m);
        for(int i=0; i<m; i++){
            int a,b; ll c; si(a); si(b); sll(c);
            edge e; e.len = c; e.u=a; e.v=b;
            E[i] = e;
        }
        sort(E, E+m);

        //KRUSKAL'S ALGORITHM
        initialize();
        ll mst_cost = 0;
        for(int i=0; i<m; i++){
            int a = E[i].u, b=E[i].v;
            if(root(a) != root(b)){
                union_(a, b);
                mst_cost += E[i].len;
            }
        }
        mst_cost *= p;
        plln(mst_cost);
    }
    return 0;
}
