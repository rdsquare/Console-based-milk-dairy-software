// mlksoft.cpp
// models the finances for milk dairy client
#include "append.h"

///////////////////////////////////////////////////////////global functions////////////////////////////////////////////
void getaLine(string& instr)     // get line of text
{
    char temp[26];
    cin.get(temp, 25, '\n');
    cin.ignore(25, '\n');
    instr = temp;
}

//-------------------------------------------------------------------------------------------------------------------

/////////////////////////////////////////////////////////////methods for class customer//////////////////////////////
customer::customer(string cn, string fn, int rno, string mno, string add) :
    custName(cn), fatherName(fn), refNumber(rno), mobileNo(mno), address(add)
    {
        /*
        empty constructor
        */
    }

//---------------------------------------------------------------------------------------------------------------
customer::customer(const customer& c)
{
    custName = c.custName;
    fatherName = c.fatherName;
    refNumber = c.refNumber;
    mobileNo = c.mobileNo;
    address = c.address;
}

//------------------------------------------------------------------------------------------------------------------
customer::~customer()
{
    /*
    empty destructor
    */
}

//-----------------------------------------------------------------------------------------------------------------
string customer::getCustName()
{
    return custName;
}

//----------------------------------------------------------------------------------------------------------------
bool operator < (const customer& c1, const customer& c2)
{
    return c1.refNumber < c2.refNumber;
}

//----------------------------------------------------------------------------------------------------------------
bool operator == (const customer& c1, const customer& c2)
{
    return c1.refNumber == c2.refNumber;
}

//-----------------------------------------------------------------------------------------------------------------
ostream& operator << (ostream& s, const customer& c)
{
    s << left << setw(7) << c.refNumber << left << setw(20) << c.custName << " "<< left << setw(20) << c.fatherName
       << left << setw(15) << c.mobileNo << left << setw(10) << c.address;
    s << endl;
    return s;
}

//------------------------------------------------------------------------------------------------------------------


