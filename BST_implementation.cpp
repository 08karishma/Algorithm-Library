//BST IMPLEMENTATION
//ALL OPERATIONS TAKE O(H) TIME, WHERE H IS HEIGHT OF TREE
#include <iostream>
using namespace std;

struct node{
    node *left, *right;
    int val;
    node(int x) : val(x), left(NULL), right(NULL) {}
};

//BST Insert
void insert(node *root, int key){
    //assuming all keys to be distinct
    if(key < root->val) {
        if(root->left==NULL) root->left = new node(key);
        else insert(root->left, key);
    }
    else if(key > root->val) {
        if(root->right == NULL) root->right = new node(key);
        else insert(root->right, key);
    } 
}

//BST Search
node *search(node *root, int key){
    if(root==NULL || key==root->val) return root;
    if(key < root->val) {
        return search(root->left, key);
    }
    else{
        return search(root->right, key);
    } 
}

//BST Delete
//deletes node with val=key and returns new root
node *_delete(node *root, int key){
    if(key < root->val) {
        root->left = _delete(root->left, key);
        return root;
    }
    else if(key > root->val){
        root->right = _delete(root->right, key);
        return root;
    } 
    //delete root
    //if root is a leaf, return NULL
    if(!(root->left) && !(root->right)) return NULL;

    //if it has only one child
    if(!(root->left)) return root->right;
    if(!(root->right)) return root->left;

    //if it has both children
    //smallest value > (root->val) will now become root
    node *cur = root->right;
    while(cur->left) cur = cur->left;
    root->val = cur->val; //swap values
    root->right = _delete(root->right, cur->val); //delete inorder successor
    return root;
}

void inorder_traversal(node *root){
    if(root->left) inorder_traversal(root->left);
    cout<<root->val<<" ";
    if(root->right) inorder_traversal(root->right);
}

int main() {
    node *root = new node(5);
    insert(root, 10);
    insert(root, -10);
    insert(root, 20);
    insert(root, 30);
    insert(root, -120);
    insert(root, 4);
    insert(root, 23);
    insert(root, 25);
    insert(root, 55);
    insert(root, 67);
    insert(root, 98);
    insert(root, 22);
    insert(root, 1);
    insert(root, 234);
    insert(root, 2);
    insert(root, 34);
    insert(root, 56);
    insert(root, 22);

    inorder_traversal(root);
    cout<<endl;

    root = _delete(root, 98);

    inorder_traversal(root);
    cout<<endl;

    node *x = search(root, 10);
    cout<<x->val<<endl;
    return 0;
}