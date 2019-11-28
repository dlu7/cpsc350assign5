#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <stdlib.h>
//#include "GenStack.h"
#include "Student.h"
#include "Program.h"
using namespace std;

Program::Program()
{
	//empty
}

Program::~Program()
{
	//empty
}

void Program::fileRead() 
{
	//master files for students and faculty
	ifstream MStudentFile;
	ifstream MFacultyFile;

	string input;
	int student = 0;
	int faculty = 0;
	int facultyTotal = 0;
	int studentTotal = 0;
	int line = 1;
	
	//variables for Master Student File
	int sID = 0;
	double gpa = 0;
	string sname = "";
	string slevel = "";
	string smajor = "";
	int advID = 0;

	//variables for Master Faculty File
	int fID = 0;
	string fname = "";
	string flevel = "";
	string dept = "";
	int adveID = 0;

	//opening faculty file -- throws exception if file format is incorrect
	MFacultyFile.open("facultyTable.txt");
	if (MFacultyFile.is_open())
	{
		try
		{
			getline(MFacultyFile, input);
			if (input != "")
				faculty = stoi(input);
		}
		catch (exception e)
		{
			cout << endl << "The file format is incorrect" << endl;
		}

		//file is being read and each line is read to designated variable via cases
		while (getline(MFacultyFile, input))
		{
			switch (line)
			{
			case 1:
			{
				if (input != "--")
					cout << endl << "The file format is incorrect" << endl;

				break;
			}
			case 2:
			{
				try
				{
					fID = stoi(input);
				}
				catch (exception e)
				{
					cout << endl << "The file format is incorrect" << endl;
				}
				break;
			}
			case 3:
			{
				fname = input;
				break;
			}
			case 4:
			{
				flevel = input;
				break;
			}
			case 5:
			{
				dept = input;
				break;
			}
			case 6:
			{
				try
				{
					studentTotal = stoi(input);
				}
				catch (exception e)
				{
					cout << endl << "The file format is incorrect" << endl;
				}

				Faculty *faculty = new Faculty(fID, fname, flevel, dept);
				facultyTotal++;

				for (int j = 0; j < studentTotal; ++j)
				{
					getline(MFacultyFile, input);
					try
					{
						adveID = stoi(input);
					}
					catch (exception e)
					{
						cout << endl << "The file format is incorrect" << endl;
					}
					faculty->addAdvisee(adveID);
				}

				TreeNode<Faculty> *facultyNode = new TreeNode<Faculty>(faculty, fID);
				mFaculty.insert(facultyNode);
				break;
			}
			default:
				break;
			}

			++line;
			if (facultyTotal == faculty)
				break;

			if (line > 6)
				line = 1;
		}
	}
	else
		cout << endl << "No file found. Program will automatically start with a blank master file." << endl;

	MFacultyFile.close();

// ---------------------------------------------------------------------------------------------------

	//opening student file
	MStudentFile.open("studentTable.txt");
	if (MStudentFile.is_open())
	{
		try
		{
			getline(MStudentFile, input);
			if (input != "")
			{
				student = stoi(input);
			}
		}
		catch (exception e)
		{
			cout << endl << "The file format is incorrect" << endl;
		}

		// every 7 lines, there will be a new student because there are 7 designated lines for each student's info
		for (int i = 0; i < (7 * student); i++)
		{
			getline(MStudentFile, input);
			switch (line)
			{
			case 1:
			{
				if (input != "--")
					cout << endl << "The file format is incorrect" << endl;
				break;
			}
			case 2:
			{
				try
				{
					sID = stoi(input);
				}
				catch (exception e)
				{
					cout << endl << "The file format is incorrect" << endl;
				}
				break;
			}
			case 3:
			{
				sname = input;
				break;
			}
			case 4:
			{
				slevel = input;
				break;
			}
			case 5:
			{
				smajor = input;
			}
			case 6:
			{
				try
				{
					gpa = stof(input);
				}
				catch (exception e)
				{
					cout << endl << "The file format is incorrect" << endl;
				}
				break;
			}
			case 7:
			{
				try
				{
					advID = stoi(input);

					Student *student = new Student(sID, sname, slevel, smajor, gpa, advID);
					TreeNode<Student> *studentNode = new TreeNode<Student>(student, sID);
					mStudent.insert(studentNode);
				}
				catch (exception e)
				{
					cout << endl << "The file format is incorrect" << endl;
				}
				break;
			}
			default:
				break;
			}
			++line;

			if (line > 7)
				line = 1;
		}
	}
	else
		cout << endl << "No file found. Program will automatically start with a blank master file." << endl;

	MStudentFile.close();
}

