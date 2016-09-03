// Include Files
#include <iostream>
#include <cstdlib>
#include "ListLinked.h"
using namespace std;

// Function Implementations
template <typename DataType>
List<DataType>::List(int ignored)
{
  // nothing to do for constructor
  head = cursor = NULL;
}

template <typename DataType>
List<DataType>::List(const List& other)
{
  // if the "other" list is not empty, this creates a copy
  if (other.head != NULL)
    {
      ListNode* temp = other.head;
      head = new ListNode(temp->dataItem,NULL);
      cursor = head;
      while (temp->next != NULL)
        { 
          temp = temp->next;
          cursor->next = new ListNode(temp->dataItem,NULL);
          cursor = cursor->next;
        } 
      cursor = head;
    }

  else 
    {
      head = cursor = NULL;
    }
}

template <typename DataType>
List<DataType>& List<DataType>::operator=(const List& other)
{
    // same as copy constructor but for "="
    if (other.head != NULL)
    {
      ListNode* temp = other.head;
      head = new ListNode(temp->dataItem,NULL);
      cursor = head;
      while (temp->next != NULL)
        { 
          temp = temp->next;
          cursor->next = new ListNode(temp->dataItem,NULL);
          cursor = cursor->next;
        } 
      cursor = head;
    }

  else 
    {
      head = cursor = NULL;
    }
}

template <typename DataType>
List<DataType>::~List()
{
  // deallocates all memory
  clear();
}

template <typename DataType>
bool List<DataType>::insert(const DataType& newDataItem)
{
  // inserts if this is the first item
  if (head == NULL)
    { 
      head = new ListNode(newDataItem, NULL);
      cursor = head;
      return true;
    }
  //inserts if the cursor is at the last item
  if (cursor->next == NULL)
    {
     ListNode* temp = cursor;
     cursor = new ListNode(newDataItem, NULL);
     temp->next = cursor;
     return true;
    }

  //inserts if the above two criterias are not met
  ListNode* temp = new ListNode(newDataItem, cursor->next);
  cursor->next = temp;
  cursor = cursor->next;
}

template <typename DataType>
bool List<DataType>::remove()
{
  // nothing to delete if it is empty
  if (head == NULL)
    {
      return false; 
    }

  // deletes for only one item
  if (head->next == NULL)
    {
      delete head;
      head = cursor = NULL; 
      return true;
    }

  // deletes if the cursor is at the first item
  if (cursor == head)
    {
      cursor = cursor -> next;
      delete head;
      head = cursor;
      return true;
    }

  // deletes everything else
  ListNode* temp = cursor;
  gotoPrior();
  cursor -> next = temp -> next;
  delete temp;
  if (cursor->next == NULL)
    {
      cursor = head; 
    }
  else
    {
      cursor = cursor -> next;
    }
}

template <typename DataType>
bool List<DataType>::replace(const DataType& newDataItem)
{
  // overwrites the data in the node
  cursor->dataItem = newDataItem;
}

template <typename DataType>
bool List<DataType>::clear()
{
  // deallocates the memory for every node
  ListNode* temp = head;

  while (head != NULL)
  {
    temp = head->next;
    delete head;
    head = temp;
  }
}

template <typename DataType>
bool List<DataType>::isEmpty() const
{
  if (head == NULL)
    {
      return true;
    }
  return false;
}

template <typename DataType>
bool List<DataType>:: isFull() const
{
  return false;
}

template <typename DataType>
bool List<DataType>::gotoBeginning()
{
  if (head == NULL)
    {
      return false;
    }

  cursor = head;
  return true;
}

template <typename DataType>
bool List<DataType>::gotoEnd()
{
  while (cursor->next != NULL)
    {
      cursor = cursor->next;
    }
}

template <typename DataType>
bool List<DataType>::gotoNext()
{
  if (head == NULL || cursor -> next == NULL)
    {
      return false;
    }

      cursor = cursor -> next;
      return true;
}

template <typename DataType>
bool List<DataType>::gotoPrior()
{
  if (cursor != head)
    {
      ListNode* temp = head;

      while (temp -> next != cursor)
        {
          temp = temp -> next;
        }

      cursor = temp;
      return true;
    }

  return false;
}

template <typename DataType>
DataType List<DataType>::getCursor() const
{
  return cursor->dataItem;
}

template <typename DataType>
List<DataType>::ListNode::ListNode(const DataType& nodeData, ListNode* nextPtr)
{
  dataItem = nodeData;
  next = nextPtr;
}

template <typename DataType>
bool List<DataType>::moveToBeginning()
{
  if (head == cursor)
    {
      return false; 
    }
  if (cursor->next == NULL)
    {
      ListNode* temp = cursor;
      gotoPrior();
      cursor->next=NULL;
      cursor = temp;
      cursor->next = head;
      head = cursor;
      return true;
    }

      ListNode* temp = cursor;
      gotoPrior();
      cursor->next=temp->next;
      cursor = temp;
      cursor->next = head;
      head = cursor;
      return true;
}

template <typename DataType>
bool List<DataType>::insertBefore(const DataType& newDataItem)
{
  if (head == NULL)
    {
      head = new ListNode(newDataItem,NULL);
      cursor = head;
      return true; 
    }

  if (cursor == head)
    {
      cursor = new ListNode(newDataItem,head);
      head = cursor;
      return true;
    }

  gotoPrior();
  insert(newDataItem);
}

template <typename DataType>
void List<DataType>::showStructure() const

// Outputs the items in a list. If the list is empty, outputs
// "Empty list". This operation is intended for testing and
// debugging purposes only.

{
    if ( isEmpty() )
    {
       cout << "Empty list" << endl;
    } 
    else
    {
  for (ListNode* temp = head; temp != 0; temp = temp->next) {
      if (temp == cursor) {
    cout << "[";
      }

      // Assumes that dataItem can be printed via << because
      // is is either primitive or operator<< is overloaded.
      cout << temp->dataItem; 

      if (temp == cursor) {
    cout << "]";
      }
      cout << " ";
  }
  cout << endl;
    }
}

