//calculate number of distinct substrings using suffix array
//not verified by submitting anywhere, gave TLE on SPOJ
#include <bits/stdc++.h>
using namespace std;
#define ll long long 
#define MAX 50004
#define NINF -1e9
#define INF 1e18
#define MOD 998244353
#define LOGN 20

struct Entry{
	int index;
	int nextRank[2];
};

bool comp(Entry entry1, Entry entry2){
	if(entry1.nextRank[0] != entry2.nextRank[0]){
		return entry1.nextRank[0] < entry2.nextRank[0];
	}
	return entry1.nextRank[1] < entry2.nextRank[1];
}

Entry temp[MAX];
int ranks[LOGN][MAX];
int suffixArr[MAX];
int lcp[MAX];
string S;
int n;
int maxSteps;

void buildLcp(){
	int matchedSoFar = 0;
	for(int i=0; i<n; i++){
		if(ranks[maxSteps][i] == n-1){
			matchedSoFar = 0;
			continue;
		}
		int j = suffixArr[ranks[maxSteps][i]+1];
		
		int k = matchedSoFar;
		while(i+k<n && j+k<n && S[i+k]==S[j+k]){
			matchedSoFar++;
			k++;
		}
		lcp[ranks[maxSteps][i]] = matchedSoFar;
		if(matchedSoFar > 0){
			matchedSoFar--;
		}
	}
}

void buildSuffixArray(){
	for(int i=0; i<n; i++){
		ranks[0][i] = S[i];
	}
	int step = 1;
	int len = 1;
	for(; len<n; len*=2){
		for(int i=0; i<n; i++){
			temp[i].nextRank[0] = ranks[step-1][i];
			temp[i].nextRank[1] = (i+len >= n) ? -1 : ranks[step-1][i+len];
			temp[i].index = i;
		}
		sort(temp, temp+n, comp);
		for(int i=0; i<n; i++){
			if(i>0 && temp[i-1].nextRank[0]==temp[i].nextRank[0] && temp[i-1].nextRank[1]==temp[i].nextRank[1]){
				ranks[step][temp[i].index] = ranks[step][temp[i-1].index];
			}
			else{
		    ranks[step][temp[i].index] = i;
			}	
		}
		step++;
	}
	
	maxSteps = step-1;
	for(int i=0; i<n; i++){
		suffixArr[ranks[maxSteps][i]] = i;
	}
}

void solve(){
	cin>>S;
	n = S.length();
	buildSuffixArray();
	buildLcp();
	
	ll numSubstrings = 0;
	for(int i=0; i<n; i++){
		ll suffixLen = n - suffixArr[i];
		ll lcpLen = lcp[i];
		numSubstrings += suffixLen - lcpLen;
	}
	cout << numSubstrings << endl;
}
 
int main() {
    ll q = 1;
    cin>>q;
    while(q--){
        solve();
    }
    return 0;
}