//program to write into the student and faculty files
void Program::fileWrite() 
{
	ofstream MStudentFile;
	ofstream MFacultyFile;

	//opening student file
	MStudentFile.open("studentTable.txt");

	if (MStudentFile.is_open()) 
	{
		MStudentFile << mStudent.getSize() << endl;
		TreeNode<Student> *s = mStudent.getRoot();
		outputMStudent(s, "studentTable.txt");
	}
	MStudentFile.close();

	//opening faculty file
	MFacultyFile.open("facultyTable.txt");

	if (MFacultyFile.is_open()) 
	{
		MFacultyFile << mFaculty.getSize() << endl;
		TreeNode<Faculty> *f = mFaculty.getRoot();
		outputMFaculty(f, "facultyTable.txt");
	}
	MFacultyFile.close();
}

//printing master student file by going through the tree
void Program::printMStudent(TreeNode<Student> *s) 
{
	if (s != NULL) 
	{
		if (s->left != NULL)
		{
			printMStudent(s->left);
		}
		s->data->printStudent();

		if (s->right != NULL) 
		{
			printMStudent(s->right);
		}
	}
	else
		cout << "Student database is empty!" << endl;
}

//print master faculty list by going through the tree
void Program::printMFaculty(TreeNode<Faculty> *f) 
{
	if (f != NULL) 
	{
		if (f->left != NULL) 
		{
			printMFaculty(f->left);
		}
		f->data->printFaculty();

		if (f->right != NULL) 
		{
			printMFaculty(f->right);
		}
	}
	else
		cout << "Faculty database is empty!" << endl;
}

//outputs all student info in file
void Program::outputMStudent(TreeNode<Student> *s, string s2) 
{
	ofstream outfile;
	outfile.open(s2.c_str());

	if (s != NULL)
	{
		outfile << "--" << endl;
		outfile << s->data->getID() << endl;
		outfile << s->data->getGPA() << endl;
		outfile << s->data->getName() << endl;
		outfile << s->data->getLevel() << endl;
		outfile << s->data->getMajor() << endl;
		outfile << s->data->getAdvisorID() << endl;

		if (s->left != NULL)
			outputMStudent(s->left, s2);

		if (s->right != NULL)
			outputMStudent(s->right, s2);
	}
	else
		cout << "Student database is empty!" << endl;

	outfile.close();
}

//outputs all faculty info in file
void Program::outputMFaculty(TreeNode<Faculty> *f, string f2) 
{
	ofstream outfile;
	outfile.open(f2.c_str());

	if (f != NULL) 
	{
		outfile << "--" << endl;
		outfile << f->data->getID() << endl;
		outfile << f->data->getName() << endl;
		outfile << f->data->getLevel() << endl;
		outfile << f->data->getDept() << endl;
		outfile << f->data->getAdvisee() << endl;

		if (f->data->getAdvisee() > 0) 
		{
			for (int i = 0; i < f->data->arrayMaxSize; ++i) 
			{
				if (f->data->adviseeArray[i] != -1) 
				{
					outfile << f->data->adviseeArray[i] << endl;
				}
			}
		}

		if (f->left != NULL)
			outputMFaculty(f->left, f2);

		if (f->right != NULL)
			outputMFaculty(f->right, f2);
	}
	else
		cout << "Faculty database is empty!" << endl;

	outfile.close();
}

