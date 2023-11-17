#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "partOne.h"
#include "partThree.h"
//part two will work on the file and will make all the data for the program that needed
// it will make struct to keep the data and will recognize all the orders and will
// keep all the 12 bit numbers and all the lables data.
// affter that we will use the data at part three

void testFirstRun(char * , row *,simbols *,simbols *); // function that start to work on the first run
void firstRun(char **,int, char *,row *,simbols *,simbols *); // the first run method of the file
char * isItALable(char *); // a function that check if there is a lable and take care of it
void secondRun(row * ,simbols *); //the second run method
char * getTheLableCode(char * ,simbols * ,int,int,row*); // function that give the lable 12 bit code for second run