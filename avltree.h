#pragma once

struct node
{
	int data;
	node* left;
	node* right;
	int heightNode;
};

class AvlTree
{

	node* root;

	/****Functions to insert a Avl****/
	int height(node* t);
	node* insert(int x, node* t);
	node* rightRotate(node* &t);
	node* leftRotate(node* &t);
	node* rightLeftRotate(node* &t);
	node* leftRightRotate(node* &t);

    node* remove(node* t, int key);
	node* findMin(node* t);
	node* findMax(node* t);

    int getBalance(node* &t);

	void inorder(node* t);
	void display(node *ptr, int level);


public:

	AvlTree();
	~AvlTree();
	void insert(int x);
	void remove(int x);
	void display();
	void displayInorder();
};

