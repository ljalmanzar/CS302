/** @file Binary Search Tree Implementation
@author Luis Almanzar
@version 1.0
@brief Implementation for a Binary Search Tree.
@details 
@date Monday, October 20.
*/
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <sys/time.h>
#include "BSTree.h"
#include "show9.cpp"

using namespace std;

/**
 * The constructor for a BST node.
 * @details Takes the parameters and sets them to its data members
 * @param The data item which can be different things, and two BST Node pointers for the left and right children.
 * @return Constructor.
 * 
 * @pre There should be an initialized tree.
 * @post There will be a new node inside of a BST tree.
 */
template < typename DataType, class KeyType >
BSTree<DataType, KeyType>::BSTreeNode::BSTreeNode( const DataType& nodeDataItem, BSTreeNode *leftPtr, BSTreeNode *rightPtr ) 
                                                                                                     : dataItem(nodeDataItem), left(leftPtr), right (rightPtr)
{
}
    
/**
 * The default BST constuctor.
 * @details Just initializes a new BST tree by setting its root to NULL.
 * @param None.
 * @return Constructor.
 * 
 * @pre None.
 * @post There is a new initialized tree.
 */
template < typename DataType, class KeyType >
BSTree<DataType, KeyType>::BSTree()
	{
		root = NULL; 
	}

/**
 * This is the copy constructor. 
 * @details Will create a new BST tree with the data from the parameter. Uses the overloaded assignment operator.
 * @param Another BST to copy from.
 * @return Constructor.
 * 
 * @pre There should be one tree already initialized.
 * @post There will be two identical trees.
 */
template < typename DataType, class KeyType >
BSTree<DataType, KeyType>::BSTree(const BSTree<DataType,KeyType>& source)
	{
		root=NULL;
		*this = source; 
	}

/**
 * This is the overloaded assignment operator. 
 * @details Will set the tree equal to the tree in the parameter. This is done by calling the copyHelp function (details there.)
 * @param Another BST to copy from.
 * @return The copied BST.
 * 
 * @pre There should two initialized trees.
 * @post There will be two identical trees.
 */
template < typename DataType, class KeyType >	
BSTree<DataType, KeyType>& BSTree<DataType, KeyType>::operator=(const BSTree<DataType, KeyType>& source)
	{
		if (this == &source)
			return *this;

		clear();
		copyHelp(root, source.root);
		return *this;
	}

/**
 * This is the function that will recursively copy two trees to eachother.
 * @details Checks if the current Node from the tree to copy from is NULL. If it is, then will end.
 * If the Node is not null will create a new node for the LHS tree with the same data then call itself
 * for the left and right side of that node. Stopping condition is until they reach the end of RHS.
 * @param Will take in two BST Node pointers. One from each Tree. Should be corresponding.
 * @return Void.
 * 
 * @pre There should two initialized trees.
 * @post There will be two identical trees.
 */
template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::copyHelp( BSTreeNode*& home, BSTreeNode* RHS )
	{
		/// Stopping condition, end of tree
		if (RHS == NULL)
			{
				home = NULL;
				return;
			}

		/// Create node
		home = new BSTreeNode (RHS->dataItem, NULL, NULL);

		/// Recall with the other parts of the tree
		copyHelp(home->left, RHS->left);
		copyHelp(home->right, RHS->right);
		return;
	}

/**
 * This is the tree destructor.
 * @details Deallocates all the memory of the tree by calling the clear function (details of that in function)
 * @param None
 * @return Destructor.
 * 
 * @pre There should be an initialized tree.
 * @post All memory will be deallocated.
 */
template < typename DataType, class KeyType >
BSTree<DataType, KeyType>::~BSTree ()
	{
		clear();
	}

/**
 * This is the function that will insert a new item into the tree. 
 * @details Inserts new data by calling its helper. Details will be there.
 * @param The new data. Could be of different types.
 * @return void
 * 
 * @pre there should an initialized tree.
 * @post there will be another item in the tree with correct positioning.
 */
template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::insert(const DataType& newDataItem)
	{
		insertHelper(root, newDataItem);
	}

/**
 * This is the function that will recursively find where to insert and insert the new data.
 * @details This first checks if we have gotten to a NULL pointer in the tree. If it has, then this is the location
 * to insert the new node. If not, compare the data to the current location. If the data is bigger, then recall going right
 * if less then recall going left until the correct positioning.
 * @param Node pointer and the data.
 * @return void
 * 
 * @pre there should an initialized tree.
 * @post there will be a new item.
 */template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::insertHelper(BSTreeNode* & location, const DataType& newDataItem)
	{
		/// if reached location, create the new node
		if (location==NULL)
			location = new BSTreeNode(newDataItem, NULL, NULL);

		/// if the current location is larger than data go left
		if (location->dataItem.getKey() > newDataItem.getKey())
			insertHelper(location->left, newDataItem);

		/// if the current location is smaller than data, go right
		if (location->dataItem.getKey() < newDataItem.getKey())
			insertHelper(location->right, newDataItem);
	}

