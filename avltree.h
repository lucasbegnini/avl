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

    /**
     * @brief Private function that insert value in a node
     * @param x - Key that will be insert
     * @param t - node where will be insert (start to check in root)
     * @return new root node
     */
    node* insert(int x, node* t);
    /**
     * @brief Private function that remove value in a tree node(not specific in one node)
     * @param t - node where start check if content the Key
     * @param key - key that will be check
     * @return new root node
     */
    node* remove(node* t, int key);

    /*
     * functions of rotations.
     * here have and left right rotate
     * have too leftRightRotate - Where firt make a left rotate than a right rotate
     * and have rightLeftRotate - As name says, make a right and than a left rotate
    */
    node* rightRotate(node* &t);
	node* leftRotate(node* &t);
	node* rightLeftRotate(node* &t);
	node* leftRightRotate(node* &t);

    /*
     * Functions that helps find max or min of one sub tree starting a node t
    */
    node* findMin(node* t);
	node* findMax(node* t);

    /**
     * @brief getBalance - get the balance of node.
     * @param t - node to get.
     * @return
     */
    int getBalance(node* &t);

    /**
     * @brief findNodeHeight - Get the height of a node C (compare) to another node T
     * @param t - node that will get the height
     * @param c - node that will be compare
     * @param height - value that will be increase with sums of all compares.
     */
    void findNodeHeight(node *&t, node* &c, int &height);

    /**
     * @brief height - return a height of node
     * @param t - node.
     * @return height of node
     */
    int height(node* t);

    /**
     * @brief display a tree in order where each node will be show with specific height to root node.
     * @param t - node where will be start to show.
     */
	void inorder(node* t);

    /**
     * @brief display - draw tree in screen
     * @param ptr
     * @param level
     */
	void display(node *ptr, int level);


public:

	AvlTree();
	~AvlTree();
	void insert(int x);
	void remove(int x);
	void display();
	void displayInorder();
};

