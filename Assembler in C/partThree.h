#include <stdio.h>
#include <string.h>
#include "partOne.h"

// part three will work on the printing file
// as like the obj, ext and ent files.
//affter the part the program will done wirking
static char *objectFile; // keep the object file name
static char *fileName; // keep the file name
extern int n; // the counter of the machine code lines
extern int smb; // counter for the lables table
extern int dataAndStringCounter; // counter for data andd string order
extern int fileLine; // counter of the row on the file
extern int errors;


char * getTheFileName(char *,int); // function that return the file name
void makeTheExportFileName(char *,int); // make the object file 
int * printHexa(char *,int*); // function that help to pring binarry string to dec numeric and then we can printing with %x
int binaryToHex(int); // convert the binarry number to dec
void printTheFile(row *);// function that start to print the file