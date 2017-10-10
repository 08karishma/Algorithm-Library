#include <iostream>
#include <climits>
#include <cstring>
#include <algorithm>
#include <vector>
#define MAX  100000001  
#define NINF INT_MIN
#define INF INT_MAX
#define ll long long
using namespace std;

unsigned int flag[MAX>>6];
vector<int> primes;

bool getPrime(int n){
    if(n==2) return true;
    if(n%2==0) return false;
    int pos = (n>>6); //(n/2)/32 = (n/64)
    int bit_pos = (n>>1)&31; // (n/2)%32
    return (flag[pos]>>bit_pos) & 1 ;
}

void setPrime(int n){
    int pos = (n>>6); //(n/2)/32 = (n/64)
    // cout<<n<<" "<<pos<<endl;
    int bit_pos = (n>>1)&31; // (n/2)%32
    flag[pos] &= ~(1<<bit_pos);
}

void bitwise_sieve(){
    for(ll i=0; i<(MAX>>6); i++){
        ll x = (1LL<<32) - 1; //set all bits in flag[i] to 1
        flag[i] = x;
    }

    for(ll i=3; i<MAX; i+=2){
        if(getPrime(i)){
            for(ll j=i*i; j<MAX; j+=(2*i)){
                setPrime(j);
            }
        }
    }

    primes.push_back(2);
    for(unsigned int i=3; i<MAX; i+=2){
        if(getPrime(i)){
            primes.push_back(i);
        }
    }
}

int main() {
    int tc; scanf("%d", &tc);
    bitwise_sieve();
    while(tc--){
        int n; scanf("%d", &n);
        printf("%d\n", primes[n-1]); //print nth prime number
    }

    return 0;
}