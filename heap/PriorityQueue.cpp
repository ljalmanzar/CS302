#include "PriorityQueue.h"

using namespace std;
/**
 * Default constructor for the priority queue
 * @details Just calls the heap constructor to initialize a heap.
 * @param Size of the heap.
 * @return Constructor.
 * 
 * @pre None.
 * @post Initialized.
 */
template <typename DataType, typename KeyType, typename Comparator>
PriorityQueue < DataType,  KeyType,  Comparator>::PriorityQueue(int maxNumber):Heap<DataType,KeyType,Comparator>::Heap(maxNumber)
{

}

/**
 * Enqueue
 * @details Using the heap insert, enqueues item into the priority queue.
 * @param The thing to add to the queue.
 * @return Void.
 * 
 * @pre Initialized tree.
 * @post New item will be in the queue.
 */
template <typename DataType, typename KeyType, typename Comparator>
void PriorityQueue < DataType,  KeyType,  Comparator>::enqueue(const DataType &newDataItem)
{
	Heap< DataType,  KeyType,  Comparator>::insert(newDataItem);
}

/**
 * Dequeue
 * @details Just calls the heap remove to remove the highest priority item.
 * @param None.
 * @return The item of highest priority.
 * 
 * @pre None.
 * @post Initialized.
 */
template <typename DataType, typename KeyType, typename Comparator>
DataType PriorityQueue < DataType,  KeyType,  Comparator>::dequeue()
{
	return Heap< DataType,  KeyType,  Comparator>::remove();
}
