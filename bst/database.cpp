//--------------------------------------------------------------------
//
//  Laboratory 11, In-lab Exercise 1                     database.cs
//
//  (Shell) Indexed accounts database program
//
//--------------------------------------------------------------------

// Builds a binary search tree index for the account records in the
// text file accounts.dat.

#include <iostream>
#include <fstream>
#include "BSTree.cpp"

using namespace std;

//--------------------------------------------------------------------
//
// Declarations specifying the accounts database
//

const int nameLength      = 11;   // Maximum number of characters in
                                  //   a name
const long bytesPerRecord = 37;   // Number of bytes used to store
                                  //   each record in the accounts
                                  //   database file

struct AccountRecord
{
    int acctID;                   // Account identifier
    char firstName[nameLength],   // Name of account holder
         lastName[nameLength];
    double balance;               // Account balance
};

//--------------------------------------------------------------------
//
// Declaration specifying the database index
//

struct IndexEntry
{
    int acctID;              // (Key) Account identifier
    long recNum;             // Record number

    int getKey () const
        { return acctID; }   // Return key field
};

//--------------------------------------------------------------------

int main ()
{
    ifstream acctFile ("accounts.dat");   // Accounts database file
    AccountRecord acctRec;                // Account record
    BSTree<IndexEntry,int> index;         // Database index
    IndexEntry entry;                     // Index entry
    int searchID;                         // User input account ID
    long recNum;                          // Record number

    // Iterate through the database records. For each record, read the
    // account ID and add the (account ID, record number) pair to the
    // index.

    /// Gets Size of the file and goes back to the beginning
    acctFile.seekg(0, acctFile.end);
    int size = acctFile.tellg();
    acctFile.seekg(0, acctFile.beg);

    /// For the number of lines (size/bytesperrecord) will grab all the info and save the wanted ones inside a BST
    for (int i = 0; i< size/bytesPerRecord; i++)
        {
            entry.recNum = i;
            acctFile >> entry.acctID >>  acctRec.firstName >> acctRec.lastName >> acctRec.balance;
            index.insert(entry);
        }

    /// Output the account IDs in ascending order.
    cout << endl;
    cout << "Account IDs :" << endl;
    index.writeKeys();
    cout << endl;

    /// Clear the status flags for the database file
    acctFile.clear();

    /// Read an account ID from the keyboard and output the
    cout << "Enter account ID : ";
    cin >> searchID;
    while (!cin.eof())
        {
            /// if valid ID grab, navigate to the line in the file and then grab all the info and print it
            /// if not valid, print error message
            if (index.retrieve(searchID, entry))
                {
                	cout << entry.recNum << " : ";
                    acctFile.seekg((entry.recNum)*bytesPerRecord);
                    acctFile >> entry.acctID >>  acctRec.firstName >> acctRec.lastName >> acctRec.balance;
                    cout << entry.acctID << " " <<  acctRec.firstName << " " << acctRec.lastName << " " << acctRec.balance;
                }
            else
            	cout << "No record with that account ID";

            /// get new ID
            cout << endl;
            cout << "Enter account ID (EOF to quit): "; 
            cin >> searchID;
            cout << endl;
        }   
    // corresponding record.

    return 0;
}
