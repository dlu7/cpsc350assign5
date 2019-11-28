#include <iostream>
#include <string>
#include "Faculty.h"
using namespace std;

Faculty::Faculty()
{

}

Faculty::Faculty(int i, string n, string l, string d)
{
	ID = i;
	name = n;
	level = l;
	dept = d;

	adviseeArray = new int[5];
	advisee = 0;
	arrayMaxSize = 5;

	for (int i = 0; i < 5; i++)
	{
		adviseeArray[i] = -1;
	}
}

Faculty::~Faculty()
{
	delete[] adviseeArray;
}

void Faculty::printFaculty()
{
	cout << "Faculty ID: " << ID << endl;
	cout << "Faculty Name: " << name << endl;
	cout << "Education Level: " << level << endl;
	cout << "Department: " << dept << endl;
	cout << "Advisee ID #s: ";
	printAdvisees();
	cout << endl;
}

void Faculty::printAdvisees()
{
	if (advisee == 0)
	{
		cout << "There are no advisees.";
	}
	else
	{
		for (int i = 0; i < arrayMaxSize; i++)
		{
			if (adviseeArray[i] != -1)
			{
				cout << adviseeArray[i];
				if (i < advisee - 1)
				{
					cout << ", ";
				}
			}
		}
	}

	cout << endl;
}

int Faculty::getAdvisee()
{
	return advisee;
}

string Faculty::getDept()
{
	return dept;
}

void Faculty::addAdvisee(int adv)
{
	if (advisee != arrayMaxSize)
	{
		int temp = 0;

		for (int i = 0; i < arrayMaxSize; i++)
		{
			if (adviseeArray[i] == ID)
			{
				temp = arrayMaxSize;
			}
		}

		while (temp < arrayMaxSize)
		{
			if (adviseeArray[temp] == -1)
			{
				adviseeArray[temp] = ID;
				advisee++;
				break;
			}
			temp++;
		}
	}
	else
	{
		if (advisee == arrayMaxSize)
		{
			int *tempArray = new int[advisee];

			for (int i = 0; i < advisee; i++)
			{
				tempArray[i] = adviseeArray[i];
			}

			adviseeArray = new int[advisee + 1];
			arrayMaxSize = advisee + 1;

			for (int i = 0; i < advisee; i++)
			{
				adviseeArray[i] = tempArray[i];
			}

			for (int i = advisee; i < advisee + 1; i++)
			{
				adviseeArray[i] = -1;
			}

			adviseeArray[advisee++] = ID;
		}
	}
}

bool Faculty::removeAdvisee(int advID)
{
	bool remove = false;

	for (int i = 0; i < arrayMaxSize; i++)
	{
		if (adviseeArray[i] == advID)
		{
			adviseeArray[i] = -1;
			advisee--;
			remove = true;
		}

		if (!remove)
		{
			cout << "Advisee has been successfully removed." << endl;
		}

		return remove;
	}
}

int Faculty::getArraySize()
{
	return arrayMaxSize;
}