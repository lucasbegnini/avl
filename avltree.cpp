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
node* AvlTree::remove(node* t,int key)
{
    node* temp;

    // Element not found
    if(t == NULL)
        return NULL;

    // Searching for element
    else if(key < t->data)
        t->left = remove(t->left,key);
    else if(key > t->data)
        t->right = remove(t->right,key);

    // Element found
    // With 2 children
    else if(t->left && t->right)
    {
        temp = findMin(t->left);
        t->data = temp->data;
        t->left = remove(t->left,t->data);
    }
    // With one or zero child
    else
    {
        //temp = t;
        if(t->left == NULL)
            t = t->right;
        else if(t->right == NULL)
            t = t->left;
    }
    if(t == NULL) {
        return t;
    }

    //UPDATE HEIGHT OF THE CURRENT NODE
    t->heightNode = 1 + max(height(t->left),
                            height(t->right));

    // check whether this node became unbalanced)
    int balance = getBalance(t);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && getBalance(t->left) >= 0)
        return rightRotate(t);

    // Left Right Case
    if (balance > 1 && getBalance(t->left) < 0)
    {
        t->left =  leftRotate(t->left);
        return rightRotate(t);
    }

    // Right Right Case
    if (balance < -1 && getBalance(t->right) <= 0)
        return leftRotate(t);

    // Right Left Case
    if (balance < -1 && getBalance(t->right) > 0)
    {
        t->right = rightRotate(t->right);
        return leftRotate(t);
    }


    //UPDATE HEIGHT OF THE CURRENT NODE
    t->heightNode = 1 + max(height(t->left),
                            height(t->right));

    return t;
}

/***************************************************************/
node* AvlTree::findMin(node* t)
{
    if (t == NULL)
        return NULL;
    else if (t->right == NULL)
        return t;
    else
        return findMin(t->right);
}

/***************************************************************/
node* AvlTree::findMax(node* t)
{
    if (t == NULL)
        return NULL;
    else if (t->left == NULL)
        return t;
    else
        return findMax(t->left);
}
/***************************************************************/
void AvlTree::findNodeHeight(node* &t, node* &c, int &height)
{
    if (t->data == c->data) {
        return;
    }
    if (t->data < c->data) {
        height++;
        findNodeHeight(t, c->left,height);
    } else if (t->data > c->data) {
        height++;
        findNodeHeight(t, c->right,height);
    }
}
/***************************************************************/
void AvlTree::inorder(node* t)
{
    if (t == NULL)
        return;

    inorder(t->left);
    int height = 0;
    findNodeHeight(t,root,height);
    cout << t->data << "," << height << endl;
    inorder(t->right);
}

/***************************************************************/
int AvlTree::getBalance(node* &t)
{
    if(t == NULL)
        return 0;
    else
        return height(t->left) - height(t->right);
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
    root = remove(root,x);
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
