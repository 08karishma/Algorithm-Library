//NEWTON RAPHSON METHOD TO FIND ROOT OF f(x)=0
#include <iostream>
#include <climits>
#include <cstring>
#include <vector>
#include <math.h>
#define MAX  100001  
#define NINF INT_MIN
#define INF INT_MAX
#define ll long long
#define si(n) scanf("%d", &n)
#define sll(n) scanf("%lld", &n)
#define pi(n) printf("%d", n)
#define pin(n) printf("%d\n", n)
#define pll(n) printf("%lld", n)
#define plln(n) printf("%lld\n", n)
using namespace std;

double A, B, C; //function parameters
const double eps = 1e-7; //epsilon

double f(double x){ //returns f(x)
    return (A*x + B*sin(x) - C);
}

double f_dash(double x){ //returns f'(x)
    return A + B*cos(x);
}

double absl(double d){
    if(d<0) return -d;
    return d;
}

int main() {
    int t; si(t);
    while(t--){
        scanf("%lf%lf%lf", &A, &B, &C);
        double x1, x0 = C/A;
        while(1){
            double fx = f(x0);
            if(absl(fx) < eps) break;
            double fdx = f_dash(x0);
            x1 = x0 - (fx/fdx);
            x0 = x1;
        }
        printf("%.6f\n", x0);
    }
    return 0;
}