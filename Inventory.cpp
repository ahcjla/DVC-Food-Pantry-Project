#include <iostream>
#include <string>
using namespace std;

#include <cstring>
#include "InventoryArray.h"
#include "Inventory.h"

void SkuInfoPrimary(const InventoryArray<int, string>&, const int&);
void NewItem(InventoryArray<int, string>&, int&);
void NewPackage(InventoryArray<int, string>&, int&);
void PQueueOutput(InventoryArray<int, string>&);
void SQueueOutput(InventoryArray<int, string>&);
void PkgArray(InventoryArray<int, string>& a);
void SkuQty(InventoryArray<int, string>&);
void DeleteSku(InventoryArray<int, string>&);

void inventory(InventoryArray<int, string> &a){
    int sku = 100000;
    int pkSku = 600000;

    const char* menu =
        "\n___________________________________________________________________________________________\n"
        "Option Number  |  Options\n"
        "___________________________________________________________________________________________\n"
        "       1       |  Enter New Item\n"
        "       2       |  Enter New Package\n"
        "       3       |  Output Item Information\n"
        "       4       |  Output Package Information\n"
        "       5       |  Output List of All Items\n"
        "       6       |  Output List of All Packages\n"
        "       7       |  Output Items Included in Specific Package\n"
        "       8       |  Change Quantity of an Item\n"
        "       9       |  Delete Item\n\n"
        "Enter your selection here or 0 to go back: ";

    bool exit = false;
    while (!exit)
    {
        char input;
        cout << menu;
        cin >> input;
        cin.ignore(1000, '\n');

        switch (input)
        {
        case '0':
            cout << "You selected to exit the inventory menu!\n";
            exit = true;
            break;
        case '1':
            NewItem(a, sku); sku++;
            break;
        case '2':
            NewPackage(a, pkSku); pkSku++;
            break;
                case '3': {
            string buf;
            cout << "Enter Sku: ";
            getline(cin, buf);
            int tsku = atoi(buf.c_str());

            if (a.containsKeyP(tsku)) {
                SkuInfoPrimary(a, tsku);
            }
            break; }
        case '4': {
            string buf;
            cout << "Enter Sku: ";
            getline(cin, buf);
            int tsku = atoi(buf.c_str());

            if (a.containsKeyS(tsku)) {
                cout << "Sku: " << tsku << "\t";
                cout << "Quantity: " << a[tsku] << "\t";
                cout << "Description: " << a.secondary(tsku) << endl;
            }
        }
            break;
        case '5':
            PQueueOutput(a);
            break;
        case '6':
            SQueueOutput(a);
            break;
        case '7':
            PkgArray(a);
            break;
        case '8':
            SkuQty(a);
            break;
        case '9':
            DeleteSku(a);
            break;
        default:
            cout << " Invalid Input!\n";
        }
    }
}


/*------------------------------------------------------------------

                              Functions

--------------------------------------------------------------------*/

// Output individual sku info
void SkuInfoPrimary(const InventoryArray<int, string>& a, const int& sku) {
    cout << "Item Info: \n";
    cout << "Sku: " << sku << "\t";
    cout << "Quantity: " << a[sku] << "\t";
    cout << "Item Name: " << a.primary(sku) << endl;
}

// new individual item
void NewItem(InventoryArray<int, string>& a, int& sku) {
    string buf;
    string buf2;
    cout << "Enter the name of the item: ";
    getline(cin, buf);
    a.primary(sku) = buf;
    cout << endl;

    cout << "Please enter quantity to add, negative to subtract\n";
    getline(cin, buf2);
    a[sku] = a[sku] + atoi(buf2.c_str());
    cout << endl;

    SkuInfoPrimary(a, sku);
    cout << endl;    
}

// new package item
void NewPackage(InventoryArray<int, string>& a, int& sku) {
    string buf;
    string buf2;
    cout << "Please enter the name of the package: ";
    getline(cin, buf);
    cout << endl;
    a.secondary(sku) = buf;
    do {
        cout << "Please enter a sku to add to this package [Q to quit]:  ";
        getline(cin, buf2);
        if (buf2 == "Q" || buf2 == "q") { break; }
        int tempSku;
        tempSku = atoi(buf2.c_str());

        if (a.containsKeyP(tempSku)) { a.packageContents(sku, tempSku); }
    } while (buf2 != "Q" && buf2 != "q");
    cout << endl;
    cout << "Sku: " << sku << "\t";
    cout << "Quantity: " << a[sku] << "\t";
    cout << "Description: " << a.secondary(sku) << endl;
}


