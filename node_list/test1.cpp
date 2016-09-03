// Include Files
#include <iostream>
#include <cstdlib>
#include "ListLinked.cpp"

using namespace std;

// Global Constants

// Structs

// Function Prototypes

// Main
int main ()
{
  List <int> list1(10);
  list1.insert(5);
  list1.insert(4);
  list1.insert(3);
  list1.insert(2);
  list1.insert(1);

  List <int> list2 = list1;

  list2.showStructure();

  cout << "Hi" << endl << endl;
  return 0;
}

// Function Implementation