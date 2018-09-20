#include <iostream>
#include <cstring>
using namespace std;

long long tree[400001], lazy[400001];

void beLazy(int node, int s, int e){
	if(lazy[node]!=0){
		tree[node]+=(e-s+1)*lazy[node];
		if(s!=e){
			lazy[2*node] += lazy[node];
			lazy[2*node+1] += lazy[node];
		}
		lazy[node] = 0;
	}
}

void update(int node, int s, int e, int l, int r, long long val){
	beLazy(node, s, e);
	if(s>r || e<l) return;
	if(s>=l && e<=r){
		tree[node] += val*(e-s+1);
		if(s!=e){
			lazy[2*node] += val;
			lazy[2*node+1] += val;
		}
		return;
	}
	int m = (s+e)/2;
	update(2*node, s, m, l, r, val);
	update(2*node+1, m+1, e, l, r, val);
	tree[node] = tree[2*node]+tree[2*node+1];
}

long long query(int node, int s, int e, int l, int r){
	beLazy(node, s, e);
	if(s>r || e<l) return 0;
	if(s>=l && e<=r) return tree[node];
	int m = (s+e)/2;
	return query(2*node, s, m, l, r)+query(2*node+1, m+1, e, l, r);
}

int main() {
	int t; cin>>t;
	while(t--){
		int n; cin>>n;
		memset(tree, 0, sizeof tree);
		memset(lazy, 0, sizeof lazy);
		
		int C; cin>>C;
		while(C--){
			int type, p, q; cin>>type>>p>>q;
			p--; q--;
			if(type==0){
				int v; cin>>v;
				update(1, 0, n-1, p, q, v);
			}
			else{
				cout<<query(1, 0, n-1, p, q)<<endl;
			}
		}
	}
	return 0;
}