// print individual sku key queue
void PQueueOutput(InventoryArray<int, string>& a) {
    Queue<int> skuList = a.primaryQueue();
    int size = skuList.size();

    // check size
    if (skuList.size() > 50) {
        string yn;
        cout << "There are more than 50 skus, would you still like to print? Y/N ";
        getline(cin, yn);
        cin.clear();
        if (yn == "N" || yn == "n") { return; }
        cout << endl;
    }

    // print sku list
    for (int i = 0; i < size; i++) {
        int sku = skuList.front();
        cout << "Sku: " << sku << "\t";
        cout << "Quantity: " << a[sku] << "\t";
        cout << "Description: " << a.primary(sku) << "\t";
        skuList.pop();
        cout << endl;
    }
}

// print package sku key queue
void SQueueOutput(InventoryArray<int, string>& a) {
    Queue<int> skuList = a.secondaryQueue();
    int size = skuList.size();
    cout << endl;

    // check size
    if (size > 50) {
        string yn;
        cout << "There are more than 50 skus, would you still like to print? Y/N: ";
        getline(cin, yn);
        if (yn == "N" || yn == "n") { return; }
    }
    cout << endl;

    // print sku list
    for (int i = 0; i < size; i++) {
        int sku = skuList.front();
        cout << "Sku: " << sku << "\t";
        cout << "Quantity: " << a[sku] << "\t";
        cout << "Description: " << a.secondary(sku) << endl;
        skuList.pop();
    }
    cout << endl;
}

// print package contents key array
void PkgArray(InventoryArray<int, string>& a) {
    string buf;
    cout << "Enter a package sku to view its contents: ";
    getline(cin, buf);
    int sku = atoi(buf.c_str());
    cout << endl;

    DynamicArray<int> tempArray = a.PackageArray(sku);
    for (int i = 0; i < a.aSize(sku); i++) {
        int iSku = tempArray[i];
        SkuInfoPrimary(a, iSku);
    }
    cout << endl;
}

// change individual sku quantity
void SkuQty(InventoryArray<int, string>& a) {
    string buf1;
    string buf2;

    cout << "Please enter sku: \n";
    getline(cin, buf1);
    int sku = atoi(buf1.c_str());

    if (a.containsKeyS(sku)) { cout << "Package quantities must be adjusted by individual item\n"; return; }
    if (!a.containsKeyP(sku)) { cout << "Invalid Sku.\n"; return; }

    cout << "Quantity of " << sku << " " << a.primary(sku);
    cout << " is: " << a[sku] << endl;
    cout << endl;

    cout << "Please enter quantity to add, negative to subtract\n";
    getline(cin, buf2);
    a[sku] = a[sku] + atoi(buf2.c_str());
    SkuInfoPrimary(a, sku);
}

// delete sku
void DeleteSku(InventoryArray<int, string>& a) {
    string buf;
    string yn;

    cout << endl;
    cout << "Please enter the sku you want to delete: ";
    getline(cin, buf);
    cout << endl;

    int sku = atoi(buf.c_str());
    if (!a.containsKey(sku)) { cout << "Sku does not exist!\n"; return; }

    if (a.containsKeyP(sku)) {
        SkuInfoPrimary(a, sku);
        cout << "Are you sure you want to delete sku? Y/N: ";
        getline(cin, yn);
        cout << endl;
        if (yn == "N" || yn == "n") { return; }
        a.deleteKey(sku);
        if (!a.containsKeyP(sku)) { cout << "successfully deleted item\n"; }
    }

    if (a.containsKeyS(sku)) {
        cout << "Sku: " << sku << "\t";
        cout << "Quantity: " << a[sku] << "\t";
        cout << "Description: " << a.secondary(sku) << endl;
        cout << "Are you sure you want to delete sku? Y/N: ";
        getline(cin, yn);
        cout << endl;
        if (yn == "N" || yn == "n") { return; }
        a.deleteKey(sku);
        if (!a.containsKeyS(sku)) { cout << "successfully deleted package\n"; }
    }
}

