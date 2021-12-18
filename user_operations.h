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

void transfer(struct Person users[USER_LIMIT], struct Transaction transactions[TRANS_LIMIT], int active_user, int total_trans, int total_users);
void deposit(struct Person users[USER_LIMIT], struct Transaction transactions[TRANS_LIMIT], int active_user, int total_trans);
void withdrawal(struct Person users[USER_LIMIT], struct Transaction transactions[TRANS_LIMIT], int active_user, int total_trans);
