#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <iomanip>
#include <exception>
#include <fstream>
using namespace std;

class Message { //abstract
private:
    string from_;
    string to_;
    
public:
    Message();
    Message(string from, string to);
    virtual ~Message();
    
    string get_from() const;
    void set_from(string from);
    string get_to() const;
    void set_to(string to) ;
    
    virtual double ComputeCharge() const = 0;
    
    bool operator== (const Message &message) const;
};

class TextMessage: public Message {
private:
    string textmessage_;
    
public:
    TextMessage();
    TextMessage(string from, string to, string textmessage);
    virtual ~TextMessage();
    
    string get_text_message() const;
    void set_text_message(string textmessage);
    
    virtual double ComputeCharge() const;
    
    friend ostream & operator<<(ostream & os, const TextMessage & t1);
    
};

class VoiceMessage: public Message {
private:
    int time_;
    
public:
    VoiceMessage();
    VoiceMessage(string from, string to, int time);
    virtual ~VoiceMessage();
    
    int get_time() const;
    void set_time(int time);
    
    virtual double ComputeCharge() const;
    
    friend ostream & operator<<(ostream & os, const VoiceMessage & v1);
};

class MediaMessage: public Message {
private:
    int media_size_;
    
public:
    MediaMessage();
    MediaMessage(string from, string to, int media_size);
    virtual ~MediaMessage();
    
    int get_media_size() const;
    void set_media_size(int media_size);
    
    virtual double ComputeCharge() const;
    
    friend ostream & operator<<(ostream & os, const MediaMessage & m1);
};

class SmartCarrier {
private:
    string carrier_name_;
    map<string, vector<Message *> > accounts_;
    
    void Menu();
    int GetChoice();
    void ListAll();
    void SearchMessage();
    void EraseMessage();
    void DisconnectAccount();
    void StopService();
    
public:
    SmartCarrier();
    SmartCarrier(string carrier_name);
    ~SmartCarrier();

    string get_carrier_name() const;
    void set_carrier_name(string carrier_name);
    const map<string, vector<Message *> > & get_accounts() const;
    
    void Init();
    void StartService();
};

Message::Message(): from_(""), to_("") {};
Message::Message(string from, string to): from_(from), to_(to) {};
Message::~Message() {};
string Message::get_from() const { return from_; };
void Message::set_from(string from) { from_ = from; };
string Message::get_to() const { return to_; };
void Message::set_to(string to) { to_=to; };
double Message::ComputeCharge() const { return 0.0; }; // pure virtual function with implementation
bool Message::operator== (const Message &message) const {
    return (this->from_ == message.get_from() && this->to_ == message.get_to());
};

TextMessage::TextMessage(): Message(), textmessage_("") {};
TextMessage::TextMessage(string from, string to, string text_message): Message(from, to), textmessage_(text_message) {};
TextMessage::~TextMessage() {};
string TextMessage::get_text_message() const { return textmessage_; };
void TextMessage::set_text_message(string text_message) { textmessage_ = text_message; };
double TextMessage::ComputeCharge() const { return .20; };
ostream & operator<<(ostream & os, const TextMessage & t1) {
    os << "From: " << t1.get_from() << "\t To: " << t1.get_to() << "\t Message: " << t1.get_text_message();
    return os;
}

VoiceMessage::VoiceMessage(): Message(), time_(0) {};
VoiceMessage::VoiceMessage(string from, string to, int time): Message(from, to), time_(time) {};
VoiceMessage::~VoiceMessage() {};
int VoiceMessage::get_time() const { return time_; };
void VoiceMessage::set_time(int time) { time_=time; };
double VoiceMessage::ComputeCharge() const { return .15 * this->time_; };
ostream & operator<<(ostream & os, const VoiceMessage & v1) {
    os << "From: " << v1.get_from() << "\t To: " << v1.get_to() << "\t Length of Voice Message: " << v1.get_time();
    return os;
}

MediaMessage::MediaMessage(): Message(), media_size_(0) {};
MediaMessage::MediaMessage(string from, string to, int media_size): Message(from, to), media_size_(media_size) {};
MediaMessage::~MediaMessage() {};
int MediaMessage::get_media_size() const { return media_size_; };
void MediaMessage::set_media_size(int media_size) { media_size_ = media_size; };
double MediaMessage::ComputeCharge() const { return .1*this->media_size_; }; // 10 cents per size
ostream & operator<<(ostream & os, const MediaMessage & m1) {
    os << "From: " << m1.get_from() << "\t To: " << m1.get_to() << "\t Size of Media Message: " << m1.get_media_size();
    return os;
}

