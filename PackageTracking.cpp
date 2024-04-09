// Programmer name: Alex Kogan
// Programmer ID: 1865080

#include <iostream>
#include <string>
using namespace std;

#include <cstring>
#include <cstdlib>

#include "PackageTracking.h"

void addStudent(PackageTracker<100, 1000> &tracker);
void removeStudent(PackageTracker<100, 1000> &tracker);
void listStudents(PackageTracker<100, 1000> &tracker);
void addMeal(PackageTracker<100, 1000> &tracker);
void popMeal(PackageTracker<100, 1000> &tracker);
void listMeals(PackageTracker<100, 1000> &tracker);

// Hashing function for student names
int studentHashFunction(const string &name)
{
	int sum = 0;
	for (char c : name)
		sum += c;
	return sum;
}

// Hashing function for package IDs (very simple)
int mealIDHashFunction(const int &id) { return id; }

void addStudent(PackageTracker<100, 1000> &tracker)
{
	string buffer;

	// Get the student ID
	cout << "Student ID to add: "; 
	cin >> buffer;
	cout << endl;

	// Check to see if the student exists already
	if (tracker.hasCustomer(buffer))
		cout << "Student ID " << buffer << " already exists" << endl;
	else
	{
		// If not, add them and display the total number of students
		tracker.addCustomer(buffer);
		cout << "Student " << buffer << " added" << endl;
		cout << "There are now " << tracker.getCustomerCount() << " student(s)" << endl;
	}
	cout << endl;
}

void removeStudent(PackageTracker<100, 1000> &tracker)
{
	string buffer;

	// Break prematurely if there are not students
	if (tracker.getCustomerCount() == 0)
	{
		cout << "There are no students" << endl;
		return;
	}

	cout << "Student ID to remove: ";
	cin >> buffer;
	cout << endl;

	// Check to see if the student does not exist already
	if (!tracker.hasCustomer(buffer))
		cout << "Student ID " << buffer << " does not exist" << endl;
	else
	{
		// If they do, remove them and display the total number of students
		tracker.removeCustomer(buffer);
		cout << buffer << " removed" << endl;
		cout << "There are now " << tracker.getCustomerCount() << " student(s)" << endl;
	}
	cout << endl;
}

void listStudents(PackageTracker<100, 1000> &tracker)
{
	string buffer;
	Queue<string> students = tracker.getCustomers();

	cout << "There are " << tracker.getCustomerCount() << " students" << endl;

	// Retrieve the student IDs queue and print out the IDs
	for (int i = 0; i < tracker.getCustomerCount(); ++i)
	{
		cout << "\t" << students.front() << endl;
		students.pop();
	}
	cout << endl;
}

void addMeal(PackageTracker<100, 1000> &tracker)
{
	string buffer;
	Package package;

	// Break prematurely if there are not students
	if (tracker.getCustomerCount() == 0)
	{
		cout << "There are no students" << endl;
		return;
	}

	// Get the meal ID
	cout << "What is the meal ID (an integer)? ";
	cin >> buffer; package.ID = atoi(buffer.c_str());

	// Get the delivery method
	cout << "What is the delivery method? ";
	cin.ignore(1000, 10);
	getline(cin, package.deliveryMethod);

	// Get the meal priority
	cout << "What is the delivery time for the package in days (an integer)? ";
	cin >> buffer; package.priority = atoi(buffer.c_str());

	// Loop until the meal is added or the user quits
	while (true)
	{
		cout << "Which student is the package for? ";
		cin >> buffer;
		cout << endl;

		if (buffer == "Q" || buffer == "q")
			break;
		else if (!tracker.hasCustomer(buffer))
			cout << "The student ID " << buffer << " is not recognized. Please try again or enter Q to quit" << endl;
		else
		{
			tracker.pushPackage(buffer, package.deliveryMethod, package.ID, package.priority);
			cout << "Meal " << package.ID << " added to student " << buffer << "'s pantry queue" << endl;
			break;
		}
	}
	cout << endl;
}

void popMeal(PackageTracker<100, 1000> &tracker)
{
	string buffer;
	Package package;

	// Break prematurely if there are not students
	if (tracker.getCustomerCount() == 0)
	{
		cout << "There are no students" << endl;
		return;
	}
	
	cout << "Which student are you retrieving their newest meal for? ";
	cin >> buffer;
	cout << endl;

	if (!tracker.hasCustomer(buffer))
		cout << "Student " << buffer << " is not recognized" << endl;
	else if (tracker.getPackageCount(buffer) == 0)
		cout << "Student " << buffer << " has no meals in queue" << endl;
	else
	{
		package = tracker.topPackage(buffer);
		cout << "\tID: " << package.ID << endl;
		cout << "\tDelivery method: " << package.deliveryMethod << endl;
		cout << "\tDelivery time: " << package.priority << endl;
		tracker.popPackage(buffer);
	}
	cout << endl;
}

void listMeals(PackageTracker<100, 1000> &tracker)
{
	string buffer;

	// Break prematurely if there are not students
	if (tracker.getCustomerCount() == 0)
	{
		cout << "There are no students" << endl;
		return;
	}
	
	cout << "Which student are you retrieving their newest meal for? ";
	cin >> buffer;
	cout << endl;

	if (!tracker.hasCustomer(buffer))
		cout << "Student " << buffer << " is not recognized" << endl;
	else if (tracker.getPackageCount(buffer) == 0)
		cout << "Student " << buffer << " has no meals in queue" << endl;
	else
	{
		cout << "Student " << buffer << " has " << tracker.getPackageCount(buffer) << " meal(s) in queue" << endl;
		
		// Loop, outputting info about the meals in queue
		auto meals = tracker.getPackages(buffer);
		for (size_t i = 0; i < meals.size(); ++i)
		{
			cout << "Meal #" << i << ':' << endl;
			cout << "\tID: " << meals[i].ID << endl;
			cout << "\tDelivery method: " << meals[i].deliveryMethod << endl;
			cout << "\tDelivery time: " << meals[i].priority << endl;
		}
	}
	cout << endl;
}

void packageTracking(PackageTracker<100, 1000> &tracker)
{
    const char *menu =
            "\n___________________________________________________________________________________________\n"
            "Option Number |  Options\n"
            "___________________________________________________________________________________________\n"
            "       1      |  Add a student\n"
            "       2      |  Remove a student\n"
            "       3      |  List students\n"
            "       4      |  Add a meal to a student's pantry\n"
            "       5      |  Pop a meal from a student's pantry\n"
            "       6      |  List meals in a student's pantry\n\n"
            "Enter your selection here or 0 to go back: ";
  bool quit = false;
  while (!quit)
  {
    cout << menu;

    char c; cin >> c;
    switch (c)
    {
        case '0':
            cout << "You selected to go back!\n";
            quit = true;
            break;
        case '1':
          addStudent(tracker);
          break;
        case '2':
          removeStudent(tracker);
          break;
        case '3':
          listStudents(tracker);
          break;
        case '4':
          addMeal(tracker);
          break;
        case '5':
          popMeal(tracker);
          break;
        case '6':
          listMeals(tracker);
          break;
        default:
          cout << "Invalid option\n" << endl;
          break;
    }
  }
}
