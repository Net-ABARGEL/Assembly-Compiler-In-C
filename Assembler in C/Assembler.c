#include <stdio.h>
#include <string.h>
#include "partOne.c"
#include "partTwo.c"
#include "partThree.c" 

int errors = 0; // counter for errors
extern int externsVlues; // counter for externs
extern int enrtyValues; // counter for entery

int main(int arg,char **argv)
 {
     
    row * lableRow = (row*)malloc(sizeof(row)); // making a table for machine code rows
    if (lableRow==NULL)
        printf("cant allocate memory");
    row * head = lableRow;

    simbols * smlb = (simbols*) malloc(sizeof(simbols)); // making a table for the lables table
    if (smlb==NULL)
        printf("cant allocate memory");
    simbols * smlbHead = smlb;

    int length =2;
    int makeFile = 0; // flag for make the file at the continue

    char * fullLine= malloc (sizeof(char)*80); // max size of line
    if (fullLine==NULL)
        printf("cant allocate memory");

    if (argv[1]!=NULL&&makeFile==0) // make the exportFiles name
    {
     length = strlen(argv[1])-1;
    makeTheExportFileName(argv[1],length);
    makeFile=1; 
    }

    firstRun(argv,arg,fullLine,lableRow, smlb,smlbHead); // doing the first run

    lableRow = head; // backed to the head of the table
    smlb = smlbHead; // backed to the head of the table

    secondRun(lableRow,smlb); // doing the second run

    lableRow = head; // backed to the head of the table
    smlb = smlbHead; // backed to the head of the table

    if (errors==0) // no errors
    printTheFile(lableRow); // print the data on  the ob file

    lableRow = head; // backed to the head of the table
    smlb = smlbHead; // backed to the head of the table

    if (errors==0) // no errors
        if (externsVlues>0) // print the ext file if there is an extern value
        {
            char * externFile = malloc(sizeof(fileName)+4);
            if (externFile==NULL)
            printf("cant allocate memory");
            strcpy(externFile,fileName);
            strcat(externFile,".ext\0"); // creating the file name
            printTheExt(lableRow,externFile); // making the file
        }
    if (errors==0) // no errors
        if (enrtyValues>0) // if there is an entry file
        {
            char * entFile = malloc(sizeof(fileName)+4);
            if (entFile==NULL)
            printf("cant allocate memory");
            strcpy(entFile,fileName);
            strcat(entFile,".ent\0"); // creating the file name
            printTheEnt(smlb,entFile); // print the data on the ent file
        }

remove("entry"); // delete the helper file for entry
if (errors!=0) // showing message if there is an errors
printf("\ncouldnt done the program because there are some errors");
return 0; //done!
 }
 
