//DIJKSTRA'S FORMULA FOR FIBONACCI NUMBERS
// if n is even then k = n/2:
// F(n) = [2*F(k-1) + F(k)]*F(k)
// if n is odd then k = (n + 1)/2
// F(n) = F(k)*F(k) + F(k-1)*F(k-1)
// time complexity O(logn)
#include <iostream>
#include <vector>
#include <cstring>
#include <math.h>
#include <queue>
#include <algorithm>
#include <climits>
#define f first
#define s second
#define MAXN 1001
#define ll long long
#define INF LLONG_MAX
#define MOD 1000000007
using namespace std;

long long dp[MAXN];

long long fibo(int n){
    if(n==0) return 0;
    if(n==1 || n==2) return 1;
    if(dp[n] != -1) return dp[n];
    if(n%2 == 0){
        int k = n/2;
        return dp[n] = fibo(k)*(fibo(k+1)+fibo(k-1));
    }
    int k = (n+1)/2;
    return dp[n] = fibo(k)*fibo(k) + fibo(k-1)*fibo(k-1);
}

int main()
{   
    int t; cin>>t;
    memset(dp, -1, sizeof dp);
    while(t--){
        int n;
        cin>>n;
        cout<<fibo(n)<<endl;
    }
    return 0;
}
