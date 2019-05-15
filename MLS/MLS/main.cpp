#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class Transaction
{
public:
    Transaction();
    Transaction(char type, string date, int id, double amount);
    virtual void Display()=0;
    virtual double EarnPoints()=0;
    char get_transaction_type() const;
    double get_transaction_amount() const;
    string get_transaction_date() const;
    int get_transaction_id() const;
    void set_transaction_type(char type);
    void set_transaction_amount(double amount);
    void set_transaction_date(string date);
    void set_transaction_id(int id);
    bool operator==(Transaction* other);
    virtual ~Transaction();
protected:
    char transaction_type_;
    string transaction_date_;
    int transaction_id_;
    double transaction_amount_;
};

Transaction::Transaction()
{
    transaction_type_ = ' ';
    transaction_date_ = "";
    transaction_id_ = 0;
    transaction_amount_ = 0.0;
}

Transaction::Transaction(char type, string date, int id, double amount)
{
    transaction_type_ = type;
    transaction_date_ = date;
    transaction_id_ = id;
    transaction_amount_ = amount;
}

bool Transaction::operator== (Transaction* other)
{
    return ((transaction_date_ == other->transaction_date_) && (transaction_amount_ == other->transaction_amount_));
}

char Transaction::get_transaction_type() const
{
    return transaction_type_;
}

double Transaction::get_transaction_amount() const
{
    return transaction_amount_;
}

string Transaction::get_transaction_date() const
{
    return transaction_date_;
}

int Transaction::get_transaction_id() const
{
    return transaction_id_;
}

void Transaction::set_transaction_type(char type)
{
    transaction_type_ = type;
}

void Transaction::set_transaction_amount(double amount)
{
    transaction_amount_ = amount;
}

void Transaction::set_transaction_date(string date)
{
    transaction_date_ = date;
}

void Transaction::set_transaction_id(int id)
{
    transaction_id_ = id;
}

Transaction::~Transaction()
{
    cout << "Transaction " << transaction_id_ << " destroyed..."<< endl;
}


class GroceryTransaction: public Transaction
{
public:
    GroceryTransaction();
    GroceryTransaction(char type, string date, int id, double amount, string name);
    void set_store_name(string name);
    string get_store_name() const;
    void Display();
    double EarnPoints();
    virtual ~GroceryTransaction();
private:
    string store_name_;
};


GroceryTransaction::GroceryTransaction():Transaction()
{
    transaction_type_ = ' ';
    transaction_date_ = "";
    transaction_id_ = 0;
    transaction_amount_ = 0.0;
    store_name_ = "";
}


GroceryTransaction::GroceryTransaction(char type, string date, int id, double amount, string name):Transaction(type, date, id, amount)
{
    transaction_type_ = type;
    transaction_date_ = date;
    transaction_id_ = id;
    transaction_amount_ = amount;
    store_name_ = name;
}

void GroceryTransaction::set_store_name(string name)
{
    store_name_ = name;
}

string GroceryTransaction::get_store_name() const
{
    return store_name_;
}

void GroceryTransaction::Display()
{
    cout.width(13);
    cout << left << get_transaction_date();
    cout.width(15);
    cout << left << "Grocery";
    cout.width(30);
    cout << left << get_store_name();
    cout.width(1);
    cout << "$";
    cout.width(8);
    cout << setprecision(2);
    cout << right << get_transaction_amount();
    cout << endl;
}


double GroceryTransaction::EarnPoints()
{
    return get_transaction_amount()*2.5;
}


GroceryTransaction::~GroceryTransaction()
{
    cout << "Transaction Grocery destroyed..." << endl;
}


class BankingTransaction: public Transaction
{
public:
    BankingTransaction();
    BankingTransaction(char type, string date, int id, double amount, string withdrawal, double fee);
    void set_transaction_withdrawal(string withdrawal);
    void set_fee_charge(double fee);
    string get_transaction_withdrawal() const;
    double get_fee_charge() const;
    void Display();
    double EarnPoints();
    virtual ~BankingTransaction();
private:
    string transaction_withdrawal_;
    double fee_charge_;
};



