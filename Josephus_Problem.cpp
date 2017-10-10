//JOSEPHOUS PROBLEM 

#include <iostream>
#define MAX 5001
using namespace std;

//every kth person removed  
//0-indexed scenario
int josephus(int n, int k){
    if(n==1) return 0;
    return (josephus(n-1, k)+k ) % n;
}

int main() {
    int t; scanf("%d", &t);
    while(t--){
        int num; scanf("%d", &num);
        printf("%d\n", josephus(num, 1)+1);
    }
    return 0;
}