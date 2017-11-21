#include <math.h>
#include <iostream>
using namespace std;

#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE

class AVLtree
{
	private:
	int count;
	//Node Class
	class BinNode
	{
		public:
		int data, height;
		BinNode * left;
		BinNode * right;

		// BinNode constructors
		// Default -- data part is default int value; both links are null.
		BinNode()
			: left(0), right(0), height(0)
		{
		}

		// Explicit Value -- data part contains item; both links are null.
		BinNode(int item)
			: data(item), left(0), right(0), height(0)
		{
		}

	};
	/***** Node class *****/
	// end of class BinNode declaration

	/***** Data Members *****/
	BinNode * myRoot;
	public:
	/***** Function Members *****/
	BinNode * return_root() { return myRoot; }						//Returns the root node of the AVLtree
	AVLtree();
	bool empty() const;
	bool search(const int & item) const;
	void pre_OrderTraversal(BinNode *node);
	void in_OrderTraversal(BinNode *node);
	int node_count(BinNode *node);
	void removeNode(int item);
	int getMin();
	void makeEmpty() { myRoot = NULL; };
	int height(BinNode *h) { return h == NULL ? -1 : h->height; }
	BinNode * AVLinsert(int item, BinNode *n);
	void AVLinsert(int item);
	BinNode *LeftLeftRotate(BinNode *n);
	BinNode *RightRightRotate(BinNode *n);
	BinNode *LeftRightRotate(BinNode *n);
	BinNode *RightLeftRotate(BinNode *n);


	private:
	void removeNodePrivate(int item, BinNode *parent);
	void removeRootNode();
	int getMinPrivate(BinNode *);
	void remove(BinNode *parent, BinNode *current, bool left);



}; // end of class declaration

#endif

