#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <iomanip>
using namespace std;

class Property  {
private:
    Property * next;
protected:
    string address_;
    int zip_;
    double price_;
    int year_;
public:
    Property();
    Property(string address, int zip, double price, int year);
    virtual ~Property();
    
    string get_address() const {return address_;};
    int get_zip() const {return zip_;};
    double get_price() const {return price_;};
    int get_year() const {return year_;};
    Property *  get_next() const {return next;};
    
    void set_next(Property * p_property) { next = p_property;};
    void set_address(string address) {address_ = address;};
    void set_zip(int zip) {zip_=zip;};
    void set_price(double price){price_ = price;};
    void set_year(int year) {year_ = year;};
    
    // ShowPropertyInfo as pure virtual function
    virtual void ShowPropertyInfo() const = 0;
   
    //overload <= operator
    const  Property &  operator<= (const Property & right);
};

Property::Property() {
    next = NULL;
    address_ = "";
    zip_ = 0;
    price_ = 0.0;
    year_ = 0;
}


Property::Property(string address, int zip, double price, int year) {
    next = NULL;
    address_ = address;
    zip_ = zip;
    price_ = price;
    year_ = year;
}

Property::~Property() {
}

//__________________

class SingleFamilyHouse :  public Property  {
    private:
        double backyardArea_;
    public:
        SingleFamilyHouse();
        SingleFamilyHouse(string address, int zip, double price, int year, double backyardArea);
        virtual ~SingleFamilyHouse(); 
        virtual void ShowPropertyInfo() const;
        double get_backyardArea() const;
        void set_backyardArea(double backyardArea);
};

SingleFamilyHouse::SingleFamilyHouse(){
    backyardArea_ = 0.0;
}

SingleFamilyHouse::SingleFamilyHouse(string address, int zip, double price, int year, double backyardArea)
:Property(address, zip, price, year) {
    backyardArea_ = backyardArea;
}

SingleFamilyHouse::~SingleFamilyHouse(){
}

double SingleFamilyHouse::get_backyardArea() const {
    return backyardArea_;
}

void SingleFamilyHouse::set_backyardArea(double backyardArea) {
    backyardArea_ = backyardArea;
}

void SingleFamilyHouse::ShowPropertyInfo() const {
    cout << left;
    cout << setw(20) << "SFH";
    cout << address_ << ";" << zip_ << ";" << price_ << ";" << year_ << ";";
    cout << backyardArea_ << endl;
}
//______

class TownHouse :  public Property  {
    private:
        double HOAFee_;
    public:
        TownHouse();
        TownHouse(string address, int zip, double price, int year, double HOAFee);
        virtual ~TownHouse(); // constructors/destructor
        virtual void ShowPropertyInfo() const;
        double get_HOAFee() const;
        void set_HOAFee(double HOAFee);
};

TownHouse::TownHouse(){
    HOAFee_ = 100.0;
}

TownHouse::TownHouse(string address, int zip, double price, int year, double HOAFee)
:Property(address, zip, price, year) {
    HOAFee_ = HOAFee;
}

TownHouse::~TownHouse() {
}

double TownHouse::get_HOAFee() const {
    return HOAFee_;
}

void TownHouse::set_HOAFee(double HOAFee) {
    HOAFee_ = HOAFee;
}

void TownHouse::ShowPropertyInfo() const {
    cout << left;
    cout << setw(20) << "Townhouse";
    cout << address_ << ";" << zip_ << ";" << price_ << ";" << year_ <<";";
    cout << HOAFee_ << endl;
}

//___________
class PropertyList {
private:
    Property * head;
public:
    PropertyList();
    ~PropertyList(); // constructors/destructor
     void  ViewAllProperties() ;
  //  Property * SearchByZipcode(int zip) ;
    void Init();
    void Insert(Property * p_property);
    Property * get_next();
    Property * set_next();
    
};

PropertyList::PropertyList() {
    head = NULL;
}

PropertyList::~PropertyList() {
    head = NULL;
}

void PropertyList::Init()  {
    Insert (new SingleFamilyHouse("123 First Street, San Jose, CA ", 95112,450000,1956,5000.0 ));
    Insert (new TownHouse("234 Hillview Ave. #245, Milpitas, CA ", 95023,670000,2010,250.0 ));
    Insert (new SingleFamilyHouse ("787 Adam Street, San Jose, CA", 95123,750000,1980,7000.0 ));
    Insert (new SingleFamilyHouse ("2580 Albert Ave., Sunnyvale, CA", 94086,1250000,2010,3000.0 ));
}

void PropertyList::Insert(Property * p_property) {
    p_property->set_next(head) ;
    head = p_property;
}

void PropertyList::ViewAllProperties() {
    Property * p = head;
    while (p!=NULL) {
        cout << p-> get_address() << endl;
        p = p->get_next();
    }
}

/*Property * PropertyList:: SearchByZipcode(int zip)  {
    Property  *  p_node = head;
    PropertyList * p_result;
    while (p_node != NULL) {
        if ( p_node->get_zip() == zip)
            cout << p_node->get_address() << "," << p_node->get_price() << "," << p_node->get_year() << endl;
        p_node = p_node->get_next();
    }
    return p_result;  // out of the loop without finding a match.
} */
//----------
class MLSListings {
private:
    PropertyList * properties;
    char getUserOption();
public:
    MLSListings();
    ~MLSListings(); // constructors/destructor
    void displayMenu();
    void run();
//    PropertyList * searchTownhouseByMaxPrice(double price) const;
//    PropertyList * searchTownhouseByZipCode(int zip) const;
};

MLSListings::MLSListings () {
    properties = new PropertyList();
    properties->Init();
}

MLSListings::~MLSListings() {
    delete properties;
}

void MLSListings::displayMenu() {
    cout<< "MLSListings options menu" << endl;
    cout << " 1. View all properties " << endl;
    cout << "2. Search Townhouse by zip code" << endl;
    cout << "3. Search properties by max price" << endl;
    cout << "4. Quit" << endl;
    cout << "Your choice: " << endl;
}

char MLSListings::getUserOption() {
    char selection;
    cin >> selection;
    return selection;
}

void MLSListings::run() {
    displayMenu();
    char selection = getUserOption();
    while (true) {
            if (selection == '1') {
                    properties->ViewAllProperties();
                    cout << "1";
            }
            else if (selection == '2') {
                cout << "2";
                       int myZip;
                       cout << " enter a zipcode: ";
                       cin >> myZip;
               //        properties->SearchByZipcode(myZip);
              //  if ( properties->SearchByZipcode(myZip) == NULL ) {
              //      cout << "can't find";
              //  }
            }
            else if (selection == '3') {
                    cout << "search by price";
            }
            else if (selection == '4') {
                    cout << "bye" << endl;
                    break;
            }
            selection = getUserOption();
        }
}

int main() {
    MLSListings *mls = new MLSListings();
    mls->run();
    delete mls;
}
