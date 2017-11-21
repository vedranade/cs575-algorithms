#include <iostream>
#include <math.h>
#include <algorithm>
//#include <iomanip>

using namespace std;

#include "AVLtree.h"

//--- Definition of constructor
AVLtree::AVLtree()
	: myRoot(0), count(0)
{
}

bool AVLtree::empty() const
{
	return myRoot == 0;
}

bool AVLtree::search(const int & item) const
{
	BinNode * locptr = myRoot;
	bool found = false;
	while ( !found && locptr != 0 )
	{
		if ( item < locptr->data )       // descend left
			locptr = locptr->left;
		else if ( locptr->data < item )  // descend right
			locptr = locptr->right;
		else                           // item found
			found = true;
	}
	return found;
}

int AVLtree::getMinPrivate(AVLtree::BinNode *current)						//Gets minimum value of data, used to replace the data to be deleted
{
	if ( myRoot == NULL )
	{
		cout << endl << "Tree is empty";
		return -1000;
	}
	else
	{
		if ( current->left != NULL )	
		{
			return getMinPrivate(current->left);							//Get minimum value in left subtree
		}
		else
		{
			return current->data;
		}
	}

}

int AVLtree::getMin()
{
	return getMinPrivate(myRoot);											//Start from root
}

AVLtree::BinNode * AVLtree::AVLinsert(int item, BinNode * n)
{
	if ( n == NULL )									
	{	
		n = new BinNode(item);												//If AVL tree is empty, call constructor class
	}
	else if ( item < n->data )												
	{
		n->left = AVLinsert(item, n->left);									//Insert into left subtree
		if ( height(n->left) - height(n->right) == 2 )						//Check for height condition
		{
			if ( item < n->left->data )
			{
				n = LeftLeftRotate(n);										//Perform left-left rotate	
			}
			else
			{
				n = LeftRightRotate(n);										//Perform left-right rotate
			}
		}
	}
	else if ( item > n->data )												
	{
		n->right = AVLinsert(item, n->right);								//Insert into right subtree
		if ( height(n->right) - height(n->left) == 2 )						//Check for height condition
		{
			if ( item > n->right->data )
			{
				n = RightRightRotate(n);									//Perform right-right rotate	
			}
			else
			{
				n = RightLeftRotate(n);										//Perform left-right rotate
			}
		}
	}

	n->height = max(height(n->left), height(n->right)) + 1;
	return n;
}

void AVLtree::AVLinsert(int item)
{
	myRoot = AVLinsert(item, myRoot);										//Start inserting from root
}

AVLtree::BinNode * AVLtree::LeftLeftRotate(AVLtree::BinNode * n1)			
{
	BinNode *n = n1->left;
	n1->left = n->right;
	n->right = n1;
	n1->height = max(height(n1->left), height(n1->right)) + 1;
	n->height = max(height(n->left), n1->height) + 1;
	return n;
}

AVLtree::BinNode * AVLtree::RightRightRotate(AVLtree::BinNode * n)
{
	BinNode *n1 = n->right;
	n->right = n1->left;
	n1->left = n;
	n->height = max(height(n->left), height(n->right)) + 1;
	n1->height = max(height(n1->right), n->height) + 1;
	return n1;
}

AVLtree::BinNode * AVLtree::LeftRightRotate(AVLtree::BinNode * n)
{
	n->left = RightRightRotate(n->left);
	return LeftLeftRotate(n);
}

AVLtree::BinNode * AVLtree::RightLeftRotate(BinNode * n)
{
	n->right = LeftRightRotate(n->right);
	return RightLeftRotate(n);
}

