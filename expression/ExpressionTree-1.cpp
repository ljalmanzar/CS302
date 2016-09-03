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

template <typename DataType>
ExprTree<DataType>::ExprTreeNode::ExprTreeNode ( char elem, ExprTreeNode *leftPtr, ExprTreeNode *rightPtr )
    {
    	dataItem = elem;
    	left = leftPtr;
    	right = rightPtr;
    }
    
template <typename DataType>
ExprTree<DataType>::ExprTree()
	{
		root = NULL; 
	}

template <typename DataType> 
ExprTree<DataType>::ExprTree(const ExprTree& source)
	{
		
	}

template <typename DataType>	
ExprTree<DataType>& ExprTree<DataType>::operator=(const ExprTree& source)
	{
		if (this == source)
			return *this;
			
		
	}
	
template <typename DataType>
ExprTree<DataType>::~ExprTree ()
	{
		
	}

template <typename DataType>
void ExprTree<DataType>:: build ()
	{
		buildHelper(root);
	}
	
template <typename DataType>
void ExprTree<DataType>:: buildHelper (ExprTreeNode* & ptr)
	{
		char val;
		cin >> val; 
		ptr = new ExprTreeNode(val, NULL, NULL);
		
		if (!isdigit(ptr->dataItem))
			{
				buildHelper(ptr->left);
				buildHelper(ptr->right);	
			}
	}
	
template <typename DataType>
void ExprTree<DataType>:: expression () const
	{
		expressionHelper(root);
	}

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
	
template <typename DataType>
DataType ExprTree<DataType>:: evaluate() const throw (logic_error)
	{
		if (isEmpty())
			{
				throw logic_error ("Empty tree");
			}
		return (evaluateHelper(root));
	}
	
template <typename DataType>
DataType ExprTree<DataType>:: evaluateHelper(ExprTreeNode* ptr) const throw (logic_error)
	{
		float answ;
		
		if (isdigit(ptr->dataItem))
			{
				answ = (ptr->dataItem) - '0';
				return answ;
			}
		
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

template <typename DataType>	
void ExprTree<DataType>:: clear ()
	{
		root =NULL;
		//	clearHelper(root);
	}   
	
template <typename DataType>
void ExprTree<DataType>:: clearHelper(ExprTreeNode* & ptr)
	{
	/*	if (ptr!=NULL)
			{
				clearHelper(ptr->left);
				clearHelper(ptr->right);
				cout << "at delete" << endl;
				delete ptr;
				cout << "delete success" << endl;
				if (ptr->left!=NULL)
				ptr->left = NULL;
				if(ptr->right!=NULL)
				ptr->right = NULL;
				
				ptr=NULL;
			}*/
	}
	
template <typename DataType>          
void ExprTree<DataType>:: commute()
	{
		commuteHelp(root);
	}

template <typename DataType>
void ExprTree<DataType>:: commuteHelp(ExprTreeNode* ptr)
	{
		if (ptr->right == NULL && ptr->left == NULL)
			{
				ExprTreeNode* temp = ptr->right;
				ptr->right = ptr->left;
				ptr->left = temp;
			}
		else
			{
				ExprTreeNode* temp = ptr->right;
				ptr->right = ptr->left;
				ptr->left = temp;
				commuteHelp(ptr->left);
				commuteHelp(ptr->right);
			}
	}
template <typename Datatype>
bool ExprTree<Datatype>::isEmpty() const
	{
		return (root == NULL);
	}
	
template <typename DataType>
bool ExprTree<DataType>:: isEquivalent(const ExprTree& source) const
	{
		return isEquivalentHelp(root,source.root);
		
	}
	
template <typename DataType>
bool ExprTree<DataType>:: isEquivalentHelp(const ExprTreeNode* home,const ExprTreeNode* source) const
	{
		if (home == NULL || source == NULL)
			return (home == source);
		else if (home->dataItem != source->dataItem)
			return 0;
		else
			{
				return (isEquivalentHelp(home->left, source->left) && isEquivalentHelp(home->right,source->right));
			}
	}	