//function prints out menu for user and user enters which option they would like
// -- they can enter however many options they want until they exit the program
void Program::printMenu()
{
	string input;
	int ninput;
	bool l;
	bool up = true;

	while (up) 
	{
		cout << endl << "------------------- MENU -------------------" << endl;
		cout << 1 << ") Print student info sorted by ascending ID #" << endl;
		cout << 2 << ") Print faculty info sorted by ascending ID #" << endl;
		cout << 3 << ") Print student info sorted by student ID #" << endl;
		cout << 4 << ") Print faculty info sorted by faculty ID #" << endl;
		cout << 5 << ") Print advisor info sorted by student ID #" << endl;
		cout << 6 << ") Print advisee info sorted by faculty ID #" << endl;
		cout << 7 << ") Add a new student" << endl;
		cout << 8 << ") Delete a student's info by using student ID #" << endl;
		cout << 9 << ") Add a new faculty member" << endl;
		cout << 10 << ") Delete a faculty's info by using faculty ID #" << endl;
		cout << 11 << ") Change advisors using student and faculty ID #s" << endl;
		cout << 12 << ") Remove advisees using student and faculty ID #s" << endl;
		cout << 13 << ") Rollback (undo the last 5 actions in this program)" << endl;
		cout << 14 << ") Exit the program" << endl;
		cout << endl << "Please enter the corresponding number to the option you would like to do: ";

		cin >> input;

		try 
		{
			ninput = stoi(input);
			if (ninput < 0 || ninput > 14) 
			{
				cout << "Please try again, that was not a valid number in the menu." << endl;
				l = true;
				ninput = 15;
			}
		}
		catch (exception e)
		{
			l = false;
			ninput = 15;
		}

		switch (ninput) 
		{
		case 1:

			printStudents();
			break;
		case 2:
			printFaculty();
			break;
		case 3:
			printSInfo();
			break;
		case 4:
			printFInfo();
			break;
		case 5:
			printAdvisors();
			break;
		case 6:
			printAdvisees();
			break;
		case 7:
			addStudent();
			break;
		case 8:
			removeStudent();
			break;
		case 9:
			addFaculty();
			break;
		case 10:
			removeFaculty();
			break;
		case 11:
			changeAdvisor();
			break;
		case 12:
			removeAdvisee();
			break;
		case 13:
			rollback();
			break;
		case 14:
			exitProgram();
			return;
		default:
			if (l == true)
				continue;
			else 
			{
				cout << "Please enter a valid number corresponding to the menu options." << endl;
				continue;
			}
		}
	}
}

//prints all students in order by going through the tree
void Program::printStudents() 
{
	if (mStudent.isEmpty()) 
		cout << endl << "Student database is empty!" << endl;
	else 
		printMStudent(mStudent.getRoot());
}

//prints all faculty members in order by going through the tree
void Program::printFaculty() 
{
	if (mFaculty.isEmpty()) 
		cout << endl << "Faculty database is empty!" << endl;
	else
		printMFaculty(mFaculty.getRoot());
}

//prints a student's info with user input
void Program::printSInfo()
{
	string input;
	int sID;
	if (mStudent.isEmpty())
		cout << endl << "Student database is empty!" << endl;
	else
	{
		while (true) 
		{
			cout << endl << "Enter a student ID #: ";
			cin >> input;

			try 
			{
				sID = stoi(input);
				if (mStudent.inside(sID))
				{
					mStudent.search(sID)->printStudent();
					break;
				}
				else
					cout << endl << "Student ID #" << sID << "does not exist in the current database" << endl;
			}
			catch (exception e) 
			{
				cout << endl << "Please enter a valid student ID #." << endl;
			}
		}
	}
}

//prints a faculty member's info with user input
void Program::printFInfo() 
{
	string input;
	int fID;

	if (mFaculty.isEmpty()) 
		cout << endl << "Faculty database is empty!" << endl;
	else 
	{
		while (true) 
		{
			cout << endl << "Enter a faculty ID #: ";
			cin >> input;

			try 
			{
				fID = stoi(input);
				if (mFaculty.inside(fID))
				{
					mFaculty.search(fID)->printFaculty();
					break;
				}
				else
					cout << endl << "Faculty ID #" << fID << " does not exist in the current database" << endl;
			}
			catch (exception e) 
			{
				cout << endl << "Please enter a valid faculty ID #." << endl;
			}
		}
	}
}

//prints advisor information given the user-inputted student ID #
void Program::printAdvisors()
{
	string input;
	int sID;

	if (mStudent.isEmpty()) 
		cout << endl << "Student database is empty!" << endl;
	else 
	{
		cout << "\nList of Students Within Database: " << endl;
		printMStudent(mStudent.getRoot());

		while (true) 
		{
			cout << endl << "Enter a student ID #: ";
			cin >> input;

			try 
			{
				sID = stoi(input);
				if (mStudent.inside(sID)) 
				{
					Student *student = mStudent.search(sID);
					mFaculty.search(student->getAdvisorID())->printFaculty();
					break;
				}
				else
					cout << endl << "Student ID #" << sID << " does not exist in the current database" << endl;
			}
			catch (exception e) 
			{
				cout << endl << "Please enter a valid student ID #." << endl;
			}
		}
	}
}

