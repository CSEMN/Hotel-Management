#include <iostream>
#include <fstream>
#include <cstdlib>
#include <direct.h>
#include <string>
#include <iomanip>
#include <vector>
#include <sstream>



using namespace std;

const string guests_path= "c:\\Hotel Management\\guests data.data" ;
const string services_path= "c:\\Hotel Management\\services data.data" ;
const string purchase_path= "c:\\Hotel Management\\purchase.money" ;

class guest
{
public :
     guest()
     {

        balance = 0 ;
     }
    void set_name (string guest_name)
    {
        name = guest_name ;
    }

    string get_name ()
    {
        return name ;
    }
    void set_balance (float guest_balance)
    {
        balance = guest_balance ;
    }
    float get_balance ()
    {
        return balance ;
    }
    void set_room (float guest_room)
    {
        room = guest_room ;
    }
    float get_room ()
    {
        return room ;
    }

    void set_phone(long int phoneNum)
     {

      phone = phoneNum ;
     }
    long int get_phone()
      {return phone ;}

private:
    string name ;
    float balance ;
    int room ;
    long int phone ;
};
class service
{
public :

    void set_name (string service_name)
    {
        name = service_name ;
    }

    string get_name ()
    {
        return name ;
    }
    void set_cost (float service_cost)
    {
        cost = service_cost ;
    }
    float get_cost ()
    {
        return cost ;
    }
private:
    string name ;
    float cost ;


};

//Functions prototype...
//
//
// menu functions ...
int menu() ;

void guestList();
void addGuest();
void removeGuest();
void servicesList();
void addService();
void removeService();
void purchase();

// checking function
bool vaild_room(int);

void watermark();

int main()
{
    mkdir("c:/Hotel management");

    cout <<"===============   HOTEL MANAGEMENT   =============== "<<endl<<endl ;
    int choice;
    while(choice != 0)
        {
        choice = menu();
        switch(choice)
         {
            case 1:
                guestList();
                break;
            case 2:
                addGuest();
                break;
            case 3:
                removeGuest();
                break;
            case 4:
                servicesList();
                break;
            case 5:
                addService();
                break;
            case 6:
                removeService();
                break;
            case 7:
                purchase();
            case 0:
                break;
            default:
                cout << "Didn't recognize your input ...  try again.."<< endl;
        }

      }

      watermark() ;

    return 0;
}

int menu()
 {
     int choice;
    cout << endl ;
    cout << "-----------" << endl ;
    cout << "Main Menu !" << endl;
    cout << "-----------" << endl << endl;

    cout << "1. Display guests list" << endl;
    cout << "2. Add new guest" << endl;
    cout << "3. Remove guest form the list"<< endl;
    cout << "4. Display services list" << endl;
    cout << "5. Add new service"<<endl ;
    cout << "6. delete a service"<<endl ;
    cout << "7. To perform a purchase" << endl ;
    cout << "0. Exit the program" << endl;
    cout << endl;
    cout << "-----------------"<<endl ;
    cout << "Enter a choice: ";
    cin >> choice;
    cout << "-----------------"<<endl ;
    return choice;
}

void guestList()
{
     cout << "------------" <<endl ;
     cout << "Guest List !" << endl ;
     cout << "------------" <<endl<<endl ;
     int counter = 1 ;
    string line;

    ifstream inFile(guests_path.c_str(), ios::in);
    if(!inFile) {
        cout << "Error : can't open guests file." << endl;
        exit(1);
    }

    while (!inFile.eof())
        {
            inFile.clear();
            inFile.sync() ;
            getline(inFile, line);
            if(line.empty())
                continue;
        cout <<counter <<". "<<"Guest name : " << line << endl ;

        counter++ ;

         inFile.clear();
        inFile.sync() ;
        getline(inFile, line);
        cout <<"   "<<"Guest phone number : " << line << endl ;

        inFile.clear();
        inFile.sync() ;
        getline(inFile, line);
        cout <<"   "<<"Guest balance : " << line << " EGP"<< endl ;

        inFile.clear();
        inFile.sync() ;
        getline(inFile, line);
        cout <<"   "<<"Guest room : " << line << endl ;

        cout <<endl << endl ;

       }
    inFile.close();
    cout << endl << endl ;
}

