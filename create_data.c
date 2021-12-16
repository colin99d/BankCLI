#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
// a struct to read and write
struct person
{
    char fname[64];
    char lname[64];
    float balance;
    int admin;
};
 
int main ()
{
    FILE *outfile;
     
    // open file for writing
    outfile = fopen ("user.dat", "w");
    if (outfile == NULL)
    {
        fprintf(stderr, "\nError opened file\n");
        exit (1);
    }
 
    struct person input1 = {"rohan", "sharma", 100.00, 1};
    struct person input2 = {"mahendra", "dhoni", 100.00, 0};
     
    // write struct to file
    fwrite (&input1, sizeof(struct person), 1, outfile);
    fwrite (&input2, sizeof(struct person), 1, outfile);
 
    // close file
    fclose (outfile);
 
    return 0;
}