//prints advisee information given the user-inputted faculty ID #
void Program::printAdvisees() 
{
	string input;
	int fID;

	if (mFaculty.isEmpty())
		cout << endl << "Faculty database is empty!" << endl;
	else
	{
		cout << endl << "List of Faculty in Database: " << endl;
		printMFaculty(mFaculty.getRoot());

		while (true) 
		{
			cout << endl << "Enter a faculty ID #: ";
			cin >> input;

			try 
			{
				fID = stoi(input);
				if (mFaculty.inside(fID)) 
				{

					Faculty *faculty = mFaculty.search(fID);
					for (int i = 0; i < faculty->getArraySize(); i++) 
					{
						if (faculty->adviseeArray[i] != -1) 
						{
							mStudent.search(faculty->adviseeArray[i])->printStudent();
							break;
						}
						else 
						{
							cout << endl << "This faculty member has no advisees." << endl;
						}
					}
					break;
				}
				else
					cout << endl << "Faculty ID #" << fID << " does not exist within the current database" << endl;
			}
			catch (exception e) 
			{
				cout << endl << "Please enter a valid faculty ID #." << endl;
			}
		}
	}
}

void Program::addStudent() 
{
	string input;
	
	//generating random student ID #s
	bool s2ID = false;
	srand(time(NULL));
	int sID = rand() % 4000 + 1000;

	while (s2ID == false) 
	{
		if (mStudent.inside(sID) == false) 
		{
			s2ID = true;
		}
		else 
		{
			int srID = rand() % 4000 + 1000;
			s2ID = false;
		}
	}

	string name;
	string level;
	string major;
	double gpa;
	int adviID;

	cout << endl << "New Student ID: " << sID << endl;
	cin.fail();

	cout << "New Student's Name: ";
	cin.ignore();
	getline(cin, name);

	cout << "New Student's Grade: ";
	cin >> level;

	cout << "New Student's Major: ";
	cin >> major;

	while (true) 
	{
		input = "";
		cout << "New Student's GPA: ";
		cin >> input;

		try 
		{
			gpa = stof(input);
			if (gpa < 0 || gpa > 5) 
				cout << endl << "Enter GPA From 0-5" << endl;
			else
				break;
		}
		catch (exception e) 
		{
			cout << endl << "Please enter a valid GPA" << endl;
		}
	}

	if (!mFaculty.isEmpty()) 
	{
		while (true) 
		{
			input = "";
			cout << "New Student Advisor ID: ";
			cin >> input;

			try 
			{
				adviID = stoi(input);

				if (mFaculty.inside(adviID) || adviID == -1) 
				{
					Faculty *faculty = mFaculty.search(adviID);
					faculty->addAdvisee(sID);
					break;
				}
				else
				{
					input = "";
					cout << endl << "Faculty ID #" << adviID << " does not exist within the current database" << endl;
					cout << "Would you like the list of current faculty? Type 'y' for yes, 'n' for no: ";
					cin >> input;

					if (input == "Y" || input == "y")
						printFaculty();
					else
						break;
				}
			}
			catch (exception e) 
			{
				cout << endl << "Please enter a valid character" << endl;
			}
		}
	}
	else 
		adviID = -1;

	Student *student = new Student(sID, name, level, major, gpa, adviID);
	TreeNode<Student> *studentNode = new TreeNode<Student>(student, sID);
	mStudent.insert(studentNode);

	//s.push(mStudent);
	//f.push(mFaculty);
}

void Program::removeStudent()
{
	string input;
	int sID = 0;

	if (mStudent.isEmpty())
		cout << endl << "Student database is empty!" << endl;
	else 
	{
		cout << endl << "List of Students in Database: " << endl;
		printMStudent(mStudent.getRoot());

		while (true)
		{
			input = "";
			cout << "Enter a student ID #: ";
			cin >> input;

			try 
			{
				sID = stoi(input);
				if (mStudent.inside(sID)) {

					if (mStudent.search(sID)->getAdvisorID() != -1)
						mFaculty.search(mStudent.search(sID)->getAdvisorID())->removeAdvisee(sID);

					mStudent.remove(sID);
					break;
				}
				else
					cout << endl << "Student ID #" << sID << " does not exist within the current database" << endl;
			}
			catch (exception e) 
			{
				cout << "Please enter a valid student ID #." << endl;
			}
		}
	}

	//s.push(mStudent);
	//f.push(mFaculty);
}

