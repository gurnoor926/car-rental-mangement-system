#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdlib.h>
#include <conio.h>
#include<windows.h>
#include<sstream>
using namespace std;
class car
{
    string carID;
    string modelname;
    int reg;
    double price;

public:
    void getdata();
    void putdata();
    void addcar();
    void rentcar(string);
    void search(string);
    void update(string);
    void recpit(string,int,int);
};
void car::getdata()
{   cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    
    cout << setw(90) << "             Enter CarID  ";
    cin >> carID;
    cout << setw(90) << "             Enter car Name ";
    cin >> modelname;
    cout << setw(90) << "             Enter registration number ";
    cin >> reg;
    cout << setw(90) << "             Enter per day price of the car ";
    cin >> price;
}
void car::addcar()
{

    getdata();
    ofstream fout;
    string line;
    fout.open("cars.txt", ios::app);
    while (fout)
    {
        getline(cin, line);
        fout << carID << setw(10) << modelname << setw(10) << reg << setw(10) << price << setw(10) << endl;
        break;
    }
    fout.close();
}

void car::putdata() {
    ifstream fin("cars.txt");
    if (!fin) {
        cout << "Error in opening file!" << endl;
        return;
    }

    string line;
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    cout << setw(58) <<"|"<< "CarID" << setw(20) << "Model Name" << setw(20) << "Reg. Number" << setw(10) << "Price" <<"|"<< endl;
    cout << setw(114) << "                 |-------------------------------------------------------|" << endl;

    while (getline(fin, line)) {
        char id[5];
        int reg;
        double price;
        char model[50];

        stringstream ss(line);  // Use stringstream to extract data from each line
        ss >> id >> model >> reg >> price;

        cout << setw(58)<<"|" << id << setw(22) << model << setw(20) << reg << setw(10) << price <<"|" << endl;
    }

    fin.close();
}                                                                                                             
void car::search(string carname) {
    ifstream fin("cars.txt");
    if (!fin) {
        cout << "Error in opening file!" << endl;
        return;
    }

    string line;
    bool found = false;

    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    cout << setw(58) <<"|"<< "CarID" << setw(20) << "Model Name" << setw(20) << "Reg. Number" << setw(10) << "Price" <<"|" << endl;
    cout << setw(114) << "                 |-------------------------------------------------------|" << endl;

    while (getline(fin, line)) {
        char id[5];
        int reg;
        double price;
        char model[50];

        stringstream ss(line);  // Extract data from the line
        ss >> id >> model >> reg >> price;

        // Check if the car name matches the search query
        if (string(model).find(carname) != string::npos) {
            found = true;
            cout << setw(58) <<"|" << id << setw(22) << model << setw(20) << reg << setw(10) << price <<"|" << endl;
        }
    }
   

    if (!found) {
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
        cout << setw(80) << "Car with the name '" << carname << "' not found." << endl;
    }

    fin.close();
}

void car::update(string carname) {
    ifstream fin("cars.txt");
    ofstream fout("temp.txt");
    string line;
    bool found = false;
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    while (getline(fin, line)) {
        if (line.find(carname) != string::npos) {
            cout<<setw(80) << "             Enter new price: ";
            int newPrice;
            cin >> newPrice;
            line.replace(line.find_last_of(" "), string::npos, to_string(newPrice));
            found = true;
        }
        fout << line << endl;
    }
    fin.close();
    fout.close();
    remove("cars.txt");
    rename("temp.txt", "cars.txt");
    if (found) {
        cout<<setw(85) << "                Price updated successfully.\n";
    } else {
        cout<<setw(85) << "                Car not found.\n";
    }
}

