/**

*/
#ifndef __WEIGHTEDGRAPH_CPP_
#define __WEIGHTEDGRAPH_CPP_
#include "WeightedGraph.h"
#include "show12.cpp"
 
/**@brief Default Constructor, This will set the max number given by user
	or use the default of 10. Then allocates all memory needed for the arrays.
 
    @post Everything will be initialized.
    @param The maxnumber of the graph. Will be default 10.
    @return Constructor.
*/
WeightedGraph::WeightedGraph( int maxNumber )
    {
    	///set max and initialize size
        maxSize = maxNumber;
        size = 0;

        ///allocate memory for graph
        vertexList = new Vertex [maxSize];
        adjMatrix = new int [maxSize*maxSize];
        pathMatrix = new int [maxSize*maxSize];

        ///initialize "matrix"
        for (int i = 0; i < maxSize*maxSize; ++i)
            {
                //assign infinity to all parameters
                adjMatrix[i] = INFINITE_EDGE_WT;
            }
    }
 
 
/**@brief Copy Constructor - Creates a new graph with the exact contents of the one in 
	the parameter.
    @pre Nothing
    @post Exact copy of other graph.
    @param Graph to copy from. 
    @return constructor.
*/
WeightedGraph::WeightedGraph( const WeightedGraph& other )
    {
        ///copy sizes
        maxSize = other.maxSize;
        size = other.size;

        /// iterate through both arrays and copy after allocating memory
        adjMatrix = new int [maxSize*maxSize];
        for(int i = 0; i < maxSize*maxSize; ++i)
            {
                adjMatrix[i] = other.adjMatrix[i];
            }

        vertexList = new Vertex [maxSize];
        for(int i = 0; i < maxSize; ++i)
        	{   
                vertexList[i] = other.vertexList[i];
            }

        pathMatrix = new int [maxSize*maxSize];
        for(int i = 0; i < maxSize*maxSize; ++i)
            {   
                pathMatrix[i] = other.pathMatrix[i];
            }
    }
 
/**@brief Overloaded operator
    @pre An initialized graph to copy from.
    @post Two equal graphs.
    @param Graph to copy from.
    @return The copy graph.
*/
WeightedGraph& WeightedGraph::operator=( const WeightedGraph& other )
    {
        ///if same return
        if(this == &other)
            return * this;
 
        ///deallocate memory
        delete [] adjMatrix;
        adjMatrix = NULL;

        delete [] vertexList;
        vertexList = NULL;
 
        ///copy sizes
        maxSize = other.maxSize;
        size = other.size;
 
        /// allocate new memory of correct size and copy from otehr
        adjMatrix = new int [maxSize*maxSize];
        for(int i = 0; i < maxSize*maxSize; ++i)
            {
                adjMatrix[i] = other.adjMatrix[i];
            }
 
        
        vertexList = new Vertex [maxSize];
        for(int i = 0; i < maxSize; ++i)
            {   
                vertexList[i] = other.vertexList[i];
            }

        pathMatrix = new int [maxSize*maxSize];
        for(int i = 0; i < maxSize*maxSize; ++i)
            {   
                pathMatrix[i] = other.pathMatrix[i];
            }
 
        return * this;
    }
 
/**@brief Destructor, deallocates all memory
    @pre initialized graph
    @post all memory will be deallocated
    @param none
    @return destructor
*/
WeightedGraph::~WeightedGraph()
    {
        ///deallocate
        delete [] adjMatrix;
        delete [] vertexList;
        delete [] pathMatrix;
    }
 
/**@brief Inserts a new vertex into the list
    @pre Initialized list.
    @post New item in the list.
    @param The new vertex to insert into the list.
    @excep If the list is full cant add more.
    @return void.
*/
void WeightedGraph::insertVertex( const Vertex& newVertex ) throw ( logic_error )
    {
        ///check for full
        if(isFull())
            {
                throw logic_error("insertVertex() while WeightedGraph isFull()");
                return;
            }
 
        ///insert new vertex into list
        vertexList[size] = newVertex;
 
        //increment size
        size++;
    }
 
