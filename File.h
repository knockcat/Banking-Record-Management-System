// Contains Defiition of Files

#include "MemeberFunctions.h" //Defintion of  Member Functions and Class
#include <fstream>
#include <iostream>
using namespace std;

void write_account();            // func to write record in bonary file
void display_sp(int);            // Func to display account details given by user
void modify_account(int);        // function to modify record into a file
void delete_account(int);        // function to delete record from a file
void display_all();              // function to display all records from a file
void deposit_withdraw(int, int); // function to deposit/withdraw amount for given account
void intro();                    // Introductory Screen

// defintion of writing record to file
void write_account()
{
    Account acc;
    ofstream outfile;
    outfile.open("knockcat.dat", ios::binary | ios::app);
    acc.create_account();
    outfile.write(reinterpret_cast<char *>(&acc), sizeof(Account));
    outfile.close();
}

// defintion for displaying specific record from a file
void display_sp(int n)
{
    Account acc;
    bool flag = 0;
    ifstream infile;

    infile.open("knockcat.dat", ios::binary);
    if (!infile)
    {
        cout << "File could not be opened !! press any key ...";
        return;
    }

    cout << "\nBALANCE DETAILS\n";

    while (infile.read(reinterpret_cast<char *>(&acc), sizeof(Account)))
    {
        if (acc.retaccno() == n)
        {
            acc.show_account();
            flag = 1;
        }
    }

    infile.close();
    if (flag == 0)
        cout << "\n\nAccount number doesn't exists...";
}

// definition for modification of record from file
void modify_account(int n)
{
    bool found = false;
    Account acc;
    fstream vj;
    vj.open("knockcat.dat", ios::binary | ios::in | ios::out);

    if (!vj)
    {
        cout << "\nFile could not be opened !! press any key ....";
        return;
    }

    while (!vj.eof() && found == false)
    {
        vj.read(reinterpret_cast<char *>(&acc), sizeof(Account));
        if (acc.retaccno() == n)
        {
            acc.show_account();
            cout << "\nEnter the New Details of the Account " << endl;
            acc.modify();
            int pos = (-1) * static_cast<int>(sizeof(Account)); //
            vj.seekp(pos, ios::cur);
            vj.write(reinterpret_cast<char *>(&acc), sizeof(Account));

            cout << "\n\n\t Record Updated";
            found = true;
        }
    }
    vj.close();
    if (found == false)
        cout << "\n\n Record Not Found ";
}

// definition of deleting record from file
void delete_account(int n)
{
    Account acc;
    ifstream infile;
    ofstream outfile;
    infile.open("knockcat.dat", ios::binary);
    if (!infile)
    {
        cout << "\nFile cannot be opened !! Press any key...";
        return;
    }

    outfile.open("Temp.dat", ios::binary);
    infile.seekg(0, ios::beg);

    while (infile.read(reinterpret_cast<char *>(&acc), sizeof(Account)))
    {
        if (acc.retaccno() != n)
        {
            outfile.write(reinterpret_cast<char *>(&acc), sizeof(Account));
        }
    }

    infile.close();
    outfile.close();
    remove("knockcat.dat");
    rename("Temp.dat", "knokcat.dat");

    cout << "\n\n\tRecord Deleted ..";
}

// definition for displaying all records from a file
void display_all()
{
    Account acc;
    ifstream infile;
    infile.open("knockcat.dat", ios::binary);
    if (!infile)
    {
        cout << "File could not be open !! Press any key...";
        return;
    }

    cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";
    cout << "==============================================================\n";
    cout << "A/C NO.              NAME              TYPE          BALANCE\n";
    cout << "==============================================================\n";

    while (infile.read((char *)(&acc), sizeof(Account)))
    {
        acc.report();
    }

    infile.close();
}

// defintion for deposit and withdraw for a record from file
void deposit_withdraw(int n, int option)
{
    int amt;
    bool found = false;
    Account acc;
    fstream vj;
    vj.open("knockcat.dat", ios::binary | ios::in | ios::out);
    if (!vj)
    {
        cout << "File could not be open !! press any key...";
        return;
    }

    while (!vj.eof() && found == false)
    {
        vj.read(reinterpret_cast<char *>(&acc), sizeof(Account));
        if (acc.retaccno() == n)
        {
            acc.show_account();

            if (option == 1)
            {
                cout << "\n\n\tTo Deposit Ammount : ";
                cout << "Enter the amount to be deposited ";
                cin >> amt;
                acc.deposit_money(amt);
            }

            if (option == 2)
            {
                cout << "\n\n\tTo Withdraw Amount : ";
                cout << "\n\nEnter the Amount you need Withdraw : ";
                cin >> amt;

                int bal = acc.retdeposit() - amt;
                if ((bal < 500 && acc.rettype() == 'S' || (bal < 1000 && acc.rettype() == 'C')))
                    cout << "Insufficent balance !!";
                else
                    acc.draw(amt);
            }

            int pos = (-1) * static_cast<int>(sizeof(acc));
            vj.seekp(pos, ios::cur);
            vj.write(reinterpret_cast<char *>(&acc), sizeof(Account));
            cout << "\n\nRecord Updated ";
            found = true;
        }
    }
    vj.close();

    if (found == false)
        cout << "\n\nRecord Not FOund";
}
