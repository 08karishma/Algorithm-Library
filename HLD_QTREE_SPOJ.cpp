#include <iostream>
#include <vector>
#define MAX 10001
#define LN 14
using namespace std;

vector<int> costs[MAX], indexx[MAX], adj[MAX];
int n;
int chainNo, ptr;
int subSize[MAX], pa[LN][MAX], depth[MAX];
int posInBase[MAX], baseArray[MAX]; //the array upon which segment tree will be built
int otherEnd[MAX], chainHead[MAX], chainInd[MAX];
int st[6*MAX];

void make_tree(int cur, int s, int e){
	if(s==e-1){
		st[cur]=baseArray[s];
		return;
	}
	int m=(s+e)/2;
	make_tree(2*cur, s, m);
	make_tree(2*cur+1, m, e);
	st[cur] = max(st[2*cur], st[2*cur+1]);
}

void update_tree(int cur, int s, int e, int ind, int val){
	if(ind<s || ind>=e) return;
	if(s==e-1) {
		st[cur]=val;
		return;
	}
	int m=(s+e)/2;
	update_tree(2*cur, s, m, ind, val);
	update_tree(2*cur+1, m, e, ind, val);
	st[cur] = max(st[2*cur], st[2*cur+1]);
}

int query_tree(int cur, int s, int e, int l, int r){
	if(r<=s || l>=e) return -1;
	if(l<=s && r>=e) return st[cur];
	int m=(s+e)/2;
	return max(query_tree(2*cur, s, m, l, r), query_tree(2*cur+1, m, e, l, r));
}

int query_up(int u, int v){
	if(u==v) return 0;
	int vchain=chainInd[v], uchain;
	int ans =-1;
	while(1){
		uchain = chainInd[u];
		if(uchain == vchain){
			if(u==v) break;
			ans = max(ans, query_tree(1, 0, ptr, posInBase[v]+1, posInBase[u]+1));
			break;
		}
		ans = max(ans, query_tree(1, 0, ptr, posInBase[chainHead[uchain]], posInBase[u]+1));
		u=chainHead[uchain];
		u=pa[0][u];
	}
	return ans;
}

void dfs(int cur, int prev){
	depth[cur] = (prev==-1) ? 0:depth[prev]+1;
	pa[0][cur]=prev;	
	subSize[cur]=1;
	for(int i=0; i<adj[cur].size(); i++){
		if(adj[cur][i]!=prev){
			otherEnd[indexx[cur][i]]=adj[cur][i];
			dfs(adj[cur][i], cur);
			subSize[cur]+=subSize[adj[cur][i]];
		}
	}
}

void HLD(int curNode, int cost, int prev){
	if(chainHead[chainNo]==-1) chainHead[chainNo]=curNode;
	chainInd[curNode]=chainNo;
	posInBase[curNode]=ptr;
	baseArray[ptr++]=cost;
	
	int sc=-1, ncost;
	for(int i=0; i<adj[curNode].size(); i++){
		if(adj[curNode][i]!=prev){
			if(sc==-1 || subSize[sc]<subSize[adj[curNode][i]]){
				sc=adj[curNode][i];
				ncost=costs[curNode][i];
			}
		}
	}
	if(sc!=-1){
		HLD(sc, ncost, curNode);
	}
	
	for(int i=0; i<adj[curNode].size(); i++){
		if(adj[curNode][i]!=prev && adj[curNode][i]!=sc){
			chainNo++;
			HLD(adj[curNode][i], costs[curNode][i], curNode);
		}
	}
}

int LCA(int u, int v){
	if(depth[u]<depth[v]) swap(u,v);
	int diff=depth[u]-depth[v];
	for(int i=0; i<LN; i++){
		if( (diff>>i)&1 ) u=pa[i][u];
	}
	if(u==v) return u;
	for(int i=LN-1; i>=0; i--){
		if(pa[i][u] != pa[i][v]){
			u=pa[i][u];
			v=pa[i][v];
		}
	}
	return pa[0][u];
}

void query(int u, int v){
	int lca=LCA(u,v);
	// cout<<"u="<<u<<" v="<<v<<" lca="<<lca<<endl;
	int ans=query_up(u, lca);
	ans = max(ans, query_up(v, lca));
	printf("%d\n", ans);
}

void change(int i, int val){
	int u=otherEnd[i];
	update_tree(1, 0, ptr, posInBase[u], val);
}

int main() {
	int t; scanf("%d", &t);
	while(t--){
		scanf("%d", &n);
		for(int i=0; i<n; i++){
			adj[i].clear(); costs[i].clear(); indexx[i].clear();
			chainHead[i]=-1;
			for(int j=0; j<LN; j++) pa[j][i]=-1;
		}
		for(int i=1; i<n; i++){
			int u,v,c; scanf("%d%d%d", &u, &v, &c);
			u--; v--;
			adj[u].push_back(v);
			costs[u].push_back(c);
			indexx[u].push_back(i-1);
			adj[v].push_back(u);
			costs[v].push_back(c);
			indexx[v].push_back(i-1);
		}
		dfs(0, -1);
		chainNo=0;
		ptr=0;
		HLD(0, -1, -1);
		make_tree(1, 0, ptr);
		
		for(int i=1; i<LN; i++){
			for(int j=0; j<n; j++){
				if(pa[i-1][j]!=-1){
					pa[i][j] = pa[i-1][pa[i-1][j]];
				}
			}
		}
		
		while(1){
			char s[100];
			scanf("%s", s);
			if(s[0]=='D') break;
			int a, b; scanf("%d%d", &a, &b);
			if(s[0]=='Q'){
				query(a-1, b-1);
			}
			else change(a-1, b);
		}
	}
	return 0;
}