////////////////////////////////////////////////////methods for class customerInputScreen///////////////////////////
void customerInputScreen::getCustomer()       //get customer's information
{
    cout << "\nEnter customer's name (e.g. Rahul Dangi): ";
    getaLine(cName);
    cout << "Enter customer's father's name (Ramsingh Dangi): ";
    getaLine(fName);
    cout << "Enter customer's reference number (234): ";
    cin >> refNo;
    cin.ignore(80, '\n');
    cout << "Enter customer's 10 digit mobile number (7568577487): ";
    getaLine(mNo);
    cout << "Enter customer's village name (Sagor): ";
    getaLine(add);
    //make customer
    customer ctr(cName, fName, refNo, mNo, add);
    inCustomerList.insertCustomer(ctr);  //send to customer list
    inCustomerList.writeData();            //write data to file
    inCustomerList.deleteCust();          //remove customer from set
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool compareCustomers::operator() (customer c1, customer c2) const
{
    return c1 < c2;
}

//------------------------------------------------------------------------------------------------------------------

//////////////////////////////////////////////methods for class customerList/////////////////////////////////////////
customerList::~customerList()                      //destructor
{
    while( !setCusts.empty() )               //delete all customers
    {                                        //remove customers from set
        iter = setCusts.begin();
        setCusts.erase(iter);
    }
}   // end ~customerList()

//------------------------------------------------------------------------------------------------------------------
void customerList::insertCustomer(customer inC)
{
    setCusts.insert(inC);            //insert
}

//------------------------------------------------------------------------------------------------------------------
string customerList::getCustomerNa(int refNo)    //reference number on list
{
    string cName;
    customer dummy(refNo);
    iter = setCusts.begin();
    while( iter != setCusts.end() )
    {
        customer ctor = *iter;
       cName = ctor.getCustName();        //look for customer
        if(dummy == *iter++)              //on the list?
            return cName;                 //yes

    }
    return "";                           //No
}

//-----------------------------------------------------------------------------------------------------------------
void customerList::readData()
{
    string cName;
    string fName;
    int refNo;
    string mNo;
    string add;
    string a, b;
    deque<string> a_deque;
    deque<string>::iterator diter;
    ifstream infile;
    infile.open("E:/program/my_soft/bin/Debug/customer.dat", ios::in | ios::binary);
    istream_iterator<string> iiter(infile);
    istream_iterator<string> eof;                //end of file iterator

    if(infile.eof())                             //check for end of file
        return ;

    copy(iiter, eof, back_inserter(a_deque));    //copy data -- file to deque

    diter = a_deque.begin();
    while( diter != a_deque.end() )
    {
        string cum = *diter++;
        stringstream geek(cum);
        geek>>refNo;
        a = *diter++;
        b = *diter++;
        cName = a + " " + b;
        a = *diter++;
        b = *diter++;
        fName = a + " " + b;

        mNo = *diter++;

        add = *diter++;

        customer care(cName, fName, refNo, mNo, add);
        setCusts.insert(care);
    }
}

//-------------------------------------------------------------------------------------------------------------------
void customerList::writeData()
{
    ofstream outfile;
    if(setCusts.empty())
        cout << "******  No DATA ENTERED ******";
    else
    {
        outfile.open("E:/program/my_soft/bin/Debug/customer.dat",ios::app | ios::binary);
        if(!outfile){
            cout << "\n   #CAN'T OPEN FILE.";
            return ;
        }
        ostream_iterator<customer> oiter(outfile);

        copy(setCusts.begin(), setCusts.end(), oiter);

        if(!outfile)
        {
            cout << "\n    #CAN'T WRITE TO FILE.";
            return ;
        }
    }
}

//--------------------------------------------------------------------------------------------------------------------
void customerList::display()               //display customer list
{
    readData();
    cout << "\n" << left << setw(7) << "RefNo" << left << setw(20) << "Name" << "     " << left << setw(20) << "Father"
      << left << setw(15) << "MobileNo"<< left << setw(10) << "Village"
     << "\n--------------------------------------------------------------------------------\n";
    if(setCusts.empty())
        cout << "******* NO CUSTOMERS AT ALL ********";
    else
    {
        iter = setCusts.begin();
        while (iter != setCusts.end())
            cout << *iter++;

        deleteCust();                             //remove from set
    }
}   //end display

//----------------------------------------------------------------------------------------------------------------------
void customerList::deleteCust()
{
    while (!setCusts.empty())    //delete customers
    {
        iter = setCusts.begin();
        setCusts.erase(iter);
    }
}

//---------------------------------------------------------------------------------------------------------------------------

/////////////////////////////////methods for class dataRow//////////////////////////////////////////////////////////////////
dataRow::dataRow(string cn) : cName(cn)    // 1-arg constructor
{
    fill(&milkQuantity[0][0][0], &milkQuantity[1][12][31], 0.0);
    fill(&milkPrice[0][0][0], &milkPrice[1][12][31], 0.0);
    fill( &nightQuantity[0][0][0], &nightQuantity[1][12][31], 0.0 );
    fill(&nightPrice[1][12][31], &nightPrice[1][12][31], 0.0);
}

//-------------------------------------------------------------------------------------------------------------------------
dataRow::dataRow(const dataRow& dr)
{
    cName = dr.cName;
    for(int i=0; i<1; i++)
    {
        for(int j=0; j<12; j++)
        {
            for(int k=0; k<31; k++)
            {
                milkQuantity[i][j][k] = dr.milkQuantity[i][j][k];
                milkPrice[i][j][k] = dr.milkPrice[i][j][k];
                nightQuantity[i][j][k] = dr.nightQuantity[i][j][k];
                nightPrice[i][j][k]  = dr.nightPrice[i][j][k];
            }
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------------
dataRow::dataRow(string name, double q[1][12][31], double p[1][12][31], double n[1][12][31],double m[1][12][31])
{
    cName = name;
    for(int i=0; i<1; i++)
    {
        for(int j=0; j<12; j++)
        {
            for(int k=0; k<31; k++)
            {
                milkQuantity[i][j][k] = q[i][j][k];
                milkPrice[i][j][k] = p[i][j][k];
                nightQuantity[i][j][k] = n[i][j][k];
                nightPrice[i][j][k] = m[i][j][k];
            }
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------
dataRow::~dataRow()
{
    //empty
}
//-------------------------------------------------------------------------------------------------------------------------
void dataRow::setData(int y, int m, int d, double quantity, double rate, bool select )
{
    if(select == true)
    {
        milkQuantity[y][m][d] = quantity;
        milkPrice[y][m][d] = quantity*rate;
    }
    else
    {
        nightQuantity[y][m][d] = quantity;
        nightPrice[y][m][d]  = quantity*rate;
    }
}

//----------------------------------------------------------------------------------------------------------------------------
void dataRow::inDisplay()
{
     string name;
     double tempQuantity[1][12][31];
     double tempPrice[1][12][31];
     double tempNightQuantity[1][12][31];
     double tempNightPrice[1][12][31];
    string emonth[12] = { "Jan",
                      "Feb",
                      "Mar",
                      "Apr",
                      "May",
                      "Jun",
                      "Jul",
                      "Aug",
                      "Sept",
                      "Oct",
                      "Nov",
                      "Dec"  };
    int eyear[1] = {2017};
    for(int i=0; i<1; i++)
    {
        for(int j=0; j<12; j++)
        {
            for(int k=0; k<31; k++)
            {
                tempQuantity[i][j][k] = milkQuantity[i][j][k];
                tempPrice[i][j][k] = milkPrice[i][j][k];
                tempNightQuantity[i][j][k] = nightQuantity[i][j][k];
                tempNightPrice[i][j][k] = nightPrice[i][j][k];
            }
        }
    }

    name = cName;
    cout << endl << name << "\n";                 //print customer name
    for(int y=0; y<1; y++)
    {
        for(int m =0; m<12; m++)
        {
            bool what = true;

            for(int d=0; d<31; d++)
            {
                if(tempQuantity[y][m][d] == 0.0 && tempNightQuantity[y][m][d] == 0.0){ /* Do Nothing */}
                else{
                       if(what)
                       {
                         cout << left << setw(5) <<emonth[m] << left << setw(5) << eyear[y] << "\n\n";
                         cout << "  " <<left << setw(5) << "Day" << "|  " << "             " << left << setw(8) << "Morning" << "             " << "|" << "             " << left << setw(8) << "Evening" << "             \n";
                         cout << "  " << "     " << "|  " << left << setw(15) << "Quantity (L)" << "   " << left << setw(12) << "Price (Rs)" << "    " << "|" << " " << left << setw(15) << "Quantity (L)" << "   " << left << setw(10) << "Price (Rs)\n" ;
                         cout << "  " << "     " << "|  " << "                    " << "   " << "           " << "|" << " " << endl;
                         cout << "  " << "     " << "|  " << "                    " << "   " << "           " << "|" << " " << endl;
                       }
                       cout << "  " << left << setw(5) << d+1 << "|  " << left << setw(10) << tempQuantity[y][m][d] << "        " << left << setw(7) << tempPrice[y][m][d]<< "         " << "| " << left << setw(10) << tempNightQuantity[y][m][d] << "        " << left << setw(7) << tempNightPrice[y][m][d] << "   " << "\n";
                       what = false;
                }
            }

            double Total, Potal;
            Total = getSumOfQuantity(y, m);
            Potal = getSumOfPrice(y, m);
            if(Total == 0) { }
            else{
                    cout << "\n---------------------------------------------\n";
            cout  << left << setw(10) << "Total" << "    " << left << setw(10) << Total << "L    " << left << setw(7) << Potal << "Rs.\n";
            cout << "---------------------------------------------\n";
            }
        }
    }
    cout << endl << endl;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------
void dataRow::outdisplay()
{
      string name;
    string emonth[12] = { "Jan",
                      "Feb",
                      "Mar",
                      "Apr",
                      "May",
                      "Jun",
                      "Jul",
                      "Aug",
                      "Sept",
                      "Oct",
                      "Nov",
                      "Dec"  };
    int eyear[1] = {2017};

    name = cName;
    cout << endl << name << "\n";                 //print customer name
    for(int y=0; y<1; y++)
    {
        bool what = true;
        for(int m =0; m<12; m++)
        {
            double kay = getSumOfQuantity(y, m);
                if(kay == 0.0){ /* Do Nothing */}
                else{
                       if(what)
                       {
                         cout << left << setw(5) << eyear[y] << "\n\n";
                         cout << "    " <<left << setw(10) << "Month" << left << setw(10) << "Quantity" << "     " << left << setw(7) << "Price" << endl<< endl;
                       }
                       cout << "    " << left << setw(10) << emonth[m] << left << setw(10) << getSumOfQuantity(y, m) << "L    " << left << setw(7) << getSumOfPrice(y, m) << "Rs." << "\n";
                       what = false;
                }
        }


            double Total, Potal;
            Total = getSumOfQuantity(y);
            Potal = getSumOfPrice(y);
            if(Total == 0) { }
            else{
                    cout << "\n---------------------------------------------\n";
            cout  << left << setw(10) << "Total" << "    " << left << setw(10) << Total << "L    " << left << setw(7) << Potal << "Rs.\n";
            cout << "---------------------------------------------\n";
            }

    }
    cout << endl << endl;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------
double dataRow::getSumOfQuantity(int y, int m)
{
    double show = 0.0;
    show += accumulate( &milkQuantity[y][m][0], &milkQuantity[y][m][31], 0.0);
    show += accumulate( &nightQuantity[y][m][0], &nightQuantity[y][m][31], 0.0);
    return show;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
double dataRow::getSumOfQuantity(int y)
{
    double show = 0.0;
    for(int m=0; m<12; m++)
    {
        show += accumulate( &milkQuantity[y][m][0], &milkQuantity[y][m][31], 0.0);
        show += accumulate( &nightQuantity[y][m][0], &nightQuantity[y][m][31], 0.0);
    }
    return show;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------
double dataRow::getSumOfQuantity( )
{
    double show = 0.0;
    for(int y=0; y<1; y++)
    {
        for(int m=0; m<12; m++)
        {
            show += accumulate( &milkQuantity[y][m][0], &milkQuantity[y][m][31], 0.0);
            show += accumulate( &nightQuantity[y][m][0], &nightQuantity[y][m][31], 0.0);
        }
    }
    return show;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------
double dataRow::getSumOfPrice(int y, int m)
{
    double show = 0.0;
     show += accumulate( &milkPrice[y][m][0], &milkPrice[y][m][31], 0.0);
    show += accumulate(&nightPrice[y][m][0], &nightPrice[y][m][31], 0.0);
    return show;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------
double dataRow::getSumOfPrice(int y)
{
    double show = 0.0;
     for(int m=0; m<12; m++)
     {
         show += accumulate( &milkPrice[y][m][0], &milkPrice[y][m][31], 0.0 );
         show += accumulate(&nightPrice[y][m][0], &nightPrice[y][m][31], 0.0);
     }
     return show;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
double dataRow::getSumOfPrice( )
{
    double show =0.0;
    for(int y=0; y<1; y++)
    {
        for(int m=0; m< 12; m++)
        {
            show += accumulate( &milkPrice[y][m][0], &milkPrice[y][m][31], 0.0);
            show += accumulate(&nightPrice[y][m][0], &nightPrice[y][m][31], 0.0);
        }
    }
    return show;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------
bool operator < (const dataRow& d1, const dataRow& d2)
{
    return d1.cName < d2.cName;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------
bool operator == (const dataRow& d1, const dataRow& d2)
{
    return  d1.cName == d2.cName;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
ostream& operator << (ostream& s, const dataRow& dr)
{
    //double zero = 0.0;
    string emonth[12] = { "Jan",
                      "Feb",
                      "Mar",
                      "Apr",
                      "May",
                      "Jun",
                      "Jul",
                      "Aug",
                      "Sept",
                      "Oct",
                      "Nov",
                      "Dec"  };
    //int eyear[1] = {2017};
    s << dr.cName << "\n";                 //print customer name
    for(int y=0; y<1; y++)
    {
        for(int m =0; m<12; m++)
        {
            for(int d=0; d<31; d++)
            {
                    s << " " << dr.milkQuantity[y][m][d] << " " << dr.milkPrice[y][m][d] << " " << dr.nightQuantity[y][m][d] << " " << dr.nightPrice[y][m][d] ;
            }
            cout << " \n";
        }
        cout << " \n";
    }
    s << endl << endl;
    return s;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool compareRows::operator() (dataRow d1, dataRow d2) const
{
    return d1 < d2;
}

//////////////////////////////////////////methods for class dataRecord/////////////////////////////////////////////////////////////////////////////
dataRecord::~dataRecord()                  //destructor
{
    while( !setDataR.empty())          //delete data rows
    {
        iter = setDataR.begin();
        setDataR.erase(iter);
    }
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
void dataRecord::insertData(string cn, int y, int m, int d, double quantity, double rate, bool select )
{
    dataRow searchRow(cn);    //temp row with same name

    iter = setDataR.begin();                 //search setDataR
    while( iter != setDataR.end())
    {
        if(searchRow == *iter)    //rent found?
        {                          // yes
            dataRow dRo = *iter;
            setDataR.erase(iter);          //remove data from row
            dRo.setData(y, m, d, quantity, rate, select);    //put updated data in row
            setDataR.insert(dRo);
            return ;
        }
        else
            iter++;
    }

    searchRow.setData(y, m, d, quantity, rate, select);   //put data in row
    setDataR.insert(searchRow);    //put in set
}   // end insert data

//--------------------------------------------------------------------------------------------------------------------------------------------------
void dataRecord::writeRow()
{
    ofstream outfile;
    if(setDataR.empty())
        cout << "\n*********** NO DATA ENTERED *************";
    else
    {
        outfile.open("E:/program/my_soft/bin/Debug/custdata.dat",ios::binary);
        if(!outfile){
            cout << "\n    #CAN'T OPEN FILE.";
            return ;
        }
        ostream_iterator<dataRow> oiter(outfile);

        copy(setDataR.begin(), setDataR.end(), oiter);

        if(!outfile)
        {
            cout << "\n    #CAN'T WRITE TO FILE.";
            return ;
        }
    }
}
//------------------------------------------------------------------------------------------------------------------------------------------------
void dataRecord::readRow()
{
    string cName;
    double quan[1][12][31];
    double price[1][12][31];
    double nQuan[1][12][31];
    double nPrice[1][12][31];
    deque<string> qRow;
    deque<string>::iterator diter;
    ifstream infile("E:/program/my_soft/bin/Debug/custdata.dat");
    istream_iterator<string> iiter(infile);
    istream_iterator<string> eof;            //end of file iterator

    if(infile.eof())               //check for end of file
        return ;

    copy(iiter, eof, back_inserter(qRow));           //insert data into deque

    diter = qRow.begin();
    while(diter != qRow.end())
    {
        string a = *diter++;
        string b = *diter++;
        cName = a + " " + b;

            for(int y=0; y<1; y++)
            {
                for(int m=0; m<12; m++)
                {
                    for(int d=0; d<31; d++)
                    {
                        string cunt = *diter++;
                        stringstream geek(cunt);
                        geek>>quan[y][m][d];
                        string fuck = *diter++;
                        stringstream gay(fuck);
                        gay>>price[y][m][d];
                        string qore = *diter++;
                        stringstream qake(qore);
                        qake>>nQuan[y][m][d];
                        string pore = *diter++;
                        stringstream pake(pore);
                        pake>>nPrice[y][m][d];
                    }
                }
            }


       dataRow drr(cName, quan, price, nQuan, nPrice);
       setDataR.insert(drr);

    }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------
void dataRecord::deleteRow()
{
     while( !setDataR.empty())          //delete data rows
    {
        iter = setDataR.begin();
        setDataR.erase(iter);
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------
void dataRecord::display()
{
    cout << "\n\nEnter 'd' for day-wise customer data, "
         << "\n      'm' for month-wise customer data: ";

    char ch  = ' ' ;
    ch = _getch();
switch(ch)
{
case 'd':
    {
    cout << "\n=============================CUSTOMER's DAY-WISE DATA===========================\n";
    string cName;
    double quan[1][12][31];
    double price[1][12][31];
    double nQuan[1][12][31];
    double nPrice[1][12][31];
    deque<string> qRow;
    deque<string>::iterator diter;
    ifstream infile("E:/program/my_soft/bin/Debug/custdata.dat");
    istream_iterator<string> iiter(infile);
    istream_iterator<string> eof;            //end of file iterator

    if(infile.eof())               //check for end of file
        {
            cout << "\n         #NO DATA IN FILE.";
            return ;
        }

    copy(iiter, eof, back_inserter(qRow));           //insert data into deque
    cout << "\n\nEnter 'a' to see all customer data,"
         << "\n      'o' to see any one customer data: ";
    char ch = ' ' ;
    ch = _getch();
    switch(ch){
    case 'a': {
        cout << "\n***************************** All CUSTOMER's DATA******************************\n";
     diter = qRow.begin();
     while(diter != qRow.end())
     {
        string a = *diter++;
        string b = *diter++;
        cName = a + " " + b;


            for(int y=0; y<1; y++)
            {
                for(int m=0; m<12; m++)
                {
                    for(int d=0; d<31; d++)
                    {
                        string cunt = *diter++;
                        stringstream geek(cunt);
                        geek>>quan[y][m][d];
                        string fuck = *diter++;
                        stringstream gay(fuck);
                        gay>>price[y][m][d];
                        string qore = *diter++;
                        stringstream qake(qore);
                        qake>>nQuan[y][m][d];
                        string pore = *diter++;
                        stringstream pake(pore);
                        pake>>nPrice[y][m][d];
                    }
                }
            }


       dataRow drr(cName, quan, price, nQuan, nPrice);
       drr.inDisplay();


    }

    break;
    }
    case 'o':
    {
        cout << "\n***************************SINGLE CUSTOMER's DATA******************************\n";
        cout << "\nEnter full name of customer (Rahul Dangi): ";
        string match;
        getaLine(match);
        diter = qRow.begin();
    while(diter != qRow.end())
    {
        string a = *diter++;
        string b = *diter++;
        cName = a + " " + b;
          for(int y=0; y<1; y++)
            {
                for(int m=0; m<12; m++)
                {
                    for(int d=0; d<31; d++)
                    {
                        string cunt = *diter++;
                        stringstream geek(cunt);
                        geek>>quan[y][m][d];
                        string fuck = *diter++;
                        stringstream gay(fuck);
                        gay>>price[y][m][d];
                        string qore = *diter++;
                        stringstream qake(qore);
                        qake>>nQuan[y][m][d];
                        string pore = *diter++;
                        stringstream pake(pore);
                        pake>>nPrice[y][m][d];
                    }
                }
            }


       dataRow drr(cName, quan, price, nQuan, nPrice);
       if(match == cName){
       drr.inDisplay();
                  }

            }

            break;
    }

    default :
        {
            cout << "\n\n#          OOPs! Invalid Selection.\n";
        }

    }

    deleteRow();
    break;
    }
    case 'm':
        {
        cout << "\n============================CUSTOMER's MONTH-WISE DATA==========================\n";
    string cName;
    double quan[1][12][31];
    double price[1][12][31];
    double nQuan[1][12][31];
    double nPrice[1][12][31];
    deque<string> qRow;
    deque<string>::iterator diter;
    ifstream infile("E:/program/my_soft/bin/Debug/custdata.dat");
    istream_iterator<string> iiter(infile);
    istream_iterator<string> eof;            //end of file iterator

    if(infile.eof())               //check for end of file
        {
            cout << "\n         #NO DATA IN FILE.";
            return ;
        }

    copy(iiter, eof, back_inserter(qRow));           //insert data into deque
    cout << "\n\nEnter 'a' to see all customer data,"
         << "\n      'o' to see any one customer data: ";
    char ch = ' ';
    ch = _getch();
    switch(ch){
    case 'a': {
        cout << "\n***************************** All CUSTOMER's DATA******************************\n";
     diter = qRow.begin();
     while(diter != qRow.end())
     {
        string a = *diter++;
        string b = *diter++;
        cName = a + " " + b;


            for(int y=0; y<1; y++)
            {
                for(int m=0; m<12; m++)
                {
                    for(int d=0; d<31; d++)
                    {
                        string cunt = *diter++;
                        stringstream geek(cunt);
                        geek>>quan[y][m][d];
                        string fuck = *diter++;
                        stringstream gay(fuck);
                        gay>>price[y][m][d];
                        string qore = *diter++;
                        stringstream qake(qore);
                        qake>>nQuan[y][m][d];
                        string pore = *diter++;
                        stringstream pake(pore);
                        pake>>nPrice[y][m][d];
                    }
                }
            }


       dataRow drr(cName, quan, price, nQuan, nPrice);
       drr.outdisplay();


    }

    break;
    }
    case 'o':
    {
        cout << "\n***************************SINGLE CUSTOMER's DATA******************************\n";
        cout << "\nEnter full name of customer (Rahul Dangi): ";
        string match;
        getaLine(match);
        diter = qRow.begin();
    while(diter != qRow.end())
    {
        string a = *diter++;
        string b = *diter++;
        cName = a + " " + b;
          for(int y=0; y<1; y++)
            {
                for(int m=0; m<12; m++)
                {
                    for(int d=0; d<31; d++)
                    {
                        string cunt = *diter++;
                        stringstream geek(cunt);
                        geek>>quan[y][m][d];
                        string fuck = *diter++;
                        stringstream gay(fuck);
                        gay>>price[y][m][d];
                        string qore = *diter++;
                        stringstream qake(qore);
                        qake>>nQuan[y][m][d];
                        string pore = *diter++;
                        stringstream pake(pore);
                        pake>>nPrice[y][m][d];
                    }
                }
            }


       dataRow drr(cName, quan, price,nQuan, nPrice);
       if(match == cName){
       drr.outdisplay();
                  }

            }

            break;
    }

    default :
        {
            cout << "\n\n#             OOPs! Invalid selection.\n";
        }

    }

    deleteRow();
        break;
        }
    default:
        cout << "\n\n#            OOPs! Invalid Selection.\n";
}

}

//---------------------------------------------------------------------------------------------------------------------------------------------
double dataRecord::getQuantity(int y, int m)
{
    double sumQuantity = 0.0;
    readRow();
    iter = setDataR.begin();
    while(iter != setDataR.end())
    {
        dataRow ddr = *iter;
        sumQuantity += ddr.getSumOfQuantity(y, m);
        iter++;
    }

    return sumQuantity;
}

//----------------------------------------------------------------------------------------------------------------------------------------------
double dataRecord::getQuantity(int y)
{
    double sumQuantity = 0.0;
    readRow();
    iter = setDataR.begin();
    while(iter != setDataR.end())
    {
        dataRow ddr = *iter;
        sumQuantity += ddr.getSumOfQuantity(y);
        iter++;
    }

    return sumQuantity;
}

//----------------------------------------------------------------------------------------------------------------------------------------------
double dataRecord::getQuantity( )
{
    double sumQuantity = 0.0;
    readRow();
    iter = setDataR.begin();
    while(iter != setDataR.end())
    {
        dataRow ddr = *iter;
        sumQuantity += ddr.getSumOfQuantity();
        iter++;
    }

    return sumQuantity;
}

//-----------------------------------------------------------------------------------------------------------------------------------------
double dataRecord::getPrice(int y, int m)
{
    double sumPrice = 0.0;
    readRow();
    iter = setDataR.begin();
    while(iter != setDataR.end())
    {
        dataRow ddr = *iter;
        sumPrice += ddr.getSumOfPrice(y, m);
        iter++;
    }

    return sumPrice;
}

//----------------------------------------------------------------------------------------------------------------------------------------------
double dataRecord::getPrice(int y)
{
    double sumPrice = 0.0;
    readRow();
    iter = setDataR.begin();
    while(iter != setDataR.end())
    {
        dataRow ddr = *iter;
        sumPrice += ddr.getSumOfPrice(y);
        iter++;
    }

    return sumPrice;
}

//----------------------------------------------------------------------------------------------------------------------------------------------
double dataRecord::getPrice()
{
    double sumPrice = 0.0;
    readRow();
    iter = setDataR.begin();
    while(iter != setDataR.end())
    {
        dataRow ddr = *iter;
        sumPrice += ddr.getSumOfPrice();
        iter++;
    }

    return sumPrice;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
void dataRecord::annualReport()
{
    cout << "\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ANNUAL REPORT~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << "_____________________________________________________________________________\n";
    deleteRow();
    readRow();
    int aYear[1] = {2017};
    string aMonth[12] = { "Jan",
                      "Feb",
                      "Mar",
                      "Apr",
                      "May",
                      "Jun",
                      "Jul",
                      "Aug",
                      "Sept",
                      "Oct",
                      "Nov",
                      "Dec"  };
    for(int y=0; y<1; y++)
    {
        cout << left << setw(7) << aYear[y] << endl;
        bool that = true;
        for(int m=0; m<12; m++)
        {
            if(that)
            {
                cout << left << setw(10) << "Month" << left << setw(10) << "Quantity" << "     " << left << setw(10) << "Price" << endl;
                that = false;
            }
            cout << left << setw(10) << aMonth[m] << left << setw(10) << getQuantity(y, m) << "L    " << left << setw(10) << getPrice(y , m) << "Rs.\n";
        }
        cout << "\n---------------------------------------------\n";
        cout << left << setw(10) << "Total" << left << setw(10) << getQuantity(y) << "     " << left << setw(10) << getPrice(y) << "Rs." << endl;
        cout << endl << endl;
    }

    deleteRow();
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

/////////////////////////////////////////////methods for class dataInputScreen///////////////////////////////////////////////////////////////////
void dataInputScreen::getData()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    bool moeve;
    string aMonth[12] = { "Jan",
                      "Feb",
                      "Mar",
                      "Apr",
                      "May",
                      "Jun",
                      "Jul",
                      "Aug",
                      "Sept",
                      "Oct",
                      "Nov",
                      "Dec"  };
    double mRate[2] = { 26.1, 38.2};
    inDataRecord.readRow();
    inCustList.readData();
    cout << "\nEnter customer's reference number: ";
    cin >> refNumber;
    cin.ignore(80, '\n');

    custName = inCustList.getCustomerNa(refNumber);
    if(custName != "")   //if name found
    {
        cout << "\nDate: " << ltm->tm_mday << " " << aMonth[1 + ltm->tm_mon] << " " << 1900 + ltm->tm_year << endl;
        year = 1900 + ltm->tm_year;
        year = year - 2017;
        month = 1 + ltm->tm_mon;
        month--;
        int hour;
        hour = 1+ltm->tm_hour;
        if(hour >= 6 && hour <= 8)
        {
            day = ltm->tm_mday;
            day--;
            cout << "Enter milk quantity in liter (e.g.  2.3): ";
           cin >> mQuantity;
           cin.ignore(80, '\n');
           cout << "Enter Milk Type\n";
           cout << "Enter '0' for Cow Milk and '1' for Buffalo Milk: ";
           int lay;
           cin >> lay;
           cin.ignore(80, '\n');
           rate = mRate[lay];
           moeve = true;
        }
        else if(hour >= 18 && hour <= 20)
        {
            day = ltm->tm_mday;
            day--;
            cout << "Enter milk quantity in liter (e.g.  2.3): ";
           cin >> mQuantity;
           cin.ignore(80, '\n');
           cout << "Enter Milk Type\n";
           cout << "Enter '0' for Cow Milk and '1' for Buffalo Milk: ";
          int lay;
          cin >> lay;
          cin.ignore(80, '\n');
          rate = mRate[lay];
          moeve = false;
        }
        else
        {
           cout << "\nEnter 'm' for morning,"
                << "\n      'e' for evening: ";
            char eve = ' ';
            eve = _getch();

            bool check = true;
           while(check)
           {
               switch(eve)
               {
               case 'm':
                   {
                       cout << "\nEnter day: ";
                 cin >> day;
                 cin.ignore(80, '\n');
                 day--;
                       cout << "Enter milk quantity in liter (e.g.  2.3): ";
           cin >> mQuantity;
           cin.ignore(80, '\n');
           cout << "Enter Milk Type\n";
           cout << "Enter '0' for Cow Milk and '1' for Buffalo Milk: ";
           int lay;
           cin >> lay;
           cin.ignore(80, '\n');
           rate = mRate[lay];
           moeve = true;
           check = false;
           break;
                   }
               case 'e':
                {
                    cout << "\nEnter day: ";
                 cin >> day;
                 cin.ignore(80, '\n');
                 day--;
                       cout << "Enter milk quantity in liter (e.g.  2.3): ";
           cin >> mQuantity;
           cin.ignore(80, '\n');
           cout << "Enter Milk Type\n";
           cout << "Enter '0' for Cow Milk and '1' for Buffalo Milk: ";
           int lay;
           cin >> lay;
           cin.ignore(80, '\n');
           rate = mRate[lay];
           moeve = false;
           check = false;
           break;
                }
               default:
                   cout << "\n\n#         OOPs Select Again.\n";


               }
           }

        }



        inDataRecord.insertData(custName, year, month, day, mQuantity, rate, moeve);
        inDataRecord.writeRow();
    }
    else
        cout << "\n\n      #NO CUSTOMER WITH THAT NAME.\n";


    inCustList.deleteCust();
    inDataRecord.deleteRow();
} // end getData
//----------------------------------------------------------------------------------------------------------------------------------------------------

/////////////////////////////////////////methods for class userInterface//////////////////////////////////////////////////////////////////////////////
userInterface::userInterface()
{
    // empty constructor
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------
userInterface::~userInterface()
{
    // empty destructor
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
void userInterface::interact()
{
    ch = ' ';
    customerList userCustomerList;
    dataRecord   userDataRecord;
    customerInputScreen userCustomerInputScreen(userCustomerList);
    dataInputScreen userDataInputScreen(userCustomerList, userDataRecord);


    cout << "#@                        You Welcome! "
        << "\n    #@This is a software to record data on Milk Dairy,\n"
        << "                             #@Created By: \n"
        << "                                             #RD_Square\n"
        << "                                 #@from JK_Lakshmipat University";


    while(true)
    {
         time_t now = time(0);                      //get current date and time
         char* dt = ctime(&now);                    // convert to string

         cout << "\n\n----------------------------------------------------------------------\n";
         cout << "Current Time/Date:           " << dt ;
         cout << "\n----------------------------------------------------------------------\n\n";
        cout << "\nEnter 'i' to input data,"
         << "\n      'd' to display data,"
         << "\n      'q' to quit program: ";

        ch = _getch();
        if(ch == 'i')
        {
            cout << endl << endl;
            cout << "\nEnter 'n' to add new customer,"
                 << "\n      'r' to record milk data: ";
            ch = _getch();

            switch(ch)
            {
            case 'n':
                userCustomerInputScreen.getCustomer();
                break;
            case 'r':
                userDataInputScreen.getData();
                break;
            default:
                cout << "\n\n#          OOPs! Invalid Selection.\n";
                break;
            }
        }

        else if(ch == 'd')
        {
            cout << endl << endl;
            cout << "\nEnter 'c' to display Customers,"
                 << "\n      'l' to display Data List,"
                 << "\n      'a' to display Annual Report: ";
            ch = _getch();

            switch(ch)
            {
            case 'c':
                userCustomerList.display();
                break;
            case 'l':
                userDataRecord.display();
                break;
            case 'a':
                userDataRecord.annualReport();
                break;
            default:
                cout << "\n\n#                OOPs Invalid Selection.\n";
                break;
            }   //end switch
        }

        else if(ch == 'q')
            return;    // quit

        else
            cout << "\n\n#OOPs! Invalid Selection. Please select again ~ \n\n";

    }
}