/**
 * This is the function that checks to see if a piece of data is in the BST.
 * @details Calls the retrieve helper.
 * @param The thing to look for (KeyType) and where to put it (DataType)
 * @return Bool, true if found. False if not.
 * 
 * @pre there should an initialized tree
 * @post Nothing changes.
 */
template < typename DataType, class KeyType >
bool BSTree<DataType, KeyType>::retrieve(const KeyType& searchKey, DataType& searchDataItem) const
	{
		return retrieveHelper(root, searchKey, searchDataItem);
	}

/**
 * This is the function that will recursively check for a data item.
 * @details Checks if we have gotten to the end. If we have and still not found will return false. If the item in the current location
 * is the same will set it equal to the parameter to copy to. If niether of those are true then checks to see if we are searching for
 * something bigger or smaller than the current and go the corresponding way.
 * @param BST node pointer (where to check), the thing to look for (keytype), where to store if found (datatype)
 * @return True if found, false if not.
 * 
 * @pre there should an initialized tree
 * @post Nothing changes.
 */
template < typename DataType, class KeyType >
bool BSTree<DataType, KeyType>::retrieveHelper(BSTreeNode* location, const KeyType& searchKey, DataType& searchDataItem) const
	{
		/// if checked the complete tree, return false
		if (location == NULL)
			return false;

		/// if found, return true
		if (location->dataItem.getKey() == searchKey)
			{
				searchDataItem = location->dataItem;
				return true;
			}

		/// if what were are looking for is smaller go left else go right
		if (location->dataItem.getKey() > searchKey)
			{
				return retrieveHelper(location->left, searchKey, searchDataItem);
			}

		else 
			{
				return retrieveHelper(location->right, searchKey, searchDataItem);
			}

	}

/**
 * This is the function that will look for something and delete it.
 * @details Calls its helper.
 * @param The thing to delete (keytype)
 * @return True, if found and deleted. False if not found.
 * 
 * @pre there should an initialized tree
 * @post there will one less node if asked to remove something found.
 */
template < typename DataType, class KeyType >
bool BSTree<DataType,KeyType>:: remove ( const KeyType& deleteKey )
	{
		return removeHelper(root, deleteKey);
	}

/**
 * This is the function that will recursively find then delete a node. Then adjusts the tree.
 * @details If it has gotten to the end and it has still not found the keytype it ends. Once found checks how 
 * many children the node of the item has. If none, just deletes. If it has one then just points the current to the next of
 * next. If two children, find the predeccsor and then overwrites the current data with the predeccesor then calls the removeHelp
 * to delete the original predeccesor Node. If nothing is found but not null recalls with the appropriate side of the tree.
 * @param BST node, the current location. What to delete, keytype.
 * @return true if something is deleted. false if not found.
 * 
 * @pre there should an initialized tree
 * @post something will be deleted and tree will still be in order.
 */
template < typename DataType, class KeyType >
bool BSTree<DataType,KeyType>:: removeHelper ( BSTreeNode* & location, const KeyType& deleteKey )
	{
		/// if at the end and not found, return false
		if (location == NULL)
			return false;

		/// if found, delete
		if (location->dataItem.getKey() == deleteKey)
			{
				/// if no children
				if ((location->left == NULL) && (location->right == NULL))
					{
						delete location;
						location = NULL;
						return true;	
					}

				/// if one child
				/// left child, no right
				if ((location->left != NULL) && (location->right == NULL))
					{
						BSTreeNode* temp;
						temp = location;
						location = location->left;
						delete temp;
						return true;
					}

				/// no left, right child
				if ((location->left == NULL) && (location->right != NULL))
					{
						BSTreeNode* temp;
						temp = location;
						location = location->right;
						delete temp;
						return true;
					}

				/// if two children	
				if ((location->left != NULL) && (location->right != NULL))
					{
						BSTreeNode* temp;
						temp = location;

						/// get predecessor
						temp = temp->left;
						while (temp->right != NULL)
							temp = temp->right;

						/// overwrite the value to delete with the predecessor
						location->dataItem = temp->dataItem;

						/// delete the node with the value just written to the new location
						return removeHelper(location->left, temp->dataItem.getKey());
					}
			}

		/// keep searching
		if (location->dataItem.getKey() > deleteKey)
			return removeHelper(location->left, deleteKey);
		else 
			return removeHelper(location->right, deleteKey);
	}

/**
 * This is the function that will write the data in the tree in order.
 * @details Calls its helper.
 * @param None.
 * @return void
 * 
 * @pre there should an initialized tree.
 * @post data will be printed on the screen.
 */
