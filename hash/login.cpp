#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <string>
#include "HashTable.cpp"

using namespace std;

/// the struct for the login and password
struct Account
{
	/// variables
	string login;
	string password;

	/// hash function
	static unsigned int hash(const string& str) 
		{
		    unsigned int val = 0;
		    for (int i = 0; i < str.length(); ++i) {
			val += str[i];
		    }
		    return val;
		}

	/// get key function
	string getKey() const 
		{
			return login;
		}
};

int main()
{
	string loginI;
	string passwordI;
	string temp;

	/// open file
	ifstream fin ("password.dat");
	fin.clear();

	/// make new account to read into
	Account acct;

	/// make the hash table
	HashTable<Account,string> data (8);

	/// read in
	while (fin.good())
		{
			fin >> acct.login >> acct.password;
			//cout << acct.login << " " << acct.password << endl;
			data.insert(acct);
			//data.showStructure();
		}

	data.showStructure();

	/// read in
	cout << "Login: ";
	cin >> loginI;

	do 
	{
		cout << "Password: ";
		cin >> passwordI;

		/// check for login
		if (data.retrieve(loginI, acct))
			{
				/// check if passwords are the same
				if ((acct.password == passwordI))
					{	
						/// same password, print success
						cout << "Authentication successful" << endl;
					}
				else
					{
						/// different password, print failure
						cout << "Authentication failure" << endl;
					}
			}
		else
			{
				/// if the data login is not saved print failure
				cout << "Authentication failure" << endl;
			}	

		cout << "Login: ";
		cin >> loginI;
	}
	while(!cin.eof());

	return 0;
}