//prime factorization of a number in O(no of prime factors(including powers))
//including powers=> 4=(2,2) => O(no of factors=2)
#include <iostream>
#include <vector>
using namespace std;
#define max 100002
 
int prime[max];
 
void sieve(){
	for(int i=1; i<max; i++) prime[i] = i;
	for(int i=2; i<max; i++){
		if(prime[i]==i) {
			for(int j=i; j<max; j+=i) prime[j]=i;
		}
	}
}
 
vector<int> factorize(int n){
	vector< int > res;
	    while(n > 1){
	        int p = prime[n];
	        while(n%p==0) n /= p;
	        res.push_back(p);
	    }
	    return res;	
}
 
int main() {
	sieve();
	int n; cin>>n;
	vector<int> factors = factorize(n);
	for(int i=0; i<factors.size(); i++) cout<<factors[i]<<" ";
	cout<<endl;
	return 0;
} 
