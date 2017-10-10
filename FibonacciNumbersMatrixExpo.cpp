//MATRIX EXPONENTIATION TO FIND NTH FIBONACCI NUMBER
//TIME COMPLEXITY O(logN)
// |Fn   Fn-1| = |1 1|^n
// |Fn-1 Fn-2| = |1 0|
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

void multMatrix(vector<vector<int>> &res, vector<vector<int>> &m1, vector<vector<int>> &m2){
    res[0][0] = m1[0][0]*m2[0][0] + m1[0][1]*m2[1][0];
    res[0][1] = m1[0][0]*m2[0][1] + m1[0][1]*m2[1][1];
    res[1][0] = m1[1][0]*m2[0][0] + m1[1][1]*m2[1][0];
    res[1][1] = m1[1][0]*m2[0][1] + m1[1][1]*m2[1][1];
}

void matrixExpo(vector<vector<int>> &M, int n){
    if(n==0) {
        //Identity Matrix
        M[0][0] = 1;
        M[0][1] = 0;
        M[1][0] = 0;
        M[1][1] = 1;
        return;
    }
    vector<vector<int>> v(M.begin(), M.end()); //v = M
    matrixExpo(v, n/2); //v = M^(n/2)
    if(n & 1) {
        vector<vector<int>> v1(2, vector<int>(2));
        multMatrix(v1, v, v); // v1 = v*v
        vector<vector<int>> v2(M.begin(), M.end()); //v2 = M
        multMatrix(M, v1, v2); // M = v1*v2 = (M^(n/2))*(M^(n/2))*M
    }
    else{
        multMatrix(M, v, v); // M = v*v = (M^(n/2))*(M^(n/2))
    }
}

long long fibo(int n){
    if(n==0) return 0;
    vector<vector<int>> M(2, vector<int>(2));
    M[0][0] = 1;
    M[0][1] = 1;
    M[1][0] = 1;
    M[1][1] = 0;
    matrixExpo(M, n-1);
    return M[0][0];
}

int main()
{   
    for(int i=0; i<101; i++) cout<<fibo(i)<<" ";
    return 0;
}