SmartCarrier::SmartCarrier(): carrier_name_("") {}
SmartCarrier::SmartCarrier(string carrier_name): carrier_name_(carrier_name) {};
SmartCarrier::~SmartCarrier() {
    map<string, vector<Message * > >::iterator m_iter;
    vector<Message *>::iterator v_iter;
    for (m_iter = accounts_.begin(); m_iter != accounts_.end(); ++m_iter) {
        for (v_iter = m_iter->second.begin(); v_iter != m_iter->second.end(); ++v_iter) {
            delete (*v_iter);
        }
        m_iter -> second.clear();
    }
    accounts_.clear();
};

string SmartCarrier::get_carrier_name() const { return carrier_name_;};
void SmartCarrier::set_carrier_name(string carrier_name) { carrier_name_ = carrier_name; };
const map<string, vector<Message *> >& SmartCarrier::get_accounts() const { return accounts_; };

void SmartCarrier::Init() {
    accounts_["650-267-1289"].push_back(new TextMessage("650-267-1289", "408-235-1500", "Do you want to learn how to program in C++?"));
    accounts_["650-267-1289"].push_back(new VoiceMessage("650-267-1289", "415-298-2162", 15));
    accounts_["650-267-1289"].push_back(new MediaMessage("945-890-5913", "650-267-1289", 19));
    
    accounts_["408-235-1500"].push_back(new TextMessage("408-720-0012", "408-235-1500", "wanna hang?"));
    accounts_["408-235-1500"].push_back(new TextMessage("408-235-1500", "555-555-5555", "mkay"));
    accounts_["408-235-1500"].push_back(new TextMessage("650-230-9912", "408-235-1500", "lol ya sure"));
    accounts_["408-235-1500"].push_back(new VoiceMessage("408-235-1500", "408-462-7890", 58));
    accounts_["408-235-1500"].push_back(new VoiceMessage("650-781-7900", "408-235-1500", 120));
    accounts_["408-235-1500"].push_back(new VoiceMessage("408-235-1500", "415-298-2162", 10));
    accounts_["408-235-1500"].push_back(new MediaMessage("408-235-1500", "650-230-9912", 32));
    accounts_["408-235-1500"].push_back(new MediaMessage("408-462-7890", "408-235-1500", 15));
    accounts_["408-235-1500"].push_back(new MediaMessage("888-888-8888", "408-235-1500", 7));
    accounts_["408-235-1500"].push_back(new MediaMessage("650-267-1289", "408-235-1500", 9));
    
    accounts_["650-781-7900"].push_back(new TextMessage("650-781-7900", "650-267-1289", "wya"));
    accounts_["650-781-7900"].push_back(new TextMessage("650-267-1289", "650-781-7900", "im gud"));
    accounts_["650-781-7900"].push_back(new MediaMessage("408-462-7890", "650-781-7900", 10));
    accounts_["650-781-7900"].push_back(new MediaMessage("650-781-7900", "408-720-0012", 42));
    accounts_["650-781-7900"].push_back(new MediaMessage("945-890-5913", "650-781-7900", 12));
    
    accounts_["415-298-2162"].push_back(new VoiceMessage("415-298-2162", "650-267-1289", 5));
    accounts_["415-298-2162"].push_back(new MediaMessage("415-902-9581", "415-298-2162", 32));
    
    accounts_["945-890-5913"];
    
    accounts_["408-720-0012"].push_back(new TextMessage("408-720-0012", "650-230-9912", "how's it going"));
    accounts_["408-720-0012"].push_back(new VoiceMessage("408-235-1500", "408-720-0012", 58));
    accounts_["408-720-0012"].push_back(new VoiceMessage("650-267-1289", "408-720-0012", 90));
    accounts_["408-720-0012"].push_back(new VoiceMessage("408-720-0012", "945-890-5913", 32));
    accounts_["408-720-0012"].push_back(new VoiceMessage("650-230-9912", "408-720-0012", 45));
    
    accounts_["650-230-9912"].push_back(new MediaMessage("650-230-9912", "415-298-2162", 19));
    accounts_["650-230-9912"].push_back(new MediaMessage("408-720-0012", "650-230-9912", 42));
    accounts_["650-230-9912"].push_back(new MediaMessage("408-235-1500", "650-230-9912", 25));
    
    accounts_["408-462-7890"].push_back(new TextMessage("408-462-7890", "650-267-1289", "lol"));
    accounts_["408-462-7890"].push_back(new TextMessage("650-781-7900", "408-462-7890", "yeah, wbu?"));
    accounts_["408-462-7890"].push_back(new TextMessage("408-462-7890", "408-235-1500", "yusss"));
    accounts_["408-462-7890"].push_back(new TextMessage("945-890-5913", "408-462-7890", "hey!"));
    accounts_["408-462-7890"].push_back(new VoiceMessage("408-462-7890", "310-290-1666", 72));
    accounts_["408-462-7890"].push_back(new VoiceMessage("310-290-1666", "408-462-7890", 61));
    accounts_["408-462-7890"].push_back(new MediaMessage("408-462-7890", "650-267-1289", 3));
    accounts_["408-462-7890"].push_back(new MediaMessage("408-462-7890", "415-902-9581", 54));
    accounts_["408-462-7890"].push_back(new MediaMessage("415-902-9581", "408-462-7890", 71));
    
    accounts_["415-902-9581"].push_back(new TextMessage("415-902-9581", "310-290-1666", "hellooo?"));
    accounts_["415-902-9581"].push_back(new VoiceMessage("415-902-9581", "310-290-1666", 152));
    accounts_["415-902-9581"].push_back(new VoiceMessage("310-290-1666", "415-902-9581", 59));
    accounts_["415-902-9581"].push_back(new MediaMessage("408-720-0012", "415-902-9581", 24));
    accounts_["415-902-9581"].push_back(new MediaMessage("415-902-9581", "650-230-9912", 53));
    
    accounts_["310-290-1666"].push_back(new TextMessage("408-720-0012", "310-290-1666", "heyyy homie"));
    accounts_["310-290-1666"].push_back(new TextMessage("310-290-1666", "415-298-2162", "l8r!!"));
    accounts_["310-290-1666"].push_back(new TextMessage("310-290-1666", "408-235-1500", "fosho fosho!!"));
}

