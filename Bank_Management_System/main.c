                    /****************************************       Bank Management System       ************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define ACCOUNTS 100
#define NAME 20
#define CITY 25

// some function's Prototypes
void menu();        // main menu where functions be accessed
void newAcc();      // add new customer's account
void ediAcc();      // edit some information about customer
void transact();    // deposit and withdraw money to and from the customer  display some customer's information deleting customer's account display all information about customer
void viewList();    // display some customer's information
void erase();       // deleting customer's account
void see();         // display all information about customer
int mainSearch();      //  decided witch operation will done
int searchCode();      // search account by account number
int searchName();      // search account by Name of customer
int searchPhone();     // search account by phone number
void deposit(int );      // to deposit money
void withdraw(int );     // to withdraw money
void sort();         // to sort accounts
void readFile();        // to read data from the file
void writeFile();       // to write data in the file
void appendFile();      // to append data in the file

// declaring some constant variables
/* struct date {
    int year,
        month,
        day;
} sDate;*/

struct account {
    int accCode,
        money,
        age;
    char name[NAME],
         city[CITY];
    long int phone,
             citNum;
} accounts[ACCOUNTS];

int accountCounter = 0,
    code = 100;

int main()
{
    // message for starting program
    puts("");
    puts("\t\t\t\xB2\xB2\xB2\xB2\t CUSTOMER ACCOUNT BANKING MANAGEMAENT SYSTEM \t\xB2\xB2\xB2\xB2");
    puts("");

    // change the color of text
    system("color 2");

    readFile();
    menu();

    return 0;
}

void menu()
{
    // declaring variables
    int choice;

    // display menu
    puts("");
    puts("\t\xB1\xB1\xB1\xB1\t WELCOME TO THE MAIN MENU \t\xB1\xB1\xB1\xB1");
    puts("");
    puts("\t==========================================");
    puts("\t 1- Create new account");
    puts("\t 2- Update information of exiting account");
    puts("\t 3- For transaction");
    puts("\t 4- Check the details of exiting account");
    puts("\t 5- Removing exiting account");
    puts("\t 6- View customer's list");
    puts("\t 0- Exit");
    puts("\t=====================");
    printf("\t Enter your choice: ");   // asking user of choice
    scanf("%d", &choice);

    // get choice and decided what the program will do
    switch(choice) {
        case 1: // case : add a new customer's account
            system("cls");
            newAcc();
            break;

        case 2: // case : edit some information about customer
            system("cls");
            ediAcc();
            break;

        case 3: // deposit and withdraw money to and from the customer
            system("cls");
            transact();
            break;

        case 4: // display some customer's information
            system("cls");
            viewList();
            break;

        case 5: // deleting customer's account
            system("cls");
            erase();
            break;

        case 6: // display all information about customer
            system("cls");
            see();
            break;

        case 0: // Exit the program
            puts("\n  Thanks for using software");
            getch();
            exit(0);
            break;

        default:    // a wrong choice
            puts("   invalid value...");
            puts("   press any key to try again!");
            getch();
            system("cls");
            main();
            break;
    }

    system("cls");
}

void newAcc()
{
    // message for creating a new account
    puts("");
    puts("\t\t\t\xB1\xB1\xB1\xB1\t CREATING NEW ACCOUNT \t\xB1\xB1\xB1\xB1");
    puts("");
    puts("\t to create an account you should fill next form");

/*    // for waiting 2 seconds
    for(int i = 1; i < 5; i++) {
        printf(".");
//        Sleep(500);
        puts("");
    }*/

    // form that will be full
    printf("Name: ");
    fflush(stdin);
    gets(accounts[accountCounter].name);

    printf("Age: ");
    scanf("%d", &accounts[accountCounter].age);

    printf("Citizenship number: ");
    scanf("%ld", &accounts[accountCounter].citNum);

    printf("Address: ");
    fflush(stdin);
    gets(accounts[accountCounter].city);

    printf("Phone number: ");
    scanf("%ld", &accounts[accountCounter].phone);

    deposit(accountCounter);
    // Give code to account
    accounts[accountCounter].accCode = ++code;

    puts("Account added successfully");
    printf("Your code is [ %d ]", accounts[accountCounter].accCode);
    puts("");

    appendFile();

    accountCounter++;   // to jump to the next account
    code++;   // to jump to the next account

    // for waiting 3 seconds
/*    for(int i = 1; i < 7; i++) {
        printf(".");
//        Sleep(500);
        puts("");
    }*/

    puts("");
    puts("Press any key to continue...");
    getch();
    system("cls");

    menu();
}

