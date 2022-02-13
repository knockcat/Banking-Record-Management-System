//Banking Record Management System (by vishal joshi)

//header files used
#include<iostream>
#include<iomanip>
#include<fstream>
#include<cctype>

using namespace std;

//class used
class Account
{
	private:
		
		int acc_no;
		char name[50];
		int deposit;
		char type;
	
	public:
		void create_account();		//func to get data from user
		
		void show_account();		//func to show data on console
	
		void modify();				//func to change previous data
		
		void deposit_money(int);	//func to add money to account
		
		void draw(int);				//func to withdraw from account
		
		void report();				//func to show data in tabular form
		
		int retaccno();				//func to return acc no
		
		int retdeposit();			//func to return balance
		
		char rettype();				//func to return type of acc (c/s)
	
};

//defintion of create account 
void Account :: create_account()
{
	cout<<"\nGreetings You are welcome to our Portfolio\n";
	cout<<"\nEnter The Account Number : ";
	cin>>acc_no;
	cout<<"\nEnter The Name of The Account Holder : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nEnter Type of The Account *Current or *Saving (C/S : ";
	cin>>type;
	type = toupper(type);
	cout<<"\nEnter the Initial amount (greater than 500 for Saving and greater than 1000 for current) : ";
	cin>>deposit;
	
	cout<<"\n\nAccount Created.........";
}

//defintion of show account 
void Account :: show_account()
{
	cout<<"\nAccount No. : "<<acc_no;
	cout<<"\nAccount Holder Name : ";
	cout<<name;
	cout<<"\nType of Account : "<<type;
	cout<<"\nBalance amount : "<<deposit;
}

//defintion of modify func
void Account :: modify()
{
	cout<<"\nAccount No. : "<<acc_no;
	cout<<"\nModify Account Holder Name : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nModify Type of Account : ";
	cin>>type;
	type=toupper(type);
	cout<<"\nModify Balance amount : ";
	cin>>deposit;
}

//definition of deposit_money func
void Account :: deposit_money(int x)
{
	deposit += x;
}

//defintion of draw func
void Account :: draw(int x)
{
	deposit -= x;
}

//defintion of report func
void Account :: report()
{
	cout<<acc_no<<setw(20)<<" "<<name<<setw(15)<<" "<<type<<setw(17)<<deposit<<endl;
}

//definition of retaccno
int Account :: retaccno()
{
	return acc_no;
}

//defintion of return deposit
int Account :: retdeposit()
{
	return deposit;
}

//definition of rettype func
char Account :: rettype()
{
	return type;
}

void write_account(); 		//func to write record in bonary file
void display_sp(int);		//Func to display account details given by user
void modify_account(int);	//function to modify record into a file
void delete_account(int );	//function to delete record from a file
void display_all(); 		//function to display all records from a file
void deposit_withdraw(int, int); //function to deposit/withdraw amount for given account
void intro();     		    //Introductory Screen


int main()
{
	system("color E9") ;	//to change foreground color to blue and baclground color to yellow
	char ch;
	int num;
	
	intro();
	do
	{
		system("cls");
		
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. CREATE ACCOUNT";
		cout<<"\n\n\t02. DEPOSIT MONEY TO AN ACCOUNT";
		cout<<"\n\n\t03. WITHDRAW MONEY FROM AN ACCOUNT";
		cout<<"\n\n\t04. BALANCE ENQUIRY OF AN ACCOUNT";
		cout<<"\n\n\t05. ALL ACCOUNT HOLDER LIST FROM BANK DATABASE";
		cout<<"\n\n\t06. CLOSE AN ACCOUNT";
		cout<<"\n\n\t07. MODIFY AN ACCOUNT";
		cout<<"\n\n\t08. EXIT";
		cout<<"\n\n\tSelect Your Option (1-8) ";
		cin>>ch;
		
		system("cls");
		
		switch(ch)
		{
			case '1':
				write_account();
				break;
				
			case '2':
				cout<<"\n\nEnter Account Number. : ";
				cin>>num;
				deposit_withdraw(num,1);
				break;
				
			case '3':
				cout<<"\nEnter the account Number. : ";
				cin>>num;
				system("color E3");
				deposit_withdraw(num,2);
				break;
				
			case '4':
				cout<<"Enter the account Number. : ";
				cin>>num;
				display_sp(num);
				break;
				
			case '5':
				display_all();
				break;
				
			case '6':
				cout<<"Enter The account No. : ";
				cin>>num;
				delete_account(num);
				break;
				
			case '7':
				cout<<"\n\nEnter The account No. :";
				cin>>num;
				modify_account(num);
				break;
				
			case '8':
				cout<<"\n\n\tThanks for Visiting our portfolio\n";
				break;
			default:
				cout<<"\nEnter Valid option\n ";
		}
		cin.ignore();
		cin.get();
	}while(ch != '8');
	
	return 0;
}

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
	rename("Temp.dat","knokcat.dat");
	
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

