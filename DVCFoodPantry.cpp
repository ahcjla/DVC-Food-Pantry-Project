#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

#include <stdlib.h> // atoi & atof
#include <cstring> // for strtok & strcpy
#include <cmath> // pow

#include "Inventory.h"
#include "Delivery.h"
#include "PackageTracking.h"

struct Student
{
    string fullName = "None";
    string id = "None";
    string email  = "None";
    int priorityNum = -1;
};

bool operator<(const Student& a, const Student& b)
{
    return b.priorityNum < a.priorityNum;
}

// menus
void studentMenu(); // show operation options

int d_hashCode(const string&); // Hashing function for student hash list

// student
void addStudent(const string&, HashTable<string, Student, 600>&, PriorityQueue<Student>&); // add student to PQ list
void studentSearch(HashTable<string, Student, 600>&); // search for students in PQ
void processStudent(const string&, HashTable<string, Student, 600>&, PriorityQueue<Student>&);
void showList(const string&); // show current students on the waitlist

int main( )
{
    // Data management
    PackageTracker<100, 1000> packages(studentHashFunction, mealIDHashFunction);
    map<string, Status> deliveries;
    InventoryArray<int, string> inventories;

    const char *menu =
        "\n                             Welcome to DVC Food Pantry System\n"
        "___________________________________________________________________________________________\n"
        "Option Number |  Options\n"
        "___________________________________________________________________________________________\n"
        "       1      |  Manage Student Waitlist\n"
        "       2      |  Manage Inventory List\n"
        "       3      |  Manage Distribution List\n"
        "       4      |  Manage Packages\n\n"
        "Enter your selection here or 0 to quit: ";

    bool exit = false;
    while (!exit)
    {
        char input;
        cout << menu;
        cin >> input;
        cin.ignore(1000, '\n');

        switch(input)
        {
            case '0':
                cout << "You selected to exit the program!\n";
                exit = true;
                break;
            case '1':
                studentMenu();
                break;
            case '2':
                inventory(inventories);
                break;
            case '3':
                delivery(deliveries);
                break;
            case '4':
                packageTracking(packages);
                break;
            default:
                cout << " Invalid Input!\n";
        }
    }
}

void studentMenu()
{
    string buf;

    // parse input file
    const string FILENAME = "waitlist.txt";
    ifstream fin(FILENAME);
    char* token;
    char buffer[1000];
    const char* const delimiter = "\t";

    // lists to handle student processing
    HashTable<string, Student, 600> searchList((d_hashCode));
    PriorityQueue<Student> stdPriorityLst; // Priority List

    const char *menu =
            "\n___________________________________________________________________________________________\n"
            "Option Number |  Options\n"
            "___________________________________________________________________________________________\n"
            "   1      |  Add Student to the Priority List\n"
            "   2      |  Process Student from the Priority List\n"
            "   3      |  Search for Students in the Priority List\n"
            "   4      |  View current Student Priority List\n\n"
            "Enter your selection here or 0 to go back: ";

    if (fin.good())
    {

        while (fin.good())
        {
            // read each line
            string line;
            getline(fin, line);
            strcpy(buffer, line.c_str());

            if (buffer[0] == 0)
            {
                continue; // skip blank lines
            }

            // parse line
            const string fullName(token = strtok(buffer, delimiter));
            const string id((token = strtok(nullptr, delimiter)) ? token : "");
            const string email((token = strtok(nullptr, delimiter)) ? token : "");
            const string priority((token = strtok(nullptr, delimiter)) ? token : "");

            // student obj
            Student student;
            student.fullName = fullName;
            student.id = id;
            student.email = email;
            student.priorityNum = atoi(priority.c_str());

            // add students lists
            stdPriorityLst.push(student);
            searchList[id] = student;
        }


        bool exit = false;
        while (!exit)
        {
            char input;
            cout << menu;
            cin >> input;
            cin.ignore(1000, '\n');

            switch(input)
            {
                case '0':
                    cout << "You selected to exit the program!\n";
                    exit = true;
                    break;
                case '1':
                    addStudent(FILENAME, searchList, stdPriorityLst);
                    break;
                case '2':
                    processStudent(FILENAME, searchList, stdPriorityLst);
                    break;
                case '3':
                    studentSearch(searchList);
                    break;
                case '4':
                    showList(FILENAME);
                    break;
                case '5':
                    exit = true;
                    break;
                default:
                    cout << "Invalid Input!\n";
                    break;
            }

        }
    }

    else
    {
        cout << "Student File could not open!\n";
    }



}

int d_hashCode(const string& key)
{
    int result = 0;
    long long unsigned int i = 0;

    if (key.length() > 4)
    {
        for ( i = 0; i < (key.length() - 4); i++)
            result += key.at(i);

        for (long long unsigned int j = 0; j < 4; j++)
            result += (int)(key.at(i+j) * pow(10, j));
    }
    else
    {
        for (long long unsigned int j = 0; j < key.length(); j++)
            result += (int)(key.at(i+j) * pow(10, j));
    }

    return result;
}

