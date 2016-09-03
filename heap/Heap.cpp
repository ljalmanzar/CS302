/** @file Heap Implementation
@author Luis Almanzar
@version 1.0
@brief Implementation for a heap.
@details 
@date Wednesday, November 5th
*/
#include "Heap.h"
#include "show11.cpp"

/**
 * Default constructor for the heap
 * @details allocates the memory for the heap of the appropriate size. saves the max size and initializes size to 0.
 * @param None.
 * @return Constructor.
 * 
 * @pre None.
 * @post Initialized.
 */
template < typename DataType, typename KeyType, typename Comparator >
Heap<DataType, KeyType, Comparator>::Heap( int maxNumber )
	{
		/// allocate the new memory
		dataItems = new DataType [maxNumber];
		/// save max size
		maxSize = maxNumber;
		/// set actual size right now
		size = 0;
	}

/**
 * Copy constructor for the heap
 * @details Copies max size from the source and allocates memory for that size. Then copies sets the two heaps equal
 * to eachother.
 * @param A heap to copy from.
 * @return Constructor.
 * 
 * @pre Heaps created.
 * @post Two equivalent heaps.
 */
template < typename DataType, typename KeyType, typename Comparator >
Heap<DataType, KeyType, Comparator>::Heap( const Heap<DataType, KeyType, Comparator>& other )
	{
		/// copy size
		maxSize = other.maxSize; 
		/// allocate the memory
		dataItems = new DataType [maxSize];
		
		/// copy
		*this = other;
	}

/**
 * Overloaded assigment operator.
 * @details Checks if the heaps are the same. If they are returns it. Then sees if the sizes are the same. If they
 * aren't, copies them then deletes current memory allocated then allocates new memory. Lastly copies items from the source
 * array to the home array. Copies size and returns.
 * @param Heap to copy from.
 * @return Copied heap.
 * 
 * @pre Two heaps.
 * @post Heaps will be equal.
 */
template < typename DataType, typename KeyType, typename Comparator >
Heap<DataType, KeyType, Comparator>& Heap<DataType, KeyType, Comparator>::operator=( const Heap<DataType, KeyType, Comparator>& other )
	{
		/// check equality
		if (this == &other)
			return *this;

		/// make same size array
		if (maxSize != other.maxSize)
			{
				delete [] dataItems;
				maxSize = other.maxSize; 
				dataItems = new DataType [maxSize];
			}

		/// copy items
		for (int i = 0; i < other.size; ++i)
			{
				dataItems[i] = other.dataItems[i];
			}

		/// copy size
		size = other.size;

		/// return
		return *this;
	}

/**
 * Destructor
 * @details Deallocates the memory or array.
 * @param None.
 * @return Destructor.
 * 
 * @pre Array initialized.
 * @post Memory released.
 */
template < typename DataType, typename KeyType, typename Comparator >
Heap<DataType, KeyType, Comparator>::~Heap()
	{
		/// delete
		delete [] dataItems;
	}

/**
 * Inserts new item.
 * @details inserts newest item to end of the array then checks the parent to see if it is bigger. if it is, they get
 * swapped and then that repeats until the parent is not smaller. 
 * @param item to insert.
 * @return void.
 * @exception if it is full throw error

 * @pre Heap initialized.
 * @post New item inserted.
 */
template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType, KeyType, Comparator>::insert( const DataType &newDataItem ) throw ( logic_error )
	{
		/// check if full
		if (isFull())
			{	
				throw logic_error("Heap is full");
				//cout << "Heap is full" << endl;
				//return;
			}
		else
			{
				/// insert
				dataItems[size] = newDataItem;
				size++;

				/// work through its parents to see if it is a max heap
				/// set indecies 
				int ci = size - 1;
				int pi = parentof(size-1);
				bool flag = true;

				while (flag)
					{
						flag = false;

						/// check if inserted if larger than parent
						if (comparator((dataItems[ci]).getPriority(), (dataItems[pi].getPriority())))
							{
								swap(ci,pi);
								ci = pi;
								pi = parentof(ci);
								flag = true; 
							}	
					}
			}
	}

/**
 * Removes highest priority item.
 * @details saves highest item in a temp and inserts last item into the first item. then compares the item to it's 
 * children, gets the larger of the children then swaps if the parent is smaller. this repeats until the end of the heap is reached.  
 * @param none.
 * @return void.
 * @exception if it is empty throw error

 * @pre Heap initialized.
 * @post front item removed.
 */
