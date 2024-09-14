# BankingSystem
This is a basic command-line banking system implemented in C++. It allows users to create accounts, make deposits, withdraw money, check their balance, and view transaction history. Each account is saved to a file, so transactions are persistent across sessions.

Features
Account Creation: Accounts are created when the user makes their first deposit.
Deposit: Users can deposit any amount into their accounts.
Withdraw: Users can withdraw money, provided there is enough balance in the account.
Check Balance: Users can check the current balance of their account.
View Transaction History: All transactions (deposits and withdrawals) are logged and can be viewed at any time.
Profile View: The profile of an account holder, including name, account number, and balance, can be viewed

How to Use
Clone this repository:
git clone https://github.com/AbhayPratap05/BankingSystem.git

Compile the program:
g++ -o P3-BankingSystem main.cpp

Run the executable:
./P3-BankingSystem

Program Flow
Enter Account Information:
The user is prompted to enter their account number (12 digits) and their first name.

Main Menu:
After account information is provided, the user is presented with the following options:
1: Deposit
2: Withdraw
3: Check Balance
4: View Transaction History
5: View Profile
6: Exit

Transaction Persistence:
Account information, balance, and transaction history are stored in text files named after the account number. For example, if the account number is 123456789012, the file will be 123456789012.txt.

File Structure
Account Class: Handles operations like deposits, withdrawals, and transaction logging.
Main Program: Provides an interactive menu to the user.

Future Improvements
Multiple accounts feature.
PIN authentication for added security.
Handling invalid inputs more robustly.


