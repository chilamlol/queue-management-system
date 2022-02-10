/*
Student’s full name: Chan Zhi Lam
Student’s ID: 7072569
Modification Date: 26/11/20
Purpose of this file (or program): Function prototype for Assignment 3
*/

#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<deque>
#include<map>
#include <algorithm>
using namespace std;

class Customer
{
    //overlord extraction
    friend ostream & operator << (ostream &out, const Customer &c);
private:
    int cusId;
    string cusName;
    int numOfPeople;
    int timeBlock;
public:
    Customer(); //default constructor
    int getCusId(); //accessors;
    string getCusName() const;
    int getNumOfPeople();
    int getTimeBlock();
    void setCusId(const int id); //mutator
    void setCusName(const string name);
    void setNumOfPeople(const int num);
    void setTimeBlock(const int time);
    bool operator<(const Customer& c) const
    {
        return cusId < c.cusId;
    }
};

class Table
{
    friend ostream & operator << (ostream &out, const Table &t);
private:
    string tableNum;
    int numOfSeats;
    bool vacant;
public:
    Table(); //default constructor
    string getTableNum(); //accessor
    int getNumOfSeats();
    bool getVacant();
    void setTableNum(const string tNum); //mutator
    void setNumOfSeats(const int num);
    void setVacant(const bool v);
};

struct TableSorter
{
    bool operator()(Table &lhs, Table &rhs);
};

int randomNum(int,int);
int checkTableStatus(int num, deque<Table> t);
void customerArrival(vector<Customer>&, deque<Table>&,map<Customer, Table>&);
void printCustomerAndTable(vector<Customer>, deque<Table>);
void closeIfNoMoreCustomer(vector<Customer>, map<Customer, Table>);
void tableBill(deque<Table>&, map<Customer, Table>&, int&);
