#include <iostream>
#include<cctype>        // isdigit
#include <algorithm>    // std::all_of()
#include <fstream>      // working with files 
#include <vector>
#include <string>       // getline()
#include <unordered_map> // to store multiple accounts

using namespace std;

class Account
{
private:
    string ownerName;
    string accNumber;
    string accPin;
    double balance = 0;
    vector <string> transactionHistory;

public:
    Account() {}
    Account(string name, string num, string pin) : ownerName(name), accNumber(num), accPin(pin){}

    bool authenticate(string pin) {
        return pin == accPin;
    }

    void deposit(double amount){
        balance += amount;
        string transaction = "Deposited $: " + to_string(amount);
        transactionHistory.push_back(transaction);
        save_to_file();
        cout << transaction <<endl;
    }

    void withdraw(double amount){
        if (balance >= amount)
        {
            balance -= amount;
            string transaction = "Withdrew $: "+to_string(amount);
            transactionHistory.push_back(transaction);
            save_to_file();
            cout << transaction <<endl;
        }
        else{
            cout << "Not Enough Balance!\n";
        }
    }

    void viewBalance() const{
        cout << "Your current balance is $: " << balance << endl;
    }

    void viewTransaction() const{
        cout << "Transaction History: \n";
        for (int i = 0; i < transactionHistory.size(); i++)
        {
            cout << transactionHistory[i] << endl;
        }
        
    }

    void viewProfile() const{
        cout << "Account Number: " << accNumber << endl;
        cout << "Account Holder's Name: " << ownerName << endl;
        cout << "Account PIN (confidential): " << accPin << endl;
        cout << "Account Balance: " << balance << endl;
    }

    void save_to_file() const{
        ofstream file(accNumber + ".txt");
        if (file.is_open())
        {
            file << "Account Number: " << accNumber << endl;
            file << "Account Holder Name: " << ownerName << endl;
            file << "Current Balance ($): " << balance << endl;
            file << "Account Pin (Confidential): " << accPin << endl;
            file << "Transaction History: \n";
            for (int i = 0; i < transactionHistory.size(); i++)
            {
                file << transactionHistory[i] << endl;
            }
            file.close();
        }
        else{
            cout << "Unable to open the file!\n";
        }
        
    }

};

int main(){
    unordered_map<string, Account> accounts;

    while (true)
    {
        int choice; 

        cout << "\n\n******* Welcome to the Banking System! *******\n\n";
        cout << "1: Create Account\n";
        cout << "2: Access Account\n";
        cout << "3: Exit\n";
        cout << "Enter your choice: ";
        cin>> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
        {    
            string name, number, pin;

            cout << "Enter the Account number (12-digits): ";
            getline(cin, number);

            while (number.size() != 12 || !all_of(number.begin(), number.end(), ::isdigit)) {
                cout << "Invalid Account Number! Please enter again: ";
                getline(cin, number);
            }

            cout << "Enter the Account holder's first name: ";
            getline(cin, name);
            while (name.size() < 2 || name.size() > 10 || !all_of(name.begin(), name.end(), ::isalpha)) {
                cout << "Invalid Name! Please enter again: ";
                getline(cin, name);
            }

            cout << "Set a 4-digit PIN: ";
            getline(cin, pin);
            while (pin.size() != 4 || !all_of(pin.begin(), pin.end(), ::isdigit)) {
                cout << "Invalid PIN! Please enter a 4-digit PIN: ";
                getline(cin, pin);
            }

            accounts.emplace(number, Account(name,number,pin));

            cout << "Account Created Successfully!\n";
            accounts[number].save_to_file();
            break;
        }
        case 2:
        {
            string accNumber, pin;
            while (true)
            {
                cout << "Enter Account Number: ";
                cin >> accNumber;
                cin.ignore();
                
                if (accounts.find(accNumber) != accounts.end()) //to check if the account exists 
                {
                    cout << "Enter the 4-digit PIN: ";
                    cin >> pin;
                    cin.ignore();
                
                    if (accounts[accNumber].authenticate(pin))  
                    {
                        int accChoice;
                        bool session = true;
                        double amount;

                        while (session)
                        {
                            cout << "\n1: Deposite\n";
                            cout << "2: Withdraw\n";
                            cout << "3: View Balance\n";
                            cout << "4: Transaction History\n";
                            cout << "5: View Profile\n";
                            cout << "6: Exit\n";
                            cout << "Enter choice: ";
                            cin >> accChoice;
                            cin.ignore();
                            cout << endl;

                            switch (accChoice)
                            {
                                case 1:
                                    cout << "Enter the amount to deposite ($): ";
                                    cin >> amount;
                                    cin.ignore();
                                    cout << endl;
                                    accounts[accNumber].deposit(amount);
                                    break;
                                case 2:
                                    cout << "Enter the amount to withdraw ($): ";
                                    cin >> amount;
                                    cin.ignore();
                                    cout << endl;
                                    accounts[accNumber].withdraw(amount);
                                    break;
                                case 3:
                                    accounts[accNumber].viewBalance();
                                    break;
                                case 4:
                                    accounts[accNumber].viewTransaction();
                                    break;
                                 case 5: 
                                    accounts[accNumber].viewProfile();
                                    break;
                                case 6:
                                cout << "Exiting...\n";
                                session = false;
                                break;
                        
                                default:
                                    cout << "Invalid Choice!\n";
                                    break;
                            }
                        }
                    
                    }
                    else cout << "Incorrect PIN!\n";
                
                }
                else
                {
                    cout << "Account not found!\n";
                    char exit;
                    cout << "Exit? (Y/N): \n";
                    cin >> exit;
                    cin.ignore();
                    if (exit == 'y' || exit =='Y')
                    {
                        cout << "Exiting...\n";
                        break;
                    }
                    else continue;
                }

            }
   
        }
        case 3:
            cout << "Thank you for using the Banking System!\n";
            return 0;

        default:
            cout << "Invalid choice! Try again.\n";
        }
    }
    return 0;
}
