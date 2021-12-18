#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "user_operations.h"

#define USER_LIMIT 100
#define TRANS_LIMIT 100000
#define STRING_LIMIT 64
#define USER_FILE "data/user.dat"
#define TRANS_FILE "data/trans.dat"


void save(int total_users, int total_trans, struct Person users[USER_LIMIT], struct Transaction transactions[TRANS_LIMIT]);
void load(int counts[3], struct Person users[USER_LIMIT], struct Transaction transactions[TRANS_LIMIT]);
void print_transactions(int total_trans, struct Transaction transactions[TRANS_LIMIT]);
void print_users(int total_users, struct Person users[USER_LIMIT]);
int login(int total_users, struct Person users[USER_LIMIT]);
int signup(int total_users, struct Person users[USER_LIMIT]);
void wait_input(char* name, int show_message);
 
int main (int argc, char *argv[])
{
    static struct Person users[USER_LIMIT];
    static struct Transaction transactions[TRANS_LIMIT];
    static int counts[3];
    int total_users = 0;
    int total_trans = 0;
    int active_user = -1;
    int input;

    load(counts, users, transactions);
    total_users += counts[0];
    total_trans += counts[1];
    printf("Welcome to the bank\n");

    while(active_user == -1)
    {
        printf("What would you like to do?\n1. Login\n2. Signup\n3. Exit\n");
        scanf("%d", &input);
        switch(input)
        {
            case 1:
                active_user = login(total_users, users);
                break;
            case 2:
                total_users += signup(total_users, users);
                save(total_users, total_trans, users, transactions);
                break;
            case 3:
                exit(0);
                break;
            default:
                printf("Invalid input\n");
        }
        
    }

    printf("Hello, %s. What would you like to do?\n\n", users[active_user].username);

    while(1==1) {
        system("clear");
        printf("What would you like to do?\n1. Deposit\n2. Withdrawal \n3. Transfer \n4. See Balance\n5. Exit\n");
        if (users[active_user].admin == 1) {
            printf("\n-----Admin Options-----\n\n");
            printf("6. Users\n7. Transactions\n");
        }
        //TODO: Add more commands for admin
        scanf("%d", &input);
        
        switch(input)
        {
            case 1:
                deposit(users, transactions, active_user, total_trans);
                total_trans += 1;
                save(total_users, total_trans, users, transactions);
                wait_input("deposit", 1);
                break;
            case 2:
                withdrawal(users, transactions, active_user, total_trans);
                total_trans += 1;
                save(total_users, total_trans, users, transactions);
                wait_input("withdrawal", 1);
                break;
            case 3:
                transfer(users, transactions, active_user, total_trans, total_users);
                total_trans += 1;
                save(total_users, total_trans, users, transactions);
                wait_input("transfer", 1);
                break;
            case 4:
                printf("Current balance is: $%.2f\n", users[active_user].balance);
                wait_input("", 0);
                break;
            case 5:
                exit(0);
            case 6:
                if (users[active_user].admin == 1) {
                    print_users(total_users, users);
                } else {
                    printf("You are not an admin.\n");
                }
                wait_input("", 0);
                break;
            case 7:
                if (users[active_user].admin == 1) {
                    print_transactions(total_trans, transactions);
                } else {
                    printf("You are not an admin.\n");
                }
                wait_input("", 0);
                break;
            default:
                printf("Invalid input\n");
        }
    }
    
    return 0;
}

void save(int total_users, int total_trans, struct Person users[USER_LIMIT], struct Transaction transactions[TRANS_LIMIT]) 
{
    FILE *outfile = fopen (USER_FILE, "w");
    int i;
     
    if (outfile == NULL)
    {
        fprintf(stderr, "\nError opened file\n");
        exit (1);
    }

    for (i=0; i<total_users; ++i) 
    {
        fwrite(&users[i], sizeof(struct Person), 1, outfile);
    }

    fclose (outfile);

    outfile = fopen (TRANS_FILE, "w");
        if (outfile == NULL)
    {
        fprintf(stderr, "\nError opened file\n");
        exit (1);
    }

    for (i=0; i<total_trans; ++i) 
    {
        fwrite(&transactions[i], sizeof(struct Transaction), 1, outfile);
    }

    fclose (outfile);
}


void load(int counts[3], struct Person users[USER_LIMIT], struct Transaction transactions[TRANS_LIMIT]) 
{
    FILE *infile = fopen (USER_FILE, "r");
    struct Person input;
    int i, j;

    // Load in the People
    if (infile == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        exit (1);
    }

    i = 0;
    while(fread(&input, sizeof(struct Person), 1, infile)) 
    {
        users[i].balance = input.balance;
        users[i].admin = input.admin;
        strcpy(users[i].username, input.username);
        strcpy(users[i].password, input.password);
        ++i;
    }

    fclose (infile);

    //Load in the Transactions
    infile = fopen (TRANS_FILE, "r");
    struct Transaction n_input;

    if (infile == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        exit (1);
    }

    j = 0;
    while(fread(&n_input, sizeof(struct Transaction), 1, infile)) 
    {
        transactions[j].amount = n_input.amount;
        transactions[j].trans_date = n_input.trans_date;
        strcpy(transactions[j].from_username, n_input.from_username);
        strcpy(transactions[j].to_username, n_input.to_username);
        ++j;
    }

    fclose (infile);
    counts[0] = i;
    counts[1] = j;
}


void print_users(int total_users, struct Person users[USER_LIMIT]) 
{
    int i;
    for (i=0; i<total_users; ++i) 
    {
        printf("%s balance: $%.2f\n", users[i].username, users[i].balance);
    }
}

void print_transactions(int total_trans, struct Transaction transactions[TRANS_LIMIT]) 
{
    int i;
    //char buffer[20];

    printf("Date\tAmount\tFrom\tTo\n");
    printf("-------------------------\n");
    for (i=0; i<total_trans; ++i)
        //strftime(buffer, 20, "%Y-%m-%d", localtime(&transactions[i].trans_date));
    {
        
        printf("date\t%.2f\t%s\t%s\n", transactions[i].amount, transactions[i].from_username,transactions[i].to_username);
    }
    
}


int login(int total_users, struct Person users[USER_LIMIT]) 
{
    int i;
    char user_pass[STRING_LIMIT];
    char user_user[STRING_LIMIT];

    printf("\nEnter username:\n");
    scanf("%63s",user_user);

    printf("Enter password:\n");
    scanf("%63s", user_pass);
    
    for (i=0; i<total_users; ++i) 
    {
        if (strcmp(users[i].username, user_user ) == 0 && strcmp(users[i].password, user_pass ) == 0)
        {
            return i;
        }
        
    }
    return -1;
}

int signup(int total_users, struct Person users[USER_LIMIT]) 
{
    int i;
    char user_pass[STRING_LIMIT];
    char user_user[STRING_LIMIT];

    printf("\nCreate a username:\n");
    scanf("%63s",user_user);

    printf("Create a password:\n");
    scanf("%63s", user_pass);
    
    for (i=0; i<total_users; ++i) 
    {
        if (strcmp(users[i].username, user_user ) == 0)
        {
            printf("Username already taken!\n");
            return 0;
        }
    }
    users[total_users].admin = 0;
    users[total_users].balance = 0.0;
    strcpy(users[total_users].username, user_user);
    strcpy(users[total_users].password, user_pass);

    return 1;

}

void wait_input(char* name, int show_message) {
    if (show_message == 1) {
        printf("The %s was succesful. Press Enter to Continue\n", name);
    } else {
        printf("Press Enter to Continue\n");
    }
    fflush(stdin);
    while (getchar() != '\n');
}
