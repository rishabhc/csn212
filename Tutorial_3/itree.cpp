#include <bits/stdc++.h>
using namespace std;

struct node{
	node *left, *right;
	int high,low,max;
};

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
	
	if(l < root->low)
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

	return search(root->right,l,h);
}

int main(){
	int intervals[][6] = {{15, 20}, {10, 30}, {17, 19},
        {5, 20}, {12, 15}, {30, 40}
    };

    int n = 6;
    node *root = NULL;
    for (int i = 0; i < n; i++)
        root = insert(root, intervals[i][0],intervals[i][1]);

    int checks[][2] = {{14,16},{21,23}};
    for(int i = 0; i < 2; i++){
	    node* ans = search(root,checks[i][0],checks[i][1]);
	    if (ans == NULL)
	        cout << "\nNo Overlapping Interval";
	    else
	        cout << "["<<checks[i][0] << ", " << checks[i][1] <<  "] overlaps with [" << ans->low << ", " << ans->high << "]" << endl;
	}

}