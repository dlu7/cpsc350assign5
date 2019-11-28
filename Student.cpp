#include <iostream>
#include <string>
#include "Student.h"
using namespace std;

Student::Student()
{

}

Student::Student(int i, string n, string l, string m, double g, int a)
{
	ID = i;
	name = n;
	level = l;
	major = m;
	gpa = g;
	advisorID = a;
}

Student::~Student()
{

}

void Student::setAdvisorID(int adv)
{
	advisorID = adv;
}

int Student::getAdvisorID()
{
	return advisorID;
}

void Student::printStudent()
{
	cout << "Student ID: " << ID << endl;
	cout << "Student Name: " << name << endl;
	cout << "Grade Level: " << level << endl;
	cout << "Major: " << major << endl;
	cout << "GPA: " << gpa << endl;
	cout << "Advisor ID: " << advisorID << endl;
}

double Student::getGPA()
{
	return gpa;
}

string Student::getMajor()
{
	return major;
}