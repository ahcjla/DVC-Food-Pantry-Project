// Programmer name: Alex Kogan
// Programmer ID: 1865080

#ifndef PACKAGE_TRACKING_DEMO_H
#define PACKAGE_TRACKING_DEMO_H

#include "PackageTracker.h"

int studentHashFunction(const string &name);
int mealIDHashFunction(const int &id);
void packageTracking(PackageTracker<100, 1000> &tracker);

#endif // !PACKAGE_TRACKING_DEMO_H