void AVLtree::removeRootNode()												//Removes root node only
{
	if ( myRoot != NULL )														//If tree is not empty
	{
		BinNode *delete_ptr = myRoot;
		int root_data = myRoot->data;
		int min_right;															//Stores smallest value from the right subtree

																				//Case 1: no children
		if ( myRoot->left == NULL && myRoot->right == NULL )
		{
			myRoot = NULL;
			delete delete_ptr;
		}
																				//Case 2: one child
		else if ( myRoot->left == NULL && myRoot->right != NULL )
		{
			myRoot = myRoot->right;
			delete_ptr->right = NULL;
			delete delete_ptr;
		}
		else if ( myRoot->left != NULL && myRoot->right == NULL )
		{
			myRoot = myRoot->left;
			delete_ptr->left = NULL;
			delete delete_ptr;
		}
																				//Case 3: two children
		else
		{
			min_right = getMinPrivate(myRoot->right);
			removeNodePrivate(min_right, myRoot);
			myRoot->data = min_right;											//Overwriting the value to be deleted with smallest value
		}
	}
	else
	{
		cout << endl << "Tree is empty";
	}
}

void AVLtree::remove(AVLtree::BinNode *parent, AVLtree::BinNode *current, bool left)						//Function to remove a non root node
{
	if ( myRoot != NULL )
	{
		BinNode *delete_ptr;
		int key = current->data;
		int min_right;

																											//Case 1: no children
		if ( current->left == NULL && current->right == NULL )
		{
			delete_ptr = current;
			if ( left == true )
				parent->left = NULL;
			else
				parent->right = NULL;
			delete delete_ptr;
			cout << endl << "Item deleted";
		}
																											//Case 2: One child
		else if ( current->left == NULL && current->right != NULL )
		{
			if ( left == true )
				parent->left = current->right;
			else
				parent->right = current->right;
			current->right = NULL;
			delete_ptr = current;
			delete delete_ptr;
			cout << endl << "Item deleted";
		}
		else if ( current->left != NULL && current->right == NULL )
		{
			if ( left == true )
				parent->left = current->left;
			else
				parent->right = current->left;
			current->left = NULL;
			delete_ptr = current;
			delete delete_ptr;
			cout << endl << "Item deleted";
		}
																						//Case 3: two children
		else
		{
			min_right = getMinPrivate(current->right);
			removeNodePrivate(min_right, current);
			current->data = min_right;													//Value to be deleted overwritten with smallest value
		}
	}
	else
	{
		cout << endl << "Tree is empty";
	}
}

void AVLtree::removeNode(int item)
{
	removeNodePrivate(item, myRoot);												//Start deletion from root
}

void AVLtree::removeNodePrivate(int item, AVLtree::BinNode *parent)
{
	if ( myRoot != NULL )
	{
		if ( myRoot->data == item )													//If the root node contains the data to be deleted
		{
			removeRootNode();
		}
		else
		{
			if ( parent->left != NULL && item < parent->data )						//If left child exists and if data is less than data of current node
			{
				parent->left->data == item ?
					remove(parent, parent->left, true) :
					removeNodePrivate(item, parent->left);
			}
			else if ( parent->right != NULL && item > parent->data )						//If right child exists and if data is greater than data of current node
			{
				parent->right->data == item ?
					remove(parent, parent->right, false) :
					removeNodePrivate(item, parent->right);
			}
			else
			{
				cout << endl << "Item not found";
			}
		}
	}
	else
	{
		cout << endl << "Tree is empty";
	}
}

void AVLtree::pre_OrderTraversal(AVLtree::BinNode *current_node)
{
	if ( current_node != NULL )
	{
		cout << current_node->data << " ";
		pre_OrderTraversal(current_node->left);
		pre_OrderTraversal(current_node->right);
	}
}

void AVLtree::in_OrderTraversal(AVLtree::BinNode *current_node)
{
	if ( current_node == NULL )
	{
		return;
	}
	if ( current_node != NULL )
	{
		in_OrderTraversal(current_node->left);
		cout << current_node->data << " ";
		in_OrderTraversal(current_node->right);
	}
}

int AVLtree::node_count(AVLtree::BinNode *current_node)
{

	if ( current_node != NULL )
	{
		node_count(current_node->left);
		count++;
		node_count(current_node->right);
	}

	return count;
}