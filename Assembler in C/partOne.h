#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// at this part of the project will be all the helpfull function that 
// i made to make this program possible and successful
// there is an explanation what is the target of any function
// this part include the struct we madde to make the program work

#ifndef STRUCT
#define STRUCT 12
typedef struct  row {

    char name[32]; // the max size of a label
    int adress;
    char machineCode[13];
    char aRE;
    struct row * newRow;
     }row;

typedef struct simbols {
    char name[32]; // the max size of a label
    int adress;
    char aRE;
    struct simbols * newSimbol;
     }simbols;

typedef struct ext {
    char name[32]; // the max size of a label
    int adress;
    struct ext * newextern;
     }ext;
typedef struct ent {
    char name[32]; // the max size of a label
    int adress;
    struct ent * newextern;
     }ent;

#endif
row * stringOpCode(char *,row*); // a function that return the char full 12 bit code
char * deleteSpaceAndTab(char*); // function that delete the spaces and tabs
char * tensToBinarry(int); // convert a number to binarry base
char * getTheArgument(char *); // function that return the argument name;
char * getTheopCode(char*); // return as char* the opCode of the move
int chekForDoublePoints(char*); // a function that will check for two points in the begging of the sentence
char * chekForPsic(char *);// function that check if there is a ,;
//char * deleteDotPsic(char*);// function that dellete the rest of the sentence affter the ';' 
char * checkTheMiunType(char*,int); // a function that check the miun type
char * miunMakorAndYaad(char*); // a func that check the miuns
row * getTheMoveName(char*,row*,simbols*); // a function that returns the move name such as mov dec and more
row * dataOpCode(char *,row*); // function that return the opcode of the .data argument
char * strrev(char *); //revers a str
char * getTheArgCode(char*,int); // function that return the argument code for first run
char * getTheOgerCode(char *); // function that retruns the oger full code
char * deleteTheWord(char *); // function that delete a full word
char * addZeroes(char * ); // function that add zeros to 12 bit number
row * addExtern(char * ,row *); // function that help to add an extern value
row * addEntry(char *,row*,simbols*); // function that help to add an entry value
int checkIfLableExist(char *); // check if the lable is already exist
int checkIfTheExternExist(char *,simbols *); // function that check if the extern is alread been externed