BankingTransaction::BankingTransaction():Transaction()
{
    transaction_type_ = ' ';
    transaction_date_ = "";
    transaction_id_ = 0;
    transaction_amount_ = 0.0;
    transaction_withdrawal_ = "";
    fee_charge_ = 0;
}


BankingTransaction::BankingTransaction(char type, string date, int id, double amount, string withdrawal, double fee):Transaction(type, date, id, amount)
{
    transaction_type_ = type;
    transaction_date_ = date;
    transaction_id_ = id;
    transaction_amount_ = amount;
    transaction_withdrawal_ = withdrawal;
    fee_charge_ = fee;
}



double BankingTransaction::get_fee_charge() const
{
    return fee_charge_;
}

string BankingTransaction::get_transaction_withdrawal() const
{
    return transaction_withdrawal_;
}

void BankingTransaction::set_fee_charge(double fee)
{
    fee_charge_ = fee;
}

void BankingTransaction::set_transaction_withdrawal(string withdrawal)
{
    transaction_withdrawal_ = withdrawal;
}

void BankingTransaction::Display()
{
    cout.width(13);
    cout << left << get_transaction_date();
    cout.width(15);
    cout << left << "Banking";
    cout.width(30);
    cout << left << (get_transaction_withdrawal() + " withdrawal");
    cout.width(1);
    cout << "$";
    cout.width(8);
    cout << setprecision(2);
    cout << right << get_transaction_amount();
    cout << endl;
}


double BankingTransaction::EarnPoints()
{
    return 0;
}


BankingTransaction::~BankingTransaction()
{
    cout << "Transaction Banking destroyed..." << endl;
}



class DepartmentStoreTransaction: public Transaction
{
public:
    DepartmentStoreTransaction();
    DepartmentStoreTransaction(char type, string date, int id, double amount, string name, int policy);
    void set_store_name(string name);
    void set_return_policy(int policy);
    string get_store_name() const;
    int get_return_policy() const;
    void Display();
    double EarnPoints();
    virtual ~DepartmentStoreTransaction();
private:
    string store_name_;
    int return_policy_;
};



DepartmentStoreTransaction::DepartmentStoreTransaction():Transaction()
{
    transaction_type_ = ' ';
    transaction_date_ = "";
    transaction_id_ = 0;
    transaction_amount_ = 0.0;
    store_name_ = "";
    return_policy_ = 0;
}



DepartmentStoreTransaction::DepartmentStoreTransaction(char type, string date, int id, double amount, string name, int policy):Transaction(type, date, id, amount)
{
    transaction_type_ = type;
    transaction_date_ = date;
    transaction_id_ = id;
    transaction_amount_ = amount;
    store_name_ = name;
    return_policy_ = policy;
}

void DepartmentStoreTransaction::set_store_name(string name)
{
    store_name_ = name;
}

string DepartmentStoreTransaction::get_store_name() const
{
    return store_name_;
}

void DepartmentStoreTransaction::set_return_policy(int policy)
{
    return_policy_ = policy;
}

int DepartmentStoreTransaction::get_return_policy() const
{
    return return_policy_;
}



void DepartmentStoreTransaction::Display()
{
    cout.width(13);
    cout << left << get_transaction_date();
    cout.width(15);
    cout << left << "Department";
    cout.width(30);
    cout << left << (get_store_name() + ", return in " + to_string(get_return_policy()) + " days");
    cout.width(1);
    cout << "$";
    cout.width(8);
    cout << setprecision(2);
    cout << right << get_transaction_amount();
    cout << endl;
}


double DepartmentStoreTransaction::EarnPoints()
{
    return get_transaction_amount()*1.5;
}


DepartmentStoreTransaction::~DepartmentStoreTransaction()
{
    cout << "Transaction Department Store destroyed..." << endl;
}