template < typename DataType, typename KeyType, typename Comparator >
DataType Heap<DataType, KeyType, Comparator>::remove() throw ( logic_error )
	{
		/// if empty throw error
		if (isEmpty())
			throw logic_error("Heap is empty");

		/// save top item
		DataType out;
		out = dataItems[0];

		DataType temp;
		int index = 0;
		int i = 0;

		/// put last item to the front
		dataItems[index] = dataItems[size-1];

		/// compare the two children
		while( i < size )
			{
			/// if left is bigger swap
			if( comparator( dataItems[leftchild(index)].getPriority(), dataItems[rightchild(index)].getPriority() ) )
				{
					if(leftchild(index) < size)
					{
						/// swaps
						temp = dataItems[index];
						dataItems[index] = dataItems[leftchild(index)];
						dataItems[leftchild(index)] = temp;
					}

					///update index to where we moved
					index = leftchild(index);
				}

			else
				{
					if(rightchild(index) < size)
						{	
							temp = dataItems[index];		
							dataItems[index] = dataItems[rightchild(index)];
							dataItems[rightchild(index)] = temp;
						}

					index = rightchild(index);
				}

			i = index;
		}

		/// update size
		size --;

		/// return removed item
		return out;
	}

/**
 * Clears the heap.
 * @details Makes size 0. 
 * @param none.
 * @return void.
 * @pre Heap initialized.
 * @post Empty heap.
 */
template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType, KeyType, Comparator>::clear()
	{
		size = 0;
	}

/**
 * Is Empty.
 * @details If the size if 0 then it is empty.  
 * @param none.
 * @return True if empty. False if not.

 * @pre Heap initialized.
 * @post Nothing different.
 */
template < typename DataType, typename KeyType, typename Comparator >
bool Heap<DataType, KeyType, Comparator>::isEmpty() const
	{
		//return if empty
		return (size == 0);
	}

/**
 * Is Full.
 * @details If size is equal to the max size of the heap, then the heap is full.  
 * @param none.
 * @return True if full. False if not.
 * @pre Heap initialized.
 * @post Nothing different.
 */
template < typename DataType, typename KeyType, typename Comparator >
bool Heap<DataType, KeyType, Comparator>::isFull() const
	{
		//return the equality
		return (size == maxSize);
	}

/**
 * Prints heap by level.
 * @details Prints out 2^n number of items, n being the number of the row (starting at zero), then inserts endl.
 * This will repeat in a loop, every loop will print out a row.
 * @param none.
 * @return void.

 * @pre Heap initialized.
 * @post Nothing changes.
 */
template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType, KeyType, Comparator>::writeLevels() const
	{
		/// check if empty
		if (isEmpty())
			{
				cout << "Empty heap" << endl;
				return;	
			}

		int n = 0;
		int i = 0;

		while (i < size)
		{
			/// for row N, print out all items
			for (int j = 0; j < pow(2,n); j++)
			{
				if (i < size)
				{
					cout << dataItems[i].getPriority() << " ";
					i++;
				}
			}

			/// end the line
			cout << endl;

			/// go to next row
			n++;
		}
	}

/**
 * @details the left child is known to be store at the equation in the function.
 * @param The index of which you want the left child.
 * @return The index of the left child of the param.
 */
template < typename DataType, typename KeyType, typename Comparator >
inline int Heap<DataType, KeyType, Comparator>::leftchild( int i )
	{
		return (2*i) + 1;
	}

/**
 * @details the right child is known to be store at the equation in the function.
 * @param The index of which you want the right child.
 * @return The index of the right child of the param.
 */
template < typename DataType, typename KeyType, typename Comparator >
inline int Heap<DataType, KeyType, Comparator>::rightchild( int i )
	{
		return (2*i) + 2;
	}

/**
 * @details the parent is known to be store at the equation in the function.
 * @param The index of which you want the parent.
 * @return The index of the parent of the child in the param.
 */
template < typename DataType, typename KeyType, typename Comparator >
inline int Heap<DataType, KeyType, Comparator>::parentof( int i )
	{
		return (i-1) / 2;
	}

/**
 * @details Simple swap of the items at the given indicies.
 * @param The indicies you want swapped.
 * @return Void.
 */
template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType, KeyType, Comparator>::swap( int i, int n )
	{
		DataType temp;
		temp = dataItems[i];
		dataItems[i] = dataItems[n];
		dataItems[n] = temp;
	}