/**@brief Inserts new edge between two given verticies. Will find where to insert then insert
	in that spot in the matrix. If there is already an edge, it updates it.
    @pre initialized matrix
    @post edge will be added in both correcsponding parts of the matrix. 
    @param Two strings which identify what the edges connect and an int for the edge's weight.
    @excep If one of the strings do not exist, if the strings are the same.
    @return void
*/
void WeightedGraph::insertEdge( const string& v1, const string& v2, int wt ) throw ( logic_error )
    {
        /// find where to insert edge
        int ndx1 = getIndex( v1 );
        int ndx2 = getIndex( v2 );
 
 		/// check for errors, 1) doesnt exist 2) same place
        if( (ndx1 == -1) || (ndx2 == -1) )
            {
                throw logic_error("insertEdge() while vertex doesn't exist");
                return;
            }

        if( ndx1 == ndx2 )
            {
                throw logic_error("insertEdge() on the same vertex");
                return;
            }

        /// print
        cout << "Size = " << size << ", " << "idx_v1 = " << ndx1 << ", ";
        cout << "idx_v2 = " << ndx2 << endl;
 
        ///update adjMatrix
        setEdge( ndx1, ndx2, wt );
        setEdge( ndx2, ndx1, wt );
    }
 
/**@brief Looks for an input given by the user. If found saves the vertex in the parameter.
    @pre Initialized vertex list.
    @post Same
    @param What to look for (string) and where to save if it is found (vertex)
    @excep If if isnt found.
    @return True if found, false if not.
*/
bool WeightedGraph::retrieveVertex( const string& v, Vertex& vData ) const
    {
        ///get index of string
        int ndx = getIndex( v );
 
        ///if the index is not found, return false
        if( ndx == -1 )
            return false;
 
        ///set other parameter to corresponding vertex and return
        vData = vertexList[ndx];
        return true;
    }
 
/**@brief Finds the weight between two verticies then returns their weight by updating the
	parameter. Gets the two indicies and then gets their edge.
    @pre Initialized.
    @post Nothing changes.
    @param The two strings to search for a edge for and where to save the weight.
    @excep If the indicies dont exist, if the indicies are the same, or the edge is not existant
    @return true if found and false if not
*/
bool WeightedGraph::getEdgeWeight( const string& v1, const string& v2, int& wt ) const throw ( logic_error )
    {
        ///check for empty
        if( isEmpty() )
            {
                throw logic_error("getEdgeWeight() while Graph isEmpty()");
                return false;
            }

        ///get indicies for boh strings
        int ndx1 = getIndex( v1 );
        int ndx2 = getIndex( v2 );
 
        ///check if valid verticies
        if( (ndx1 == -1) || (ndx2 == -1) )
            {
                throw logic_error("getEdgeWeight() while edge doesn't exist");
                return false;
            }

        if( ndx1 == ndx2 )
            {
                throw logic_error("getEdge() on the same vertex");
                return false;
            }

        if (getEdge(ndx1,ndx2) == INFINITE_EDGE_WT)
        	{
        		//throw logic_error("getEdgeWeight() while edge doesn't exist");
                return false;	
        	}
        wt = getEdge( ndx1,ndx2 );
        return true;
    }
 