template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>:: writeKeys () const
	{
		writeKeysHelper(root);
		cout << endl;
	}

/**
 * This is the function that will recursively print out all the data in order. 
 * @details Navigates all the way to the left of the BST, then prints out. Recalls the function with the children to 
 * the left of the most left node that has not been printed yet.
 * @param BST node. The current location.
 * @return void
 * 
 * @pre there should an initialized tree.
 * @post data will be printed on the screen.
 */
template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>:: writeKeysHelper (BSTreeNode* location) const
	{
		if (!isEmpty())
			{
				/// go all the way to the left
				if (location->left != NULL)
					{
						writeKeysHelper(location->left);	
					}

				/// once all the way to the left print out the current
				cout << location->dataItem.getKey() << " ";

				/// check for the children to the right of the most left node
				if (location->right != NULL)
					{
						writeKeysHelper(location->right);	
					}
			}
	}

/**
 * This is the function that will deallocate all memory of the BST.
 * @details Calls its helper then sets the root to NULL.
 * @param None.
 * @return void
 * 
 * @pre there should an initialized tree.
 * @post there will be an empty tree.
 */
template < typename DataType, class KeyType >
void BSTree<DataType,KeyType>:: clear()
	{
		clearHelper(root);
		root = NULL;
	}

/**
 * This is the function that will recursively deallocate all memory.
 * @details If the the tree is not empty, goes down all nodes on the left, checks if they have a right child. If they do
 * recalls. If they dont, they get deleted.
 * @param ExprTree, the tree to copy to and copy from
 * @return void
 * 
 * @pre there should two initialized trees
 * @post there will be two identical trees
 */
template < typename DataType, class KeyType >
void BSTree<DataType,KeyType>:: clearHelper( BSTreeNode* & location )
	{
		if(!isEmpty())
			{
				/// if there is more to the left recall with child
				if (location->left != NULL)
					clearHelper(location->left);

				/// if leftmost has a right child repeat process with the right child
				if (location->right != NULL)
					clearHelper(location->right);

				/// deallocate
				delete location;
			}
	}

/**
 * This is the function that checks if the tree is empty.
 * @details Checks if the root is null to see if the tree is empty.
 * @param None.
 * @return True if empty. False if not.
 * 
 * @pre there should an initialized tree.
 * @post Nothing changes.
 */
template < typename DataType, class KeyType >
bool BSTree<DataType, KeyType>:: isEmpty () const
	{
		return (root == NULL);
	}

/**
 * This is the function that will get the height of the tree. 
 * @details Checks if the tree is empty. If it is, returns 0 for height. If it isnt, calls the helper.
 * @param None.
 * @return Int, height of the tree.
 * 
 * @pre there should an initialized tree.
 * @post the height will be returned.
 */
template < typename DataType, class KeyType >
int BSTree<DataType, KeyType>:: getHeight () const
	{
		if (isEmpty())
			return 0;

		heightHelper(root);
	}

/**
 * This is the function that will recursively check for the height of the tree.
 * @details If reached the end returns 0, Otherwise keeps calling itself for the size of both the left and right part.
 * @param BST node. Current location.
 * @return Int for the height.
 * 
 * @pre there should an initialized tree.
 * @post height will be returned
 */
template < typename DataType, class KeyType >
int BSTree<DataType, KeyType>:: heightHelper ( BSTreeNode* location) const
	{
		/// if we reached a null spot, return 0 since nothing is added
		if (location == NULL)
			return 0;
		/// get the size of the left and right by recalling and going to the left and right
		int leftTree = heightHelper(location->left);
		int rightTree = heightHelper(location->right);

		/// return which ever is larger plus one since the current node is part of the height
		if (leftTree > rightTree)
			return leftTree+1;
		else
			return rightTree+1;
	}

/**
 * This is the function counts the total amount of nodes in the BST.
 * @details calls the helper.
 * @param None.
 * @return Int, the amount of nodes.
 * 
 * @pre there should an initialized tree.
 * @post number of nodes will be returned.
 */
template < typename DataType, class KeyType >
int BSTree<DataType, KeyType>:: getCount () const
	{
		return countHelper(root);
	}

/**
 * This is the function that will recursively count the number of items in the tree.
 * @details Basically adds one and recalls for the left and right every time a node is not NULL. If
 * NULL then just adds 0.
 * @param BST node, location.
 * @return Int, the amount of nodes.
 * 
 * @pre there should an initialized tree.
 * @post tree will be counted.
 */
template < typename DataType, class KeyType >
int BSTree<DataType, KeyType>:: countHelper (BSTreeNode* location) const
	{
		if (location == NULL)
			return 0;
		else
			return (countHelper(location->left)+countHelper(location->right)+1);
	}

/**
 * NOT USED
 */
template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>:: writeLessThan ( const KeyType& searchKey ) const
	{
	
	}