void SmartCarrier::StartService() {
    int input;
    input = 0;
    do {
        Menu();
        input = GetChoice();
        switch (input) {
            case 1:
                ListAll();
                break;
                
            case 2:
                SearchMessage();
                break;
                
            case 3:
                EraseMessage();
                break;
                
            case 4:
                DisconnectAccount();
                break;
                
            case 5:
                StopService();
                return;
        }
    }
    while (input != 0);
}

void SmartCarrier::Menu() {
    cout << setw(15) << right<< "" << "FOOTHILL WIRELESS" << endl;
    cout << setw(10) << "" << "MESSAGE UTILIZATION AND ACCOUNT ADMIN" << endl;
    cout << "1. List summary of message usages/charges for all accounts" << endl;
    cout << "2. Search a message from an account" << endl;
    cout << "3. Erase a message from an account" << endl;
    cout << "4. Disconnect an account" << endl;
    cout << "5. Quit" << endl;
    
};

int SmartCarrier::GetChoice() {
    int choice;
    cin >> choice;
    return choice;
};

void SmartCarrier::ListAll() {
    double tot_charge;
    int num_message;
    int num_text;
    int num_voice;
    int num_media;
    map <string, vector<Message *> >::iterator m_iter1;
    map <string, vector<Message *> >::iterator m_iter2;
    vector<Message *>::iterator v_iter;
    num_message = 0;
    cout << setw(20) << left << "Phone Number" << setw(20) << "Total Messages" << setw(15) << "Text" << setw(15) << "Voice" << setw(15) << "Media" << setw(20) << "Total Charges" << endl;
    
    for (m_iter1 = accounts_.begin(); m_iter1 != accounts_.end(); ++ m_iter1) { // get "master" account
        tot_charge = 0;
        num_message = 0;
        num_text = 0;
        num_voice = 0;
        num_media = 0;
        TextMessage * p_text_message = NULL;
        VoiceMessage * p_voice_message = NULL;
        MediaMessage * p_media_message = NULL;
        for (m_iter2 = accounts_.begin(); m_iter2 != accounts_.end(); ++m_iter2) {
            for (v_iter = m_iter2->second.begin(); v_iter != m_iter2->second.end(); ++v_iter) { //vector loop
                if (!m_iter2->second.empty() && ((*v_iter) -> Message::get_from() == m_iter1 -> first |(*v_iter) -> Message::get_to() == m_iter1 -> first)) {
                    if ((p_text_message = dynamic_cast<TextMessage *>(*v_iter)) != NULL) {
                        ++num_text;
                    }
                    else if ((p_voice_message = dynamic_cast<VoiceMessage *>(*v_iter)) != NULL) {
                        ++num_voice;
                    }
                    else if ((p_media_message = dynamic_cast<MediaMessage *>(*v_iter)) != NULL) {
                        ++num_media;
                    }
                    tot_charge += (*v_iter) -> ComputeCharge();
                    ++num_message;
                }
            }
        }
        cout << setw(20) << m_iter1->first << setw(20) << left << num_message << setw(15) << num_text << setw(15) << num_voice << setw(15) << num_media << setw(3) << "$" << setprecision(2) << fixed << tot_charge << endl;
    }
};