/**@brief Removes a vertex by furst deleting the whole correcsponding row and moving
	everything up. the does virtually the same with the colums.
    @pre initialized graph
    @post given vertex will be removed
    @param the vertex identifer to delete
    @excep if the graph is empty
    @return void
*/
void WeightedGraph::removeVertex( const string& v ) throw ( logic_error )
    {
    	 ///check for empty
        if( isEmpty() )
            {
                throw logic_error("removeVertex() while isEmpty()");
                return;
            }
 
        ///get index
        int ndx = getIndex( v );
 
        ///remove from list
        for(int i = ndx; i < size-1; ++i)
            {
                vertexList[i] = vertexList[i+1];
            }

        vertexList[size-1].setLabel("");
        vertexList[size-1].setColor(0);

        /// move up rows
        for(int i = 0; i < size; ++i)
            {
                for(int j = ndx; j < size; ++j)
                    {
                        adjMatrix[(i*maxSize) + j] = adjMatrix[(i*maxSize) + j+1];
                    }
            }

        ///move columns left
        for(int i = ndx; i < size; ++i)
            {
                for(int j = 0; j < size; j++)
                    {
                        adjMatrix[(i*maxSize) + j] = adjMatrix[((i+1)*maxSize) + j];
                    }
            }

        ///initialize left over spots to infinite edge wt
        for (int i = 0; i < maxSize; ++i)
            {
                for (int j = 0; j < maxSize; ++j)
                    {
                        if( (i == maxSize-1) || (j == maxSize-1) )
                            {
                                adjMatrix[i*maxSize + j] = INFINITE_EDGE_WT;
                            }
                    }
            }
 
        size--;
    }
 
/**@brief This will just go to the associated edges from the parameters and set them to
	their initialized values.
    @pre Edge with value
    @post Edge will be "empty"
    @param the two verticies to look for
    @excep if the verticies are not valid 
    @return void
*/
void WeightedGraph::removeEdge( const string& v1, const string& v2 ) throw ( logic_error )
    {
        ///find locations
        int ndx1 = getIndex( v1 );
        int ndx2 = getIndex( v2 );
 
        ///check for valid edges
        if( (ndx1 == -1) || (ndx2 == -1) )
            {
                throw logic_error("removeEdge() while edge doesn't exist");
                return;
            }

        if( ndx1 == ndx2 )
            {
                throw logic_error("removeEdge() on the same vertex");
                return;
            }
 
        ///replace current weight with infinite
        setEdge( ndx1, ndx2, INFINITE_EDGE_WT );
        setEdge( ndx2, ndx1, INFINITE_EDGE_WT );
    }
 
/**@brief Common Sense
*/
void WeightedGraph::clear()
    {
        ///overwrite "matrix"
        for(int i = 0; i < maxSize*maxSize; ++i)
            {
                adjMatrix[i] = INFINITE_EDGE_WT;
            }

        ///clear all values
        for(int i = 0; i < size; ++i)
            {
                //assign null values to vertices
                vertexList[i].setLabel("");
                vertexList[i].setColor(0);
            }

        ///reset size
        size = 0;
    }

/**@brief Checks if empty...
*/
bool WeightedGraph::isEmpty() const
    {
        //return depending on size
        if(size == 0)
            return true;
        else
        	return false;
    }
 
/**@brief Checks if full...
*/
bool WeightedGraph::isFull() const
    {
        //return depending on size
        if(size == maxSize)
            return true;
        else
        	return false;
    }
 
/**@brief Finds the shortest paths from every possible connection. I do not understand
	100% how the algorithm works. I just took what was in the book and put it into code.
    @pre Initialized.
    @post A Path matrix will be created and printed. 
    @param None
    @excep None
    @return Void.
*/
void WeightedGraph::showShortestPaths() //const
    {
    	int wt;

        /// copy edge matrix
        for (int i = 0; i < maxSize*maxSize; ++i)
	        {
	        	pathMatrix[i] = adjMatrix[i];
	        	//cout << pathMatrix[i] << " ";
	        }

	    /// FLOYD
	    for (int i = 0; i < size; ++i)
	    {
	    	for (int j = 0; j < size; ++j)
	    	{
	    		for (int k = 0; k < size; ++k)
	    		{
	    			if ( getPath(j,i) != INFINITE_EDGE_WT && getPath(i,k) != INFINITE_EDGE_WT)
	    				{
	    					if (getPath(j,i) + getPath(i,k) < getPath(j,k) || getPath(j,k) == INFINITE_EDGE_WT)
	    						{
	    							setPath( j,k, (getPath(j,i) + getPath(i,k)) );
	    						}	
	    				}
	    		}
	    	}
	    }

	    /// print the matrix
	    cout << endl << "Path matrix: " << endl << '\t';
	    for (int i = 0; i < size; ++i)
			{
		    	cout << i << '\t';
		    } 
		cout << endl;

		/// print actual data and - for infinite
		for (int i = 0; i < size; ++i)
			{
				cout << i << '\t';
				for (int j = 0; j < size; ++j)
					{
						wt = getPath(i,j);

						if (i!=j)
							{	
								if (wt == INFINITE_EDGE_WT)
									cout << '-' << '\t';
								else
									cout << wt << '\t';
							}
						else
							cout << "0" << '\t';
					}

				cout << endl;
			}



    }
 
