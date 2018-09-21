#include <iostream>
#include <climits>
#include <cstring>
#define N 1025
using namespace std;

int tree[4*N][4*N];
int n;

void update(int node, int s, int e, int y, int val, int o){
	if(s>y || e<y) return;
	if(s==e){
		tree[o][node]=val;
		return;
	}
	int m=(s+e)/2;
	update(2*node, s, m, y, val, o);
	update(2*node+1, m+1, e, y, val, o);
	tree[o][node] = tree[o][2*node]+tree[o][2*node+1];
}

void update1(int node, int s, int e, int x, int y, int val){
	if(s>x || e<x) return;
	if(s==e){
		update(1, 0, n-1, y, val, node);
		return;
	}
	int m=(s+e)/2;
	update1(2*node, s, m, x, y, val);
	update1(2*node+1, m+1, e, x, y, val);
	update(1, 0, n-1, y, val, node);
}

int sum(int node, int s, int e, int yl, int yr, int o){ //o=outer tree index
	if(s>yr || e<yl) return 0;
	if(s>=yl && e<=yr) return tree[o][node];
	int m=(s+e)/2;
	return sum(2*node, s, m, yl, yr, o)+sum(2*node+1, m+1, e, yl, yr, o);
}

int sum1(int node, int s, int e, int xl, int xr, int yl, int yr){
	if(s>xr || e<xl) return 0;
	if(s>=xl && e<=xr) return sum(1, 0, n-1, yl, yr, node);
	int m=(s+e)/2;
	return sum1(2*node, s, m, xl, xr, yl, yr)+sum1(2*node+1, m+1, e, xl, xr, yl, yr);
}

int main() {
	int t; scanf("%d", &t);
	while(t--){
		scanf("%d", &n);
		memset(tree, 0, sizeof tree);
		while(1){
			string s; cin>>s;
			if(s=="END") break;
			if(s=="SET"){
				int x,y,val; scanf("%d%d%d", &x, &y, &val);
				update1(1, 0, n-1, x, y, val);
			}
			else if(s=="SUM"){
				int x1, y1, x2, y2; scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
				printf("%d\n", sum1(1, 0, n-1, x1, x2, y1, y2));
			}
		}
		printf("\n");
	}
	return 0;
}
