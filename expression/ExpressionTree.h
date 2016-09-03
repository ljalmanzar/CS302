//--------------------------------------------------------------------
//
//  Laboratory 8                                     ExpressionTree.h
//
//  Class declarations for the linked implementation of the
//  Expression Tree ADT -- including the recursive helpers for the
//  public member functions
//
//  Instructor copy with the recursive helper function declarations.
//  The student version does not have those, but has a place to write
//  the declarations in the private section.
//
//--------------------------------------------------------------------

#ifndef EXPRESSIONTREE_H
#define EXPRESSIONTREE_H

#include <stdexcept>
#include <iostream>

using namespace std;

template <typename DataType>
class ExprTree {
  public:

    // Constructor
    ExprTree ();
    ExprTree(const ExprTree& source);

    ExprTree& operator=(const ExprTree& source);

    // Destructor
    ~ExprTree ();

    // Expression tree manipulation operations
    void build ();
    void expression () const;
    DataType evaluate() const throw (logic_error);
    void clear ();              // Clear tree
    void commute();
    bool isEmpty() const;
    bool isEquivalent(const ExprTree& source) const;
    void showStructure () const;

  private:

    class ExprTreeNode {
      public:
        // Constructor
        ExprTreeNode ( char elem,
                       ExprTreeNode *leftPtr, ExprTreeNode *rightPtr );

        // Data members
        char dataItem;          // Expression tree data item
        ExprTreeNode *left,     // Pointer to the left child
                     *right;    // Pointer to the right child
    };

    // Recursive helper functions for the public member functions -- insert
    // prototypes of these functions here.
    void copyHelper(ExprTreeNode * & ptr, ExprTreeNode * source );
    void showHelper ( ExprTreeNode *p, int level ) const;
    void buildHelper (ExprTreeNode* & top); 
    void expressionHelper (ExprTreeNode* ptr) const;
    void clearHelper(ExprTreeNode* & ptr);
    DataType evaluateHelper(ExprTreeNode* ptr) const throw (logic_error);
    void commuteHelp(ExprTreeNode* ptr);
    bool isEquivalentHelp(const ExprTreeNode* home,const ExprTreeNode* source) const;

    // Data member
    ExprTreeNode *root;   // Pointer to the root node
};

#endif		// #ifndef EXPRESSIONTREE_H
