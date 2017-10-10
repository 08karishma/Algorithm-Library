//Knuth–Morris–Pratt string searching algorithm 
//Time complexity O(N+M), N=length of haystack, M=length of needle
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

int F[MAX];

void build_failure(string s){
    F[0]=0; //empty prefix
    F[1]=0;
    for(int i=2; i<=s.length(); i++){
        int j = F[i-1];
        while(1){
            if(s[j-1+1] == s[i-1]) {
                F[i] = j+1;
                break;
            }
            if(j==0){
                F[i]=0;
                break;
            }
            j = F[j];
        }
    }
}

int main()
{
    string needle, haystack;
    needle = "abcabc";
    haystack = "ajdlejwoabcdbjfsabcdjabcabcabcdbsjfsifo";

    build_failure(needle);
    //print failures
    for(int i=0; i<=needle.length(); i++){
        if(i==0) cout<<endl;
        else{
            cout<<needle.substr(0, i)<<" ";
            if(F[i]==0) cout<<endl;
            else cout<<needle.substr(0, F[i])<<endl;
        }
    }

    //search
    int i=0, j=0;
    while(i<haystack.length()){
        if(haystack[i] == needle[j-1+1]) {
            j++; i++;
            if(j==needle.length()){
                cout<<"found needle at "<<i-needle.length()+1<<endl;
                j = F[j];
            }
        }
        else{
            j=F[j]; i++;
        }
    }
    return 0;
}
