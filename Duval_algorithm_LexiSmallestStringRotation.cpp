//DUVAL'S ALGORITHM TO FIND LEXICOGRAPHICALLY SMALLEST STRING ROTATION
//LINEAR TIME COMPLEXITY
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string s_rotated(string s, int ind){
    int len = s.length();
    s += s;
    return s.substr(ind, len);
}

int lyndon_word(string s){
    int ans = 0;
    int j = 1;
    int n = s.length();
    while(j<n){
        cout<<s_rotated(s, ans)<<" "<<s_rotated(s, j)<<endl;
        int k=0;
        while(k<n && s[(j+k)%n] == s[(ans+k)%n]) k++;
        if(s[(j+k)%n] >= s[(ans+k)%n]) j = j+k+1;
        else{
            ans = min(j, ans+k+1);
            j = ans+1;
        }
    }
    cout<<s_rotated(s, ans)<<endl;
    return ans;
}

int main() {
    int t; cin>>t;
    while(t--){
        string s; cin>>s;
        cout<<lyndon_word(s)+1<<endl;
    }
    return 0;
} 