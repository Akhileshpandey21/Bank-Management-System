#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#define MAX_TRANSACTIONS 1000 
static int nextAccountNumber = 1000; // Initial account number 
struct Transaction 
{ 
 char type; // 'D' for deposit, 'W' for withdrawal, 'T' for transfer 
 float amount; 
}; 
struct BankAccount 
{ 
 int accountNumber; 
 char customerName[50]; 
 float balance; 
 struct Transaction transactions[MAX_TRANSACTIONS]; 
 int transactionCount; 
}; 
struct BankAccount createAccount(const char *customerName, float 
initialBalance) 
{ 
 struct BankAccount account; 
 account.accountNumber = nextAccountNumber++; 
 strcpy(account.customerName, customerName); 
 account.balance = initialBalance; 
 account.transactionCount = 0; 
 return account; 
} 
void displayAccount(struct BankAccount *accounts, int accountCount, int 
accountNumber) 
{ 
 int found = 0; 
 for (int i = 0; i < accountCount; ++i) 
 { 
 if (accounts[i].accountNumber == accountNumber) 
 { 
 printf("Account Number: %d\n", accounts[i].accountNumber); 
 printf("Customer Name: %s\n", accounts[i].customerName); 
 printf("Balance: %.2f\n", accounts[i].balance); 
 found = 1; 
 break; 
 } 
 } 
 if (!found) 
 { 
 printf("Account with account number %d not found.\n", accountNumber); 
 } 
} 
void deposit(struct BankAccount *accounts, int accountCount, int 
accountNumber, float amount) 
{ 
 for (int i = 0; i < accountCount; ++i) 
 { 
 if (accounts[i].accountNumber == accountNumber) 
 { 
 accounts[i].balance += amount; 
 // Add transaction to the history 
 accounts[i].transactions[accounts[i].transactionCount].type = 'D'; 
 accounts[i].transactions[accounts[i].transactionCount].amount = 
amount; 
 accounts[i].transactionCount++; 
 printf("Deposit successful. New balance for account %d: %.2f\n", 
accountNumber, accounts[i].balance); 
 return; 
 } 
 } 
 printf("Account with account number %d not found.\n", accountNumber); 
} 
void withdraw(struct BankAccount *accounts, int accountCount, int 
accountNumber, float amount) 
{ 
 for (int i = 0; i < accountCount; ++i) 
 { 
 if (accounts[i].accountNumber == accountNumber) 
 { 
 if (amount <= accounts[i].balance) 
 { 
 accounts[i].balance -= amount; 
 // Add transaction to the history 
 accounts[i].transactions[accounts[i].transactionCount].type = 'W'; 
 accounts[i].transactions[accounts[i].transactionCount].amount = 
amount; 
 accounts[i].transactionCount++; 
 printf("Withdrawal successful. New balance for account %d: %.2f\n", 
accountNumber, accounts[i].balance); 
 } 
 else 
 { 
 printf("Insufficient funds for withdrawal.\n"); 
 } 
 return; 
 } 
 } 
 printf("Account with account number %d not found.\n", accountNumber); 
} 
void transfer(struct BankAccount *accounts, int accountCount, int 
sourceAccount, int destinationAccount, float amount) 
{ 
 int sourceIndex = -1; 
 int destinationIndex = -1; 
 for (int i = 0; i < accountCount; ++i) 
 { 
 if (accounts[i].accountNumber == sourceAccount) 
 { 
 sourceIndex = i; 
 } 
 if (accounts[i].accountNumber == destinationAccount) 
 { 
 destinationIndex = i; 
 } 
 } 
 if (sourceIndex != -1 && destinationIndex != -1) 
 { 
 if (amount <= accounts[sourceIndex].balance) 
 { 
 accounts[sourceIndex].balance -= amount; 
 accounts[destinationIndex].balance += amount; 
 // Add transaction to the history for both source and destination accounts 
 
accounts[sourceIndex].transactions[accounts[sourceIndex].transactionCount].type = 'T'; 
 
accounts[sourceIndex].transactions[accounts[sourceIndex].transactionCount].amount = amount; 
 accounts[sourceIndex].transactionCount++; 
 
accounts[destinationIndex].transactions[accounts[destinationIndex].transactionCount].type = 'T'; 
 
accounts[destinationIndex].transactions[accounts[destinationIndex].transactionCount].amount = amount; 
 accounts[destinationIndex].transactionCount++; 
 printf("Transfer successful. New balance for source account %d: %.2f\n", 
sourceAccount, accounts[sourceIndex].balance); 
 printf("New balance for destination account %d: %.2f\n", 
destinationAccount, accounts[destinationIndex].balance); 
 } 
 else 
 { 
 printf("Insufficient funds for transfer.\n"); 
 } 
 } 
 else 
 { 
 printf("One or both accounts not found.\n"); 
 } 
} 
void changeCustomerName(struct BankAccount *accounts, int accountCount, 
int accountNumber, const char *newName) 
{ 
 for (int i = 0; i < accountCount; ++i) 
 { 
 if (accounts[i].accountNumber == accountNumber) 
 { 
 strcpy(accounts[i].customerName, newName); 
 printf("Customer name for account %d changed to %s\n", 
accountNumber, newName); 
 return; 
 } 
 } 
 printf("Account with account number %d not found.\n", accountNumber); 
} 
void closeAccount(struct BankAccount *accounts, int *accountCount, int 
accountNumber) 
{ 
 for (int i = 0; i < *accountCount; ++i) 
 { 
 if (accounts[i].accountNumber == accountNumber) 
 { 
 printf("Account %d closed. Thank you for banking with us.\n", 
accountNumber); 
 // Remove the closed account by shifting remaining accounts 
 for (int j = i; j < *accountCount - 1; ++j) 
 { 
 accounts[j] = accounts[j + 1]; 
 } 
 (*accountCount)--; 
 return; 
 } 
 } 
 printf("Account with account number %d not found.\n", accountNumber); 
} 
void displayTransactionHistory(struct BankAccount *accounts, int 
accountCount, int accountNumber) 
{ 
 int found = 0; 
 for (int i = 0; i < accountCount; ++i) 
 { 
 if (accounts[i].accountNumber == accountNumber) 
 { 
 printf("Transaction History for Account %d:\n", accountNumber); 
 for (int j = 0; j < accounts[i].transactionCount; ++j) 
 { 
 printf("Transaction Type: %c, Amount: %.2f\n", 
accounts[i].transactions[j].type, accounts[i].transactions[j].amount); 
 } 
 found = 1; 
 break; 
 } 
 } 
 if (!found) 
 { 
 printf("Account with account number %d not found.\n", accountNumber); 
 } 
} 
void calculateInterest(struct BankAccount *accounts, int accountCount, float 
interestRate) 
{ 
 for (int i = 0; i < accountCount; ++i) 
 { 
 float interest = accounts[i].balance * (interestRate / 100); 
 accounts[i].balance += interest; 
 printf("Interest calculated for account %d. New balance: %.2f\n", 
accounts[i].accountNumber, accounts[i].balance); 
 } 
} 
void displayMenu() 
{ 
 printf("\nMenu:\n"); 
 printf("1. Display Account Details\n"); 
 printf("2. Deposit\n"); 
 printf("3. Withdraw\n"); 
 printf("4. Transfer\n"); 
 printf("5. Calculate Interest\n"); 
 printf("6. Change Customer Name\n"); 
 printf("7. Close Account\n"); 
 printf("8. Create New Account\n"); 
 printf("9.Display Transaction History\n"); 
 printf("10. Exit\n"); 
} 
int main() 
{ 
 struct BankAccount accounts[10]; // Assuming a maximum of 10 accounts for simplicity
 int accountCount = 0; 
 int choice, accountNumber; 
 float amount, interestRate; 
 char newName[50]; 
 do 
 { 
 displayMenu(); 
 printf("Enter your choice: "); 
 scanf("%d", &choice); 
 switch (choice) 
 { 
 case 1: 
 if (accountCount > 0) 
 { 
 printf("Enter account number: "); 
 scanf("%d", &accountNumber); 
 displayAccount(accounts, accountCount, accountNumber); 
 } 
 else 
 { 
 printf("No accounts available.\n"); 
 } 
 break; 
 case 2: 
 if (accountCount > 0) 
 { 
 printf("Enter account number: "); 
 scanf("%d", &accountNumber); 
 printf("Enter deposit amount: "); 
 scanf("%f", &amount); 
 deposit(accounts, accountCount, accountNumber, amount); 
 } 
 else 
 { 
 printf("No accounts available.\n"); 
 } 
 break; 
 case 3: 
 if (accountCount > 0) 
 { 
 printf("Enter account number: "); 
 scanf("%d", &accountNumber); 
 printf("Enter withdrawal amount: "); 
 scanf("%f", &amount); 
 withdraw(accounts, accountCount, accountNumber, amount); 
 } 
 else 
 { 
 printf("No accounts available.\n"); 
 } 
 break; 
 case 4: 
 if (accountCount > 1) 
 { 
 int destinationAccount; 
 printf("Enter source account number: "); 
 scanf("%d", &accountNumber); 
 printf("Enter destination account number: "); 
 scanf("%d", &destinationAccount); 
 printf("Enter transfer amount: "); 
 scanf("%f", &amount); 
 transfer(accounts, accountCount, accountNumber, 
destinationAccount, amount); 
 } 
 else 
 { 
 printf("Insufficient accounts available for transfer.\n"); 
 } 
 break; 
 case 5: 
 if (accountCount > 0) 
 { 
 printf("Enter interest rate: "); 
 scanf("%f", &interestRate); 
 calculateInterest(accounts, accountCount, interestRate); 
 } 
 else 
 { 
 printf("No accounts available.\n"); 
 } 
 break; 
 case 6: 
 if (accountCount > 0) 
 { 
 printf("Enter account number: "); 
 scanf("%d", &accountNumber); 
 printf("Enter new customer name: "); 
 scanf("%s", newName); 
 changeCustomerName(accounts, accountCount, accountNumber, 
newName); 
 } 
 else 
 { 
 printf("No accounts available.\n"); 
 } 
 break; 
 case 7: 
 if (accountCount > 0) 
 { 
 printf("Enter account number: "); 
 scanf("%d", &accountNumber); 
 closeAccount(accounts, &accountCount, accountNumber); 
 } 
 else 
 { 
 printf("No accounts available.\n"); 
 } 
 break; 
 case 8: 
 printf("Enter customer name for the new account: "); 
 scanf("%s", newName); 
 printf("Enter initial balance: "); 
 scanf("%f", &amount); 
 struct BankAccount newAccount = createAccount(newName, amount); 
 accounts[accountCount++] = newAccount; 
 printf("New account created with the following details:\n"); 
 displayAccount(accounts, accountCount, newAccount.accountNumber); 
 break; 
 case 9: 
 if (accountCount > 0) 
 { 
 printf("Enter account number: "); 
 scanf("%d", &accountNumber); 
 displayTransactionHistory(accounts, accountCount, accountNumber); 
 } 
 else 
 { 
 printf("No accounts available.\n"); 
 } 
 break; 
 case 10: 
 printf("Exiting the program. Thank you!\n"); 
 break; 
 } 
 } while (choice != 10); 
 return 0; 
}
