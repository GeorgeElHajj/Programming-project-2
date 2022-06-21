#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cstring>
#include "sha1.hpp"
using namespace std;
// function for password verification
bool Passwordverification(string password)
{
    bool Length=true;
    int Letters = 0, Numbers = 0, SpecialCharacters = 0;
    if (password.length() >= 8)
        Length = true;
    for (int i = 0; i < password.length(); i++)
    {
        if (password[i] >= 65 && password[i] <= 90 || password[i] >= 97 && password[i] <= 122)
            Letters++;
        else
            if (password[i] >= 48 && password[i] <= 57)
                Numbers++;
            else
                if (password[i] >= 33 && password[i] <= 47 || password[i] >= 58 && password[i] <= 64 || password[i] >= 91 && password[i] <= 96 || password[i] >= 123 && password[i] <= 126)
                    SpecialCharacters++;
    }
    if (Length == true && Letters > 0 && Numbers > 0 && SpecialCharacters > 0)
    {
        return true;
    }
    return false;
}
// function for Email format verification
bool Emailverification(string email)
{
    int length = email.length();
    bool Exist = true; // to verify that '@' and '.' are in the email format
    bool Position = true; // '@' should be before '.'
    bool Dotposition = true; // '.' should not be the last character
    int At = 0, Dot = 0;
    for (int i = 0; i < length; i++)
    {
        if (email[i] == '@')
            At++;
        if (email[i] == '.')
            Dot++;
    }
    if ( Dot >= 1 && At == 1 )
        Exist = true;
        else 
        Exist = false;
        if(Dot>1)
        {
            int dotpos=0;
            dotpos=email.find(".");
            string email1=email.substr(dotpos+1,length-1);
             if (email1.find("@") < email1.find("."))
            Position = true;
             else 
                 Position = false;
        }
        if(Dot==1){
            if (email.find("@") < email.find("."))
            Position = true;
            else 
            Position = false;
        }
    if (email[length - 1] == '.')
        Dotposition = false;
        else
        Dotposition = true;
    if (Exist == true && Position == true && Dotposition == true)
        return true;
    

    return false;
}
bool PhoneNumberverification(string phonenumber)
{
    int length = phonenumber.length();
    bool length9 = true;
    bool thirdchar = true;
    int numbers = 0;
    if (length == 9)
        length9 = true;
        else 
        length9 = false;
    if (phonenumber[2] == '-')
        thirdchar = true;
        else 
        thirdchar = false;
    for (int i = 0; i < length; i++)
    {
        if (phonenumber[i] >= 48 && phonenumber[i] <= 57)
            numbers++;
    }
    if (length9 == true && thirdchar == true && numbers == 8)
        return true;
    else
        return false;
}
//creating Date structure
struct Date {
    int day;
    int month;
    int year;
};
//creating Room structure
struct Room {
    int num;
    string address;
    string type;
    double price;
    string* options;
    Date start_date;
    Date end_date;
};
//creating Client structure
struct Client {
    int ID;
    string firstName;
    string lastName;
    string password;
    string address;
    string tel;
    Room *r;
};
//Number of clients
int NumofUsers(fstream &f){
    int Num;
    while(f)
    {
        Num++;
        f.ignore();
    }
    return Num;
}
//Client info
void UserInfo(fstream& f)
{
    string Firstname, Lastname, Password, EmailAddress, Phonenumber;
    int ID;
    Client client;
     int Id=1;
        cout << "Please fill the following questions:\n";
         cout << "Your ID is:" << Id << endl;
             f << Id<<",";
             client.ID=Id;

        cout << "Enter the first name:" << endl;
        getline(cin, Firstname);
        f << Firstname << ",";
        client.firstName=Firstname;

        cout << "Enter the last name:" << endl;
        getline(cin, Lastname);
        f << Lastname << ",";
        client.lastName=Lastname;

        cout << "Enter a password(its length must be at least 8, while containing numbers, letters, and special characters('!','@','#','$')):" << endl;
        do
        {
            getline(cin, Password);
            if (Passwordverification(Password) == false) {
                cout << "Weak Password." << endl;
                cout << "Password must contain:" << endl;
                cout << "1.At least 8 characters.\n 2.Numbers(0-->9),Letters(a-->z or A-->Z) and SpecialCharacters('!','@','#','$',...) \n";
            }
            }while (Passwordverification(Password) == false);
            SHA1 checksum;
            checksum.update(Password);
            const string hash = checksum.final();



            f << hash << ",";
            
            client.password=Password;

            cout << "Enter an Email:" << endl;
            do {
                getline(cin, EmailAddress);
                if (Emailverification(EmailAddress) == false)
                    cout << "Invalid Email.Please verify the email format(ex:example123@gmail.com" << endl;
            } while (Emailverification(EmailAddress) == false);
            f << EmailAddress << ",";
            client.address=EmailAddress;

            cout << "Enter a Phone number(Format:00-000000):" << endl;
            do {
                getline(cin, Phonenumber);
                if (PhoneNumberverification(Phonenumber) == false)
                    cout << "Invalid Phone number.Please verify the Phone number format(ex:00-000000" << endl;
            } while (PhoneNumberverification(Phonenumber) == false);
            f << Phonenumber << "\n";
            client.tel=Phonenumber;
}
//Log in
void Login(fstream& f,string Email,string Pass)
{       string Firstname, Lastname, Password, EmailAddress, Phonenumber;
        int ID;
        int size=NumofUsers(f);
        Client *p= new Client[size];
          int c=0;
        while(f)
        {   
            f>>ID;
            getline(f,Firstname,',');
            getline(f,Lastname,',');
            getline(f,Password,',');
            getline(f,EmailAddress,',');
            getline(f,Phonenumber,',');
            client.ID=ID;
            client.firstName=Firstname;
            client.lastName=Lastname;
            client.password=Password;
            client.address=EmailAddress;
            client.tel=Phonenumber;
            if( client.password==Password && client.address==EmailAddress )
                    c=1;
        f.ignore();







}
  
    int main()
    {
        //creating csv files
        fstream  Room("Room.csv", ios::in | ios::out | ios::app);
        fstream Client("Client.csv", ios::in | ios::out | ios::app);
        fstream Reservation("Reservation.csv", ios::in | ios::out | ios::app);
        char answer;
        string Email,Pass;
        cout << "Are you a new User (y/n):\n";
    do {
        cin >> answer;
        if ( answer != 'y' && answer != 'Y' && answer != 'N' && answer != 'n')
            cout << "Please answer correctly by 'y' or 'n':\n";
         } while (answer != 'y' && answer != 'Y' && answer != 'N' && answer != 'n');
    cin.ignore();
    if (answer == 'y' || answer == 'Y')
         UserInfo(Client);
    else
    {   
        cout<<"Log in :"<<endl;
        cout<<"Enter your E-mail adress:\n";
            getline(cin,Email);
        cout<<"Enter your Password:\n";
            getline(cin,Pass);
        Login(Client,Email, Pass);

    }



        




























        return 0;
    }
