//LONGEST INCREASING SUBSEQUENCE IN O(nlogn)
//https://stackoverflow.com/questions/2631726/how-to-determine-the-longest-increasing-subsequence-using-dynamic-programming
#include <iostream>
using namespace std;

//return minimum j s.t. tail[j]>=key
int lowerBound(int *v, int *tail, int l, int r, int key){
    while(l <= r){
        int m = (l+r)/2;
        if(v[tail[m]] < key) l = m+1;
        //if(v[tail[m]] <= key) l = m+1; --TO GET NON-STRICTLY INCREASING SUBSEQ.
        else r = m-1;
    }
    return l;
}

int lis(int *v, int n){

    //tail[i] stores index of last element of subs of length i+1
    int *tail = new int[n];
    tail[0] = 0;
    int len = 1;

    int par[n];
    par[0] = -1;

    for(int i=1; i<n; i++){
        if(v[i] > v[tail[len-1]]) {
        //if(v[i] >= v[tail[len-1]]) { --TO GET NON-STRICTLY INCREASING SUBSEQ.
            par[i] = tail[len-1];
            tail[len] = i;
            len++;
        }
        else{
            int j = lowerBound(v, tail, 0, len-1, v[i]);
            par[i] = (j==0) ? -1 : tail[j-1];
            tail[j] = i;
        }
    }

    cout<<"The LIS is: "; //print LIS in reverse
    int k = tail[len-1];
    int cnt=0;
    while(k!=-1){
        cout<<v[k]<<" ";
        k = par[k];
        cnt++;
    }
    cout<<endl;

    return len;
}

int main() {
    
    int n; cin>>n;
    //int v[] = { 2, 5, 3, 7, 11, 8, 10, 13, 6 };
    int *v = new int[n];
    for(int i=0; i<n; i++) cin>>v[i];

    cout<<lis(v, n)<<endl;
    return 0;
}
