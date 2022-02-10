/*
Student’s full name: Chan Zhi Lam
Student’s ID: 7072569
Modification Date: 26/11/20
Purpose of this file (or program): Driver code for Assignment 3
*/

#include "header.h"
#include "function.cpp"

int main()
{
    cout << "\t\t=====================================" << endl
         << "\t\t|WELCOME to Gordan Ramsey Restaurant|" << endl
         << "\t\t=====================================" << endl << endl;
    //initialize seed of random generator with time
    srand(time(0));
    //initialize map with customer as key and table as value
    map<Customer, Table> ct;
    //declaring iterator
    vector<int>::iterator it;

    ifstream infile;
    string line, arrival;
    int record, table, temp, counter =1;
    char option;

    //open customer.txt
    infile.open("customers.txt");
    if(!infile)
    {
        cout << "Error >> unable to open customer.txt." << endl;
        return -1;
    }

    getline(infile, line);
    //covert string to int
    record = stoi(line);
    //initialize vector with number of records
    vector<Customer> custList(record);
    //loop to insert data from customer.txt into vector
    for(int x = 0; x < record; ++x)
    {
        //set Customer Id using simple counter
        custList[x].setCusId(x+1);

        //set Customer Name
        getline(infile, line);
        custList[x].setCusName(line);

        //set number of people
        getline(infile, line);
        temp = stoi(line); //StringtoInt
        custList[x].setNumOfPeople(temp);

        //set time block with random number from 1 to 10
        custList[x].setTimeBlock(randomNum(10, 1));
    }
    infile.close(); // close file

    //open tables.txt
    infile.open("tables.txt");
    if(!infile)
    {
        cout << "Error >> unable to open tables.txt." << endl;
        return -1;
    }
    getline(infile, line);
    //covert string to int
    table = stoi(line);
    //initialize vector with number of records
    deque<Table> tableList(table);
    //loop to insert data from customer.txt into vector
    for (int x = 0; x < table; ++x)
    {
        //set table number
        getline(infile, line);
        tableList[x].setTableNum(line);

        //set number of seats
        getline(infile, line);
        temp = stoi(line); //StringtoInt
        tableList[x].setNumOfSeats(temp);
    }

    infile.close();

    //sorting the table container
    TableSorter ts;
    sort (tableList.begin(), tableList.end(), ts);

    while(true)
    {
        //close if every customer left the restaurant
        closeIfNoMoreCustomer(custList, ct);

        cout << "========Time Block "<< counter << "========" << endl << endl;
        cout << "option:\n\t[A] - Assign customer in line\n\t[B] - Customer bill" << endl;
        cout << "\n>> ";
        cin >> option;
        if(option=='A' || option=='a')
        {
            customerArrival(custList, tableList, ct);
            printCustomerAndTable(custList, tableList);
        }
        else if(option=='B' || option=='b')
        {
            tableBill(tableList, ct, counter);
            printCustomerAndTable(custList, tableList);
        }
        else
        {
            cout << "\nError >> Invalid option input. Please try again !!!" << endl << endl;
            counter--;
        }
        counter++;
    }

    return 0;
}
