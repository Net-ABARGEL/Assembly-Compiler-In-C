#include <stdio.h>
#include <string.h>
#include "partOne.h"
//
// poart three will work on the printing file
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

// function that print the ext file
void printTheExt(row * lableRow,char * ch)
{
	FILE *fp = fopen(ch,"w"); // creat the fike
	for (int i  = 0; i<n;i++) // going throw the machine code table
	{
		if (lableRow->aRE == 'E') // if there is an extern lable
		fprintf(fp,"%s %04d\n",lableRow->name,lableRow->adress); // print it on the new file
		lableRow = lableRow->newRow; // get to the next
	}
}

// function that pring the entry file
void printTheEnt(simbols * smlb,char * ch)
{
	int t =0;
	simbols * head = smlb; // to keep the head
	FILE *fp = fopen("entry","r"); // open the file we made at the program
	FILE *wfp = fopen(ch,"w"); // creat the entry file
	char *fullLine = malloc ( sizeof(32)); // max size of lable
	if (fullLine==NULL)
        printf("cant allocate memory");
	
	while (fgets(fullLine,80,fp)!=NULL) // moving throw all the file
	{
		t=0;
		
		if (*(fullLine+strlen(fullLine)-1)=='\n')
			*(fullLine+strlen(fullLine)-1)='\0'; // change the end of line to null insted of lnew line
		for (int i =0; i<smb;i++) // check if the entry is not already exist at the lables table
		{
			
			if (!(strcmp(fullLine,smlb->name)))
			{
				// not exist and print it
				fprintf(wfp,"%s %04d\n",smlb->name,smlb->adress);
				t=1;
				break;
			}
			smlb = smlb->newSimbol;
		}
		smlb = head;
		if (t==0)
		{
		printf("error , unkown entery lable on line %d \n",fileLine); // never seen lable error
		errors++;
		}
	}
	free(fullLine);
}

// function that print the object file
void printTheFile(row * lableRow)
{
	int * num = malloc(sizeof(int)*3); // arry for the 3 hex numbers
	if (num==NULL)
        printf("cant allocate memory");
	FILE *fp = fopen(objectFile,"w"); //creat the object file
	if (fp == NULL)
	printf ( "cant open the file");
	else
	fprintf(fp,"    %d %d  \n",n- dataAndStringCounter,dataAndStringCounter);
	for (int i =0;i<n;i++)
	{
		fprintf(fp,"%d",lableRow->adress);
		num = printHexa(lableRow->machineCode,num); // convert the binnary to dec
		fprintf(fp," %X%X%X ", num[0],num[1],num[2]); // print the dec at hex
		fprintf(fp,"%c\n",lableRow->aRE); // print the ARE type
		lableRow = lableRow->newRow; // get to the next row
	}
	//free(num);
}
//function that make the other files name;
void makeTheExportFileName(char *ch,int length)
{
	fileName=  getTheFileName(ch,length); //copy the file name
	objectFile = malloc (sizeof(ch)+3);
	if (objectFile==NULL)
        printf("cant allocate memory");
	strcpy(objectFile,fileName);
	strcat(objectFile ,".ob\0"); //will free at the end
	
}

//function that returns the file name only if its .as file
char * getTheFileName(char *ch,int length)
{
	int i =0;
		char * theName = malloc (sizeof(ch)+1); // one to add the \0
		if (theName==NULL)
        printf("cant allocate memory");
	
		while (*(ch+i)!=NULL) // copy the file name
		{
			*(theName+i) = *(ch+i);
			i++;
		}
        *(theName+i) = '\0';
		return theName;
}

// function that get a string and convert to hex number
int * printHexa(char *ch,int *num)
 {
     char first[5],second[5],third[5]; //arrays to seperate the number because atoi wont work with 12 bit
     int n1,n2,n3;
     int  j=4, p =8,i=0;
     for (; i<4;i++) // copy the binarry number
     {
         first[i] = *(ch+i);
         second[i]= *(ch+j);
         third[i] = *(ch+p);
         j++;p++;
     }
     first[i+1] = '\0';
	 //convert to string every 4 bit to integer
     n1 = atoi(first);
     n2 = atoi(second);
     n3 = atoi(third);

     num[0]= binaryToHex(n1); //convert 4 bit of binary to dec
	 num[1] =binaryToHex(n2);
	 num [2] = binaryToHex(n3);
	 return num;
    
 }

// function that convert a binary number to dec
 int binaryToHex(int n)
 {
     int num;
     int hexa=0;
     int i=1;
     while (n != 0) //doing the process to convert the number from binarry to dec
    {
        num = n % 10;
        hexa = hexa + num * i;
        i = i * 2;
        n = n / 10;
    }
    return hexa; // to make hexa we need to call the tensToBinarry function right after
 }