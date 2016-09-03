/** @file Expression Tree Implementation
@author Luis Almanzar
@version 1.0
@brief Implementation for the expression tree class.
@details 
@date Wednesday, October 8th
*/
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <sys/time.h>
#include "ExpressionTree.h"
#include "show8.cpp"

using namespace std;

/**
 * This is the tree node constructor. Will just create the node.
 * @param char elem (the data), 2 node pointers (will be the children of the created node
 * @return constructor, no return
 * 
 * @pre no pre conditions
 * @post there will be a node created with the data  
 */
template <typename DataType>
ExprTree<DataType>::ExprTreeNode::ExprTreeNode ( char elem, ExprTreeNode *leftPtr, ExprTreeNode *rightPtr )
    {
    	dataItem = elem;
    	left = leftPtr;
    	right = rightPtr;
    }
    
/**
 * This is the tree constructor.
 * @param none
 * @return constructor, no return
 * 
 * @pre no pre conditions
 * @post the root will be null
 */
template <typename DataType>
ExprTree<DataType>::ExprTree()
	{
		root = NULL; 
	}

/**
 * This is the tree copy constructor. Will create another tree just like the initial one.
 * Just uses the copyHelper function. 
 * @param ExprTree, the tree to copy to
 * @return constructor, no return
 * 
 * @pre there should be another tree initialized already
 * @post there will be two identical trees
 */
template <typename DataType> 
ExprTree<DataType>::ExprTree(const ExprTree& source)
	{
		/// initialize
		root = NULL;
		
		/// if the source is not empty proceed to copying
		if(source.root != NULL)
			copyHelper(root, source.root);
	}

/**
 * This is the overloaded assignment operator, will set two trees equal to eachother
 * Just uses the copyHelper function. 
 * @param ExprTree, the tree to copy to
 * @return returns the copied tree
 * 
 * @pre there should be a tree to copy to and copy from already created
 * @post there will be two identical trees
 */
template <typename DataType>	
ExprTree<DataType>& ExprTree<DataType>::operator=(const ExprTree& source)
	{
		/// check to see if the trees are the same, if they are return it
		if(this == &source)
			return *this;
	
		/// if not empty, make empty
		if(root != NULL)
			clear();
	
		/// if the source is empty return empty tree
		if(source.root == NULL)
			return *this;
	
		/// copy
		copyHelper(root, source.root);
		return *this;
	}

/**
 * This is the function that will recursively copy two trees to eachother
 * @details Checks if the current item is a character or digit,  calls itself two more timess then creates the new node
 * if it is a digit, it will only create a new node and stop
 * @param ExprTree, the tree to copy to and copy from
 * @return void
 * 
 * @pre there should two initialized trees
 * @post there will be two identical trees
 */
template <typename DataType>
void ExprTree<DataType>::copyHelper(ExprTreeNode * & ptr, ExprTreeNode * source )
{
	if(source != NULL)
	{
		ptr = new ExprTreeNode (source->dataItem ,NULL,NULL);
		
		if (isdigit(ptr->dataItem))
			{
				
			}
		else
			{
				copyHelper(ptr->left, source->left);
				copyHelper(ptr->right, source->right);
			}
	}
}

/**
 * This is the tree destructor.
 * @details frees all memory by using clear function 
 * @param none
 * @return void
 * 
 * @pre there should be an initialized tree
 * @post all memory will be freed and the tree will be destroyed
 */
template <typename DataType>
ExprTree<DataType>::~ExprTree ()
	{
		clear();
	}

/**
 * This is the build function.
 * @details just calls the buildhelper
 * @param none
 * @return void
 * 
 * @pre there should be an initialized tree
 * @post a tree with valid data will be created
 */
template <typename DataType>
void ExprTree<DataType>:: build ()
	{
		buildHelper(root);
	}
	
/**
 * This is the build helper
 * @details creates the tree recursively
 * basically creates a new node if it is not a digit will call the function again
 * to create the children nodes
 * @param the pointer to work on, initially the root
 * @return void
 * 
 * @pre there should be an initialized tree
 * @post an expression tree will be created
 */
template <typename DataType>
void ExprTree<DataType>:: buildHelper (ExprTreeNode* & ptr)
	{
		/// read in
		char val;
		cin >> val;
		
		/// create new node 
		ptr = new ExprTreeNode(val, NULL, NULL);
		
		/// if it is a digit stop, if not make more
		if (!isdigit(ptr->dataItem))
			{
				buildHelper(ptr->left);
				buildHelper(ptr->right);	
			}
	}
	
/**
 * This is the expression function.
 * @details calls the expression helper to show the function with parenthesis
 * @param none
 * @return void
 * 
 * @pre there should be a built tree
 * @post the function will be displayed on the screen
 */
template <typename DataType>
void ExprTree<DataType>:: expression () const
	{
		expressionHelper(root);
	}

/**
 * This is the expression helper function.
 * @details prints out the function recursively, if current item is a digit will print out digit
 * if the current item is not a digit, will print the beginning parenthesis and recalls itself for left and right
 * @param the ptr, initially the root
 * @return void
 * 
 * @pre there should be a built tree
 * @post the function will be displayed on the screen
 */
template <typename DataType>
void ExprTree<DataType>:: expressionHelper(ExprTreeNode* ptr) const
	{
		if (isdigit(ptr->dataItem))
			{
				int i = ptr->dataItem - '0';
				cout << i;
			}
		if (!isdigit(ptr->dataItem))
			{
				cout << "(";
				expressionHelper(ptr->left);
				cout << (ptr -> dataItem);
				expressionHelper(ptr->right);
				cout << ")";
			}
	}
	