class Customer
{
public:
    Customer();
    Customer(string name, string number, double balance);
    void set_customer_name(string name);
    void set_card_number(string number);
    void set_transaction_balance(double balance);
    void set_rewards_points(double points);
    string get_customer_name() const;
    string get_card_number() const;
    double get_transaction_balance() const;
    double get_rewards_points() const;
    Transaction* get_transaction_from_array(int location);
    void ReadTransactions();
    void ReportAllTransactions();
    void ReportRewardSummary();
    ~Customer();
protected:
    string customer_name_;
    string card_number_;
    double transaction_balance_;
    double rewards_points_;
    Transaction* transactions_[16];
};



Customer::Customer()
{
    customer_name_ = "";
    card_number_ = "";
    transaction_balance_ = 0.0;
    rewards_points_ = 1000;
    for (int i=0; i< 16; i++)
    {
        transactions_[i] = NULL;
    }
}



Customer::Customer(string name, string number, double balance)
{
    customer_name_ = name;
    card_number_ = number;
    transaction_balance_ = balance;
    rewards_points_ = 1000;
    for (int i=0; i< 16; i++)
    {
        transactions_[i] = NULL;
    }
}



string Customer::get_customer_name() const
{
    return customer_name_;
}

string Customer::get_card_number() const
{
    return card_number_;
}

double Customer::get_transaction_balance() const
{
    return transaction_balance_;
}

double Customer::get_rewards_points() const
{
    return rewards_points_;
}

Transaction* Customer::get_transaction_from_array(int location)
{
    return transactions_[location];
}

void Customer::set_customer_name(string name)
{
    customer_name_ = name;
}

void Customer::set_card_number(string number)
{
    card_number_ = number;
}

void Customer::set_transaction_balance(double balance)
{
    transaction_balance_ = balance;
}

void Customer::set_rewards_points(double points)
{
    rewards_points_ = points;
}

void Customer::ReadTransactions()
{
    ifstream file ("bill.txt");
    Transaction* transaction = NULL;
    int count = 0;
    char type;
    string date;
    int id;
    double amount;
    string buffer;
    int policy;
    string withdrawal;
    string store;
    double fee;
    if (!file)
    {
        cout << "ERROR: Failed to open input file\n";
        exit(-1);
    }
    while (getline(file, buffer, '~') )
    {
        type = buffer[0];
        getline(file, buffer, '~');
        date = buffer;
        getline(file, buffer, '~');
        id = atol(buffer.c_str());
        getline(file, buffer, '~') ;
        amount = atof(buffer.c_str());
        switch (type)
        {
            case 'D':
            {
                getline(file, buffer, '~');
                store = buffer;
                getline(file, buffer, '\n');
                policy= atol(buffer.c_str());
                transaction = new DepartmentStoreTransaction(type, date, id, amount, store, policy);
                transactions_[count] = dynamic_cast <DepartmentStoreTransaction*>(transaction);
                break;
            }
            case 'G':
            {
                getline(file, buffer, '\n');
                store = buffer;
                transaction = new GroceryTransaction(type, date, id, amount, store);
                transactions_[count] = dynamic_cast <GroceryTransaction*>(transaction);
                break;
            }
            case 'B':
            {
                getline(file, buffer, '~');
                withdrawal = buffer;
                getline(file, buffer, '\n');
                fee = atof(buffer.c_str());
                transaction = new BankingTransaction(type, date, id, amount, withdrawal, fee);
                transactions_[count] = dynamic_cast <BankingTransaction*>(transaction);
                break;
            }
        }
        ++count;
    }
}