// student functions
void addStudent(const string& fileName, HashTable<string, Student, 600>& searchList, PriorityQueue<Student>& stdPriorityLst)
{
    char userChoice ='y';

    ofstream fou (fileName, ios_base::app);
    Student std;
    string buf;

    if (!fou.good())
        cout << "I/O file could not be opened!\n";

    while (userChoice == 'y' || userChoice == 'Y')
    {
        cout << "Enter Student Full Name\n";
        getline(cin, std.fullName);
        fou << std.fullName << "\t";

        cout << "Enter Student ID\n";
        getline(cin, std.id);
        fou << std.id << "\t";

        cout << "Enter Student Email\n";
        getline(cin, std.email);
        fou << std.email << "\t";

        cout << "Assign a Priority Number to Student\n";
        getline(cin, buf);
        std.priorityNum = atoi(buf.c_str());
        fou << std.priorityNum << "\n";

        // add student to PQ
        stdPriorityLst.push(std);
        searchList[std.id] = std;

        cout << "Would like to add another student (Y or N): ";
        cin >> userChoice;
        cin.ignore(1000, '\n');


    }


    // close file
    fou.close();



}
void studentSearch(HashTable<string, Student, 600>& searchLst)
{
    string stdId;
    char userChoice = 'Y';

    while (userChoice == 'Y' || userChoice == 'y')
    {
        cout << "Enter Student ID for Lookup:";
        getline(cin, stdId);

        if (searchLst[stdId].priorityNum != -1)
        {
            Student student = searchLst[stdId];

            cout << "Student Full Name: " << student.fullName << endl;
            cout << "Student ID: " << student.id << endl;
            cout << "Student Email: " << student.email << endl;
            cout << "Student Priority Number: " << student.priorityNum << endl;
        }
        else
        {
            cout << "Student with the ID " << stdId << " could not be found in the Priority List!\n";
        }

        cout << "Would you like to search for another student (Y|N)?";
        cin >> userChoice;
        cin.ignore(1000, '\n');
        cout << endl;
    }
}
void processStudent(const string& fileName, HashTable<string, Student, 600>&searchLst, PriorityQueue<Student>& stdPriorityLst)
{
    char userChoice = 'Y';
    bool isProcess = false;

    while ((userChoice == 'Y' || userChoice == 'y') && !stdPriorityLst.empty())
    {
        Student student = stdPriorityLst.top();
        cout << "\nDetails of Next Student in the Priority List:\n";
        cout << "Student Full Name: " << student.fullName << endl;
        cout << "Student ID: " << student.id << endl;
        cout << "Student Email: " << student.email << endl;
        cout << "Student Priority Number: " << student.priorityNum << endl;

        cout << "\n\nHas the Student Been Given a Food Basket? (Y|N)";
        cin >> userChoice;
        cin.ignore(1000, '\n');
        cout << endl;

        if (userChoice == 'Y' || userChoice == 'y')
        {
            isProcess = true;
            cout << "Student with ID " << student.id << " will be removed from the priority list\n\n";
            stdPriorityLst.pop();
            searchLst.deleteKey(student.id);

            cout << "Would you like to process the next student in the priority list? (Y|N)";
            cin >> userChoice;
            cin.ignore(1000, '\n');

        }
        else
        {
            cout << "Students can only be processed after receiving food baskets!\n";

            cout << "Would you like to continue processing students in the priority list? (Y|N)";
            cin >> userChoice;
            cin.ignore(1000, '\n');
        }

        if (stdPriorityLst.empty())
        {
            cout << "There are no more students in the Priority List\n";
        }
    }

    // Overwrite the waitlist file
    if (isProcess)
    {
        ofstream fou (fileName);
        Student std;
        string buf;

        if (!fou.good())
            cout << "I/O file could not be opened!\n";

        while (!stdPriorityLst.empty())
        {
            Student student = stdPriorityLst.top();

            fou << student.fullName << "\t";
            fou << student.id << "\t";
            fou << student.email << "\t";
            fou << student.priorityNum << "\n";

            stdPriorityLst.pop();
        }
    }

}
void showList(const string& fileName)
{

    // parse input file
    char* token;
    char buffer[1000];
    const char* const delimiter = "\t";

    ifstream fin(fileName);
    cout << endl;

    cout << setw(93) << setfill('_') << " \n";

    cout << setw(7) << setfill(' ') << left << " ";
    cout << "Student Name";
    cout << setw(7) << setfill(' ') << right << "|";

    cout << setw(2) << setfill(' ') << left << " ";
    cout << "Student ID";
    cout << setw(2) << setfill(' ') << right << "|";

    cout << setw(2) << setfill(' ') << left << " ";
    cout << "Priority Number";
    cout << setw(2) << setfill(' ') << right << "|";

    cout << setw(10) << setfill(' ') << left << " ";
    cout << "Email Address";
    cout << setw(10) << setfill(' ') << right << "|\n";

    cout << setw(26) << setfill('_') << "|";
    cout << setw(14) << setfill('_') << "|";
    cout << setw(19) << setfill('_') << "|";
    cout << setw(33) << setfill('_') << "|\n";

    // to display 10 results at a time
    int counter = 0;
    char userChoice;

    while (fin.good() && (userChoice != 'Q' && userChoice !='q'))
    {
        counter++;
        // read line
        string line;
        getline(fin, line);
        strcpy(buffer, line.c_str());

        // skip blank lines
        if (buffer[0] == 0)
            continue;

        const string studentName(token = strtok(buffer, delimiter));
        const string id((token = strtok(nullptr, delimiter))? token:"");
        const string email((token = strtok(nullptr, delimiter))? token:"");
        const string priorityNum((token = strtok(nullptr ,delimiter))? token: "");

        cout << setw(26) << setfill(' ') << left << studentName;
        cout << setw(14) << setfill(' ') << left << id;
        cout << setw(19) << setfill(' ') << left << priorityNum;
        cout << setw(19) << setfill(' ') << left << email << endl;



        if (counter % 10 == 0)
        {
            cout << "Enter any key show more or q to quit:";
            cin >> userChoice;
            cin.ignore(1000, '\n');

        }

    }
    cout << endl;

    // close file
    fin.close();
}
