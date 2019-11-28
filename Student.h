#include <iostream>
#ifndef include //this class is redefined in multiple other .cpp files so this is included to fix the redefinition error
#define include
#include "Person.h"
using namespace std;

class Student : public Person
{
public:
	double gpa;
	string major;
	int advisorID;

	Student();
	Student(int i, string n, string l, string m, double g, int a);
	~Student();

	void setAdvisorID(int adv);

	void printStudent();

	double getGPA();
	string getMajor();
	int getAdvisorID();
};

#endif