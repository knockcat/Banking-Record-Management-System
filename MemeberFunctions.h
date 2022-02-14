// Member Functions Definition

#include "class.h" // class Definition
#include <iostream>
#include <iomanip>
using namespace std;

// defintion of create account
void Account ::create_account()
{
    cout << "\nGreetings You are welcome to our Portfolio\n";
    cout << "\nEnter The Account Number : ";
    cin >> acc_no;
    cout << "\nEnter The Name of The Account Holder : ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "\nEnter Type of The Account *Current or *Saving (C/S : ";
    cin >> type;
    type = toupper(type);
    cout << "\nEnter the Initial amount (greater than 500 for Saving and greater than 1000 for current) : ";
    cin >> deposit;

    cout << "\n\nAccount Created.........";
}

// defintion of show account
void Account ::show_account()
{
    cout << "\nAccount No. : " << acc_no;
    cout << "\nAccount Holder Name : ";
    cout << name;
    cout << "\nType of Account : " << type;
    cout << "\nBalance amount : " << deposit;
}

// defintion of modify func
void Account ::modify()
{
    cout << "\nAccount No. : " << acc_no;
    cout << "\nModify Account Holder Name : ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "\nModify Type of Account : ";
    cin >> type;
    type = toupper(type);
    cout << "\nModify Balance amount : ";
    cin >> deposit;
}

// definition of deposit_money func
void Account ::deposit_money(int x)
{
    deposit += x;
}

// defintion of draw func
void Account ::draw(int x)
{
    deposit -= x;
}

// defintion of report func
void Account ::report()
{
    cout << acc_no << setw(20) << " " << name << setw(15) << " " << type << setw(17) << deposit << endl;
}

// definition of retaccno
int Account ::retaccno()
{
    return acc_no;
}

// defintion of return deposit
int Account ::retdeposit()
{
    return deposit;
}

// definition of rettype func
char Account ::rettype()
{
    return type;
}