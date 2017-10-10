//AVL TREE IMPLEMENTATION
//SEE BST IMPLEMENTATION FIRST FOR EASIER UNDERSTANDING
#include <iostream>
using namespace std;

struct node{
    node *left, *right;
    int val;
    node(int x) : val(x), left(NULL), right(NULL) {}
};

int height(node *root){
    if(root==NULL) return -1;
    return max(height(root->left), height(root->right))+1;
}

node* right_rotate(node *root){
    node *temp = root->left;
    root->left = temp->right;
    temp->right = root;
    return temp;
}

node *left_rotate(node *root){
    node *temp = root->right;
    root->right = temp->left;
    temp->left = root;
    return temp;
}

node* balance(node *root){
    int bal_factor = height(root->left) - height(root->right);
    if(bal_factor > 1){ 
        int diff = height(root->left->left) - height(root->left->right);
        if(diff > 0){ //LL Case
            root = right_rotate(root);
        }
        else { //LR Case
            root->left = left_rotate(root->left);
            root = right_rotate(root);
        }
    }
    else if(bal_factor < -1) {
        int diff = height(root->right->left) - height(root->right->right);
        if(diff > 0){ //RL Case
            root->right = right_rotate(root->right);
            root = left_rotate(root);
        }
        else {//RR Case
            root = left_rotate(root);
        }
    }
    return root;
}

node* insert(node *root, int key){
    if(root==NULL) return new node(key);
    //assuming all keys to be distinct
    if(key < root->val) {
        root->left = insert(root->left, key);
        root = balance(root);
    }
    else if(key > root->val) {
        root->right = insert(root->right, key);
        root = balance(root);
    } 
    return root;
}

node *search(node *root, int key){
    if(root==NULL || key==root->val) return root;
    if(key < root->val) {
        return search(root->left, key);
    }
    else{
        return search(root->right, key);
    } 
}

node *_delete(node *root, int key){
    if(!root) return NULL;
    if(key < root->val) {
        root->left = _delete(root->left, key);
        root = balance(root);
        return root;
    }
    else if(key > root->val){
        root->right = _delete(root->right, key);
        root = balance(root);
        return root;
    } 

    if(!(root->left) && !(root->right)) return NULL;

    if(!(root->left)) return root->right;
    if(!(root->right)) return root->left;

    node *cur = root->right;
    while(cur->left) cur = cur->left;
    root->val = cur->val; //swap values
    root->right = _delete(root->right, cur->val); //delete inorder successor
    // root = balance(root);
    return root;
}

void display(node *ptr, node *root, int level)
{
    int i;
    if (ptr!=NULL)
    {
        display(ptr->right, root, level + 1);
        printf("\n");
        if (ptr == root)
        cout<<"Root -> ";
        for (i = 0; i < level && ptr != root; i++)
            cout<<"        ";
        cout<<ptr->val;
        display(ptr->left, root, level + 1);
    }
}

int main() {

    node *root = new node(5);
    root = insert(root, 10);
    root = insert(root, -10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, -120);
    root = insert(root, 4);
    root = insert(root, 23);
    root = insert(root, 25);
    root = insert(root, 55);
    root = insert(root, 67);
    root = insert(root, 98);
    root = insert(root, 22);
    root = insert(root, 1);
    root = insert(root, 234);
    root = insert(root, 2);
    root = insert(root, 34);
    root = insert(root, 56);
    root = insert(root, 22);

    display(root, root, 1);
    cout<<endl;

    root = _delete(root, 98);

    display(root, root, 1);
    cout<<endl;

    node *x = search(root, 10);
    cout<<x->val<<endl;
    return 0;
}