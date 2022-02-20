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
			if (PassWord()) // if password goes wrong 3 times , return to main menu
				break;
			cout << "Enter The account No. : ";
			cin >> num;
			delete_account(num);
			break;

		case '7':
			if (PassWord()) // if password goes wrong 3 times , return to main menu
				break;
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
<<<<<<< HEAD

//defintion of writing record to file
void write_account()
{
	Account acc;
	ofstream outfile;
	outfile.open("knockcat.dat", ios::binary | ios::app);
	acc.create_account();
	outfile.write(reinterpret_cast<char *> (&acc) , sizeof(Account));
	outfile.close();
}

//defintion for displaying specific record from a file
void display_sp(int n)
{
	Account acc;
	bool flag = 0;
	ifstream infile;
	
	infile.open("knockcat.dat",ios::binary);
	if(! infile)
	{
		cout<<"File could not be opened !! press any key ...";
		return ;
	}	
	
	cout<<"\nBALANCE DETAILS\n";
	
	while(infile.read(reinterpret_cast<char *> (&acc), sizeof(Account)))
	{
		if(acc.retaccno() == n)
		{
			acc.show_account();
			flag = 1;
		}
	}
	
	infile.close();
	if(flag == 0)
		cout<<"\n\nAccount number doesn't exists...";
}

//definition for modification of record from file
void modify_account(int n)
{
	bool found = false;
	Account acc;
	fstream vj;
	vj.open("knockcat.dat",ios::binary | ios::in | ios::out);
	
	if(!vj)
	{
		cout<<"\nFile could not be opened !! press any key ....";
		return;
	}
	
	while(! vj.eof() && found == false)
	{
		vj.read(reinterpret_cast<char *> (&acc) , sizeof(Account));
		if(acc.retaccno() == n)
		{
			acc.show_account();
			cout<<"\nEnter the New Details of the Account "<<endl;
			acc.modify();
			int pos = (-1)*static_cast<int> (sizeof(Account));	//
			vj.seekp(pos, ios::cur);
			vj.write(reinterpret_cast<char *> (&acc) , sizeof(Account));
			
			cout<<"\n\n\t Record Updated";
			found = true;
		}
	}
	vj.close();
	if(found == false)
		cout<<"\n\n Record Not Found ";
}

//definition of deleting record from file
void delete_account(int n)
{
	Account acc;
	ifstream infile;
	ofstream outfile;
	infile.open("knockcat.dat",ios::binary);
	if(!infile)
	{
		cout<<"\nFile cannot be opened !! Press any key...";
		return ;
	}
	
	outfile.open("Temp.dat", ios::binary);
	infile.seekg(0, ios::beg);
	
	while(infile.read(reinterpret_cast<char *> (&acc) , sizeof(Account)))
	{
		if(acc.retaccno() != n)
		{
			outfile.write(reinterpret_cast<char *> (&acc) , sizeof(Account));
		}
	}
	
	infile.close();
	outfile.close();
	remove("knockcat.dat");
	rename("Temp.dat","knockcat.dat");
	
	cout<<"\n\n\tRecord Deleted ..";
}

//definition for displaying all records from a file
void display_all()
{
	Account acc;
	ifstream infile;
	infile.open("knockcat.dat" , ios::binary);
	if(!infile)
	{
		cout<<"File could not be open !! Press any key...";
		return ;
	}
	
	cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"==============================================================\n";
	cout<<"A/C NO.              NAME              TYPE          BALANCE\n";
	cout<<"==============================================================\n";
	
	while(infile.read((char *) (&acc) , sizeof(Account)))
	{
		acc.report();
	}
	
	infile.close();
}

//defintion for deposit and withdraw for a record from file
void deposit_withdraw(int n, int option)
{
	int amt;
	bool found = false;
	Account acc;
	fstream vj;
	vj.open("knockcat.dat", ios::binary | ios::in | ios::out);
	if(!vj)
	{
		cout<<"File could not be open !! press any key...";
		return ;
	}
	
	while(!vj.eof() && found == false)
	{
		vj.read(reinterpret_cast<char *> (&acc), sizeof(Account));
		if(acc.retaccno() == n)
		{
			acc.show_account();
			
			if(option == 1)
			{
				cout<<"\n\n\tTo Deposit Ammount : ";
				cout<<"Enter the amount to be deposited ";
				cin>>amt;
				acc.deposit_money(amt);
			}
			
			if(option == 2)
			{
				cout<<"\n\n\tTo Withdraw Amount : ";
				cout<<"\n\nEnter the Amount you need Withdraw : ";
				cin>>amt;
				
				int bal = acc.retdeposit() - amt;
				if((bal < 500 && acc.rettype() == 'S' || (bal <1000 && acc.rettype() == 'C')))
					cout<<"Insufficent balance !!";
				else
					acc.draw(amt);
			}
			
			int pos = (-1)*static_cast<int> (sizeof(acc));
			vj.seekp(pos,ios::cur);
			vj.write(reinterpret_cast<char *> (&acc) , sizeof(Account));
			cout<<"\n\nRecord Updated ";
			found = true;
		}
	}
	vj.close();
	
	if(found == false)
		cout<<"\n\nRecord Not FOund";
}

//defintion for introduction menu
void intro()
{
	cout<<"\n\n\n\n";
	cout<<"\t\t\t===================================================================\n";
	cout<<"\t\t\t====								===\n";
	cout<<"\t\t\t====		     \tBANKING					===\n";
	cout<<"\t\t\t====								===\n";
	cout<<"\t\t\t====								===\n";
	cout<<"\t\t\t====								===\n";
	cout<<"\t\t\t====	    	\tRECORD					===\n";
	cout<<"\t\t\t====								===\n";
	cout<<"\t\t\t====								===\n";
	cout<<"\t\t\t====								===\n";
	cout<<"\t\t\t====		     \tMANAGEMENT				===\n";
	cout<<"\t\t\t====								===\n";
	cout<<"\t\t\t====								===\n";
	cout<<"\t\t\t====								===\n";
	cout<<"\t\t\t====		    \tSYSTEM					===\n";
	cout<<"\t\t\t====								===\n";
	cout<<"\t\t\t====								===\n";
	cout<<"\t\t\t====								===\n";
	cout<<"\t\t\t====		        By			   		===\n";
	cout<<"\t\t\t====								===\n";
	cout<<"\t\t\t====								===\n";
	cout<<"\t\t\t====			VISHAL JOSHI				===\n";				
	cout<<"\t\t\t===================================================================\n";
	
	cin.get();
																		
}

=======
>>>>>>> update
