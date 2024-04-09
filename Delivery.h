#ifndef DELIVERY_DEMO_H
#define DELIVERY_DEMO_H

#include <map>
using namespace std;

struct Calendar 
{
  int day;
  int month;
  int year;
};

struct Status 
{
  Calendar deliveryDate = { 0, 0, 0 };
  Calendar deliveredDate = { 0, 0, 0 };
  bool deliveredStatus = false;
  string deliveryCompany = "";
  string trackingNumber = "";
};

void delivery(map<string, Status> &);

#endif // !DELIVERY_DEMO_H
