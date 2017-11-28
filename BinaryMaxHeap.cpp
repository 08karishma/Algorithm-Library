//IMPLEMENTATION OF BINARY MAX HEAP
#include <iostream>
#include <climits>
using namespace std;
#define MAX 1000001

int arr[MAX];
int length;

//O(logN)
void insert(int val){
	if(length==(MAX-1)){
		cout<<"Queue is full"<<endl;
		return;
	}

	length++;
	arr[length] = val;

	int i = length;
	while(i>1 && arr[i/2]<arr[i]){
		swap(arr[i/2], arr[i]);
		i = i/2;
	}
}

//O(logN)
void max_heapify(int ind){
	int largest = ind;

	int left = 2*ind, right = 2*ind+1;
	if(left <= length && arr[left] > arr[largest]) largest = left;
	if(right<=length && arr[right] > arr[largest]) largest = right;

	if(largest != ind){
		swap(arr[ind], arr[largest]);
		max_heapify(largest);
	}
}

//O(logN)
int extractMax(){
	if(length==0) return INT_MIN; //error

	int res = arr[1];
	arr[1] = arr[length];
	length--;
	max_heapify(1);
	return res;
}

//O(N)
void build_maxheap(){
	for(int i = length/2; i>=1; i--){
		max_heapify(i);
	}
}

int main() {

	int n; cin>>n;
	for(int i=1; i<=n; i++) cin>>arr[i];
	length = n;
	
	build_maxheap();	

	cout<<extractMax()<<endl;
	cout<<extractMax()<<endl;
	cout<<extractMax()<<endl;
	cout<<extractMax()<<endl;
	cout<<extractMax()<<endl;
	cout<<extractMax()<<endl;

    return 0;
}
