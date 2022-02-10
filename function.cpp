/*
Student’s full name: Chan Zhi Lam
Student’s ID: 7072569
Modification Date: 26/11/20
Purpose of this file (or program): Function implementation for Assignment 3
*/

//function implementation
ostream & operator << (ostream &out, const Customer &c)
{
    out << "Customer Id: " << c.cusId << endl
        << "Customer Name: " << c.cusName << endl
        << "Number of people: " << c.numOfPeople << endl
        << "Number of time block: " << c.timeBlock << endl;

    return out;
}

Customer::Customer()
{
    cusId = 0;
    cusName = "nil";
    numOfPeople = 0;
    timeBlock = 0;
}

int Customer::getCusId()
{
    return cusId;
}

string Customer::getCusName() const
{
    return cusName;
}

int Customer::getNumOfPeople()
{
    return numOfPeople;
}

int Customer::getTimeBlock()
{
    return timeBlock;
}

void Customer::setCusId(const int id)
{
    cusId = id;
}

void Customer::setCusName(const string name)
{
    cusName = name;
}

void Customer::setNumOfPeople(const int num)
{
    numOfPeople = num;
}

void Customer::setTimeBlock(const int time)
{
    timeBlock = time;
}

ostream & operator << (ostream &out, const Table &t)
{
    out << "Table number: " << t.tableNum << endl
        << "Number of seats: " << t.numOfSeats << endl
        << "Vacant: " << t.vacant << endl;

    return out;
}

Table::Table()
{
    tableNum = "nil";
    numOfSeats = 0;
    vacant = true;
}

string Table::getTableNum()
{
    return tableNum;
}

int Table::getNumOfSeats()
{
    return numOfSeats;
}

bool Table::getVacant()
{
    return vacant;
}

void Table::setTableNum(const string tNum)
{
    tableNum = tNum;
}

void Table::setNumOfSeats(const int num)
{
    numOfSeats = num;
}

void Table::setVacant(const bool v)
{
    vacant = v;
}

//sorter for table
bool TableSorter::operator()(Table &lhs, Table &rhs)
{
    return lhs.getNumOfSeats() < rhs.getNumOfSeats();
}

int randomNum(int max,int min)
{
    return rand() % max + min; // random Number between 1 and 10
}

int checkTableStatus(int num, deque<Table> t)
{
    for(int x = 0; x < t.size(); ++x)
    {
        if(num <= t[x].getNumOfSeats() && t[x].getVacant() == true)
        {
            return x;
        }
        if(x + 1 == t.size() && t.size() != 1)
        {
            return -1;
        }
        else if (x == t.size() && t.size() == 1)
        {
            return -1;
        }
    }
}

void customerArrival(vector<Customer>& custList, deque<Table>& tableList, map<Customer, Table>& ct)
{
    int temp;

    if(custList.size() != 0)
    {
        for(int x = 0; x < custList.size(); ++x)
        {
            //starting by first customer
            temp = checkTableStatus(custList[x].getNumOfPeople(),tableList);
            if(temp != -1)
            {
                //making customer and table to pair
                //then add it as STL MAP
                ct.insert(make_pair(custList[x], tableList[temp]));
                //update the status to occupied
                tableList[temp].setVacant(false);

                cout << "\nMr/Ms " << custList[x].getCusName() << " has been successfully assigned to a table." << endl;

                //showing customer details occupying the table
                cout << "\nCustomer details: " << endl;
                cout << custList[x] << endl;
                //remove customer object using iterator
                custList.erase(custList.begin()+x);
                break;
            }
            if (temp == -1)
            {
                cout << "\nNo suitable table for customer infront, skipping to next customer in line." << endl;
            }
        }
    } else
    {
        cout << "\nError >> Empty customer waiting listing" << endl;
    }
}

void printCustomerAndTable(vector<Customer> custList, deque<Table> tableList)
{
    cout << "\n--------Table Status--------" << endl << endl;
    for(int x = 0; x< tableList.size(); x++)
    {
        //show all table with their status
        cout << tableList[x] << endl;
    }
    cout << "--------Customer Wait list--------" << endl << endl;
    for(int x = 0; x< custList.size(); x++)
    {
        //show all customer that still waiting
        cout << custList[x] << endl;
    }
    cout << "--------END--------" << endl << endl;
}

void closeIfNoMoreCustomer(vector<Customer> custList, map<Customer, Table> ct)
{
    if(custList.size() == 0 && ct.size() == 0)
    {
        cout << "\nAll customers have left this restaurant.\nTherefore restaurant is nore closed." << endl;
        exit(0);
    }
}

void tableBill(deque<Table>& tableList, map<Customer, Table>& ct, int& counter)
{
    string temp;

    cout << "\nWhich table is billing? : ";
    cin >> temp;

    //using iterator loop thorugh map
    for (map<Customer, Table>::iterator it = ct.begin(); it != ct.end(); ++it)
    {
        if (it->second.getTableNum() == temp)
        {
            cout << "\nTotal amount: RM" << randomNum(200, 45) << endl;
            cout << "Thank you Mr/Ms " << it->first.getCusName() << ", please come again." << endl;
            //erase map element by iterator
            ct.erase(it);
            break;
        }
        if(++it == ct.end())
        {
            cout << "\nError >> Table number entered is Invalid/ Vacant." << endl;
            counter--;
            break;
        }
    }

    //update table status after customer left
    for (int x =0; x < tableList.size(); x++)
        if(tableList[x].getTableNum() == temp)
            tableList[x].setVacant(true);
}
