#include <bits/stdc++.h>
using namespace std;

struct node{
	node* left, right;
	int high,low,max;
}

node* newNode(int l, int h){
	node* temp = new node;
	temp->high = h;
	temp->low = l;
	temp->max = h;
	temp->left = temp->right = NULL;
	return temp;
}

node* insert(node* root, int l, int h){
	if(root == NULL)
		return newNode(l,h);
	
	if(l < root->l)
		root->left = insert(root->left,l,h);

	else 
		root->right = insert(root->right,l,h);

	if(root->max < h)
		root->max = h;

	return root;
}

bool overlap(node* root, int l, int h){
	if(l <= root->high && root->low <= h)
		return true;
	return false;
}

node* search(node* root, int l, int h){
	if(root == NULL)
		return root;

	if(overlap(root,l,h))
		return root;

	if(root->left != NULL && root->left->max >= l)
		return search(root->left,l,h);

	return(root->right,l,h);
}

int main(){
	
}