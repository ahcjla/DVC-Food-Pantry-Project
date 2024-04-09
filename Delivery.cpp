#include <iostream>
#include <map>
#include <string>
using namespace std;

#include <cstring>
#include <cctype>

#include "Delivery.h"

void getDeliveryDate(map<string, Status>& delivery, string& studentID);
void getDeliveredDate(map<string, Status>& delivery, string& studentID);
void setDeliveryDate(map<string, Status>& delivery, const string& studentID, Calendar& date);
void setDeliveredDate(map<string, Status>& delivery, const string& studentID, Calendar& date);
void setDeliveryStatus(map<string, Status>& delivery, const string& studentID, string& status);
void setDeliveryCompany(map<string, Status>& delivery, const string& studentID, const string& company);
void setTrackingNumber(map<string, Status>& delivery, const string& studentID, const string& trackingNumber);
void getDeliveryCompany(map<string, Status>& delivery, const string& studentID);
void getTrackingNumber(map<string, Status>& delivery, const string& studentID);
void showAllDelivered(map<string, Status>& delivery);
void showAllUndelivered(map<string, Status>& delivery);
void searchByTracking(map<string, Status>& delivery, const string& trackingNumber);
Calendar dateValidation(Calendar& date);
string convertMonth(const int& month);

void delivery(map<string, Status> &deliveries)
{

  string buf;
  string studentID;

    cout << "Enter student ID: ";
    cin >> studentID;


    const char *menu =
            "\n___________________________________________________________________________________________\n"
            "Option Number |  Options\n"
            "___________________________________________________________________________________________\n"
            "       1      |  Get delivery date\n"
            "       2      |  Set delivery date\n"
            "       3      |  Get delivered date\n"
            "       4      |  Set delivered status & date\n"
            "       5      |  Get tracking number\n"
            "       6      |  Set tracking number\n"
            "       7      |  Get delivery company\n"
            "       8      |  Set delivery company\n"
            "       9      |  Display all undelivered packages\n"
            "      10      |  Display all delivered packages\n\n"
            "Enter your selection here or 0 to go back: ";

    bool exit = false;

    while (!exit) {
        char input;
        cout << menu;
        cin >> buf;
        input = atoi(buf.c_str());

        switch (input)
        {
            // Get delivery date
            case 0:
                exit = true;
                break;
            case 1:
            {
                getDeliveryDate(deliveries, studentID);
                break;
            }

                // Set delivery date
            case 2:
            {
                int day, month, year;
                cout << "Enter delivery date(dd mm yyyy): ";
                cin >> buf;
                day = atoi(buf.c_str());
                cin >> buf;
                month = atoi(buf.c_str());
                cin >> buf;
                year = atoi(buf.c_str());
                Calendar temp = { day, month, year };

                setDeliveryDate(deliveries, studentID, temp);
                break;
            }

                // Get delivered date
            case 3:
            {
                getDeliveredDate(deliveries, studentID);
                break;
            }

                // Set delivered date
            case 4:
            {
                string userInput;

                while (true)
                {
                    cout << "Enter 'delivered' if package has arrived, else enter 'undelivered': ";
                    cin >> userInput;
                    if (userInput == "delivered" || userInput == "undelivered")
                        break;
                }

                setDeliveryStatus(deliveries, studentID, userInput);
                break;
            }

                // Get tracking number
            case 5:
            {
                getTrackingNumber(deliveries, studentID);
            }

                // Set tracking number
            case 6:
            {
                string trackingNumber;
                cin >> trackingNumber;
                setTrackingNumber(deliveries, studentID, trackingNumber);
                break;
            }

                // Get delivery company
            case 7:
            {
                getDeliveryCompany(deliveries, studentID);
                break;
            }

                // Set delivery company
            case 8:
            {
                string deliveryCompany;
                cin >> deliveryCompany;
                setDeliveryCompany(deliveries, studentID, deliveryCompany);
                break;
            }

                // Display all undelivered packages + student ID
            case 9:
            {
                showAllUndelivered(deliveries);
                break;
            }

            case 10:
            {
                showAllDelivered(deliveries);
                break;
            }

            default:
                cout << "Invalid Input!\n";
                break;
        }
    }

}

void getDeliveryDate(map<string, Status>& delivery, string& studentID)
{
  Calendar deliveryStatus = delivery[studentID].deliveryDate;
  if (deliveryStatus.day == 0 || deliveryStatus.month == 0 || deliveryStatus.year == 0)
  {
    cout << "No delivery has been made" << endl;
  }
  else
  {
    cout << "Delivery date: " << deliveryStatus.day << " " << convertMonth(deliveryStatus.month) << " " << deliveryStatus.year << endl;
  } 
}

void getDeliveredDate(map<string, Status>& delivery, string& studentID)
{
  Calendar deliveredStatus = delivery[studentID].deliveredDate;
  if (delivery[studentID].deliveredStatus == false)
  {
    cout << "No package has been delivered" << endl;
  }
  else
  {
    cout << "Delivered date: " << deliveredStatus.day << " " << convertMonth(deliveredStatus.month) << " " << deliveredStatus.year << endl;
  }
}

void setDeliveryDate(map<string, Status>& delivery, const string& studentID, Calendar& date)
{
  delivery[studentID].deliveryDate = dateValidation(date);
}

void setDeliveredDate(map<string, Status>& delivery, const string& studentID, Calendar& date)
{
  delivery[studentID].deliveredDate = dateValidation(date);
}