void Customer::ReportAllTransactions()
{
    double total_fee = 0.0;
    double total_department = 0.0;
    double total_grocery = 0.0;
    double total_banking = 0.0;
    int count_department = 0;
    int count_grocery = 0;
    int count_banking = 0;
    cout << "***********************Transactions Listings***********************" << endl;
    for (int i=0; i< 16; i++)
    {
        cout << fixed;
        transactions_[i]->Display();
        if (transactions_[i]->get_transaction_type() == 'B')
        {
            total_fee += dynamic_cast <BankingTransaction*>(transactions_[i])->get_fee_charge();
            total_banking += transactions_[i]->get_transaction_amount();
            ++count_banking;
        }
        if (transactions_[i]->get_transaction_type() == 'G')
        {
            total_grocery += transactions_[i]->get_transaction_amount();
            ++count_grocery;
        }
        if (transactions_[i]->get_transaction_type() == 'D')
        {
            total_department += transactions_[i]->get_transaction_amount();
            ++count_department;
        }
        
        set_transaction_balance(get_transaction_balance()+transactions_[i]->get_transaction_amount());
    }
    cout << "*******************************************************************" << endl;
    cout << endl;
    cout << endl;
    cout << fixed;
    cout << "Total Fee Charge: $";
    cout << setprecision(2) << total_fee << endl;
    cout << "Total Balance:    $";
    cout << setprecision(2) << (get_transaction_balance() + total_fee) << endl;
    cout << endl;
    cout << "*******************************Transactions Summary*******************************" << endl;
    cout << "Transaction Type                  Transaction Count                Total Purchase" << endl;
    cout << "Department Store                          " << count_department << "                               $" << total_department << endl;
    cout << "Banking                                   " << count_banking << "                               $" << total_banking << endl;
    cout << "Grocery                                   " << count_grocery << "                               $" << total_grocery << endl;
    cout << "___________________________________________________________________________________" << endl;
    cout << "                                                                         $" << get_transaction_balance() << endl;
}

void Customer::ReportRewardSummary()
{
    double department_points = 0.0;
    double grocery_points = 0.0;
    for (int i=0; i<16; i++)
    {
        if (transactions_[i]->get_transaction_type() == 'D')
        {
            department_points += dynamic_cast<DepartmentStoreTransaction*>(transactions_[i])->EarnPoints();
        }
        if (transactions_[i]->get_transaction_type() == 'G')
        {
            grocery_points += dynamic_cast<GroceryTransaction*>(transactions_[i])->EarnPoints();
        }
    }
    cout << "Rewards Summary for " << get_customer_name() << " " << get_card_number().substr(get_card_number().length()-4) << endl;
    cout << "     Previous points balance               " << get_rewards_points() << endl;
    cout << "     + Department Store Purchases          " << department_points << endl;
    cout << "     + Grocery Purchases                   " << grocery_points << endl;
    cout << "    ____________________________________________________" << endl;
    cout << "     = Total Points Available for Redemption    " << (get_rewards_points() + department_points + grocery_points) << endl;
}

Customer::~Customer()
{
    for (int i=0; i < 16; i++)
    {
        delete transactions_[i];
    }
}



int main() {
    Customer* p_customer = NULL;
    p_customer = new Customer("Alexa Intosh", "4532 0198 7531 2778", 0);
    p_customer->ReadTransactions();
    p_customer->ReportAllTransactions();
    p_customer->ReportRewardSummary();
    cout << endl;
    Transaction* p = p_customer->get_transaction_from_array(0);
    Transaction* q = p_customer->get_transaction_from_array(2);
    cout << "Overloaded Operator Test #1:" << endl;
    cout << "     Expected: 0" << endl;
    cout << "          Got: " << (*p_customer->get_transaction_from_array(0) == p_customer->get_transaction_from_array(1)) << endl;
    cout << endl;
    cout << "Overloaded Operator Test #2:" << endl;
    cout << "     Expected: 1" << endl;
    cout << "          Got: " << (*p_customer->get_transaction_from_array(2) == p_customer->get_transaction_from_array(9)) << endl;
    cout << endl;
    cout << "Overloaded Operator Test #3:" << endl;
    cout << "     Expected: 0" << endl;
    cout << "          Got: " << (*p_customer->get_transaction_from_array(5) == p_customer->get_transaction_from_array(7)) << endl;
    cout << endl;
    cout << "Overloaded Operator Test #4:" << endl;
    cout << "     Expected: 1" << endl;
    cout << "          Got: " << (*p_customer->get_transaction_from_array(14) == p_customer->get_transaction_from_array(15)) << endl;
    cout << endl;
    delete p_customer;
    exit(0);
}
