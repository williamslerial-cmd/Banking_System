// ============================================
// GGC BANK - Banking System
// Introduction to Programming NQF 4 ============================================
#include <iostream>
#include <string>
using namespace std;

// --- Function Prototypes ---
void displayMenu();
int findAccount(int accNum, int accNums[], int size);
bool deposit(double balances[], int index, double amount);
bool withdraw(double balances[], int index, double amount);
bool sendCash(double balances[], int accNums[], int size, int fromIndex, int toAccNum, double amount);
void checkBalance(string names[], double balances[], int index);

int main() {
    // --- User details stored in ARRAYS  ---
    // Requirement: Storing user details
    string names[3] = {"Thabo Molefe", "Lerato Dube", "Sipho Nkosi"};
    int accountNumbers[3] = {1001, 1002, 1003};
    int pins[3] = {1234, 2345, 3456};
    double balances[3] = {1500.00, 2500.50, 500.00};
    int size = 3;

    // --- Login ---
    int enteredAcc, enteredPin;
    cout << "===== Welcome to GGC BANK =====" << endl;
    cout << "Enter account number: ";
    cin >> enteredAcc;

    int currentUser = findAccount(enteredAcc, accountNumbers, size);

    if (currentUser == -1) {
        cout << "Error: Account number not found!" << endl;
        return 0;
    }

    cout << "Enter PIN: ";
    cin >> enteredPin;

    if (enteredPin != pins[currentUser]) {
        cout << "Error: Wrong PIN!" << endl;
        return 0;
    }

    cout << "\nWelcome, " << names[currentUser] << "!" << endl;

    // --- Menu Loop  ---
    int choice;
    do {
        displayMenu();
        cout << "Enter choice: ";
        cin >> choice;

        // Input validation
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Error: Please enter a number 1-5." << endl;
            continue;
        }

        if (choice == 1) {
            // DEPOSIT (15 marks)
            double amount;
            cout << "Enter amount to deposit: R";
            cin >> amount;
            if (deposit(balances, currentUser, amount))
                cout << "Deposit successful! New balance: R" << balances[currentUser] << endl;
            else
                cout << "Error: Amount must be more than 0." << endl;

        } else if (choice == 2) {
            // WITHDRAW
            double amount;
            cout << "Enter amount to withdraw: R";
            cin >> amount;
            if (withdraw(balances, currentUser, amount))
                cout << "Withdrawal successful! New balance: R" << balances[currentUser] << endl;
            else
                cout << "Error: Amount must be more than 0 and not more than balance (R"
                     << balances[currentUser] << ")." << endl;

        } else if (choice == 3) {
            // SEND CASH
            int toAcc;
            double amount;
            cout << "Enter recipient account number: ";
            cin >> toAcc;
            cout << "Enter amount to send: R";
            cin >> amount;
            if (sendCash(balances, accountNumbers, size, currentUser, toAcc, amount))
                cout << "Send Cash successful! New balance: R" << balances[currentUser] << endl;
            else
                cout << "Error: Check recipient exists, amount > 0 and balance is enough." << endl;

        } else if (choice == 4) {
            // CHECK BALANCE
            checkBalance(names, balances, currentUser);

        } else if (choice == 5) {
            cout << "Thank you for banking with GGC BANK. Goodbye!" << endl;
        } else {
            cout << "Error: Invalid menu choice. Choose 1-5." << endl;
        }

    } while (choice != 5);

    return 0;
}

// --- Functions ---

void displayMenu() {
    cout << "\n===== GGC BANK =====" << endl;
    cout << "1. Deposit" << endl;
    cout << "2. Withdraw" << endl;
    cout << "3. Send Cash" << endl;
    cout << "4. Check Balance" << endl;
    cout << "5. Exit" << endl;
}

int findAccount(int accNum, int accNums[], int size) {
    for (int i = 0; i < size; i++) {
        if (accNums[i] == accNum)
            return i; // return index
    }
    return -1; // not found
}

bool deposit(double balances[], int index, double amount) {
    if (amount <= 0) return false;
    balances[index] = balances[index] + amount;
    return true;
}

bool withdraw(double balances[], int index, double amount) {
    if (amount <= 0) return false;
    if (amount > balances[index]) return false;
    balances[index] = balances[index] - amount;
    return true;
}

bool sendCash(double balances[], int accNums[], int size, int fromIndex, int toAccNum, double amount) {
    if (amount <= 0) return false;
    if (amount > balances[fromIndex]) return false;
    int toIndex = findAccount(toAccNum, accNums, size);
    if (toIndex == -1) return false; // recipient does not exist
    if (toIndex == fromIndex) return false; // cannot send to yourself

    balances[fromIndex] = balances[fromIndex] - amount;
    balances[toIndex] = balances[toIndex] + amount;
    return true;
}

void checkBalance(string names[], double balances[], int index) {
    cout << "\n--- Account Details ---" << endl;
    cout << "Name: " << names[index] << endl;
    cout << "Balance: R" << balances[index] << endl;
}