void car::rentcar(string carname) {
    ifstream fin("cars.txt");
    ofstream fout("temp.txt");
    string line;
    bool found = false;
    double carPrice = 0;
    
    // First, find the car in the file and store its price
    while (getline(fin, line)) {
        if (line.find(carname) != string::npos) {
            found = true;
            size_t pos = line.find_last_of(" ");
            carPrice = stod(line.substr(pos + 1));  // Extract the price
        } else {
            fout << line << endl;
        }
    }
    fin.close();
    fout.close();
    
    // If car was found, proceed to print the receipt and remove the car
    if (found) {
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
        cout<<setw(85) << "                Enter number of days: ";
        int days;
        cin >> days;
        cout<<setw(60) << "                Car rented successfully.\n";

        recpit(carname, carPrice, days);  // Pass price to the receipt function
        remove("cars.txt");
        rename("temp.txt", "cars.txt");  // Remove the rented car from the list
    } else {
        cout<<setw(60) << "                Car not found.\n";
        remove("temp.txt");
    }
}


void car::recpit(string carname, int price, int days) {
    system("cls");
    double total = price * days;
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    cout<<setw(110) << "|***********************************************|" << endl;
    cout<<setw(110) << "|                    Receipt:                   |" << endl;
    cout<<setw(110) << "|***********************************************|" << endl;
    cout<<setw(81) << "|    Car:           " <<"    |         "<< carname <<setw(12)<<"|"<< endl;
    cout<<setw(81) << "|    Price per day: " <<"    |        "<< price   <<setw(12)<<"|"<< endl;
    cout<<setw(81) << "|    Days:          " <<"    |        "<< days    <<setw(15)<<"|"<< endl;
    cout<<setw(81) << "|    Total amount:  " <<"    |        "<< total   <<setw(12)<<"|"<< endl;
    cout<<setw(110) << "|***********************************************|" << endl;
    cout<<setw(110) << "|                    Thank You                  |" << endl;
    cout<<setw(110) << "|***********************************************|" << endl;
}

void login()
{  
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    cout << setw(100) << "***********************************************" << endl;
    cout << setw(100) << "                   CAR RENTAL                  " << endl;
    cout << setw(100) << "***********************************************" << endl;
    char user[20];
    int pass;
    cout << setw(80) << "                   Enter user name = ";
    cin >> user;
    cout << setw(80) << "                    Password = ";
    cin >> pass;
    if ( pass != 1234)
    {
        cout << setw(80) << "            login failed" << endl;
        cout << setw(80) << "        (Press enter to retry)" << endl;
        getch();
        system("cls");
        login();
    }

    else
    {
        cout << setw(80) << "             login successful" << endl;
        cout << setw(80) << "              (Press enter)";
        getch();
    }
}
int main()
{  system("color 02");
    int choice;
    car ob;
    system("cls");
    login();
    system("cls");
    while (true)
    {  
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
        cout << setw(75) << " Menu " << endl;
        cout << setw(90) << "             Enter 1 to add a car       " << endl;
        cout << setw(90) << "             Enter 2 to Rent a car      " << endl;
        cout << setw(90) << "             Enter 3 to Display all cars" << endl;
        cout << setw(90) << "             Enter 4 to search a car    " << endl;
        cout << setw(90) << "             Enter 5 to update price    " << endl;
        cout << setw(90) << "             Enter 6 exit               " << endl;
        cout << setw(90) << "             Enter choice               ";
        cin >> choice;
        system("cls");
        switch (choice)
        {
            
        case 1:
            cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
            system("cls");
            ob.addcar();
            getch();
            system("cls");
            break;

        case 2:
            cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
            system("cls");
            char carname[100];
            cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
            cout << setw(80) << "    Enter car name   ";
            cin >> carname;
            system("cls");
            ob.rentcar(carname);
            getch();
            system("cls");
            break;

        case 3:
        
            cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
            system("cls");
            ob.putdata();
            getch();
            system("cls");
            break;

        case 4:
        
            cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
            system("cls");
             carname[100];
            cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
            cout << setw(80) << "    Enter car name   ";
            cin >> carname;
            system("cls");
            ob.search(carname);
            getch();
            system("cls");
            break;

        case 5:
       
       cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
            system("cls");
            cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
            cout << setw(80) << "    Enter car name   ";
            cin >> carname;
            system("cls");
           ob.update(carname);
           getch();
           system("cls");
            break;

        case 6:
        
         exit(0);

        default:
        
        system("cls");
        cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
            cout << setw(75) << "    Invalid choice "  << endl;
             getch();
             system("cls");
            break;
        }
    }
}