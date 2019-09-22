//https://www.spoj.com/submit/MATSUM/id=19011663
#include <iostream>
#include <climits>
#include <cstring>
#define N 1025
using namespace std;

int BIT[N][N];
int arr[N][N];
int n;

void update(int x , int y , int val){
    for(; x<=n; x+=(x&-x)){
    	int y1=y;
    	for(; y1<=n; y1+=y1&-y1){
    		BIT[x][y1]+=val;
    	}
    }
}

int sum(int x , int y){
    int ans=0;
    for(; x>0; x-=(x&-x)){
    	int y1=y;
    	for(;y1>0; y1-=(y1&-y1)){
    		ans += BIT[x][y1];
    	}
    }
    return ans;
}

int main() {
	int t; scanf("%d", &t);
	while(t--){
		scanf("%d", &n);
		memset(BIT, 0, sizeof BIT);
		memset(arr, 0, sizeof arr);
		while(1){
			char s[10]; scanf("%s", s);
			if(s[0]=='E') break;
			if(s[1]=='E'){
				int x,y,val; scanf("%d%d%d", &x, &y, &val);//x,y 0-indexed
			//	int org = sum(x+1, y+1)- sum(x, y+1) - sum(x+1, y) + sum(x,y);
				int upd = val-arr[x][y];
				arr[x][y]=val;
				update(x+1, y+1, upd); //BIT works on 1-indexed arr
			}
			else if(s[1]=='U'){
				int x1, y1, x2, y2; scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
				int ans = sum(x2+1, y2+1) - sum(x2+1, y1) - sum(x1, y2+1) + sum(x1, y1);
				printf("%d\n", ans);
			}
		}
		printf("\n");
	}
	return 0;
}
