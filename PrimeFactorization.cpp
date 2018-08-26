#include <iostream>
#include <climits>
#include <cstring>
#define f first
#define s second
using namespace std;

int main() {
	// int t; scanf("%d", &t);
	while(1){
		long long n; scanf("%lld", &n);
		if(n==0) break;
		int cnt=0;
		
		while(n%2==0){
			n=n/2; cnt++;
		}
		if(cnt>0) printf("2^%d ", cnt);
		
		for(long long i=3; i*i<=n; i+=2){
			cnt=0;
			while(n%i==0){
				n=n/i; cnt++;
			}
			if(cnt>0) printf("%lld^%d ", i, cnt);
		}
		
		if(n>1) printf("%lld^1 ", n);
		printf("\n");
	}
	return 0;
}
