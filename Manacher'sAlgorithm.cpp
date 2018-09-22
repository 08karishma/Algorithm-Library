//MANACHER'S ALGORITHM TO FIND LONGEST PALINDROMIC SUBSTRING 
//RUNNING TIME O(N)
#include <iostream>
#include <vector>
#include <cstring>
#include <math.h>
#include <map>
#include <algorithm>
#include <climits>
#define f first
#define s second
#define MAX 10001
#define LN 14
#define ll long long
#define INF -1e+16
#define MOD 1000000007
using namespace std;

//each element is iterated at most twice
string manacher(string s1){
    string s = "$";
    for(int i=0; i<s1.length(); i++){
        s += "#";
        s.append(1, s1[i]);
    }
    s += "$";

    int n = s.length();
    int P[n];
    memset(P, 0, sizeof P);
    int c=0, r=0;
    for(int i=1; i<n; i++){
        if(i<r){
            int iMirr = c-(i-c);
            P[i] = min(P[iMirr], r-i);
        }
        while(i+P[i]+1<n && i-P[i]-1>=0 && s[i+P[i]+1] == s[i-P[i]-1]){
            P[i]++;
        }
        if(i+P[i] > r){
            c = i;
            r = i+P[i];
        }
    }

    int max_len=0;
    c=-1;
    for(int i=0; i<n; i++){
        if(P[i]>=max_len) {
            max_len = P[i];
            c = i;
        }
    }

    string ans = "";
    for(int i=c-P[c]; i<=c+P[c]; i++){
        if(s[i]!='#' && s[i]!='$') ans.append(1, s[i]);
    }
    return ans;
}

int main(){

    cout<<manacher("ssbdbsbbsbdbsaaa")<<endl;
    return 0;
}
