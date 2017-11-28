#include <iostream>
#include <climits>
using namespace std;
#define MAX 1000001

struct trieNode;

struct node{
	int value;
	string word;
	trieNode *tnode;
	node(int x, string s) : value(x), word(s) {}
};

int heap_length;
node *heap[MAX];

void min_heapify(int i){
	int left = 2*i, right = 2*i+1;
	int smallest = i;

	if(left<=heap_length){
		if((heap[left]->value) < (heap[smallest]->value) ) smallest = left;
	}
	if(right<=heap_length){
		if((heap[right]->value) < (heap[smallest]->value) ) smallest = right;
	}

	if(smallest != i){
		node *temp = heap[i];
		heap[i] = heap[smallest];
		heap[smallest] = temp;
		min_heapify(smallest);
	}
}

void heap_insert(node *cur){
	heap_length++;
	heap[heap_length] = cur;

	int i = heap_length;
	while(i>1){
		if((heap[i]->value) < (heap[i/2]->value)){
			node *temp = heap[i];
			heap[i] = heap[i/2];
			heap[i/2] = temp;
			i = i/2;
		}
		else break;
	}
}

struct trieNode{
	char c;
	int count;
	node *ptr;
	trieNode* child[26];
	trieNode(char c1) {
		c= c1; count=0;
		ptr=NULL;
		for(int i=0; i<26; i++) child[i]=NULL;
	}
};

trieNode* trieRoot;

void process(string str, int K){
	trieNode *cur = trieRoot;
	for(int i=0; i<str.length(); i++){
		int j = str[i]-'a';
		if((cur->child)[j] == NULL) (cur->child)[j] = new trieNode(str[i]);
		cur = (cur->child)[j];
	}
	cur->count += 1;
	if(cur->ptr == NULL) {
		if(heap_length == K){
			if((cur->count) > (heap[1]->value)){
				heap[1]->value = (cur->count);
				heap[1]->word = str;
				heap[1]->tnode->ptr = NULL;
				heap[1]->tnode = cur;
				cur->ptr = heap[1];
				min_heapify(1);
			}
		}
		else{
			node *p = new node(1, str);
			cur->ptr = p;
			p->tnode = cur;
			heap_insert(p);
		}
	}
	else{
		cur->ptr->value += 1;
		min_heapify(1);
	}
}

int main() {

	trieRoot = new trieNode('$');
	heap_length = 0;

	int K; cin>>K;
	string str;
	while(cin>>str){
		process(str, K);
	}

	cout<<heap_length<<endl;
	for(int i=1; i<=heap_length; i++){
		cout<<heap[i]->word<<endl;
	}

    return 0;
}
