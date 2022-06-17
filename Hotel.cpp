#include <iostream>
#include <cstring>
#include <string>
using namespace std;
//creating Date structure
struct Date{
    int day;
    int month;
    int year;
};
//creating Room structure
struct Room{
    int num;
    string address;
    string type;
    double price;
    string *options;
    Date start_date;
    Date end_date;
};
//creating Client structure
struct Client{
    int ID;
    string firstName;
    string lastName;
    string password;
    string address;
    string tel;
    Room *r;
};
int main()
{



































    return 0;
}
