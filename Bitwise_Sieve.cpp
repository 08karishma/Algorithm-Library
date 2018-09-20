#include <iostream>
#include <vector>
#define MAX 100000001
using namespace std;

int bitvector[(MAX>>5)+1];
vector<int> primes;

bool getPrime(int n){
	int bv_index = (n>>5);
	int bit_pos = n%32; 
	return ( (bitvector[bv_index]>>bit_pos) & 1);
}

void setPrime(int n){
	int bv_index = (n>>5) ;
	int bit_pos = n%32;
	bitvector[bv_index] = bitvector[bv_index] & (~(1<<bit_pos));
}

void seive(){
	for(int i=0; i<=(MAX>>5); i++){
		long long x =(1LL<<32)-1LL;
		bitvector[i] = x;
	}
	
	for(long long i=2; i<MAX; i++){
		if(getPrime(i)){
			for(long long j=i*i; j<MAX; j+=i){
				setPrime(j);
			}
		}
	}
	
	for(int i=2; i<MAX; i++){
		if(getPrime(i)){
			primes.push_back(i);	
		} 
	}
}

int main(){
	seive();
	int idx=0;
	 //cout<<primes.size()<<endl;
	while(idx < primes.size()){
		cout<<primes[idx]<<endl;
		idx += 100;
	}
	return 0;
}
