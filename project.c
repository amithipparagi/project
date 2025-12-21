#include <stdio.h>
#include <string.h>

#define MAX_TRANS 100

/* Structure to store bank account details */
struct BankAccount {
    char name[30];
    int acc_no;
    float balance;
    char password[10]; // Password is now part of the account
};

/* Global variables */
struct BankAccount acc;
float transactions[MAX_TRANS];
int trans_count = 0;

/* Function to check password against the account password */
int authenticate() {
    char input_pass[10];
    printf("Enter Password: ");
    scanf("%s", input_pass);

    if (strcmp(input_pass, acc.password) == 0) {
        return 1;
    } else {
        printf("Access Denied: Incorrect Password!\n");
        return 0;
    }
}

/* Function to deposit money */
void deposit(float amount) {
    if (amount > 0) {
        if (trans_count < MAX_TRANS) {
            acc.balance += amount;
            transactions[trans_count++] = amount;
            printf("Amount Deposited: %.2f\n", amount);
        } else {
            printf("Transaction limit reached!\n");
        }
    } else {
        printf("Invalid deposit amount!\n");
    }
}

/* Function to withdraw money with security check */
void withdraw(float amount) {
    // Check password BEFORE checking balance or processing
    if (!authenticate()) {
        return; // Exit function if password is wrong
    }

    if (amount > 0 && amount <= acc.balance) {
        if (trans_count < MAX_TRANS) {
            acc.balance -= amount;
            transactions[trans_count++] = -amount;
            printf("Withdrawal Successful! Amount: %.2f\n", amount);
        } else {
            printf("Transaction limit reached!\n");
        }
    } else {
        printf("Insufficient balance or invalid amount!\n");
    }
}

/* Function to display balance */
void check_balance() {
    printf("Current Balance: %.2f\n", acc.balance);
}

/* Function to display account details */
void account_details() {
    printf("\n--- Account Details ---\n");
    printf("Name       : %s\n", acc.name);
    printf("Account No : %d\n", acc.acc_no);
    printf("Balance    : %.2f\n", acc.balance);
}

/* Function to show transaction history */
void transaction_history() {
    int i;
    if (trans_count == 0) {
        printf("\nNo transactions yet.\n");
        return;
    }

    printf("\n--- Transaction History ---\n");
    for (i = 0; i < trans_count; i++) {
        if (transactions[i] > 0)
            printf("Deposit  : %.2f\n", transactions[i]);
        else
            printf("Withdraw : %.2f\n", -transactions[i]);
    }
}

int main() {
    int choice;
    float amount;

    /* Initialize account */
    printf("--- Create Your Account ---\n");
    printf("Enter Account Holder Name: ");
    // Clear buffer and use fgets for names with spaces
   // scanf(" %[^\n]s", acc.name);
   fgets(acc.name,100,stdin);

    printf("Enter Account Number: ");
    scanf("%d", &acc.acc_no);

    printf("Set your Account Password: ");
    scanf("%s", acc.password);

    acc.balance = 0.0;
    printf("\nAccount created successfully!\n");

    while (1) {
        printf("\n===== BANK ACCOUNT SIMULATOR =====\n");
        printf("1. Deposit Money\n");
        printf("2. Withdraw Money\n");
        printf("3. Check Balance\n");
        printf("4. Account Details\n");
        printf("5. Transaction History\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter deposit amount: ");
                scanf("%f", &amount);
                deposit(amount);
                break;

            case 2:
                printf("Enter withdrawal amount: ");
                scanf("%f", &amount);
                withdraw(amount);
                break;

            case 3:
                check_balance();
                break;

            case 4:
                account_details();
                break;

            case 5:
                transaction_history();
                break;

            case 6:
                printf("Thank you for using the Bank Simulator!\n");
                return 0;

            default:
                printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}