void addGuest()
{
    cout << "-----------" <<endl ;
    cout << "New Guest !\n";
    cout << "-----------" <<endl<<endl ;
    string n ;
    guest newGuest ;
    cout << "Guest name : " ;
    cin.clear();
    cin.sync();
    getline(cin ,n ) ;
    newGuest.set_name(n) ;

    long int  ph ;
    cout << "Guest phone number : " ;
    cin.clear();
    cin.sync();
    cin >> ph ;
    newGuest.set_phone(ph) ;

    int rnum ;
    for (;;)
    {
    cout << "Guest room number : " ;
    cin.clear();
    cin.sync();
    cin >> rnum ;

        if(vaild_room(rnum))
         {
           newGuest.set_room(rnum) ;
           break ;
         }

    else continue;
    }

    fstream outFile(guests_path.c_str() , ios::app);
    if(!outFile)
    {
        cout << "Error : can't open guests file"  <<endl ;
        exit(2);
    }
    outFile << newGuest.get_name() <<endl ;
    outFile << newGuest.get_phone() <<endl ;
    outFile << newGuest.get_balance() <<endl ;
    outFile << newGuest.get_room() <<endl ;

    outFile.close();
    cout << "\nAddition Completed ! " <<endl ;
    cout <<endl << endl ;

}

void removeGuest()
{
    cout << "--------------" <<endl ;
    cout << "Remove Guest !" << endl ;
    cout << "--------------" <<endl<<endl ;
    int choice;
    guestList();
    cin.clear();
    cin.sync();
    cout << "Which Guest do you want to remove? : ";
    cin >> choice;
    vector<string> items;
    int number = 1;
    ifstream inFile(guests_path.c_str(), ios::in);
    if(!inFile) {
        cout << "Error : can't open Services file " << endl;
        exit(4);
    }
    string item;
    getline(inFile, item);
    while (!inFile.eof()) {
        if (number != choice)
        {
            for (int i=0 ; i<4;i++)
            {
            items.push_back(item);
            getline(inFile, item);
            }
        }else{
        for (int i =0 ; i<4 ; i++)
        getline(inFile, item);
        }
        ++number;
    }
    inFile.close();
    ofstream outFile(guests_path.c_str(), ios::out);
    if(!outFile) {
        cout << "Error : can't open guests file " << endl;
        exit(5);
    }
    for(int i = 0; i < items.size(); ++i)
        outFile << items[i] << endl;
    outFile.close();

    cout << "\nRemoval Completed !" << endl ;
    cout <<endl <<endl ;

}
void servicesList()
{
    int counter=1 ;
    cout << "---------------" << endl ;
    cout << "Services List !" << endl;
    cout << "---------------" << endl <<endl ;
    string line;

    ifstream inFile(services_path.c_str(), ios::in);
    if(!inFile) {
        cout << "Error : can't open Services file." << endl;
        exit(1);
    }

    while (!inFile.eof())
        {
            inFile.clear();
            inFile.sync() ;
            getline(inFile, line);
            if(line.empty())
                continue;
        cout <<counter <<". "<<"Service name : " << line << endl ;

        counter++ ;

         inFile.clear();
        inFile.sync() ;
        getline(inFile, line);
        cout <<"   "<<"Service cost : " << line  << " EGP" << endl ;

        cout <<endl << endl ;

       }
    inFile.close();
    cout << endl << endl ;
}


void addService()
{
    cout << "-------------" << endl ;
    cout << "New Service !"<< endl ;
    cout << "-------------" << endl ;
    string n ;
    service newService ;
    cout << "Service name : " ;
    cin.clear();
    cin.sync();
    getline(cin ,n ) ;
    newService.set_name(n) ;

    float cost ;
    cout<< "Service cost : " ;
    cin.clear();
    cin.sync();
    cin >> cost;
    newService.set_cost(cost) ;

    fstream outFile(services_path.c_str() , ios::app);
    if(!outFile)
    {
        cout << "Error : can't open Services file"  <<endl ;
        exit(3);
    }
    outFile << newService.get_name() <<endl ;
    outFile << newService.get_cost() <<endl ;

    outFile.close();
    cout << "\nAddition Completed !" << endl ;
    cout <<endl << endl ;
}

void removeService()
{
    cout << "----------------" << endl ;
    cout << "Remove Service !" <<endl ;
    cout << "----------------" << endl <<endl;

    int choice;
    servicesList();
    cin.clear();
    cin.sync();
    cout << "Which service do you want to remove? ";
    cin >> choice;
    vector<string> items;
    int number = 1;
    ifstream inFile(services_path.c_str(), ios::in);
    if(!inFile) {
        cout << "Error : can't open Services file" << endl;
        exit(6);
    }
    string item;
    getline(inFile, item);
    while (!inFile.eof())
        {
        if (number != choice)
        {


            for(int i =0 ; i<2 ; i++)
            {
            items.push_back(item);
            getline(inFile, item);
            }
        }
        else
        {
        for(int i =0 ; i<2 ; i++)
        getline(inFile, item);
        }
        ++number;

    }
    inFile.close();
    ofstream outFile(services_path.c_str(), ios::out);
    if(!outFile) {
        cout << "Error : can't open Services file" << endl;
        exit(7);
    }
    for(int i = 0; i < items.size(); ++i)
        outFile << items[i] << endl;
    outFile.close();
    cout <<"\nRemoval Completed !" <<endl;
    cout << endl << endl ;
}

