#include <iostream>
#ifndef included //this class is redefined in multiple other .cpp files so this is included to fix the redefinition error
#define included
using namespace std;

class Person
{
public:
	int ID;
	string name;
	string level;

	Person();
	~Person();

	int getID();
	void setID(int i);

	string getName();
	string getLevel();
};

#endif