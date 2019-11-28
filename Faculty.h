#include <iostream>
#include "DoubleLinkedList.h"
#include "Person.h"
using namespace std;

class Faculty : public Person
{
public:
	string dept;

	unsigned int advisee;
	unsigned int arrayMaxSize;

	int *adviseeArray;

	Faculty();
	Faculty(int i, string n, string l, string d);
	~Faculty();

	void printFaculty();
	void printAdvisees();

	int getAdvisee();
	string getDept();

	void addAdvisee(int adv);
	bool removeAdvisee(int advID);

	int getArraySize();
};