void ediAcc()
{
    // message for editing the account
    puts("");
    puts("\t\t\t\xB1\xB1\xB1\xB1\t EDIT THE ACCOUNT \t\xB1\xB1\xB1\xB1");

    readFile();

    int index = mainSearch();

    if(index > -1) {
        puts("");
        printf("Account number: %d", accounts[index].accCode);
        printf("Name: %s", accounts[index].name);
        printf("Address: %s", accounts[index].city);
        printf("Phone number: %ld", accounts[index].phone);
        puts("============================================");
        puts("");

        printf("Change name to: ");
        scanf("%s", accounts[index].name);

        printf("Change phone number to: ");
        scanf("%ld", &accounts[index].phone);

        printf("Change city to: ");
        scanf("%s", accounts[index].city);
        puts("");
        puts("");
        puts("Changing accepted...");

        writeFile();
    }

    else
        puts("Not found!");

    puts("");
    puts("Press any key to continue...");
    getch();
    system("cls");;

    menu();
}

void transact()
{
    // message for Transaction
    puts("");
    puts("\t\t\t\xB1\xB1\xB1\xB1\t TRANSACTIONS MONEY \t\xB1\xB1\xB1\xB1");
    puts("");

    int index = mainSearch();

    puts("Chose what would you do:");
    puts("==========================");
    puts("(1) Deposit money.");
    puts("(2) Withdraw money.");
    puts("=======================");
    printf("Enter your choice: ");
    int o;
    scanf("%d", &o);

    switch(o) {
        case 1:
            deposit(index);  // to deposit money to the account
            break;

        case 2:
            withdraw(index); // to withdraw money fro the account
            break;

        default:
            puts("   invalid value...");
            puts("   press any key to try again!");
            getch();
            break;
    }

    puts("");
    puts("Press any key to continue...");
    getch();
    system("cls");

    writeFile();

    menu();
}

void viewList()
{
    // message for view list of account
    puts("");
    puts("\t\t\t\xB1\xB1\xB1\xB1\t VIEW LIST OF ACCOUNT \t\xB1\xB1\xB1\xB1");
    puts("");

    readFile();

    int index = mainSearch();

    if(index > -1) {
        puts("");
        printf("Account number: %d\n", accounts[index].accCode);
        printf("Name: %s\n", accounts[index].name);
        printf("Address: %s\n", accounts[index].city);
        printf("Phone number: %ld\n", accounts[index].phone);
        puts("");
    }

    else
        puts("Not found!");

    puts("");
    puts("Press any key to continue...");
    getch();
    system("cls");

    menu();
}

void erase()
{
    // message for deleting account
    puts("");
    puts("\t\t\t\xB1\xB1\xB1\xB1\t VIEW LIST OF ACCOUNT \t\xB1\xB1\xB1\xB1");
    puts("");

    int index = mainSearch();

    if(index > -1) {
    accounts[index].accCode = 0;
//    ramove(accounts[index]);
    }

    else
        puts("Not found!");

    sort();
    writeFile();

    puts("");
    puts("Press any key to continue...");
    getch();
    system("cls");

    menu();
}

void see()
{
    // message for displaying all information about customer's account
    puts("");
    puts("\t\t\t\xB1\xB1\xB1\xB1\t VIEW LIST OF ACCOUNT \t\xB1\xB1\xB1\xB1");
    puts("");

    readFile();

    int index = mainSearch();

    printf("Code: %d\n", accounts[index].accCode);
    printf("Name: %s\n", accounts[index].name);
    printf("Age: %d\n", accounts[index].age);
    printf("Citizenship number: %ld\n", accounts[index].citNum);
    printf("Address: %s\n", accounts[index].city);
    printf("Phone number: %ld\n", accounts[index].phone);
    puts("");

    puts("");
    puts("Press any key to continue...");
    getch();
    system("cls");

    menu();
}

