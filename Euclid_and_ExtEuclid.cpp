#include <iostream>
#include <climits>
#include <cstring>
#include <map>
#include <vector>
#define MAX  100001  
#define NINF INT_MIN
#define INF INT_MAX
#define ll long long
using namespace std;

int extended_euclid(int a, int b, int &x, int &y){
    if(a==0){
        x=0; y=1; return b;
    }
    int x1, y1;
    int g = extended_euclid(b%a, a, x1, y1);
    x = y1 - (b/a)*x1;
    y = x1;
    return g;
}

int euclid(int a, int b){
    if(a==0){
        return b;
    }
    return euclid(b%a, a);
}

int main() {
    int x, y;
    cout<<"gcd = "<<extended_euclid(15, 35, x, y)<<endl;
    cout<<"x="<<x<<" y="<<y<<endl;
    cout<<"gcd = "<<euclid(15, 35)<<endl;
    return 0;
}