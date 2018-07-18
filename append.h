//append.h
// header file for the software
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <algorithm>   // for  fill
#include <iterator>    // for ostream and istream iterator
#include <numeric>     //for accumulate
#include <fstream>     //for file
#include <sstream>     // for  change basic type
#include <deque>
#include <iomanip>     // for setw()
#include <conio.h>     //for _getch()
#include <ctime>      //for current time and date
using namespace std;

////////////////////////////////////global methods//////////////////////////////////
void getaLine(string& instr);  //get line of text


///////////////////////////////////class customer/////////////////////////////////////
class customer
{
private:
    string custName;     //customer name
    string fatherName;   //customer's father's name
    int refNumber;       //customer's reference number
    string mobileNo;     //customer's mobile number
    string address;      //customer's address
public:
    customer( int r) : custName(), fatherName(), refNumber(r), mobileNo(), address()  //1-arg constructor
    {
        /*
        empty constructor
        */
    }
    customer(string cn, string fn, int rno, string mno, string add);       //5-arg constructor
    customer(const customer&);                                              //copy constructor
    ~customer();
    string getCustName();
    //needed for use in 'set'
    friend bool operator < (const customer&, const customer&);
    friend bool operator == (const customer&, const customer&);
    //for I/O
    friend ostream& operator << (ostream& , const customer&);
}; //end class customer

/////////////////////////////////////class compareCustomers//////////////////////////
class compareCustomers   //function object -- compare customers
{
public:
    bool operator () (customer , customer) const;
};

/////////////////////////////////////class customerList///////////////////////////////
class customerList
{
private:
    //sets of customers
    set<customer, compareCustomers> setCusts;
    set<customer, compareCustomers>::iterator iter;
public:
    ~customerList();                //destructor (delete customers)
    void insertCustomer(customer);  // put customers on list
    string getCustomerNa(int);      //return customer's name
    void display();                 // display customer list
    void readData();                 // read data from file
    void writeData();                //write data to file
    void deleteCust();               // delete customers
};  //end class customerList

/////////////////////////////////////class customerInputScreen////////////////////////
class customerInputScreen
{
private:
    customerList inCustomerList;
    string cName;
    int refNo;
    string fName;
    string mNo;
    string add;
public:
    customerInputScreen(customerList inCL) : inCustomerList(inCL)
    {
        /*
        empty constructor
        */
    }
    void getCustomer();
};   //end class customerInputScreen

////////////////////////////////////////////////////////class dataRow////////////////////
// one row of the data record: Name, milk quantity and price for  a month
class dataRow
{
private:
    string cName;
    double milkQuantity[1][12][31];
    double milkPrice[1][12][31];
    double nightQuantity[1][12][31];
    double nightPrice[1][12][31];
public:
    dataRow(string);
    dataRow(const dataRow&);                            //1-arg constructor
    dataRow(string name, double q[1][12][31], double p[1][12][31], double n[1][12][31], double m[1][12][31]);
    void setData(int, int, int, double, double, bool);         //record milk quantity and price
    double getSumOfQuantity(int, int);              //return sum of quantity in a month
    double getSumOfQuantity(int);                //return sum of quantity in a year
    double getSumOfQuantity();                   //return sum of quantity in a gross years
    double getSumOfPrice(int, int);              //return sum of price in a month
    double getSumOfPrice(int);                   //return sum of price in a year
    double getSumOfPrice();                       //return sum of price in gross years
    void inDisplay();                  //for displaying data
    void outdisplay();
    // needed to store data in 'set'
    friend bool operator < (const dataRow&, const dataRow&);
    friend bool operator == (const dataRow&, const dataRow&);
    // for I/O
    friend ostream& operator << (ostream& , const dataRow&);
    ~dataRow();
};  // end class dataRow

////////////////////////////////////////////////////////////////////////////////////////////
class compareRows      //function object -- compare dataRows
{
public:
    bool operator () (dataRow, dataRow) const;
};

/////////////////////////////////////////////class dataRecord///////////////////////////////////
class dataRecord
{
private:
    // set of dataRow objects (one per customer)
    set<dataRow, compareRows> setDataR;
    set<dataRow, compareRows>::iterator iter;

public:
    ~dataRecord();
    void insertData(string, int, int, int, double, double, bool);
    void display();
    // sum of all quantity
    double getQuantity(int, int);
    double getQuantity(int);
    double getQuantity();
    //sum of all price
    double getPrice(int, int);
    double getPrice(int);
    double getPrice();
    void readRow();
    void writeRow();
    void deleteRow();
    void annualReport();        //Annual for Clients
};    //end class dataRecord

/////////////////////////////////////////////class dataInputScreen//////////////////////////////
class dataInputScreen
{
private:
    customerList inCustList;
    dataRecord   inDataRecord;

    int refNumber;
    double mQuantity;
    int year;
    int month;
    int day;
    double rate;
    string custName;
public:
    dataInputScreen(customerList inCL, dataRecord inDR) :
        inCustList(inCL), inDataRecord(inDR)
        {

            //empty constructor

        }
    void getData();                  //data for one customer and one day
};  // end class dataInputScreen

//------------------------------------------------------------------------------------------------

//////////////////////////////////////class userInterface//////////////////////////////////////////
class userInterface
{
private:
    char ch;
public:
    userInterface();
    ~userInterface();
    void interact();
};    // end class userInterface
