/*----- treetester.cpp -----------------------------------------------------
Program for testing AVLtree.
------------------------------------------------------------------------*/
#include <math.h>
#include <iostream>
using namespace std;

#include "AVLtree.h"

int main()
{
	// Testing Constructor and empty()
	AVLtree intAVLtree;            // test the class constructor
	cout << "Constructing empty AVLtree\n";
	cout << "AVLtree " << (intAVLtree.empty() ? "is" : "is not") << " empty\n";

	// Testing insert
	cout << "\nNow insert a bunch of integers into the AVLtree."
		"\nTry items not in the AVLtree and some that are in it:\n";
	int number;
	for ( ;;)
	{
		cout << "Item to insert (-999 to stop): ";
		cin >> number;
		if ( number == -999 ) break;
		intAVLtree.AVLinsert(number);
	}
	cout << "AVLtree " << (intAVLtree.empty() ? "is" : "is not") << " empty\n";

	// Testing search()
	cout << "\n\nNow testing the search() operation."
		"\nTry both items in the AVLtree and some not in it:\n";
	for ( ;;)
	{
		cout << "Item to find (-999 to stop): ";
		cin >> number;
		if ( number == -999 ) break;
		cout << (intAVLtree.search(number) ? "Found" : "Not found") << endl;
	}

	cout << endl << "Pre order traversal of tree:" << endl;
	intAVLtree.pre_OrderTraversal(intAVLtree.return_root());

	cout << endl << "In order traversal of tree:" << endl;
	intAVLtree.in_OrderTraversal(intAVLtree.return_root());

	cout << endl << "No. of nodes in AVLtree: " << intAVLtree.node_count(intAVLtree.return_root()) << endl;

	//Testing node removal
	for ( ;;)
	{
		cout << endl << "Item to delete (-999 to stop): ";
		cin >> number;
		if ( number == -999 ) break;
		intAVLtree.removeNode(number);
		cout << endl << "In order traversal of tree:" << endl;
		intAVLtree.in_OrderTraversal(intAVLtree.return_root());
	}

	return 0;
}