void Program::addFaculty()
{
	string input;
	string name;
	string level;
	string dept;
	int adviseeTotal = 0;
	int sID = 0;

	//generates random faculty ID #s
	bool f2ID = false;
	srand(time(NULL));
	int fID = rand() % 5000 + 5000;

	while (f2ID == false) 
	{
		if (mFaculty.inside(fID) == false)
			f2ID = true;
		else
		{
			int frID = rand() % 5000 + 5000;
			f2ID = false;
		}
	}

	cout << "New Faculty ID: " << fID << endl;
	cin.clear();

	cout << "New Faculty Name: ";
	cin.ignore();
	getline(cin, name);

	cout << "New Faculty Level: ";
	cin >> level;

	cout << "New Faculty Department: ";
	cin >> dept;

	Faculty *faculty = new Faculty(fID, name, level, dept);

	if (!mStudent.isEmpty())
	{
		while (true)
		{
			cout << "Number of advisees this faculty member has: ";
			cin >> input;

			try
			{
				adviseeTotal = stoi(input);
				break;
			}
			catch (exception e) 
			{
				cout << "Please type a valid character" << endl;
			}
		}

		if (adviseeTotal != 0) 
		{
			cout << endl << "List of Students in Database: " << endl;
			printStudents();
		}

		for (int i = 0; i < adviseeTotal; i++) 
		{
			while (true)
			{
				input = "";
				cout << "[" << adviseeTotal << " Remaining] Enter a student ID #: ";
				cin >> input;

				try
				{
					sID = stoi(input);
					if (mStudent.inside(sID)) 
					{
						faculty->addAdvisee(sID);
						mStudent.search(sID)->setAdvisorID(fID);
						--adviseeTotal;
						break;
					}
					else
						cout << "Student ID #" << sID << " does not exist within the current database" << endl;
				}
				catch (exception e)
				{
					cout << endl << "Please enter a valid student ID #." << endl;
				}
			}
		}
	}
	TreeNode<Faculty> *facultyNode = new TreeNode<Faculty>(faculty, fID);
	mFaculty.insert(facultyNode);

	//s.push(mStudent);
	//f.push(mFaculty);
}

//function allows for faculty member removal and advisees under the removed faculty member will be transferred to a different one
void Program::removeFaculty() 
{
	string input;
	int fID = 0;
	int tID = 0;

	if (mFaculty.isEmpty())
		cout << endl << "Faculty data is empty!" << endl;
	else 
	{
		cout << endl << "List of Faculty in Database: " << endl;
		printMFaculty(mFaculty.getRoot());

		while (true) 
		{
			input = "";
			cout << endl << "Enter a faculty ID #: ";
			cin >> input;

			try 
			{
				fID = stoi(input);
				if (mFaculty.inside(fID)) 
				{
					if (mFaculty.search(fID)->advisee > 0) 
					{
						while (true) 
						{
							input = "";
							cout << endl << "Enter a faculty ID to transfer these advisees: ";
							cin >> input;

							try 
							{
								tID = stoi(input);
								if (mFaculty.inside(tID)) 
								{
									for (int i = 0; i < mFaculty.search(fID)->arrayMaxSize; ++i) 
									{
										if (mFaculty.search(fID)->adviseeArray[i] != -1) 
											mStudent.search(mFaculty.search(fID)->adviseeArray[i])->setAdvisorID(tID);
									}
								}
								else 
									cout << endl << "Faculty Transfer ID #: " << tID << " does not exist within the current database" << endl;
								break;
							}
							catch (exception e) 
							{
								cout << endl << "Please enter a valid faculty transfer ID #." << endl;
							}
						}
					}
					else 
					{
						mFaculty.remove(fID);
						break;
					}
				}
				else 
					cout << endl << "Faculty ID #" << fID << " does not exist within the current database" << endl;
				break;
			}
			catch (exception e) 
			{
				cout << endl << "Please enter a valid faculty ID #." << endl;
			}
		}
	}

	//s.push(mStudent);
	//f.push(mFaculty);
}

