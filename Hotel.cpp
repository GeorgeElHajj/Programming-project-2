#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cstring>
#include "md5.h"
using namespace std;
// function for password verification
bool Passwordverification(string password)
{
bool length;
int Letters=0,Numbers=0,SpecialCharacters=0;
if(password.length() >= 8)
 length=true;
for(int i=0;i<password.length();i++)
{
if( password[i]>=65 && password[i]<=90 || password[i]>=97 && password[i]<=122)
Letters++;
else 
if(password[i]>=48 && password[i]<=57)
Numbers++;
else 
if(password[i]>=33 && password[i]<=47 || password[i]>=58 && password[i]<=64 || password[i]>=91 && password[i]<=96||password[i]>=123 && password[i]<=126)
SpecialCharacters++;
}
if(length==true && Letters > 0 && Numbers > 0 && SpecialCharacters > 0)
{
    return true;
}
return false;
}
// function for Email format verification
bool Emailverification(string email)
{
int length=email.length();
bool Exist=true; // to verify that '@' and '.' are in the email format
bool Position=true; // '@' should be before '.'
bool Dotposition=true; // '.' should not be the last character
int At=0,Dot=0;
for(int i=0;i<length;i++)
{
    if(email[i]=='@')
    At++;
    if(email[i]=='.')
    Dot++;
}
if(At==1 && Dot==1)
Exist=true;
if(email.find("@") < email.find("."))
Position=true;
if(email[length-1]=='.')
Dotposition==false;
if(Exist=true && Position=true && Dotposition==true)
return true;
else 
return false;
}
bool PhoneNumberverification(string phonenumber)
{
    int length=phonenumber.length();
    bool length9=true;
    bool thirdchar=true;
    int numbers=0;
    if(length==9)
    length9=true;
    if(phonenumber[2]=='-')
    thirdchar=true;
    for(int i=0;i<length;i++)
    {
        if(phonenumber[i]>=48 && phonenumber[i]<=57)
        numbers++;
    }
    if(length9=true && thirdchar=true && numbers==8)
    return true;
    else 
    return false;
}
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
if(answer != 'y'|| answer != 'Y'|| answer != 'N'|| answer != 'n')
cout<<"Please answer correctly by 'y' or 'n'\n";
}while(answer != 'y'|| answer != 'Y' || answer != 'N'|| answer != 'n' );

if(answer == 'y' || answer == 'Y')
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

    cout<<"Enter a password(its length must be at least 8, while containing numbers, letters, and special characters('!','@','#','$')):"<<endl;
   do
   {
    getline(cin,Password);
    if(Passwordverification(Password)==false){
        cout<<"Weak Password."<<endl;
        cout<<"Password must contain:"<<endl;
        cout<<"1.At least 8 characters.\n 2.Numbers(0-->9),Letters(a-->z or A-->Z) and SpecialCharacters('!','@','#','$',...) \n";
    }while(Passwordverification(Password)==false);
   f<<md5(Password)<<",";
   cout<<"Enter an Email:"<<endl;
   do{
   getline(cin,EmailAddress);
    if(Emailverification(EmailAddress)==false)
        cout<<"Invalid Email.Please verify the email format(ex:example123@gmail.com"<<endl;
   }while(Emailverification(EmailAddress)==false);
   f<<EmailAddress<<",";









}








}
int main()
{ //creating csv files
    fstream  Room("Room.csv" , ios::in | ios:: out | ios::app);
    fstream Client("Client.csv" , ios::in | ios:: out | ios::app);
    fstream Reservation("Reservation.csv" , ios::in | ios:: out | ios::app);





































    return 0;
}
