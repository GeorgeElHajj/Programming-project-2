#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cstring>
#include<cstdlib>
#include<ctime>
#include "sha1.hpp"
//#include "aspose.cells.h";
using namespace std;
// function for password verification
bool Passwordverification(string password)
{
    bool Length=true;
    int Letters = 0, Numbers = 0, SpecialCharacters = 0;
    if (password.length() >= 8)
        Length = true;
        else
        Length=false;
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
//ID Genreator
int IdGenerator()
{
    srand(time(0));
    int id = 1 + rand() % 1000;//generates number between 1 and 1000
    return id;
}
//ID check
bool UniqueID(int id)
{
    int check;
    int counter=0;
    string s;
    fstream f;
    f.open("Client.csv",ios::in);
    while (f)
    {
        f >> check;
        f.ignore();
        getline(f,s,'\n');
    if (check == id)
        counter++;
    }
    f.close();
    if(counter==1)
        return false;
        else 
        return true;
}
//Number of clients
int NumofUsers(fstream &f){
    int Num=-1;
    int ID;
    string Firstname, Lastname, Password, EmailAddress, Phonenumber;
    while(f)
    {
        
            getline(f,Firstname,',');
            getline(f,Lastname,',');
            getline(f,Password,',');
            getline(f,EmailAddress,',');
            getline(f,Phonenumber,'\n');
            f.ignore();
            Num++;
    }
    f.close();
    return Num;
}
//Number of rooms
int NumofRooms(fstream &f){
int count=-1;
int Numr;
string add,type;

while(f)
{
    getline(f,add,',');
    getline(f,type,'\n');
    f.ignore();
    count++;
}
f.close();
return count;
}
//Client info
void UserInfo(fstream& f)
{
    string Firstname, Lastname, Password, EmailAddress, Phonenumber;
    int ID;
    Client client;
     do{
         ID=IdGenerator();
        }while(UniqueID(ID)==false);
        cout<< "Please fill the following questions:\n";
         cout << "Your ID is:" << ID << endl;
             f <<ID<<",";
             client.ID=ID;

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
//Copy file to client structure
void Copy(fstream &f,int n,string address)
{ 
       bool exist=true;
   int size=NumofRooms(f);
       Room *room = new Room[size];
        int i=0;
         ifstream file;
    file.open("Room.csv");
while(file.good())
{
            file>>room[i].num;
            file.ignore();
            getline(file,room[i].address,',');
            getline(file,room[i].type,'\n');
            file.ignore();
            i++;
}
        for(int j=0;j<size;j++)
        {
            if(room[j].num==n && room[j].address==address)
           {
             exist=true;
            break;
           }
           else
           exist=false;
        }
        if(exist==true)
        cout<<",";
        else
       cout<<";;;;";
}
//Log in
bool Login(fstream& f,string Email,string Pass)
{ 
       int counter=0;
    int size=NumofUsers(f);
        Client *client = new Client[size];
        int i=0;
     ifstream file;
    file.open("Client.csv");
while(file.good())
{
            file>> client[i].ID;
            file.ignore();
            getline(file,client[i].firstName,',');
            getline(file,client[i].lastName,',');
            getline(file,client[i].password,',');
            getline(file,client[i].address,',');
            getline(file,client[i].tel,'\n');
            i++;
}
 SHA1 checksum;
            checksum.update(Pass);
            const string hash = checksum.final();
for(int j=0;j<size;j++)
{   
    if( Email==client[j].address && hash==client[j].password)
       counter++;
}
if(counter==1)
    return true;
else 
    return false;
}
// Room check
bool Roomcheck(fstream& f,int n,string address)
{  bool exist=true;
   int size=NumofRooms(f);
       Room *room = new Room[size];
        int i=0;
         ifstream file;
    file.open("Room.csv");
while(file.good())
{
            file>>room[i].num;
            file.ignore();
            getline(file,room[i].address,',');
            getline(file,room[i].type,'\n');
            file.ignore();
            i++;
}
file.close();
        for(int j=0;j<size;j++)
        {
            if(room[j].num==n && room[j].address==address)
           {
             exist=true;
            break;
           }
           else
           exist=false;
        }
        if(exist==true)
        return true;
        else
        return false;
}
//ADD Room
void AddRoom(fstream &f)
{   Room r;
     cout<<"Enter the Room number and the address:\n";
        cout<<"Room:\n";
        cin>>r.num;
        cin.ignore();
        cout<<"Address:\n";
        getline(cin,r.address);
   if(Roomcheck(f ,r.num,r.address)==true)
    {
        cout<<"The room already exist.\nPlease try again\n";
        return;
    }
    ofstream file;
    file.open("Room.csv",ios::out|ios::app);
     file<<r.num<<",";
     file<<r.address<<",";
    cout<<"Enter the room type:\n";
    getline(cin,r.type);
    file<<r.type<<",";
    cout<<"Enter the room price:\n";
    cin>>r.price;
    char answer;
    cout<<"Do you want to add additional features(ex:free Wifi - free cancellation)(y/n):\n";
    do {
        cin >> answer;
        if ( answer != 'y' && answer != 'Y' && answer != 'N' && answer != 'n')
            cout << "Please answer correctly by 'y' or 'n':\n";
         } while (answer != 'y' && answer != 'Y' && answer != 'N' && answer != 'n');
    cin.ignore();
    if (answer == 'y' || answer == 'Y') 
        { 
        file<<r.price<<"$"<<",";
        int features;
        cout<<"Enter how many features you want to add:\n";
        cin>>features;
        cin.ignore();
        r.options = new string[features];
        for(int i=0;i<features-1;i++)
        {
            cout<<"feature "<<i+1<<endl;
            getline(cin,r.options[i]);
            file<<r.options[i]<<",";
        }
        cout<<"The last feature:\n";
        getline(cin,r.options[features-1]);
        file<<r.options[features-1]<<"\n";
        }
    else
    {
    file<<r.price<<"$"<<"\n";
         file.close();
    }
    cout<<"Enter the starting date(day-month-year)\n";
do{
    cout<<"Day:"<<endl;
    cin>>r.start_date.day;
    if(r.start_date.day < 0 || r.start_date.day > 31 )
    cout<<"Please enter a correct day.\n";
}while(r.start_date.day < 0 || r.start_date.day > 31 );
do{
    cout<<"Month:"<<endl;
    cin>>r.start_date.month;
    if(r.start_date.month < 0 || r.start_date.month > 31 )
    cout<<"Please enter a correct month.\n";
}while(r.start_date.month < 0 || r.start_date.month > 12 );
do{
    cout<<"year:"<<endl;
    cin>>r.start_date.year;
    if(r.start_date.year >= 2022 )
    cout<<"Please enter a correct year.\n";
}while(r.start_date.year >= 2022 );
cout<<"Enter the ending date(day-month-year)\n";
do{
    cout<<"Day:"<<endl;
    cin>>r.end_date.day;
    if(r.end_date.day < 0 || r.end_date.day > 31 )
    cout<<"Please enter a correct day.\n";
}while(r.end_date.day < 0 || r.end_date.day > 31 );
do{
    cout<<"Month:"<<endl;
    cin>>r.start_date.month;
    if(r.end_date.month < 0 || r.end_date.month > 31 )
    cout<<"Please enter a correct month.\n";
}while(r.end_date.month < 0 || r.end_date.month > 12 );
do{
    cout<<"year:"<<endl;
    cin>>r.end_date.year;
    if(r.end_date.year >= 2022 )
    cout<<"Please enter a correct year.\n";
}while(r.end_date.year >= 2022 );
fstream check;
check.open("info.csv",ios::out|ios :: app);
check<<r.num<<","<<r.address<<","<<r.start_date.day<<","<<r.start_date.month<<","<<r.start_date.year<<","<<r.end_date.day<<","<<r.end_date.month<<","<<r.end_date.year<<"\n";
check.close();
}
//Delete Room
void DeleteRoom()
{
    fstream f;
    fstream froom;
    int number;
    int numR;
    string add;
    string address,type;
    double price;
    string options;
    cout<<"Enter the number of the room you want to delete:\n";
    cin>>number;
    cin.ignore();
    cout<<"Enter the address of the room you want to delete:\n";
    getline(cin,add);
    f.open("Room.csv",ios::in);
    froom.open("froom.csv",ios::out);
    while(f)
    {  
         address=" ";
         options=" ";
        f>>numR;
        f.ignore();
        getline(f,address,',');
        getline(f,type,',');
        f>>price;
        f.ignore();
        getline(f,options,'\n');
        if(numR ==number && address ==add)
            continue;
            else
            froom<<numR<<","<<address<<","<<type<<","<<price<<"$"<<","<<options<<"\n";
    }
    f.close();
    froom.close();
    froom.open("froom.csv",ios::in);
    f.open("Room.csv",ios::out|ios::app);
    while(froom)
    {
         address=" "; 
         options=" ";
        froom>>numR;
        froom.ignore();
        getline(froom,address,',');
        getline(froom,type,',');
        froom>>price;
        froom.ignore();
        getline(froom,options,'\n');
        if(address != " " && options != " ")
            f<<numR<<","<<address<<","<<type<<","<<price<<"$"<<","<<options<<"\n";
        else if(address != " " && options == " ")
            f<<numR<<","<<address<<","<<type<<","<<price<<"$"<<"\n";
    }
    froom.close();
    f.close();
    remove("froom.csv");
}
//Modify Room
void ModifyRoom()
{
    int number;
    char choice;
    string add;
    fstream f,froom;
    int numR;
    string address,type;
    double price;
    string Options;
     cout<<"Enter the number of the room you want to modify:\n";
     cin>>number;
     cin.ignore();
     cout<<"Enter the address of the room you want to nodify:\n";
     getline(cin,add);
     cout<<"Choose the mofidification that you want:\n1.Price\n2.Options\n3.Both\n";
         do{   cout<<"Choice:\n";
            cin>>choice;
            if(choice != '1' && choice != '2' && choice != '3')
            cout<<"Please choose correctly the modification you want to make\n";
          }while(choice != '1' && choice != '2' && choice != '3');
    if( choice == '1')
    {   int nprice;
        cout<<"Enter the new price:\n";
        cin>>nprice;
        f.open("Room.csv",ios::in);
        froom.open("froom.csv",ios::out);
        while(f)
    {   address=" ";
        f>>numR;
        f.ignore();
        getline(f,address,',');
        getline(f,type,',');
        f>>price;
        f.ignore();
        getline(f,Options,'\n');
        if(numR ==number && address ==add)
           { froom<<numR<<","<<address<<","<<type<<","<<nprice<<"$"<<","<<Options<<"\n";
           continue;
           }
            else if(address != " ")
            froom<<numR<<","<<address<<","<<type<<","<<price<<"$"<<","<<Options<<"\n";
    }
    f.close();
    froom.close();
    froom.open("froom.csv",ios::in);
    f.open("Room.csv",ios::out);
    while(froom)
    {
         address=" "; 
        froom>>numR;
        froom.ignore();
        getline(froom,address,',');
        getline(froom,type,',');
        froom>>price;
        froom.ignore();
        getline(froom,Options,'\n');
        if(address != " " )
            f<<numR<<","<<address<<","<<type<<","<<price<<"$"<<","<<Options<<"\n";
    }
    froom.close();
    f.close();
    remove("froom.csv");
    }
    else if( choice == '2')
    {
        int Opnum;
        cout<<"You have to add the options(Old+New):\n";
        cout<<"How many options do you want to add:\nIf you want to remove the options press 0.\n ";
        cin>>Opnum;
        cin.ignore();
        string *Option = new string[Opnum];
        string Opt;
        for(int i=0;i<Opnum;i++)
        {
            cout<<"Enter option"<< i+1<<":\n";
            getline(cin,Option[i]); 
        }
        for(int i=0;i<Opnum-1;i++)
        {
            Opt += (Option[i] + ",");
        }
        Opt += Option[Opnum-1];
        f.open("Room.csv",ios::in);
        froom.open("froom.csv",ios::out);
        while(f)
    {   address=" ";
        f>>numR;
        f.ignore();
        getline(f,address,',');
        getline(f,type,',');
        f>>price;
        f.ignore();
        getline(f,Options,'\n');
        if(numR ==number && address ==add)
            {
                if(Opt != " ")
           froom<<numR<<","<<address<<","<<type<<","<<price<<"$"<<","<<Opt<<"\n";
           else
            froom<<numR<<","<<address<<","<<type<<","<<price<<"$"<<"\n";
            }
            else
            froom<<numR<<","<<address<<","<<type<<","<<price<<"$"<<","<<Options<<"\n";
    }
    f.close();
    froom.close();
    froom.open("froom.csv",ios::in);
    f.open("Room.csv",ios::out);
    while(froom)
    {
         address=" "; 
        froom>>numR;
        froom.ignore();
        getline(froom,address,',');
        getline(froom,type,',');
        froom>>price;
        froom.ignore();
        getline(froom,Options,'\n');
        if(address != " " )
            f<<numR<<","<<address<<","<<type<<","<<price<<"$"<<","<<Options<<"\n";
    }
    froom.close();
    f.close();
    remove("froom.csv");
            }
    else
        {
        int Nprice;
        cout<<"Enter the new price:\n";
        cin>> Nprice;
        cin.ignore();
        int Opnum;
        cout<<"You have to add the options(Old+New):\n";
        cout<<"How many options do you want to add:\nIf you want to remove the options press 0.\n ";
        cin>>Opnum;
        cin.ignore();
        string *Option = new string[Opnum];
        string Opt;
        for(int i=0;i<Opnum;i++)
        {
            cout<<"Enter option"<< i+1<<":\n";
            getline(cin,Option[i]); 
        }
        for(int i=0;i<Opnum-1;i++)
        {
            Opt += (Option[i] + ",");
        }
        Opt += Option[Opnum-1];
        f.open("Room.csv",ios::in);
        froom.open("froom.csv",ios::out);
        while(f)
    {   address=" ";
        f>>numR;
        f.ignore();
        getline(f,address,',');
        getline(f,type,',');
        f>>price;
        f.ignore();
        getline(f,Options,'\n');
        if(numR ==number && address ==add)
            {
                if(Opt != " ")
           froom<<numR<<","<<address<<","<<type<<","<<Nprice<<"$"<<","<<Opt<<"\n";
           else
            froom<<numR<<","<<address<<","<<type<<","<<Nprice<<"$"<<"\n";
            }
            else
            froom<<numR<<","<<address<<","<<type<<","<<price<<"$"<<","<<Options<<"\n";
    }
    f.close();
    froom.close();
    froom.open("froom.csv",ios::in);
    f.open("Room.csv",ios::out);
    while(froom)
    {
         address=" "; 
        froom>>numR;
        froom.ignore();
        getline(froom,address,',');
        getline(froom,type,',');
        froom>>price;
        froom.ignore();
        getline(froom,Options,'\n');
        if(address != " " )
            f<<numR<<","<<address<<","<<type<<","<<price<<"$"<<","<<Options<<"\n";
    }
    froom.close();
    f.close();
    remove("froom.csv");
        }
}
//Administrator
void Admin(fstream &f)
{   char task;
        cout<<"Hello Admin:\n";
        cout<<"Pick the task you want to make:\n";
        cout<<"1.Add rooms.\n2.Delete rooms.\n3.Modify the data of a room.\n";
        do{ cout<<"Task:\n";
            cin>>task;
            if(task != '1' && task != '2' && task != '3')
            cout<<"Please choose correctly the task you want to make\n";
          }while(task != '1' && task != '2' && task != '3');
            if(task == '1')
                AddRoom(f);
            else if(task == '2')
                DeleteRoom();
            else   
                ModifyRoom();

}
//Room Reservation
void RoomReservation(string firstname,string lastname)
{  
    Date start,end;
    int Rnum;
    string address;
    int sday,smonth,syear,eday,emonth,eyear;
    cout<<"Welcome to the Reservation page:\n ";
do{
    cout<<"Day:"<<endl;
    cin>>start.day;
    if(start.day < 0 || start.day > 31 )
    cout<<"Please enter a correct day.\n";
}while(start.day < 0 || start.day > 31 );
do{
    cout<<"Month:"<<endl;
    cin>>start.month;
    if(start.month < 0 || start.month > 31 )
    cout<<"Please enter a correct month.\n";
}while(start.month < 0 || start.month > 12 );
do{
    cout<<"year:"<<endl;
    cin>>start.year;
    if(start.year >= 2022 )
    cout<<"Please enter a correct year.\n";
}while(start.year >= 2022 );
cout<<"Enter the ending date(day-month-year)\n";
do{
    cout<<"Day:"<<endl;
    cin>>end.day;
    if(end.day < 0 || end.day > 31 )
    cout<<"Please enter a correct day.\n";
}while(end.day < 0 || end.day > 31 );
do{
    cout<<"Month:"<<endl;
    cin>>end.month;
    if(end.month < 0 || end.month > 31 )
    cout<<"Please enter a correct month.\n";
}while(end.month < 0 || end.month > 12 );
do{
    cout<<"year:"<<endl;
    cin>>end.year;
    if(end.year >= 2022 )
    cout<<"Please enter a correct year.\n";
}while(end.year >= 2022 );
fstream check;
check.open("info.csv",ios::in);
int size=NumofRooms(check);
int *room = new int[size];
int i=0;
while(check)
{
    check>>Rnum;
    check.ignore();
    getline(check,address,',');
    check>>sday;
    check>>smonth;
    check>>syear;
    check>>eday;
    check>>emonth;
    check>>eyear;
    check.ignore();
    if(start.day >= sday && start.month >= smonth && start.year >= syear && end.day <=eday && end.month <= emonth && end.year <= eyear )
        {
            room[i]=Rnum;
            i++;
        }
}
check.close();
int numR;
    string add;
    string ADDRESS,type;
    double price;
    string options;
cout<<"The rooms You can reserve are:\n";
fstream f;
f.open("Room.csv",ios::in);
for(int j=0;j<size;j++)
{
    while(f)
    {
        address=" ";
         options=" ";
        f>>numR;
        f.ignore();
        getline(f,ADDRESS,',');
        getline(f,type,',');
        f>>price;
        f.ignore();
        getline(f,options,'\n');
        if(numR==room[j])
        cout<<numR<<"\t"<<address<<"\t"<<type<<"\t"<<price<<"$\t"<<options<<"\n";
        else
        continue;
    }
}
    f.close();
    int num;
    cout<<"How many rooms you want to reserve:\n";
    cin>>num;
    cin.ignore();
    int *Roomnum = new int[num];
    for(int i=0;i<num;i++)
    {
        cout<<"Enter tne number of the room "<<i+1<<" :";
        cin>>Roomnum[i];
    }
    int numRoom;
    string Address,Type;
    double Price;
    string Options;
    fstream Reservation;
    Reservation.open("Reservation.csv",ios::out|ios::app);
    f.open("Room.csv",ios::in);
    for(int j=0;j<num;j++)
    {
    while(f)
    {
         Address=" ";
         Options=" ";
        f>>numRoom;
        f.ignore();
        getline(f,Address,',');
        getline(f,Type,',');
        f>>Price;
        f.ignore();
         getline(f,Options,'\n');
        if(numRoom==Roomnum[j])
        Reservation<<numR<<","<<firstname<<","<<lastname<<","<<start.day<<"-"<<start.month<<"-"<<start.year<<","<<end.day<<"-"<<end.month<<"-"<<end.year<<"\n";
    }
    }
    f.close();
    Reservation.close();
}
//Cancellation
void Cancellation(string first,string last)
{   int Rnum;
    char answer;
    cout<<"Please enter the number of the room you want to cancel it's reservation:\n";
    cin>>Rnum;
    cin.ignore();
cout<<"Does your room come with additional options (y/n):\n";
 do {
        cin >> answer;
        if ( answer != 'y' && answer != 'Y' && answer != 'N' && answer != 'n')
            cout << "Please answer correctly by 'y' or 'n':\n";
    } while (answer != 'y' && answer != 'Y' && answer != 'N' && answer != 'n');
cin.ignore();
    if (answer == 'y' || answer == 'Y')
    {   int features;
        int counter=0;
        cout<<"How many features:\n";
        cin>>features;
        string *Features= new string[features];
        for(int i=0;i<features;i++)
        {
            cout<<"Enter feature "<<i+1<<" :\n";
            getline(cin,Features[i]);
            if(Features[i]=="free cancellation"||Features[i]=="Free cancellation")
            counter++;
        }
        if(counter==1)
        {cout<<"Your cancellation is done.No additional fees.\n";
        fstream reserv;
        reserv.open("Reservation.csv",ios::in);
        fstream temp;
        temp.open("temp.csv", ios::out);
        int num;
        string fn,ln;
        string start;
        string end;
        while (reserv)
        {
        fn = " ";
        ln = " ";
        reserv >> num;
        reserv.ignore();
        getline(reserv, fn, ',');
        getline(reserv, ln, ',');
        getline(reserv, start, ',');
        getline(reserv,end,'\n');
        if (Rnum == num && fn == first && ln == last)
            continue;
        else
            temp<< num << "," << fn << "," << ln << "," << start<<","<< end << "\n";
        }
        reserv.close();
        temp.close();
        temp.open("temp.csv", ios::in);
        reserv.open("Reservation.csv", ios::out|ios::app);

         while (temp)
        {
        fn = " ";
        ln = " ";
        temp >> num;
        temp.ignore();
        getline(temp, fn, ',');
        getline(temp, ln, ',');
        getline(temp,first, ',');
        getline(temp,last,'\n');
        if (fn != " " )
        reserv<< num << "," << fn << "," << ln << "," <<start<<","<< end << "\n";
        }
        temp.close();
        reserv.close();
        remove("temp.csv");
    }
    else
    cout<<"You can not cancel your reservation.\n";
    }
    else
    cout<<"You can not cancel your reservation.\n";
}
//PDF
void PDF(string first,string last)
{
    fstream file,froom;
    file.open("Reservations.csv",ios::in|ios::out|ios::app);
    int num;
    string fname,lname,start,end;
    int *roomnum = new int[NumofRooms(file)];
    int i=0;
    while(file)
    {
        fname=" ";
        file>>num;
        file.ignore();
        getline(file,fname,',');
        getline(file,lname,',');
        getline(file,start,',');
        getline(file,end,'\n');
        file.ignore();
        if(fname==first && lname==last)
        {
            roomnum[i]=num;
            i++;
        }
    }
    file.close();
        froom.open("Room.csv",ios::in|ios::out|ios::app);
int numR;
    string add;
    string address,type;
    double price;
    string options;
    double *Price = new double[i];
    for(int j=0;j<i;j++)
    {
    while(froom)
    {  
         address=" ";
         options=" ";
         froom>>numR;
        froom.ignore();
        getline(froom,address,',');
        getline(froom,type,',');
        froom>>price;
        froom.ignore();
        getline(froom,options,'\n');
        if(roomnum[j]==numR)
      Price[j]=price; 
    }
    }
    froom.close();
    double sum=0;
    double totalbill=0;
    for(int k=0;k<i;k++)
    {
        sum+=Price[k];
    }
    totalbill=sum+(sum*0.11);
    //Sort price
    for(int a=0;a<i;a++)
    {
        for(int b=a+1;b<i;b++)
        {
            if(Price[a]> Price[b])
            {
                double  PRICE = Price[a];
                Price[a]= Price[b];
                Price[b]= PRICE;
                int room=roomnum[a];
                roomnum[a]=roomnum[b];
                roomnum[b]=room;
            }
        }
    }
    fstream Invoice;
    Invoice.open("Invoice.csv",ios::in|ios::out|ios::app);
    for(int k=0;k<i;k++)
    {
        Invoice<<roomnum[k]<<","<<first<<","<<last<<","<<Price[k]<<"$"<<"\n";
    }
    Invoice<<"Bill without tax:"<<","<<sum<<"$"<<"\n";
    Invoice<<"Bill with tax(11%):"<<","<<totalbill<<"$"<<"\n";
    Invoice.close();
 /*   // Source directory path.
StringPtr srcDir = new String("SourceDirectory\\");

// Output directory path.
StringPtr outDir = new String("OutputDirectory\\");

// Create CSV LoadOptions object
intrusive_ptr<ILoadOptions> loadOptions = Factory::CreateILoadOptions(LoadFormat_CSV);

// Load the input Excel file
intrusive_ptr<IWorkbook> workbook = Factory::CreateIWorkbook(srcDir->StringAppend(new String("Sample1.csv")), loadOptions);

// Save as PDF file
workbook->Save(outDir->StringAppend(new String("Sample1_out.pdf")), SaveFormat_Pdf);
}*/
}
    int main()
    {
        //creating csv files
        fstream Clients("Client.csv", ios:: in | ios::out | ios::app);
        fstream  Room("Room.csv", ios:: in | ios::out | ios::app);
        fstream Reservation("Reservation.csv", ios:: in | ios::out | ios::app);
        char answer;
        string Email,Pass;
        string first,last;
       cout << "Are you a new User (y/n):\n";
        do {
        cin >> answer;
        if ( answer != 'y' && answer != 'Y' && answer != 'N' && answer != 'n')
            cout << "Please answer correctly by 'y' or 'n':\n";
         } while (answer != 'y' && answer != 'Y' && answer != 'N' && answer != 'n');
    cin.ignore();
    if (answer == 'y' || answer == 'Y')
     UserInfo(Clients);
    else
    {   
        cout<<"Sign in :"<<endl;
         cout<<"Enter your E-mail adress:\n";
            getline(cin,Email);
        cout<<"Enter your Password:\n";
            getline(cin,Pass);
        if(Login(Clients,Email,Pass)==true)
        cout<<"Welcome back!!!"<<endl;
       else
        cout<<"Invalid Email Or password.\nTry again\n";

    }
      if(Email=="admin@gmail.com")
        {
            Admin(Room);
        }
        else
        {   char Option;
            cout<<"Hello Client:\n";
            cout<<"Choose what option you want:\n";
            cout<<"1.Make a Reservation.\n2.Cancel a Reservation.";
            do{ 
                cout<<"Option:\n";
                cin>>Option;
                cin.ignore();
            if(Option != '1' && Option != '2' )
            cout<<"Please choose correctly the Option. \n";
             }while(Option != '1' && Option != '2' );
                if(Option == '1'){
                    cout<<"Enter your first name:\n";
                getline(cin,first);
                cout<<"Enter your last name:\n";
                getline(cin,last);
                RoomReservation(first,last);
                }
                else
                {
                    cout<<"Enter your first name:\n";
                    getline(cin,first);
                    cout<<"Enter your last name:\n";
                    getline(cin,last);
                    Cancellation(first,last);
                }
        Clients.close();
        Room.close();
        Reservation.close();
        }
     return 0;
    }
