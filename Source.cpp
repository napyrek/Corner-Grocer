/* Author: Nicholas Pyrek
 * Course: CS-210: Programming Languages
 * Southern New Hampshire University
 * April 11, 2022
 */

#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("CS210_Starter_PY_Code");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"CS210_Starter_PY_Code");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"CS210_Starter_PY_Code");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}


void displayMenu() { // displays menu, starts program

	bool runApp = true;
	bool validEntry;
	int userChoice; // gets user input for menu choice
	string item; // gets user input for item to look up

	do {
		cout << endl;
		cout << "******************************************************************************" << endl;
		cout << "*                               Corner Grocer                                *" << endl;
		cout << "******************************************************************************" << endl;
		cout << "*  1. Print List of All Items Purchased and Frequency of Items               *" << endl;
		cout << "*  2. Print Purchase Frequency of a Specific Item                            *" << endl;
		cout << "*  3. Display Histogram                                                      *" << endl;
		cout << "*  4. Exit Program                                                           *" << endl;
		cout << "******************************************************************************" << endl;
		cout << endl;

		try {
			cin >> userChoice;
			cout << endl;
	
			while (std::cin.fail()) { // verify user inputs integer
				std::cin.clear();
				std::cin.ignore(256, '\n');
				cout << "Invalid Entry." << endl;

				cout << "Please enter only 1, 2, 3, or 4." << endl;
				cin >> userChoice;
				cout << endl;
			}
			if ((userChoice >= 0) && (userChoice <= 4)) { // verify user inputs positive integer between 1-4 inclusive

				validEntry = true;
			}
			else { throw (userChoice); }
		}
		catch (...) { cout << "Please Enter only 1, 2, 3, or 4." << endl; }


		if (userChoice == 1) { 

			CallProcedure("read_File"); // reads file from python

		}
		else if (userChoice == 2) {
			
			cout << "Enter item: ";
			cin >> item; // get user input for item to look up
			cout << endl;

			int freq = callIntFunc("find_Frequency", item); // finds frequency of item in list

			if (freq == -1) {
				cout << "Item not found." << endl; // input validation for items
			}
			else {
				cout << item << " sold: " << freq << endl; // prints frequency of item sold
			}
		}
		else if (userChoice == 3) {

			CallProcedure("read_And_Write_File"); // reads from input file and creates output file "frequency.dat"

		}
		else { runApp = false;} // exits program

	} while (runApp == true); // loops through program

	cout << endl;
	cout << "Exiting Program..." << endl;
}

int main()
{
	displayMenu(); // displays menu, starts program
	
	return 0;
}