/**@brief This checks that any two connected verticies dont have the same color. 
	This is done by comparing each vertex to its connections through a loop.
    @pre Initialized.
    @post Same. (Nothing changes) 
    @param None.
    @excep None.
    @return True if the coloring is ok and false if not. 
*/
bool WeightedGraph::hasProperColoring() const
    {
    	/// check if empty
    	if (isEmpty())
    		return true;

    	/// initialize color variable for comparison
    	char com;

    	/// loop through list of verticies
        for (int i = 0; i < size; ++i)
	        {
	        	/// get color of first vertex
	        	com = vertexList[i].getColor();

	        	/// set index for corresponding matricies 
	        	int ndx = i*maxSize;

	        	/// prime loop and go through corresponding edges for current vertex
	        	int j = 0;
	        	while (j < maxSize)
		        	{
		        		if (adjMatrix[ndx] != INFINITE_EDGE_WT)
		        			{	
		        				/// compare, if same colors return false
		        				if (com == vertexList[j].getColor())
		        					return false; 
		        			}

		        		j++; 
		        		ndx++;
		        	}
	        }

        return true;
    }
 
/**@brief This function checks if any given edge could be deleted and keep the graph
	completely intact. This checks if each vertex has an even number of connections.
    @pre Initialized graph.
    @post Same.
    @param None.
    @excep None.
    @return True if all verticies has even numbers of connections false otherwise.
*/
bool WeightedGraph::areAllEven() const
    {
         /// check if empty
    	if (isEmpty())
    		return true;

    	/// loop through list of verticies
        for (int i = 0; i < size; ++i)
	        {
	        	/// set index for corresponding matricies 
	        	int ndx = i*maxSize;

	        	/// make counter to check degree of vertex
	        	int degree = 0;

	        	/// prime loop and go through corresponding edges for current vertex
	        	int j = 0;
	        	while (j < maxSize)
		        	{
		        		if (adjMatrix[ndx] != INFINITE_EDGE_WT)
		        			{	
		        				/// if the edge is not infinite increment
		        				degree++;
		        			}

		        		j++; 
		        		ndx++;
		        	}

		        if ((degree % 2)!= 0)
		        	return false;
	        }

        return true;
    }

/**@brief Finds where the vertex in the parameter is in the vertex list.
    @return the index of the spot.
*/
int WeightedGraph::getIndex( const string& v ) const
    {
        ///look for item in list
        for( int i = 0; i < size; ++i )
            {
                ///if equal return index
                if(vertexList[i].getLabel() == v)
                    return i;
            }

        /// fail
        return -1;
    }
 
/**@brief Finds a spot in the Edge array with the given coordinates
    @return the index of the spot.
*/
int WeightedGraph::getEdge( int row, int col ) const
    {
        ///return length
        return adjMatrix[(row*maxSize) + col];
    }
 
/**@brief Sets a spot in the Edge array with the given info
    @return void.
*/
void WeightedGraph::setEdge( int row, int col, int wt )
    {
        /// set egdge if valid
        if(row != col)
            adjMatrix[(row * maxSize) + col] = wt;
    }

/**@brief Finds a spot in the Path array with the given coordinates
    @return the index of the spot.
*/
int  WeightedGraph::getPath ( int row, int col ) const
	{
		///return length
        return pathMatrix[(row*maxSize) + col];
	}
    
/**@brief Sets a spot in the Path array with the given info
    @return void.
*/
void WeightedGraph::setPath ( int row, int col, int wt)
	{
		/// set egdge if valid
        if(row != col)
            pathMatrix[(row * maxSize) + col] = wt;
	}

#endif