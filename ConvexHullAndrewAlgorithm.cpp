//ALGORITHM TO FIND CONVEX HULL IN O(nlogn) TIME
#include <iostream>
#include <vector>
#include <cstring>
#include <math.h>
#include <stack>
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

struct point{
    int ind; int x; int y;
    bool operator<(const point &p1){
        if(x!=p1.x) return x<p1.x;
        if(y!=p1.y) return y<p1.y;
        return ind<p1.ind;
    }
};

int hull[MAXN];
int hull_size;
point P[MAXN];
int N;

int cross(int o, int a, int b){
    //return ao X bo
    int ans = ((P[a].x-P[o].x)*(P[b].y-P[o].y)) - ((P[b].x-P[o].x)*(P[a].y-P[o].y));
    return ans;
}

double dis(int i, int j){
    double ans = (double)(P[i].x-P[j].x)*(P[i].x-P[j].x);
    ans += (double)(P[i].y-P[j].y)*(P[i].y-P[j].y);
    ans = sqrt(ans);
    return ans;
}

//stores in hull indices of points (as in P) on hull starting from leftmost (then bottommost) point 
//and moving in ANTICLOCKWISE direction
//this function returns minimum set of such pts
//to get max set, we don't remove hull[k-1] if i, hull[k-1] & hull[k-2] are collinear
void convexHull(){
    sort(P, P+N);
    int k = 0;
    //LOWER HULL
    for(int i=0; i<N; i++){
        if(i>0 && P[i].x==P[i-1].x && P[i].y==P[i-1].y) continue; //ignore repeated points
        //if hull[k-2] -> hull[k-1] -> i is clockwise direction, then hull[k-1] can be ignored
        while(k>=2 && cross(hull[k-2], i, hull[k-1])>=0) k--; 
        hull[k++] = i;
    }
    //UPPER HULL
    int u_start = k-1; //since last point in lower hull is same as first point in upper hull
    for(int i=N-2; i>=0; i--){
        if(P[i].x==P[i+1].x && P[i].y==P[i+1].y) continue; //ignore repeated points
        //if hull[k-2] -> hull[k-1] -> i is clockwise direction, then hull[k-1] can be ignored
        while(k>=u_start+2 && cross(hull[k-2], i, hull[k-1])>=0) k--; 
        hull[k++] = i;
    }
    hull_size = k;
    //the hull will now contain the complete closed polygon eg, ABCDA
}

int main()
{   
    int t; scanf("%d", &t);
    while(t--){
        scanf("%d", &N);
        for(int i=0; i<N; i++){
            scanf("%d%d", &P[i].x, &P[i].y);
            P[i].ind = i;
        }

        convexHull();

        double ans = 0.0;
        for(int i=0; i<hull_size-1; i++){
            ans += dis(hull[i], hull[i+1]);
        }
        printf("%0.2f\n", ans);
    }
    return 0;
}