/**
 * This is the evaluate.
 * @details calls the evaluation helper to get the output
 * @param none
 * @return the datatype, most likely a float
 * 
 * @pre there should be a built tree
 * @post the function will be solved
 */
template <typename DataType>
DataType ExprTree<DataType>:: evaluate() const throw (logic_error)
	{
		if (isEmpty())
			{
				throw logic_error ("Empty tree");
			}
		return (evaluateHelper(root));
	}
	
/**
 * This is the evaluate helper.
 * @details evaluates the tree recusively, works its way to the bottom of the tree then solves 
 * the left and right of each individual expression
 * @param the current ptr, initially the root
 * @return the datatype, most likely a float
 * 
 * @pre there should be a built tree
 * @post the function will be solved
 */
template <typename DataType>
DataType ExprTree<DataType>:: evaluateHelper(ExprTreeNode* ptr) const throw (logic_error)
	{
		float answ;
		
		/// if it is a digit convert and return
		if (isdigit(ptr->dataItem))
			{
				answ = (ptr->dataItem) - '0';
				return answ;
			}
		/// if an expression get the left and right values by recalling, then check for char and do operation
		else 
			{
				float lval , rval;
				lval = evaluateHelper(ptr->left);
				rval = evaluateHelper(ptr->right);
			
				if (ptr -> dataItem == '+')
					return lval + rval;
				if (ptr -> dataItem == '-')
					return lval - rval;
				if (ptr -> dataItem == '*')
					return lval * rval;
				if (ptr -> dataItem == '/')
					return lval / rval;
			}
		
	}

/**
 * This is the clear.
 * @details calls the clear helper
 * @param none
 * @return void
 * 
 * @pre there should be a built tree
 * @post all memory will be freed
 */
template <typename DataType>	
void ExprTree<DataType>:: clear ()
	{
			clearHelper(root);
	}   
	
/**
 * This is the clear helper.
 * @details deallocates all memory recursively, if the pointer is not null
 * it will call itself to the pointers left and right then will delete
 * @param ptr, initially root
 * @return void
 * 
 * @pre there should be a built tree
 * @post all memory will be freed
 */
template <typename DataType>
void ExprTree<DataType>:: clearHelper(ExprTreeNode* & ptr)
	{
		if (ptr!=NULL)
			{
				/// recall to left and right of node
				clearHelper(ptr->left);
				clearHelper(ptr->right);
				
				/// delete the node
				delete ptr;
				
				if (ptr->left!=NULL)
				ptr->left = NULL;
				if(ptr->right!=NULL)
				ptr->right = NULL;
				
				ptr=NULL;
			}
	}
	
/**
 * This is the commute function.
 * @details calls commute help function
 * @param none
 * @return void
 * 
 * @pre there should be a built tree
 * @post the tree will be flipped
 */
template <typename DataType>          
void ExprTree<DataType>:: commute()
	{
		commuteHelp(root);
	}

/**
 * This is the commute helper function.
 * @details swaps every single left and right child pointer down the tree recursively
 * @param ptr, intially the root
 * @return void
 * 
 * @pre there should be a built tree
 * @post the tree will be flipped
 */
template <typename DataType>
void ExprTree<DataType>:: commuteHelp(ExprTreeNode* ptr)
	{
		/// if at the end, do nothing (i believe this stuff isnt needed but too lazy to test without
		if (ptr->right == NULL && ptr->left == NULL)
			{
				ExprTreeNode* temp = ptr->right;
				ptr->right = ptr->left;
				ptr->left = temp;
			}
		/// if not at the end, swap left and right and recall for new pointers
		else
			{
				ExprTreeNode* temp = ptr->right;
				ptr->right = ptr->left;
				ptr->left = temp;
				commuteHelp(ptr->left);
				commuteHelp(ptr->right);
			}
	}
	
/**
 * This is the isempty funtion.
 * @details 
 * @param none
 * @return true if empty, false if not
 * 
 * @pre an initialized tree
 * @post same
 */
template <typename Datatype>
bool ExprTree<Datatype>::isEmpty() const
	{
		return (root == NULL);
	}
	
/**
 * This is the is eqeuivalent function.
 * @details compared two trees to see if they are the same by calling its helper
 * @param the tree to compare with
 * @return bool, true if the same, false if not
 * 
 * @pre there should be 2 built trees
 * @post nothing will change
 */	
template <typename DataType>
bool ExprTree<DataType>:: isEquivalent(const ExprTree& source) const
	{
		return isEquivalentHelp(root,source.root);
		
	}
	
/**
 * This is the is eqeuivalent helper function.
 * @details compares two trees to see if they are the same recursively
 * the 2 stopping conditions are that 1, a pointer is null (at the end) so it compares it to the other and if the same returns true
 * and 2, if they are not the same will return false.
 * if niether is met then calls itself twice for the left and right
 * @param the tree to compare with
 * @return bool, true if the same, false if not
 * 
 * @pre there should be 2 built trees
 * @post nothing will change
 */	
template <typename DataType>
bool ExprTree<DataType>:: isEquivalentHelp(const ExprTreeNode* home,const ExprTreeNode* source) const
	{
		/// if pointers are null compare them, should both be null
		if (home == NULL || source == NULL)
			{
				return (home == source);
			}
		/// check for equivalency, if not return false
		else if (home->dataItem != source->dataItem)
			{
				return false;
			}
		/// if passed other 2, then call for left and right
		else
			{
				return (isEquivalentHelp(home->left, source->left) && isEquivalentHelp(home->right,source->right));
			}
	}	
