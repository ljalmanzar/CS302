/**
@file pumpkin.cpp
@author Luis Almanzar
@version 1
@brief Takes "gardens" in and finds the pumpkin patches.
@details Takes multiple gardens up to size 40x40 and while determain the size of
the pumpkin patches inside and how many there are.
@date Due 9/17/14
*/

// Include Files
#include <iostream>
#include <cstdlib>
using namespace std;

// Global Constants
const int MAX_ROW = 41;
const int MAX_COL = 41;

// Structs

// Function Prototypes
char getInput();
bool findPatch(char arr[][MAX_COL], int &row, int &col);
int patchSize (char arr[][MAX_COL], int rowNdx, int colNdx);
void sort (int arr[], int size);

// Main
int main ()
{
  int inputRows = 1;
  int inputColumns = 1;
  int ndxOne, ndxTwo;
  int ndxGarden = 0;
  int ndx = 1;
  int numArr[MAX_ROW][MAX_COL];

  while (inputRows != 0)
    {
      // get the dimensions of the garden, the rows and columns (0-40)
      cin >> inputRows >> inputColumns;

      // get inputs
      if (inputColumns != 0 && inputRows != 0)
        {
          char patch[MAX_ROW][MAX_COL];
          for (ndxOne = 0; ndxOne<inputRows+2; ndxOne++)
            {
              for (ndxOne = 0; ndxOne<inputRows+2; ndxOne++)
                {
                  for (ndxTwo = 0; ndxTwo < inputColumns+2; ndxTwo++)
                    {
                      if (ndxOne == 0 || ndxTwo == 0 || ndxOne == inputRows+1 || ndxTwo == inputColumns+1)
                        {
                          patch[ndxOne][ndxTwo] = 'x'; 
                        }
                      else
                        {
                          patch[ndxOne][ndxTwo] = getInput();
                        }
                    }
              
                } 

            } 
        

      // find patches
      int ROW, COL, size, numberOfPatches = 0;
      bool fPatch = true;
      ndx = 1;

      while (fPatch == true)
        {
          ROW = inputRows+2;
          COL = inputColumns+2;
          fPatch = findPatch(patch, ROW, COL);

          // check patch size
          if (fPatch == true)
            {
              numberOfPatches++;
              size = patchSize(patch, ROW, COL);
              numArr[ndxGarden][ndx] = size;
              ndx++;
            } 
        }
        numArr[ndxGarden][0] = numberOfPatches;
        ndxGarden++;
      }
    }

  // sort and display
      for ( ndx = 0; ndx < ndxGarden; ndx++ ) 
        {
          cout << "Garden # " << ndx + 1 <<": " << numArr[ndx][0] << " patches, sizes: "; 
          int temp = numArr[ndx][0]; 
          int tempArr[temp];   
          int colNdx; 
          for ( colNdx = 0; colNdx < temp; colNdx++ ) 
              {
              tempArr[colNdx] = numArr[ndx][colNdx+1];   

              }
          sort (tempArr, temp);  

          for ( colNdx = 0; colNdx < temp; colNdx++ )  
              {
              cout << tempArr[colNdx] << " "; 
              }

          cout << endl; 
       }
  return 0;
}

// Function Implementation
/**
 * This function will return the input of the user for the garden
 * 
 * @param none
 * @return the char (fruit) 
 * 
 * @pre nothing
 * @post there will be one more fruit in the garden 
 */
char getInput()
  {
    char fruit;
    cin >> fruit;
    return fruit;
  }


/**
 * this function will cycle through the garden array and find a pumpkin. 
 * 
 * will also change the row and col parameters to the indicies it found the p
 * 
 * @param the char arr(garden), the row and col index to be able to return it's
 coordinates
 * @return true if it finds a pumpkin, false if it finds nothing
 * 
 * @pre nothing
 * @post a patch will be found of the garden will be determined as empty  
 */
bool findPatch(char arr[][MAX_COL], int &row, int &col)
  {
    int rowNdx = 0;
    int colNdx = 0;

    while (arr[rowNdx][colNdx] != 'p' && rowNdx < row)
      {
        colNdx = 0;
        while (arr[rowNdx][colNdx] != 'p' && colNdx < col)
          {
            colNdx++;
          } 
        if (arr[rowNdx][colNdx] != 'p')
          {
            rowNdx++; 
          }
      }

    if (arr[rowNdx][colNdx] != 'p')
      {
       return false;
      }

    row = rowNdx;
    col = colNdx;
    return true;
  }

/**
 * will determine how large a found patch extends
 * 
 * @param the char arr(garden), coordinates of the found patch
 * @return the final return will be the size of the patch
 * 
 * @pre there must be a garden already and a patch must be found
 * @post the patch will have its size  
 */
int patchSize (char arr[][MAX_COL], int rowNdx, int colNdx)
  {
    int ndx = 0;

    if (arr[rowNdx][colNdx] == 'p')
      {
        ndx++;

        arr[rowNdx][colNdx] = 'X';

        ndx += patchSize(arr, rowNdx + 1, colNdx);
        ndx += patchSize(arr, rowNdx, colNdx + 1);
        ndx += patchSize(arr, rowNdx - 1, colNdx);
        ndx += patchSize(arr, rowNdx, colNdx - 1);

        return ndx;
      }

    return 0;
  }

/**
 * This function just sorts 
 * 
 * @param an array of integers and the size of the array
 * @return This function is a void. 
 * 
 * @pre The array will be unsorted
 * @post The array will be sorted  
 * 
 */
void sort (int arr[], int size)
  {
    int ndx = 0;
    bool ordered = true;

    while (ordered == true)
      { 
        ordered = false;
        for (ndx = 0; ndx < size - 1; ndx++)
          {
            if (arr[ndx] > arr[ndx+1])
              {
                int temp = arr[ndx];
                arr[ndx] = arr[ndx+1];
                arr[ndx+1] = temp;
                ordered = true; 
              }
          } 
      }
  }