void SmartCarrier::SearchMessage() {
    string type_message;
    string acc;
    string from;
    string to;
    map<string, vector<Message *> >:: iterator m_iter;
    vector<Message *>:: iterator v_iter;
    TextMessage * p_text = NULL;
    VoiceMessage * p_voice = NULL;
    MediaMessage * p_media = NULL;
    Message * p_user_message = NULL;
    try {
        cout << "Please enter a hyphen separated account number to search for (ex: 123-456-7890)." << endl;
        cin >> acc;
        cout << "Please enter a message type (Text, Voice, or Media)." << endl;
        cin >> type_message;
        cout << "Who is the message from? Please enter response as a hyphen seperated account number (ex: 123-456-7890)." << endl;
        cin >> from;
        cout << "Who is the message to? Please enter response as a hyphen seperated account number (ex: 123-456-7890)." << endl;
        cin >> to;
        
        m_iter = accounts_.find(acc);
        if (m_iter == accounts_.end()) { //check if valid account
            throw runtime_error("Cannot find account.");
        } else {
            TextMessage user_message(from, to, "Test");
            p_user_message = &user_message;
            for (v_iter = m_iter->second.begin(); v_iter != m_iter->second.end(); ++v_iter) {
                if(**v_iter == *p_user_message) {
                    if (type_message == "Text" && (p_text = dynamic_cast<TextMessage *>(*v_iter)) != NULL) {
                        cout << *p_text << endl;
                        return;
                        
                    }
                    else if (type_message == "Voice" && (p_voice = dynamic_cast<VoiceMessage *>(*v_iter)) != NULL) {
                        cout << *p_voice << endl;
                        return;
                        
                    }
                    else if (type_message == "Media" && (p_media = dynamic_cast<MediaMessage *>(*v_iter)) != NULL) {
                        cout << *p_media << endl;
                        return;
                        
                    }
                }
            }
            throw runtime_error("Cannot find message.");
        }
    }
    catch (exception & e) {
        cout << "Exception: " << e.what() << endl;
        return;
    }
};

