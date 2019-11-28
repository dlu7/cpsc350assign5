#include <iostream>
#include "BST.h"
using namespace std;

class Program
{
public:
	BST<Student> mStudent;
	BST<Faculty> mFaculty;

	Program();
	~Program();

	void fileRead();
	void fileWrite();

	void printMStudent(TreeNode<Student> *s);
	void printMFaculty(TreeNode<Faculty> *f);

	void outputMStudent(TreeNode<Student> *s, string s2);
	void outputMFaculty(TreeNode<Faculty> *f, string f2);

	void printMenu(); 
	void printStudents(); // 1
	void printFaculty(); // 2
	void printSInfo(); // 3
	void printFInfo(); // 4
	void printAdvisors(); // 5
	void printAdvisees(); // 6
	void addStudent(); // 7
	void removeStudent(); // 8
	void addFaculty(); // 9
	void removeFaculty(); // 10
	void changeAdvisor(); // 11
	void removeAdvisee(); // 12
	void rollback(); // 13
	void exitProgram(); // 14

	TreeNode<Student>* getMStudentRoot();
	TreeNode<Faculty>* getMFacultyRoot();
};
