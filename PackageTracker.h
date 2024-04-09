// Programmer name: Alex Kogan
// Programmer ID: 1865080

#ifndef PACKAGE_TRACKER_H
#define PACKAGE_TRACKER_H

#include <string>
#include <vector>
using namespace std;

#include "HashTable.h"
#include "PriorityQueue.h"

struct Package
{
  string deliveryMethod;
  int ID;
  int priority;

  // Comparison operator for the customer priority queues
  bool operator<(const Package &ref) const { return this->priority < ref.priority; }
};

template <int CUSTOMER_CAP, int PACKAGE_CAP>
class PackageTracker
{
  HashTable<string, PriorityQueue<Package>, CUSTOMER_CAP> customers; // The key is the customer ID and the value is a priority queue of packages for that customer
  HashTable<int, bool, PACKAGE_CAP> packageIDs; // Stores the packageIDs in a quickly accessible fashion for checking
public:
  PackageTracker(int(*)(const string&), int(*)(const int&)); // Constructor requires 2 hashing functions for the customer and package hastables

  // Customer management
  void addCustomer(const string &); // Creates a new customer association if it doesn't already exist
  void removeCustomer(const string &); // Removes a customer if it exists
  bool hasCustomer(const string &) const; // Checks to see if a customer exists
  int getCustomerCount() const; // Get the number of customers
  Queue<string> getCustomers() const; // Get a queue of customers
  
  // Package management
  void pushPackage(const string &, const string &, int, int); // Pushes a package to a customer's queue
  void popPackage(const string &); // Pops a package from a customer's queue
  bool hasPackage(int) const; // Checks to see if a package exists
  Package topPackage(const string &) const; // Retrieves a package from the front of a customer's queue
  int getPackageCount(const string &) const; // Get the number of packages in a customer's queue
  vector<Package> getPackages(const string &) const; // Get a copy of packages for a specific customer
};

template <int CUSTOMER_CAP, int PACKAGE_CAP>
PackageTracker<CUSTOMER_CAP, PACKAGE_CAP>::PackageTracker(int(*customerHash)(const string&), int(*packageHash)(const int&))
  : customers(customerHash), packageIDs(packageHash)
{}

template <int CUSTOMER_CAP, int PACKAGE_CAP>
void PackageTracker<CUSTOMER_CAP, PACKAGE_CAP>::addCustomer(const string &customerID)
{
  // Allocate a customer ID and package queue key value pair to the customer hashtable
  if (!customers.containsKey(customerID))
    customers[customerID] = PriorityQueue<Package>();
}

template <int CUSTOMER_CAP, int PACKAGE_CAP>
void PackageTracker<CUSTOMER_CAP, PACKAGE_CAP>::removeCustomer(const string &customerID)
{
  customers.deleteKey(customerID);
}

template <int CUSTOMER_CAP, int PACKAGE_CAP>
bool PackageTracker<CUSTOMER_CAP, PACKAGE_CAP>::hasCustomer(const string &custumerID) const
{
  return customers.containsKey(custumerID);
}

template <int CUSTOMER_CAP, int PACKAGE_CAP>
int PackageTracker<CUSTOMER_CAP, PACKAGE_CAP>::getCustomerCount() const
{
  return customers.size();
}

template <int CUSTOMER_CAP, int PACKAGE_CAP>
Queue<string> PackageTracker<CUSTOMER_CAP, PACKAGE_CAP>::getCustomers() const
{
  return customers.keys();
}

template <int CUSTOMER_CAP, int PACKAGE_CAP>
void PackageTracker<CUSTOMER_CAP, PACKAGE_CAP>::pushPackage(const string &customerID, const string &deliveryMethod, int packageID, int priority)
{
  // Only perform the push if the package number is unique and the customer exists
  if (!packageIDs.containsKey(packageID) && customers.containsKey(customerID))
  {
    Package pack{deliveryMethod, packageID, priority};

    // Push the package
    customers[customerID].push(pack);
    packageIDs[packageID] = true;
  }
}

template <int CUSTOMER_CAP, int PACKAGE_CAP>
void PackageTracker<CUSTOMER_CAP, PACKAGE_CAP>::popPackage(const string &customerID)
{
  // Don't bother popping if the customer doesn't exist
  if (customers.containsKey(customerID))
  {
    // Pop frpm the front of the customer's queue and remove the packageID from data
    int packageID = customers[customerID].top().ID;
    packageIDs.deleteKey(packageID);
    customers[customerID].pop();
  }
}

template <int CUSTOMER_CAP, int PACKAGE_CAP>
Package PackageTracker<CUSTOMER_CAP, PACKAGE_CAP>::topPackage(const string &customerID) const
{
  // Only works if a customer was already added
  if (customers.containsKey(customerID))
    return customers[customerID].top();
  return Package();
}

template <int CUSTOMER_CAP, int PACKAGE_CAP>
int PackageTracker<CUSTOMER_CAP, PACKAGE_CAP>::getPackageCount(const string &customerID) const
{
  // Only works if a customer was already added
  if (customers.containsKey(customerID))
    return customers[customerID].size();
  return 0;
}

template <int CUSTOMER_CAP, int PACKAGE_CAP>
vector<Package> PackageTracker<CUSTOMER_CAP, PACKAGE_CAP>::getPackages(const string &customerID) const
{
  PriorityQueue<Package> copy = customers[customerID]; // Retrieve a copy of a customer's package queue
  
  vector<Package> packages(copy.size()); // The vector of packages to be returned, intialized to a cap of the queue's size
  
  // Loop, copy packages to the vector from the queue
  for (int i = 0; i < copy.size(); ++i)
  {
    packages[i] = copy.top();
    copy.pop();
  }
  return packages;
}

#endif // !PACKAGE_TRACKER_H