//function allows for students to change faculty advisors per the user's discretion
void Program::changeAdvisor()
{
	string input;
	int sID = 0;
	int fID = 0;

	if (mStudent.isEmpty() || mFaculty.isEmpty())
	{
		cout << endl << "Student and/or faculty database is empty!" << endl;
	}
	else 
	{
		cout << endl << "List of Students in Database: ";
		printMStudent(mStudent.getRoot());

		while (true) 
		{
			input = "";
			cout << endl << "Enter a student ID #: ";
			cin >> input;

			try 
			{
				sID = stoi(input);

				if (mStudent.inside(sID)) 
				{
					while (true) 
					{
						input = "";
						cout << endl << "Enter a faculty ID #: ";
						cin >> input;

						try 
						{
							fID = stoi(input);

							if (mFaculty.inside(fID))
								break;
							else 
								cout << endl << "Faculty ID #" << fID << " does not exist in the current database" << endl;
						}
						catch (exception e) 
						{
							cout << endl << "Please enter a valid faculty ID #." << endl;
						}
					}
					break;
				}
				else
					cout << endl << "Student ID #" << sID << " does not exist in the current database" << endl;
			}
			catch (exception e) 
			{
				cout << "Please enter a valid student ID #." << endl;
			}
		}
		mStudent.search(sID)->setAdvisorID(fID);
		mFaculty.search(fID)->addAdvisee(sID);
	}

	//s.push(mStudent);
	//f.push(mFaculty);
}

// can remove advisees per user's discretion
void Program::removeAdvisee()
{
	string input;
	int sID = 0;
	int fID = 0;

	if (mStudent.isEmpty() || mFaculty.isEmpty())
		cout << endl << "Student and/or faculty database is empty!" << endl;
	else
	{
		cout << "List of Faculty in Database: ";
		printMFaculty(mFaculty.getRoot());

		while (true)
		{
			input = "";
			cout << endl << "Enter a faculty ID #: ";
			cin >> input;

			try
			{
				fID = stoi(input);
				if (mFaculty.inside(fID))
				{
					cout << endl << "List of Advisees for Faculty ID #: " << fID << endl;
					mFaculty.search(fID)->printAdvisees();

					while (true)
					{
						input = "";
						cout << endl << "Enter a student ID #: ";
						cin >> input;

						try
						{
							sID = stoi(input);

							if (mStudent.inside(sID))
								break;
							else
								cout << endl << "Student ID #" << sID << " does not exist in the current database" << endl;
						}
						catch (exception e)
						{
							cout << "Please enter a valid student ID #." << endl;
						}
					}
					break;
				}
				else
					cout << endl << "Faculty ID #" << fID << " does not exist in the current database" << endl;
			}
			catch (exception e)
			{
				cout << "Please enter a valid faculty ID #." << endl;
			}
		}

		if (mFaculty.search(fID)->removeAdvisee(sID))
			mStudent.search(sID)->setAdvisorID(-1);
	}

	input = "";
	cout << "Would you like to set a new advisor? Enter 'y' for yes, 'n' for no: ";
	cin >> input;

	if (input == "y" || input == "Y")
	{
		cout << endl << "List of Current Faculty: ";
		printFaculty();

		while (true)
		{
			input = "";
			cout << "Enter a faculty ID #: ";
			cin >> input;

			try
			{
				fID = stoi(input);

				if (mFaculty.inside(fID))
					break;
				else
					cout << "Faculty ID #" << fID << " does not exist in the current database" << endl;
			}
			catch (exception e)
			{
				cout << "Please enter a valid faculty ID #." << endl;
			}
		}
		mStudent.search(sID)->setAdvisorID(fID);
	}

	//s.push(mStudent);
	//f.push(mFaculty);
}

// undo the last 5 commands the user did
// DOES NOT WORK
//uses GenStack header file
void Program::rollback() 
{/*
	try 
	{
		mStudent = s.pop();
		mFaculty = f.pop();
	}
	catch(exception e) 
	{
		cout << "The undo button is not functioning correctly. Please try again at a different time." << endl;
	}
	*/
}

//exits the program
void Program::exitProgram() 
{
	cout << "-- Program is now exiting. --" << endl;
}

TreeNode<Student>* Program::getMStudentRoot()
{
	return mStudent.getRoot();
}

TreeNode<Faculty>* Program::getMFacultyRoot()
{
	return mFaculty.getRoot();
}