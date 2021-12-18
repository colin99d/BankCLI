#include <stdio.h>
#include <string.h>
#include <time.h>

#define USER_LIMIT 100
#define TRANS_LIMIT 100000
#define STRING_LIMIT 64

struct Person
{
    char username[STRING_LIMIT];
    char password[STRING_LIMIT];
    float balance;
    int admin;
};

struct Transaction
{
    char from_username[STRING_LIMIT];
    char to_username[STRING_LIMIT];
    float amount;
    time_t trans_date;

};

void deposit(struct Person users[USER_LIMIT], struct Transaction transactions[TRANS_LIMIT], int active_user, int total_trans) {
    float amount;

    printf("\nAmount to deposit:\n");
    scanf("%f", &amount);

    transactions[total_trans].amount = amount;
    transactions[total_trans].trans_date = time(NULL);
    strcpy(transactions[total_trans].from_username, users[active_user].username);
    strcpy(transactions[total_trans].to_username, "");

    users[active_user].balance += amount;
}

void withdrawal(struct Person users[USER_LIMIT], struct Transaction transactions[TRANS_LIMIT], int active_user, int total_trans) {
    float amount;

    printf("\nAmount to withdrawal:\n");
    scanf("%f", &amount);

    if (users[active_user].balance > amount) {
        transactions[total_trans].amount = -amount;
        transactions[total_trans].trans_date = time(NULL);
        strcpy(transactions[total_trans].from_username, users[active_user].username);
        strcpy(transactions[total_trans].to_username, "");

        users[active_user].balance -= amount;
    } else {
        printf("You cannot withdrawal $%.2f, you only have $%.2f.\n", amount, users[active_user].balance);
    }
}

void transfer(struct Person users[USER_LIMIT], struct Transaction transactions[TRANS_LIMIT], int active_user, int total_trans, int total_users) {
    struct Person to_users[USER_LIMIT];
    struct Person to_user;
    float amount;
    int to_user_num;
    int i, j;

    printf("\nAmount to transfer:\n");
    scanf("%f", &amount);

    printf("\nWho would you like to transfer to:\n");
    j = 0;
    for (i=0; i<total_users; ++i) {
        if (strcmp(users[active_user].username, users[i].username) != 0) {
            to_users[j] = users[i];
            printf("%d. %s\n", j, users[i].username);
            ++j;
        }
    }
    scanf("%d", &to_user_num);

    if (to_user_num >= 0 && to_user_num <= j) {
        to_user = to_users[to_user_num];

        if (users[active_user].balance > amount) {
            transactions[total_trans].amount = -amount;
            transactions[total_trans].trans_date = time(NULL);
            strcpy(transactions[total_trans].from_username, users[active_user].username);
            strcpy(transactions[total_trans].to_username, to_user.username);

            users[active_user].balance -= amount;
            for (i=0; i<total_users; ++i) {
                if (strcmp(to_user.username, users[i].username) == 0) {
                    break;
                }
            }
            users[i].balance += amount;
        } else {
            printf("You cannot transfer $%.2f, you only have $%.2f.\n", amount, users[active_user].balance);
        }
    }
}