void setDeliveryStatus(map<string, Status>& delivery, const string& studentID, string& status)
{
  if (status == "delivered")
  {
    delivery[studentID].deliveredStatus = true;

    string buf;
    int day, month, year;
    cout << "Delivered on (dd mm yyyy): ";
    cin >> buf;
    day = atoi(buf.c_str());
    cin >> buf;
    month = atoi(buf.c_str());
    cin >> buf;
    year = atoi(buf.c_str());
    Calendar temp = { day, month, year };

    setDeliveredDate(delivery, studentID, temp);
  }
  else if (status == "undelivered")
  {
    delivery[studentID].deliveredStatus = false;
  }
}

void setDeliveryCompany(map<string, Status>& delivery, const string& studentID, const string& company)
{
  delivery[studentID].deliveryCompany = company;
}

void setTrackingNumber(map<string, Status>& delivery, const string& studentID, const string& trackingNumber)
{
  delivery[studentID].trackingNumber = trackingNumber;
}

void getDeliveryCompany(map<string, Status>& delivery, const string& studentID)
{
  if (delivery[studentID].deliveryCompany == "")
  {
    cout << "No delivery company available" << endl;
  }
  else
  {
    cout << "Delivery number: " << delivery[studentID].deliveryCompany << endl;
  }
}

void getTrackingNumber(map<string, Status>& delivery, const string& studentID)
{
  if (delivery[studentID].trackingNumber == "")
  {
    cout << "No tracking number available" << endl;
  }
  else
  {
    cout << "Tracking number: " << delivery[studentID].trackingNumber << endl;
  }
}

void showAllDelivered(map<string, Status>& delivery)
{
  cout << "Show all students with undelivered packages:" << endl;
  for (map<string, Status>::iterator it = delivery.begin(); it != delivery.end(); ++it)
  {
    if (it->second.deliveredStatus == true)
    {
      Calendar temp = it->second.deliveredDate;
      cout << "StudentID: " << it->first << endl;
      cout << "Delivered on: " << temp.day << " " << convertMonth(temp.month) << " " << temp.year << endl;
    }
  }
}

void showAllUndelivered(map<string, Status>& delivery)
{
  cout << "Show all students with undelivered packages:" << endl;
  for (map<string, Status>::iterator it = delivery.begin(); it != delivery.end(); ++it)
  {
    if (it->second.deliveredStatus == false)
    {
      cout << "StudentID: " << it->first << endl;
      cout << "Tracking number: " << it->second.trackingNumber << endl;
    }
  }
}

void searchByTracking(map<string, Status>& delivery, const string& trackingNumber)
{
  for (map<string, Status>::iterator it = delivery.begin(); it != delivery.end(); ++it)
  {
    if (it->second.trackingNumber == trackingNumber)
    {
      Calendar temp = it->second.deliveryDate;
      cout << "Student ID: " << it->first << endl;
      cout << "Delivery date: " << temp.day << " " << convertMonth(temp.month) << " " << temp.year << endl;
      if (it->second.deliveredStatus == true)
      {
        cout << "Delivered date: " << it->second.deliveredDate.day << " " << convertMonth(it->second.deliveredDate.month) << " " << it->second.deliveredDate.year << endl;
      }
      else
      {
        cout << "Package not delivered" << endl;
      }
      return;
    }
  }

  cout << "Tracking number not found" << endl;
}

Calendar dateValidation(Calendar& date)
{
  bool flag = true;
  while (flag)
  {
    string buf;
    if (date.year > 0)
    {
      if (date.month >= 1 && date.month <= 12)
      {
        switch (date.month)
        {
        case 1:
        case 3:
        case 5:
        case 7: 
        case 8:
        case 10:
        case 12:
          if (date.day < 1 || date.day > 31)
          {
            int newDay;
            cout << "Invalid date. Please enter a valid date (dd): ";
            cin >> buf;
            newDay = stoi(buf.c_str());
            date.day = newDay;
          }
          else 
          {
            flag = false;
          }
          break;
        case 4:
        case 6:
        case 9:
        case 11:
          if (date.day < 1 || date.day > 30)
          {
            int newDay;
            cout << "Invalid date. Please enter a valid date (dd): ";
            cin >> buf;
            newDay = stoi(buf.c_str());
            date.day = newDay;
          }
          else 
          {
            flag = false;
          }
          break;
        default:
          if (date.day < 1 || date.day > 28)
          {
            int newDay;
            cout << "Invalid date. Please enter a valid date (dd): ";
            cin >> buf;
            newDay = stoi(buf.c_str());
            date.day = newDay;
          }
          else
          {
            flag = false;
          }
          break;
        }
      }
      else
      {
        int newMonth;
        cout << "Invalid month. Please enter a valid month (mm): ";
        cin >> buf;
        newMonth = stoi(buf.c_str());
        date.month = newMonth;
      }
    }
    else
    {
      int newYear;
      cout << "Invalid year. Please enter a valid year (yyyy): ";
      cin >> buf;
      newYear = stoi(buf.c_str());
      date.year = newYear;
    }
  }
  return date;
}


string convertMonth(const int& month)
{
  switch (month)
  {
  case 1:
    return "January";
  case 2:
    return "February";
  case 3:
    return "March";
  case 4:
    return "April";
  case 5:
    return "May";
  case 6:
    return "June";
  case 7:
    return "July";
  case 8:
    return "August";
  case 9:
    return "September";
  case 10:
    return "October";
  case 11:
    return "November";
  case 12:
    return "December";
  default:
    return "0";
  }
}