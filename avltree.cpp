#include "stdafx.h"
#include "avltree.h"


/**********************************************************************************/
/**************************** PRIVATE FUNCTIONS ***********************************/
/**********************************************************************************/

int AvlTree::height(node* t)
{
	return (t == NULL ? -1 : t->heightNode);
}

/***************************************************************/
node* AvlTree::insert(int x, node* t)
{
	if (t == NULL)
	{
		t = new node;
		t->data = x;
		t->heightNode = 0;
		t->left = t->right = NULL;
	}
	else if (x < t->data)
	{
		t->left = insert(x, t->left);
		if (height(t->left) - height(t->right) == 2)
		{
			if (x < t->left->data)
				t = rightRotate(t);
			else
				t = leftRightRotate(t);
		}
	}
	else if (x > t->data)
	{
		t->right = insert(x, t->right);
		if (height(t->right) - height(t->left) == 2)
		{
			if (x > t->right->data)
				t = leftRotate(t);
			else
				t = rightLeftRotate(t);
		}
	}

	t->heightNode = max(height(t->left), height(t->right)) + 1;
	return t;
}

/***************************************************************/
node* AvlTree::rightRotate(node* &t)
{
	node* u = t->left;
	t->left = u->right;
	u->right = t;
	t->heightNode = max(height(t->left), height(t->right)) + 1;
	u->heightNode = max(height(u->left), t->heightNode) + 1;
	return u;
}

/***************************************************************/
node* AvlTree::leftRotate(node* &t)
{
	node* u = t->right;
	t->right = u->left;
	u->left = t;
	t->heightNode = max(height(t->left), height(t->right)) + 1;
	u->heightNode = max(height(t->right), t->heightNode) + 1;
	return u;
}

/***************************************************************/
node* AvlTree::rightLeftRotate(node* &t)
{
	t->right = rightRotate(t->right);
	return leftRotate(t);
}

/***************************************************************/
node* AvlTree::leftRightRotate(node* &t)
{
	t->left = leftRotate(t->left);
	return rightRotate(t);
}


/***************************************************************/
node* AvlTree::remove(int x, node* t)
{
	node* temp;
	// Element not found
	if (t == NULL) {
		return NULL;
		// Searching for element
	}
	else if (x < t->data) {
		t->left = remove(x, t->left);
	}
	else if (x > t->data) {
		t->right = remove(x, t->right);

		// Element found
		// With 2 children
	}
	else if (t->left && t->right)
	{
		temp = findMax(t->left);
		t->data = temp->data;
		t->left = remove(t->data, t->left);
	}
	// With one or zero child
	else
	{
		temp = t;
		if (t->left == NULL)
			t = t->right;
		else if (t->right == NULL)
			t = t->left;
		delete temp;
	}
	if (t == NULL)
		return t;

	t->heightNode = max(height(t->left), height(t->right)) + 1;

	// If node is unbalanced
	// If left node is deleted, right case
	if (height(t->left) - height(t->right) == 2)
	{
		// right right case
		if (height(t->left->left) - height(t->left->right) == 1)
			return leftRotate(t);
		// right left case
		else
			return rightLeftRotate(t); // rightLeftRotate(t);
	}
	// If right node is deleted, left case
	else if (height(t->right) - height(t->left) == 2)
	{
		// left left case
		if (height(t->right->right) - height(t->right->left) == 1)
			return rightRotate(t);
		// left right case
		else
			return leftRightRotate(t);// leftRightRotate(t);
	}
	return t;
}

/***************************************************************/
node* AvlTree::findMin(node* t)
{
	if (t == NULL)
		return NULL;
	else if (t->left == NULL)
		return t;
	else
		return findMin(t->left);
}

/***************************************************************/
node* AvlTree::findMax(node* t)
{
	if (t == NULL)
		return NULL;
	else if (t->right == NULL)
		return t;
	else
		return findMax(t->right);
}
/***************************************************************/
void AvlTree::inorder(node* t)
{
	if (t == NULL)
		return;

	inorder(t->left);
	cout << t->data << "," << root->heightNode - t->heightNode  << " " << t->heightNode << " " << root->heightNode << endl;
	inorder(t->right);
}

/**********************************************************************************/
/**************************** PUBLIC FUNCTIONS ************************************/
/**********************************************************************************/

AvlTree::AvlTree()
{
	root = NULL;
}

/***************************************************************/
AvlTree::~AvlTree()
{
}

/***************************************************************/
void AvlTree::insert(int x)
{
	root = insert(x, root);
}

/***************************************************************/
void AvlTree::remove(int x)
{
	root = remove(x, root);
}

/***************************************************************/
void AvlTree::displayInorder()
{
	inorder(root);
}

void AvlTree::display()
{
	display(root, 0);
	cout << endl;
}

void AvlTree::display(node *ptr, int level)
{
	int i;
	if (ptr != NULL)
	{
		display(ptr->right, level + 1);
		cout << endl;
		if (ptr == root)
			cout << "Root -> ";
		for (i = 0; i < level && ptr != root; i++) {
			cout << "           ";

		}
		cout << ptr->data;
		display(ptr->left, level + 1);
	}
}
