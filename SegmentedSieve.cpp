//Takes lesser memory compared to normal sieve, time taken is the same
#include<iostream>
#include<cstring>
#include <cmath>
#define MAX 100000000 //10^8
#define LIM 10000 //10^4
using namespace std;

int primes[5000001];

void segmented_Seive(){
    bool isPrime[LIM+1];
    memset(isPrime, true, sizeof isPrime);
    for(int i=2; i*i<LIM; i++){
        if(isPrime[i]){
            for(int j=2*i; j<LIM; j+=i){
                isPrime[j]=false;
            }
        }
    }
    int cnt=0;
    for(int i=2; i<LIM; i++){
        if(isPrime[i]) {
            primes[cnt]=i;
            cnt++;
        }
    }
    int primes_till_lim=cnt;
    int low = LIM;
    int high = 2*LIM;
    while(high<MAX && cnt<5000000){
        memset(isPrime, true, sizeof isPrime);
        for(int i=0; i<primes_till_lim; i++){
            int start = primes[i] * ceil(low/primes[i]);
            //if(start<low) start+=primes[i];
            for(int j=start; j<high; j+=primes[i]){
                isPrime[j-low]=false;
            }
        }
        for(int i=0; i<LIM && cnt<5000000; i++){
            if(isPrime[i]){
                primes[cnt]=i+low;
                cnt++;
            }
        }
        low+=LIM;
        high+=LIM;
    }
    // cout<<cnt<<endl;
}


int main()
{
    segmented_Seive();
    int q; scanf("%d", &q);
    while(q--){
        int k; scanf("%d", &k);
        printf("%d\n", primes[k-1]);
    }
    return 0;
}
