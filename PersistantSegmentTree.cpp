//PERSISTANT SEGMENT TREE
//MKTHNUM PROBLEM - SPOJ
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

struct node{
    int count;
    node *left, *right;
    node(int cnt, node *l, node *r) : count(cnt), left(l), right(r) {}
    node *insert(int s, int e, int val);
};

node *null;
map<int,int> mp, rev_mp;
int arr[MAX];
node * root[MAX];

node * node::insert(int s, int e, int val){
    if(val>=s  && val<=e){
        if(s==e) return new node(1, null, null);
        int m = (s+e)/2;
        return new node(this->count+1, this->left->insert(s, m, val), this->right->insert(m+1, e, val));
    }
    return this;
}

int query(node *a, node *b, int s, int e, int k){
    if(s==e) {
        return s;
    }
    int cnt = (a->left->count) - (b->left->count);
    int m = (s+e)>>1;
    if(cnt>=k) return query(a->left, b->left, s, m, k);
    else return query(a->right, b->right, m+1, e, k-cnt);
}

int main() {
    null = new node(0, NULL, NULL);
    null->left = null;
    null->right = null;

    mp.clear(); rev_mp.clear();
    int n, m; scanf("%d%d", &n, &m);

    for(int i=0; i<n; i++){
        scanf("%d", &arr[i]);
        if(mp.find(arr[i]) == mp.end())  mp[arr[i]] = -1;
    }

    int maxi=0;
    for(map<int,int>::iterator it=mp.begin(); it!=mp.end(); it++){
        it->second = maxi;
        rev_mp[maxi] = it->first;
        maxi++;
    }

    for(int i=0; i<n; i++){
        if(i==0) root[i] = null->insert(0, maxi-1, mp[arr[i]]);
        else root[i] = root[i-1]->insert(0, maxi-1, mp[arr[i]]);
    }

    while(m--){
        int l, r, k; scanf("%d%d%d", &l, &r, &k);
        l--; r--;
        int ans;
        if(l>0) ans = query(root[r], root[l-1], 0, maxi-1, k);
        else ans = query(root[r], null, 0, maxi-1, k);
        printf("%d\n", rev_mp[ans]);
    }


    return 0;
}