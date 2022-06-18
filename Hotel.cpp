#include <iostream>
#include <fstream>
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
//Client info
void ClientInfo(fstream &f)
{
string Firstname,Lastname,Password,EmailAddress,Phonenumber;
string answer;
int Id=1;
cout<<"Are you a new Client (y/n):\n";
do{
cin>>answer;
if(answer != 'y'|| answer != 'Y'|| answer !='N'|| answer !='n')
cout<<"Please answer correctly by 'y' or 'n'\n";
}while(answer != 'y'|| answer != 'Y' || answer != 'N'|| answer != 'n' );

if(answer =='y'|| answer =='Y')
{ 
  cout<<"Please fill the following questions:\n";
  cout<<"Your ID is:"<<Id<<endl;
   f<<Id<<",";

   cout<<"Enter the first name:"<<endl;
   getline(cin,Firstname);
   f<<Firstname<<",";

   cout<<"Enter the last name:"<<endl;
   getline(cin,Lastname);
   f<<Lastname<<",";

    cout<<"Enter a password(its length must be at least 8, while containing 
numbers, letters, and special characters)"<<endl;
   getline(cin,password);
   f<<Lastname<<",";








}








}
int main()
{ //creating csv files
    fstream  Room("Room.csv" , ios::in | ios:: out | ios::app);
    fstream Client("Client.csv" , ios::in | ios:: out | ios::app);
    fstream Reservation("Reservation.csv" , ios::in | ios:: out | ios::app);





































    return 0;
}
