/** @file Hash Table Implementation
@author Luis Almanzar
@version 1.0
@brief Implementation for a Binary Search Tree.
@details 
@date Monday, October 26
*/
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <sys/time.h>
#include "HashTable.h"
#include "show10.cpp"

using namespace std;

/**
 * This is the default constructor. 
 * @details Will set the table size, and allocate the memory for the table.
 * @return Constructor.
 * 
 * @pre Nothing.
 * @post There will be an empty initialized tree.
 */
template <typename DataType, typename KeyType>
HashTable<DataType, KeyType>::HashTable(int initTableSize)
	{
		/// save size
		tableSize = initTableSize;
		/// initialize the array
		dataTable = new BSTree<DataType, KeyType>[tableSize];
	}

/**
 * This is the copy constructor. 
 * @details Will set the table size equal to the parameter's table size and allocates memory 
 * for the new table. Then uses the equal operator to set the tables equal to eachother.
 * @return Constructor.
 * 
 * @pre There should be one table already initialized.
 * @post There will be two identical tables.
 */
template <typename DataType, typename KeyType>
HashTable<DataType, KeyType>::HashTable(const HashTable& other)
	{
		/// copy size and create new table
		tableSize = other.tableSize;
		dataTable = new BSTree<DataType, KeyType>[tableSize];

		*this = other;
	}

/**
 * This is the equal operator. 
 * @details Will set the tree equal to the tree in the parameter. This is done by copying the size then iterating through the tress 
 * array spots then copying each tree to eachother.
 * @param Another HashTable to copy from.
 * @return The copied Table.
 * 
 * @pre There should two initialized tables.
 * @post There will be two identical tables.
 */
template <typename DataType, typename KeyType>
HashTable<DataType, KeyType>& HashTable<DataType, KeyType>:: operator=(const HashTable& other)
	{
		/// if the same return
		if (this = &other)
			return *this;

		/// clear 
		clear();

		/// copy the size and create new table
		tableSize = other.tableSize;
		dataTable = new BSTree<DataType, KeyType>[tableSize];

		/// go through tables and copy the trees
		for (int i = 0; i < tableSize; ++i)
		{
			dataTable[i] = other.dataTable[i];
		}

		return *this;
	}

/**
 * This is the destructor. 
 * @details This simply calls clear to deallocate all memory in each tree. Then deletes the table. 
 * @param None.
 * @return None.
 * 
 * @pre There should an initialized table.
 * @post All memory will be deallocated.
 */
template <typename DataType, typename KeyType>
HashTable<DataType, KeyType>::~HashTable()
	{
		clear();
		delete[] dataTable;
	}

/**
 * This is insert function. 
 * @details finds the index the item should go into then calls the BST insert function to insert it.
 * @param the new dataitem.
 * @return void.
 * 
 * @pre There should an initialized table.
 * @post There will be a new item inside.
 */
template <typename DataType, typename KeyType>
void HashTable<DataType, KeyType>::insert(const DataType& newDataItem)
	{
		/// get hash
		int location = newDataItem.hash(newDataItem.getKey()) % tableSize;

		/// insert into tree
		dataTable[location].insert(newDataItem);
	}

/**
 * This is the remove function. 
 * @details finds the index the item should go into then calls the BST remove function to remove it.
 * @param the key to delete
 * @return true if found and deleted, false if not.
 * 
 * @pre There should an initialized table.
 * @post An item will be removed.
 */
template <typename DataType, typename KeyType>
bool HashTable<DataType, KeyType>:: remove(const KeyType& deleteKey)
	{
		/// get its location in the array
		int location = DataType::hash(deleteKey) % tableSize;

		/// check to delete it
		return dataTable[location].remove(deleteKey);
	}

/**
 * This is the retrieve. 
 * @details Will check where the key should be then checks if the given is there. If it is then will return it by reference the type it belongs to
 * in the parameter.  
 * @param The key to delete, the thing to save to (datatype).
 * @return True if found. False if not found.
 * 
 * @pre There should be a table.
 * @post Nothing changes.
 */
template <typename DataType, typename KeyType>
bool HashTable<DataType, KeyType>:: retrieve(const KeyType& searchKey, DataType& returnItem) const
	{
		/// find location in the array
		int location = DataType::hash(searchKey) % tableSize;
		
		/// check if the item is there
		return dataTable[location].retrieve(searchKey, returnItem);
	}
 
/**
 * This is the clear function. 
 * @details Will iterate throught the table and calls the BST clear for each tree.
 * @param None.
 * @return Void.
 * 
 * @pre There should be a table.
 * @post There will be an empty tree.
 */   
template <typename DataType, typename KeyType>    
void HashTable<DataType, KeyType>:: clear()
	{
		/// iterate through the complete hash table
		for (int i = 0; i < tableSize; ++i)
		{
			dataTable[i].clear();
		}
	}

/**
 * Not Used
 */
template <typename DataType, typename KeyType>
bool HashTable<DataType, KeyType>:: isEmpty() const
	{
		bool flag = true;

		for (int i = 0; i < tableSize; ++i)
		{
			/// check to see if each tree insdie the table is empty
			flag = dataTable[i].isEmpty();
			/// if flag is ever turned into false, then return false
			if (flag == false)
				return false;
		}

		return true;
	}

template <typename DataType, typename KeyType>
double HashTable<DataType, KeyType>:: standardDeviation() const
	{

	}

/**
 * This copies two tables. 
 * @details Calls equal operator.
 * @return Void.
 * 
 * @pre There should an initialized tree to copy from.
 * @post There will be two identical trees.
 */
template <typename DataType, typename KeyType>
void HashTable<DataType, KeyType>:: copyTable(const HashTable& source) 
	{
		*this = source;
	}