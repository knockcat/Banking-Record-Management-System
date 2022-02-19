// Banking Record Management System (by vishal joshi)

// header files used
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cctype>
#include "File.h"  // contains definition of Files
#include "Intro.h" // contains defintion for introduction menu

using namespace std;

int main()
{
	char ch;
	int num;

	intro();
	system("color 90"); // to change foreground color to blue and baclground color to yellow
	do
	{
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

		system("cls");

		switch (ch)
		{
		case '1':
			write_account();
			break;

		case '2':
			cout << "\n\nEnter Account Number. : ";
			cin >> num;
			deposit_withdraw(num, 1);
			break;

		case '3':
			cout << "\nEnter the account Number. : ";
			cin >> num;
			deposit_withdraw(num, 2);
			break;

		case '4':
			cout << "Enter the account Number. : ";
			cin >> num;
			display_sp(num);
			break;

		case '5':
			if (PassWord()) // if password goes wrong 3 times , return to main menu
				break;

			display_all();
			break;

		case '6':
			cout << "Enter The account No. : ";
			cin >> num;
			delete_account(num);
			break;

		case '7':
			cout << "\n\nEnter The account No. :";
			cin >> num;
			modify_account(num);
			break;

		case '8':
			system("color E9");
			End();
			cout << "\n\n\t\t\t\t\t\tThanks for Visiting our portfolio\n";
			break;
		default:
			cout << "\nEnter Valid option\n ";
		}
		cin.ignore();
		cin.get();
	} while (ch != '8');

	return 0;
}
