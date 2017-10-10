//ALGORITHM TO FIND CONVEX HULL IN O(n^2) TIME
#include <iostream>
#include <vector>
#include <cstring>
#include <math.h>
#include <queue>
#include <algorithm>
#include <climits>
#define pii pair<int,int>
#define f first
#define s second
#define MAXN 100001
#define ll long long
#define INF LLONG_MAX
#define MOD 1000000007
using namespace std;

vector<int> hull;
int x[MAXN], y[MAXN];
int N;

int cross(int o, int a, int b){
    //return ao X bo
    int ans = ((x[a]-x[o])*(y[b]-y[o])) - ((x[b]-x[o])*(y[a]-y[o]));
    return ans;
}

double dis(int i, int j){
    double ans = (double)(x[i]-x[j])*(x[i]-x[j]);
    ans += (double)(y[i]-y[j])*(y[i]-y[j]);
    ans = sqrt(ans);
    return ans;
}

//stores in vector hull indices of points on hull starting from bottom-left point 
//and moving in CLOCKWISE direction
void convexHull(){
    int vis[N];
    memset(vis, 0, sizeof vis);

    //find leftmost-bottommost point
    int p = 0;
    for(int i=1; i<N; i++){
        if(y[i]<y[p] || (y[i]==y[p] && x[i]<x[p])) p=i;
    }

    int start = p;
    hull.push_back(p);
    do{
        int n = -1; //next point in hull
        for(int i=0; i<N; i++){
            if(vis[i]==1) continue; //already in hull
            if(n==-1) n = i;
            int c = cross(p, i, n);
            if(c < 0) n = i;
            else if(c==0){
                //do this if we need to choose minimum number of pts in the hull
                //next pt should be farthest from p
                if(dis(n, p) < dis(i, p)) n = i; 
                //to include maximum no of pts in the hull
                //next pt should be nearest from p
                //if(dis(n,p) > dis(i, p)) n = i;
            }
        }
        hull.push_back(n);
        vis[n]=1;
        p=n;
    }while(p!=start);
}

int main()
{   
    int t; scanf("%d", &t);
    while(t--){
        scanf("%d", &N);
        for(int i=0; i<N; i++){
            scanf("%d%d", &x[i], &y[i]);
        }
        hull.clear();
        convexHull();

        //circumference of the hull
        double ans = 0.0;
        for(int i=0; i<hull.size()-1; i++){
            ans += dis(hull[i], hull[i+1]);
        }
        printf("%0.2f\n", ans);
    }
    return 0;
}
