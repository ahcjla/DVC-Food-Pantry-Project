//
// Created by alsha on 12/4/2021.
//

#ifndef _DVC_FOOD_PANTRY_CLIENT_H
#define _DVC_FOOD_PANTRY_CLIENT_H
#include <String>


#include "PriorityQueue.h"
#include "HashTable.h"

class Client
{
    // shared
    static string FILENAME;
    static HashTable<string, Client, 600> searchList;
    static PriorityQueue<Client> priorityLst; // Priority List
    static int d_hashCode(const string& key);
    static string clientType;

    string fullName;
    string id;
    string email;
    int priorityNum;

public:
    Client(string, string, HashTable<string, Client<CAP>, CAP>, PriorityQueue<Client<CAP>> stdPriorityLst);
    bool operator<(const Client<CAP>&);
    void menu( );
    void addClient( );
    void processClient( );
    void showClientList( );
    void searchClient( );


};

Client::Client(string fileName, string type, HashTable<string, Client<CAP>, CAP> search, PriorityQueue<Client<CAP>> stdPriorityLst)
{
    FILENAME = fileName;
    clientType = type;

    fullName = "N/A";
    id = "N/A";
    email = "N/A";
    priorityNum = -1;


}
template<int CAP>
bool Client<CAP>::operator<(const Client<CAP> & other)
{
    return this->id < other->id;
}

template<int CAP>
void Client<CAP>::menu( )
{
    string buf;
    int userInput;

    // parse input file
    ifstream fin(FILENAME);
    char* token;
    char buffer[1000];
    const char* const delimiter = "\t";

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

            // client obj
            Client<CAP> client;
            client.fullName = fullName;
            client.id = id;
            client.email = email;
            client.priorityNum = atoi(priority.c_str());

            // add students lists
            priorityLst.push(client);
            searchList[id] = client;
        }

        cout << endl;
        cout << endl;

        cout << setw(93) << setfill('_') << " \n";

        cout << "Option Number";
        cout << setw(2) << setfill(' ') << right << "|";

        cout << setw(2) << setfill(' ') << left << " ";
        cout << "Options";
        cout << setw(2) << setfill(' ') << right << " \n";

        cout << setw(93) << setfill('_') << " \n";


        cout << setw(7) << setfill(' ') << left << " ";
        cout << "1";
        cout << setw(7) << setfill(' ') << right << "|";
        cout << setw(2) << setfill(' ') << right << " ";
        cout << "Add Student to the Priority List\n";

        cout << setw(7) << setfill(' ') << left << " ";
        cout << "2";
        cout << setw(7) << setfill(' ') << right << "|";
        cout << setw(2) << setfill(' ') << right << " ";
        cout << "Process Student from the Priority List\n";

        cout << setw(7) << setfill(' ') << left << " ";
        cout << "3";
        cout << setw(7) << setfill(' ') << right << "|";
        cout << setw(2) << setfill(' ') << right << " ";
        cout << "Search for Students in the Priority List\n";

        cout << setw(7) << setfill(' ') << left << " ";
        cout << "4";
        cout << setw(7) << setfill(' ') << right << "|";
        cout << setw(2) << setfill(' ') << right << " ";
        cout << "View current Student Priority List\n";

        cout << setw(7) << setfill(' ') << left << " ";
        cout << "5";
        cout << setw(7) << setfill(' ') << right << "|";
        cout << setw(2) << setfill(' ') << right << " ";
        cout << "Go Back to the Previous Menu\n";

        cout <<"\nEnter your selection here or 0 to quit:";
        getline(cin, buf);
        userInput = atoi(buf.c_str());

        switch(userInput)
        {
            case 0:
                cout << "You selected to exit the program!\n";
                break;
            case 1:
                addClient( );
                menu();
                break;
            case 2:
                processClient();
                menu();
                break;
            case 3:
                searchClient( );
                menu();
                break;
            case 4:
                showClientList(FILENAME);
                menu();
                break;
            case 5:
                // TODO: fix main menu
                break;
            default:
                cout << "Invalid Input!\n";
                break;
        }
    }

    else
    {
        cout << "Student File could not open!\n";
    }
}

template<int CAP>
void Client<CAP>::addClient( )
{
    char userChoice ='y';

    ofstream fou (FILENAME, ios_base::app);
    Client client;
    string buf;

    if (!fou.good())
        cout << "I/O file could not be opened!\n";

    while (userChoice == 'y' || userChoice == 'Y')
    {
        cout << "Enter " << clientType << "'s Full Name\n";
        getline(cin, client.fullName);
        fou << client.fullName << "\t";

        cout << "Enter " << clientType << "'s ID\n";
        getline(cin, client.id);
        fou << client.id << "\t";

        cout << "Enter " << clientType << "'s Email\n";
        getline(cin, client.email);
        fou << client.email << "\t";

        cout << "Enter " << clientType << "'s Priority Number\n";
        getline(cin, buf);
        client.priorityNum = atof(buf.c_str());
        fou << client.priorityNum << "\n";

        // add student to PQ
        priorityLst.push(client);
        searchList[client.id] = client;

        cout << "Would like to add another student (Y or N): ";
        cin >> userChoice;
        cin.ignore(1000, '\n');


    }


    // close file
    fou.close();

    // load student menu
    menu();

}

#endif //_DVC_FOOD_PANTRY_CLIENT_H
