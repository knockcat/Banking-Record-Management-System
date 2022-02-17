#include <iostream>
#include <string>
#include <conio.h>
using namespace std;

// User menu Choice
char menu()
{
    char ch;
    system("cls");

    cout << "\n\n\n\tMAIN MENU";
    cout << "\n\n\t01. CREATE ACCOUNT";
    cout << "\n\n\t02. DEPOSIT MONEY TO AN ACCOUNT";
    cout << "\n\n\t03. WITHDRAW MONEY FROM AN ACCOUNT";
    cout << "\n\n\t04. BALANCE ENQUIRY OF AN ACCOUNT";
    cout << "\n\n\t05. ALL ACCOUNT HOLDER LIST FROM BANK DATABASE";
    cout << "\n\n\t06. CLOSE AN ACCOUNT";
    cout << "\n\n\t07. MODIFY AN ACCOUNT";
    cout << "\n\n\t08. EXIT";
    cout << "\n\n\tSelect Your Option (1-8) ";
    cin >> ch;

    return ch;
}

void PassWord()
{
    int n = 3;
    int ind = 0;

    while (n--)
    {
        string user;
        string pass;

        cout << "Verify YourSelf" << endl;

        cout << "\n\nEnter Username : ";
        cin >> user;

        cout << "\n\nEnter PassWord : ";
        cin >> pass;

        if (user != "Knockcat" && pass != "1234")
        {
            ++ind;
            cout << "\n\n!!! ###############  Invalid Credential  ############### !!!\n"
                 << endl;

            continue;
        }

        if (user == "knockcat" && pass == "1234")
        {
            cout << "*******************  Logged In Successfully  *******************" << endl;
            break;
        }
    }

    if (ind == 3)
    {
        cout << "Returning to Main Window" << endl;
        getch();
        menu();
    }
}