int mainSearch()
{
    // message for search account
    puts("");
    puts("\t Choose what way would you prefer to search for account:");
    puts("========================================================");
    puts("\t (1) Search by account number");
    puts("\t (2) Search by name");
    puts("\t (3) Search by phone number");
    puts("\t ============================");
    puts("");

    int ch,
        index;
    printf("\t Enter your choice: ");
    scanf("%d", &ch);

    switch(ch) {
        case 1:
            index = searchCode();   // search account by code
            break;

        case 2:
            index = searchName();   // search account by customer's name
            break;

        case 3:
            index = searchPhone();  // search account by phone number
            break;

        default:    // a wrong choice
            puts("   invalid value...");
            puts("   press any key to try again!");
            getch();
            break;
    }

    puts("");
    puts("Press any key to continue...");
    getch();
    system("cls");

    if(index > -1)
        return index;

    else
        return -1;
}

int searchCode()
{
    printf("Enter your code: ");
    int index;
    scanf("%d", &index);

    for(int i = 0; i < accountCounter; i++)
        if(index == accounts[i].accCode)
            return i;

    return -1;
}

int searchName()
{
    printf("Enter your name: ");
    char n[20];
    fflush(stdin);
    gets(n);

    for(int i = 0; i < accountCounter; i++)
        for(int j = 0; j < accountCounter - 1; j++)
            if(strcmp(accounts[j].name, accounts[j + 1].name) == 0)
                return j;

    return -1;
}

int searchPhone()
{
    printf("Enter your phone number: ");
    long int n;
    scanf("%ld", &n);

    for(int i = 0; i < accountCounter; i++)
        if(n == accounts[i].phone)
            return i;

    return -1;
}

void deposit(int index)
{
    printf("How much money would you deposit? ");
    int m;
    scanf("%d", &m);

    accounts[index].money = m;

    puts("");
    puts("Money deposit successfully");
}

void withdraw(int index)
{
    printf("How much money would you withdraw? ");
    int m;
    scanf("%d", &m);

    accounts[index].money = -m;

    puts("");
    puts("Money withdraw successfully");
}

void sort()
{
    for(int i = 0; i <= accountCounter; i++)
        for(int j = 0; j < accountCounter - 1; j++)
            if((accounts[j + 1].accCode - accounts[j].accCode) != 1) {
                struct account temp = accounts[j];
                accounts[j] = accounts[j + 1];
                accounts[j + 1] = temp;
    }
}

void readFile()
{
    FILE *rfPtr;

    if((rfPtr = fopen("system.txt", "r")) == NULL)
        puts("File is not exist!");

    else {
        accountCounter = 0;

        while(!feof(rfPtr)) {
            fscanf(rfPtr, "%6d", &accounts[accountCounter].accCode);
            fgets(accounts[accountCounter].name, 23, rfPtr);
            fscanf(rfPtr, "%6d%15ld", &accounts[accountCounter].age, &accounts[accountCounter].phone);
            fgets(accounts[accountCounter].city, 13, rfPtr);
            fscanf(rfPtr, "%12ld%d", &accounts[accountCounter].citNum, &accounts[accountCounter].money);

            accountCounter++;
        }
        fclose(rfPtr);
    }
}

void writeFile()
{
    FILE *wfPtr;

    if((wfPtr = fopen("system.txt", "r")) == NULL)
        puts("File is not exist!");

    else {
        accountCounter = 0;

        while(accounts[accountCounter].accCode != 0) {
            fprintf(wfPtr, "%-6d %-23s %-5d %-15ld %-28s %-12ld %d \n", accounts[accountCounter].accCode,
                    accounts[accountCounter].name, accounts[accountCounter].age, accounts[accountCounter].phone,
                    accounts[accountCounter].city, accounts[accountCounter].citNum, accounts[accountCounter].money);

            accountCounter++;
        }
        fclose(wfPtr);
    }

    readFile();
}

void appendFile()
{
    FILE *afPtr;

    if((afPtr = fopen("system.txt", "a")) == NULL)
        puts("File is not exist!");

    else {
        while(accounts[accountCounter].accCode != 0) {
            fprintf(afPtr, "%-6d %-23s %-5d %-15ld %-28s %-12ld %d \n", accounts[accountCounter].accCode,
                accounts[accountCounter].name, accounts[accountCounter].age, accounts[accountCounter].phone,
                accounts[accountCounter].city, accounts[accountCounter].citNum, accounts[accountCounter].money);

            accountCounter++;
        }
        fclose(afPtr);
    }
}