void purchase()
{
    cout << "----------" << endl ;
    cout << "Purchase !" <<endl ;
    cout << "----------" << endl << endl ;
    int choise_1 , choise_2 ;
    guestList();
    cout << "Which guest will purchase ? : " ;
    cin >> choise_1 ;
    int counter = 1 ;
    string name ;
    fstream file(guests_path.c_str() , ios::in);
    if(!file)
    {
        cout << "Can't open Guests file" << endl ;
        exit(8);
    }
    while(!file.eof())
    {
        if(!(counter== choise_1))
        {
        for(int i =0 ; i<4 ;i++)
        getline(file, name);
        }
        else{
            getline(file, name);

            break ;
        }
        counter++ ;

    }
      file.close();
      //Getting name done ...

    servicesList();
    cout << "Which service will be purchased by " << name << " ? : " ;
    cin >> choise_2 ;


    int counter_2=1 ;
    float cost=0 ;
    fstream infile (services_path.c_str() , ios ::in);
     if(!infile)
    {
        cout << "Can't open Services file" << endl ;
        exit(9);
    }

    string item_name ;

    while(!infile.eof())
    {
        if(!(counter_2== choise_2))
        {
        for(int i =0 ; i<2 ;i++)
        getline(infile, item_name);
        }
        else{

            getline(infile, item_name);
            infile >> cost ;

            break ;
        }

        counter_2++ ;
    }
        infile.close();


        fstream infl(guests_path.c_str(), ios::in );
    if(!infl) {
        cout << "Error : can't open guests file" << endl;
        exit(10);
    }
    int counter_3 =1 ;
    vector<string> items ;
    string item;

    while (!(infl.eof()))
    {
        if (counter_3 != choise_1)
        {
            for(int i =0 ; i<4 ;i++)
            {
                getline(infl,item);

                if(item.empty())
                continue;

                items.push_back(item);
            }
        }
        else
        {
            for(int i =0 ; i<2 ;i++)
            {
                getline(infl,item);

                if(item.empty())
                continue;

                items.push_back(item);
            }

            getline(infl,item);

            float temp = ::strtod(item.c_str(), 0);
            float result= temp+cost;
            stringstream ss (stringstream::in | stringstream::out);
            ss << result;
            string test = ss.str();
            items.push_back(test);

            for(int i =0 ; i<1 ;i++)
            {
                getline(infl,item);

                if(item.empty())
                continue;

                items.push_back(item);
            }

        }

        counter_3++ ;
    }


    ofstream outFile2(guests_path.c_str(), ios::out);
    if(!outFile2) {
        cout << "Error : can't open guests file" << endl;
        exit(11);
    }
    for(int i = 0; i < items.size(); ++i)
        outFile2 << items[i] << endl;

    outFile2.close();

    fstream purch(purchase_path.c_str(), ios::app ) ;

    purch << name << " purchased " << item_name <<endl << endl;
    purch.close();

    cout << "\nPurchase Completed ! \n\n";

}

bool vaild_room(int room_num)
{
    string temp ;
    int arr_size=0 ,roomNum ;
     fstream infile(guests_path.c_str() , ios::in);
    if(!infile)
    {
        cout << "no  guests file existed \n" ;
        return 1 ;
    }
    while(!infile.eof())
    {
        for(int i =0 ; i<4 ; i++)
        {
            infile.clear();
            infile.sync();
            getline(infile, temp);
        }
        arr_size++ ;
    }
    infile.close();

    int *ptr = new int[arr_size] ;

    fstream infile_1 (guests_path.c_str() , ios::in);
    if(!infile_1)
    {
        cout << "can't open guests file \n" ;
        exit(13);
    }
    getline(infile_1,temp);
    getline(infile_1,temp);
    getline(infile_1,temp);

    while(!infile_1.eof())
    {


        for(int j=0 ; j< arr_size ; j++)
        {
            infile_1 >> roomNum ;
             *(ptr+j) = roomNum ;

            for(int i =0 ; i<4 ; i++)
            {
              getline(infile_1,temp);
            }
          if (temp.empty()) break ;
        }

    }

    infile_1.close();

    //the check ...
    for (int i =0 ; i< arr_size ; i++)
    {
        if(room_num != *(ptr+i))
            continue ;
        else
        {
            cout << "There is a guest in "<< *(ptr+i) << "  ... try another room"<<endl ;
            return false ;

        }
    }
    return true ;
    delete [] ptr;

}


void watermark()
{
    cout << endl << endl ;
    cout << "*************** Written by : ***************"<<endl ;
    cout << "********************************************"<<endl ;
    cout << "**************                **************"<<endl ;
    cout << "*************  Mahmoud Nasser  *************"<<endl ;
    cout << "**************                **************"<<endl ;
    cout << "********************************************"<<endl ;
    cout << "********************************************"<<endl ;
}
