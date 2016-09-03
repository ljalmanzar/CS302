/**
This is an implementation of a Queue

This is a linked queue implemented with nodes
*/

// Include Files
#include <iostream>
#include <cstdlib>
#include "QueueLinked.h"

using namespace std;

// Function Implementations

/**Default Constructor, sets pointers to NULL
input parameter is irrelevant since we have no max size
*/
template <typename DataType>
QueueLinked<DataType>::QueueLinked(int maxNumber)
{
  front = back = NULL;
}

/**Copy Constructor
copies the input parameter of another queue
*/
template <typename DataType>
QueueLinked<DataType>::QueueLinked(const QueueLinked& other)
{
  /// if it is empty just set pointers to NULL otherwise copy
  if (other.front != NULL)
    {
      QueueNode* temp = other.front;
      QueueNode* newtemp;
      front = new QueueNode(temp->dataItem,NULL);
      newtemp = front;
      while (temp->next!=NULL)
        {
          temp=temp->next;
          newtemp->next=new QueueNode(temp->dataItem,NULL);
          newtemp=newtemp->next;
        }
      back = newtemp;
      back->next = NULL;
    }
  else
    {
      front = back = NULL;
    }
}

/// Assignment operator overloaded 
template <typename DataType>
QueueLinked<DataType>& QueueLinked<DataType>::operator=(const QueueLinked& other)
{
    if (other.front != NULL)
    {
      QueueNode* temp = other.front;
      QueueNode* newtemp;
      front = new QueueNode(temp->dataItem,NULL);
      newtemp = front;
      while (temp->next!=NULL)
        {
          temp=temp->next;
          newtemp->next=new QueueNode(temp->dataItem,NULL);
          newtemp=newtemp->next;
        }
      back = newtemp;
      back->next = NULL;
    }
  else
    {
      front = back = NULL;
    }

  return *this;
}

/**
Deconstructor
clears  all memory
*/
template <typename DataType>
QueueLinked<DataType>::~QueueLinked()
{
  clear();
}

/**
Enqueue
adds new data to queue
*/
template <typename DataType>
void QueueLinked<DataType>::enqueue(const DataType& newDataItem) throw (logic_error)
{
  /// create new node
  QueueNode* temp = new QueueNode(newDataItem, NULL);

  /// if the current is empty make first 
  ///(just realized this could have been coded better, too late to fix/test)
  if (isEmpty())
    {
      front = temp;
      back = temp; 
    }
  else 
    {
      back->next = temp;
      back = temp;
    }
}

/**
dequeue
takes the front data
*/
template <typename DataType>
DataType QueueLinked<DataType>::dequeue () throw (logic_error)
{
  if (isEmpty())
    {
      throw logic_error ("dequeue() while queue empty");
    }

  DataType data;
  QueueNode* temp = front;
  front = front -> next; 
  if (front == NULL)
    {
      back = NULL; 
    }

  data = temp->dataItem;
  delete temp;
  return data;
}

/**
clear
deletes all allocated memory for the queue nodes
*/
template <typename DataType>
void QueueLinked<DataType>::clear()
{
  QueueNode* temp = front;

  while (front != NULL)
    {
      temp = front;
      front = front->next;
      delete temp; 
    }
}

/**
isEmpty checks to see if the queue has any data
*/
template <typename DataType>
bool QueueLinked<DataType>::isEmpty() const
{
  if (front == NULL)
    {
      return true;
    }
  else 
    {
      return false;
    }
}

/**
ifFull
irrelevant because always false
*/
template <typename DataType>
bool QueueLinked<DataType>::isFull() const
{
  return false;
}

/**
putfront
will add new data to the queue but differently than enqueue, will put the 
newest data up front
*/
template <typename DataType>
void QueueLinked<DataType>::putFront(const DataType& newDataItem) throw (logic_error)
{
  if (isEmpty())
    {
      enqueue(newDataItem); 
    }
  else
    {
      QueueNode* temp = new QueueNode(newDataItem, front);
      front = temp;
    }
}

/**
getrear
grabs the last data item in the queue
*/
template <typename DataType>
DataType QueueLinked<DataType>::getRear() throw (logic_error)
{
  /// check for empty
  if (isEmpty())
    {
      throw logic_error ("getRear() while queue empty"); 
    }

  DataType data;
  data = back->dataItem;

  /// if there is only one item
  if (front == back)
      {
        delete front;
        front = back = NULL;
        return data;
      }

  else 
    {
      /// save the back
      QueueNode* temp = back;
      
      /// go to prior
      back = front; 
      while (back->next != temp)
        {
          back = back->next;
        }

      /// delete the last
      delete temp;
      /// set the next of the new back to null
      back->next = NULL;

      return data;
    }
}

/**
getlength
returns the length of the queue
*/
template <typename DataType>
int QueueLinked<DataType>::getLength() const
{
  int counter = 0;
  QueueNode* temp = front;

  while (temp != NULL)
    {
      counter ++;
      temp = temp->next;
    }

  return counter;
}

template < typename DT >
void QueueLinked<DT>:: showStructure () const

// Linked list implementation. Outputs the elements in a queue. If
// the queue is empty, outputs "Empty queue". This operation is
// intended for testing and debugging purposes only.

{
    QueueNode *p;   // Iterates through the queue

    if ( isEmpty() )
  cout << "Empty queue" << endl;
    else
    {
  cout << "Front\t";
  for ( p = front ; p != 0 ; p = p->next )
  {
      if( p == front ) 
      {
    cout << '[' << p->dataItem << "] ";
      }
      else
      {
    cout << p->dataItem << " ";
      }
  }
  cout << "\trear" << endl;
    }
}

template <typename DataType>
QueueLinked<DataType>::QueueNode::QueueNode(const DataType& nodeData, QueueNode* nextPtr)
{
  dataItem = nodeData;
  next = nextPtr;
}