void SmartCarrier::EraseMessage() {
    string type_message;
    string acc;
    string from;
    string to;
    map<string, vector<Message *> >:: iterator message_iter;
    vector<Message *>:: iterator v_iter;
    TextMessage * p_text = NULL;
    VoiceMessage * p_voice = NULL;
    MediaMessage * p_media = NULL;
    Message * p_user_message = NULL;
    try {
        cout << "Please enter a hyphen separated account number to search for (ex: 123-456-7890)." << endl;
        cin >> acc;
        cout << "Please enter a message type (Text, Voice, or Media)." << endl;
        cin >> type_message;
        cout << "Who is the message from? Please enter response as a hyphen seperated account number (ex: 123-456-7890)." << endl;
        cin >> from;
        cout << "Who is the message to? Please enter response as a hyphen seperated account number (ex: 123-456-7890)." << endl;
        cin >> to;
        
        message_iter = accounts_.find(acc);
        if (message_iter == accounts_.end()) {
            throw runtime_error("Cannot account, and so cannot erase message.");
        }
        else {
            TextMessage user_message(from, to, "Test");
            p_user_message = &user_message;
            for (v_iter = message_iter->second.begin(); v_iter != message_iter->second.end(); ++v_iter) {
                if(**v_iter == *p_user_message &&
                   ((type_message == "Text" && (p_text = dynamic_cast<TextMessage *>(*v_iter)) != NULL) ||
                    (type_message == "Voice" && (p_voice = dynamic_cast<VoiceMessage *>(*v_iter)) != NULL) ||
                    (type_message == "Media" && (p_media = dynamic_cast<MediaMessage *>(*v_iter)) != NULL))
                   ) {
                    delete (*v_iter);
                    message_iter -> second.erase(v_iter);
                    cout << "Message erased." << endl;
                    return;
                }
            }
            throw runtime_error("Cannot find message.");
        }
    }
    catch (exception & e) {
        cout << "Exception: " << e.what() << endl;
        return;
    }
};

void SmartCarrier::DisconnectAccount() {
    string input;
    map<string, vector<Message *> >::iterator message_iter;
    vector<Message *>::iterator v_iter;
    cout << "Enter an account phone number to disconnect." << endl;
    cin >> input;
    try {
        message_iter = accounts_.find(input);
        if (message_iter != accounts_.end()) {
            for (v_iter = message_iter->second.begin(); v_iter != message_iter -> second.end(); ++v_iter) {
                delete (*v_iter);
            }
            message_iter->second.clear();
            accounts_.erase(message_iter->first);
            cout << "Account deleted." << endl;
        }
    }
    catch (exception & e) {
        cout << "Cannot find account." << endl;
        return;
    }
};

void SmartCarrier::StopService() {
    ofstream fout("AccountsInfo.txt");
    map <string, vector<Message *> >::iterator message_iter;
    vector<Message *>::iterator v_iter;
    TextMessage * p_text = NULL;
    VoiceMessage * p_voice = NULL;
    MediaMessage * p_media = NULL;
    
    bool first_text;
    bool first_media;
    bool first_voice;
    if (!fout) {
        cout << "can't open input file.\n";
        exit(-2);
    }
    
    ListAll();
    for (message_iter = accounts_.begin(); message_iter != accounts_.end(); ++message_iter) {
        first_text = false;
        first_media = false;
        first_voice = false;
        fout << message_iter ->first << endl;
        for (v_iter = message_iter->second.begin(); v_iter != message_iter->second.end(); ++v_iter) {
            if ((p_text = dynamic_cast<TextMessage *>(*v_iter)) != NULL) {
                if (!first_text) {
                    fout << "\t Text:" << endl;
                }
                fout << "\t\t" << p_text -> Message::get_from() << ';' << p_text -> Message::get_to() << ';' <<  p_text -> get_text_message() << endl;
                first_text = true;
            } else if ((p_voice = dynamic_cast<VoiceMessage *>(*v_iter)) != NULL) {
                if (!first_voice) {
                    fout << "\t Voice:" << endl;
                }
                fout << "\t\t" << p_voice -> Message::get_from() << ';' << p_voice -> Message::get_to() << ';' << p_voice -> get_time() << endl;
                first_voice = true;
            } else if ((p_media = dynamic_cast<MediaMessage *>(*v_iter)) != NULL) {
                if (!first_media) {
                    fout << "\t Media:" << endl;
                }
                fout << "\t\t" << p_media -> Message::get_from() << ";" << p_media -> Message::get_to() << ';' << p_media -> get_media_size() << endl;
                first_media = true;
            }
        }
    }
    cout << "Stopped services" << endl;
    fout.close();
    return;
};

int main() {
    SmartCarrier * p_smart_carrier = NULL;
    p_smart_carrier = new SmartCarrier("Verizon");
    p_smart_carrier -> Init();
    p_smart_carrier -> StartService();
    delete p_smart_carrier;
}

