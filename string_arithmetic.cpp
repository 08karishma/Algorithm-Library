#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string divide_str(string s, int n){
    if(s=="0") return 0;
    string res="";
    int cur=0;
    int i=0, cnt;
    while(i<s.length()){
        cnt=0;
        while(i<s.length() && cur<n){
            if(!res.empty() && cnt>0) res.push_back('0');
            cnt++;
            cur = cur*10 + (s[i]-'0'); i++;
        }
        res.push_back((cur/n) +'0');
        cur = cur%n;
    }
    return res;
}

string add_str(string a, string b){
    string res="";
    int carry=0;
    int n1=a.length(), n2=b.length();
    int i=n1-1, j=n2-1;
    while(i>=0 && j>=0){
        int ans = (a[i]-'0')+(b[j]-'0')+carry;
        carry = ans/10;
        ans = ans%10;
        res.append(1, ans+'0');
        i--; j--;
    }
    while(i>=0){
        int ans = (a[i]-'0')+carry;
        carry = ans/10;
        ans = ans%10;
        res.append(1, ans+'0');
        i--; 
    }
    while(j>=0){
        int ans = (b[j]-'0')+carry;
        carry = ans/10;
        ans = ans%10;
        res.append(1, ans+'0');
        j--;
    }
    while(carry>0){
        int ans = carry;
        carry = ans/10;
        ans = ans%10;
        res.append(1, ans+'0');
    }
    reverse(res.begin(), res.end());
    return res;
}

string subt_str(string a, string b){ //return (a-b), assuming a>b
    string res="";
    int carry=0;
    int n1=a.length(), n2=b.length();
    int i=n1-1, j=n2-1;
    while(i>=0 && j>=0){
        int a1=a[i]-'0'; int b1=b[j]-'0';
        a1-=carry;
        int ans;
        if(a1>=b1){
            ans=a1-b1; carry=0;
        }
        else{
            a1+=10; ans=a1-b1; carry=1;
        }
        res.append(1, ans+'0');
        i--; j--;
    }
    while(i>=0){
        int a1=a[i]-'0'; 
        a1-=carry;
        int ans;
        if(a1>=0){
            ans=a1; carry=0;
        }
        else{
            a1+=10; ans=a1; carry=1;
        }
        res.append(1, ans+'0');
        i--; 
    }
    reverse(res.begin(), res.end());
    i=0;
    while(i<res.length() && res[i]=='0') i++;
    if(i==res.length()) return "0";
    if(i>0) res=res.substr(i, res.length()-i);
    return res;
}

string mult(string s, int n){
    string res="";
    int ans, carry=0;
    for(int i=s.length()-1; i>=0; i--){
        ans = (s[i]-'0')*n + carry;
        carry = ans/10;
        res.append(1, (ans%10) + '0');
    }
    while(carry!=0){
        res.append(1, (carry%10) + '0');     
        carry = carry/10;   
    }
    reverse(res.begin(), res.end());
    return res;
}

string mult_str(string s1, string s2){
    string res="0";
    int cnt = 0;
    string temp;
    for(int i=s2.length()-1; i>=0; i--){
        temp = mult(s1, s2[i]-'0');
        temp.append(cnt++, '0');
        res = add_str(res, temp);
    }
    return res;
}

int main() {
    string a,b;
    cin>>a>>b;
    cout<<a<<"+"<<b<<"="<<add_str(a, b)<<endl;
    cout<<a<<"-"<<b<<"="<<subt_str(a, b)<<endl;
    cout<<a<<"*"<<b<<"="<<mult_str(a, b)<<endl;
    return 0;
} 