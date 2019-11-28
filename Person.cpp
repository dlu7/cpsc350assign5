#include <iostream>
#include "Person.h"
using namespace std;

Person::Person()
{
	//empty
}

Person::~Person()
{
	//empty
}

void Person::setID(int i)
{
	ID = i;
}

int Person::getID()
{
	return ID;
}

string Person::getName()
{
	return name;
}

string Person::getLevel()
{
	return level;
}