/* testing program
****OPTION 1 OUTPUT*********
 FOOTHILL WIRELESS
 MESSAGE UTILIZATION AND ACCOUNT ADMIN
 1. List summary of message usages/charges for all accounts
 2. Search a message from an account
 3. Erase a message from an account
 4. Disconnect an account
 5. Quit
 1
 Phone Number        Total Messages      Text           Voice          Media          Total Charges
 310-290-1666        8                   4              4              0              $  52.40
 408-235-1500        15                  6              4              5              $  46.90
 408-462-7890        12                  4              3              5              $  44.75
 408-720-0012        10                  3              4              3              $  45.15
 415-298-2162        6                   1              3              2              $  9.80
 415-902-9581        8                   1              2              5              $  55.25
 650-230-9912        8                   2              1              5              $  24.25
 650-267-1289        10                  4              3              3              $  20.40
 650-781-7900        7                   3              1              3              $  25.00
 945-890-5913        4                   1              1              2              $  8.10


********OPTION 2 OUTPUT:********
 (non-existing account search)
 Please enter a hyphen separated account number to search for (ex: 123-456-7890).
 111-222-3456
 Please enter a message type (Text, Voice, or Media).
 Text
 Who is the message from? Please enter response as a hyphen seperated account number (ex: 123-456-7890).
 310-290-1666
 Who is the message to? Please enter response as a hyphen seperated account number (ex: 123-456-7890).
 408-720-0012
 Exception: Cannot find account.
 
 
 (non-existing message search)
 Please enter a hyphen separated account number to search for (ex: 123-456-7890).
 650-230-9912
 Please enter a message type (Text, Voice, or Media).
 Media
 Who is the message from? Please enter response as a hyphen seperated account number (ex: 123-456-7890).
 650-230-9912
 Who is the message to? Please enter response as a hyphen seperated account number (ex: 123-456-7890).
 415-290-1592
 Exception: Cannot find message.
 
 ****OPTION 3 OUTPUT****
 Please enter a hyphen separated account number to search for (ex: 123-456-7890).
 408-462-7890
 Please enter a message type (Text, Voice, or Media).
 Text
 Who is the message from? Please enter response as a hyphen seperated account number (ex: 123-456-7890).
 408-462-7890
 Who is the message to? Please enter response as a hyphen seperated account number (ex: 123-456-7890).
 408-235-1500
 Message erased.
 
 //evoke option 2 to verify that the message is erased
 FOOTHILL WIRELESS
 MESSAGE UTILIZATION AND ACCOUNT ADMIN
 1. List summary of message usages/charges for all accounts
 2. Search a message from an account
 3. Erase a message from an account
 4. Disconnect an account
 5. Quit
 2
 Please enter a hyphen separated account number to search for (ex: 123-456-7890).
 408-462-7890
 Please enter a message type (Text, Voice, or Media).
 Text
 Who is the message from? Please enter response as a hyphen seperated account number (ex: 123-456-7890).
 408-462-7890
 Who is the message to? Please enter response as a hyphen seperated account number (ex: 123-456-7890).
 408-235-1500
 Exception: Cannot find message.
 
 
 ****OPTION 4 OUTPUT*****
 FOOTHILL WIRELESS
 MESSAGE UTILIZATION AND ACCOUNT ADMIN
 1. List summary of message usages/charges for all accounts
 2. Search a message from an account
 3. Erase a message from an account
 4. Disconnect an account
 5. Quit
 4
 Enter an account phone number to disconnect.
 310-290-1666
 Account deleted.
 
 //verifying this w option 1
 FOOTHILL WIRELESS
 MESSAGE UTILIZATION AND ACCOUNT ADMIN
 1. List summary of message usages/charges for all accounts
 2. Search a message from an account
 3. Erase a message from an account
 4. Disconnect an account
 5. Quit
 1
 Phone Number        Total Messages      Text           Voice          Media          Total Charges
 408-235-1500        14                  5              4              5              $  46.70
 408-462-7890        12                  4              3              5              $  44.75
 408-720-0012        9                   2              4              3              $  44.95
 415-298-2162        5                   0              3              2              $  9.60
 415-902-9581        8                   1              2              5              $  55.25
 650-230-9912        8                   2              1              5              $  24.25
 650-267-1289        10                  4              3              3              $  20.40
 650-781-7900        7                   3              1              3              $  25.00
 945-890-5913        4                   1              1              2              $  8.10
*/
