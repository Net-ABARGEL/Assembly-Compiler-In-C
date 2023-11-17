#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "partOne.h"
#include "partThree.h"
//part two will work on the file and will make all the data for the program that needed
// it will make struct to keep the data and will recognize all the orders and will
// keep all the 12 bit numbers and all the lables data.
// affter that we will use the data at part three

extern int line; // machine code line
extern int n; // the assembler orders counter
//static int checkk=0; // help to check at the 
extern int smb; //how many lables there are
int lableFlag = 0; // a flag to kn ow there is a lable
int fileLine=0;
extern int errors;
    extern int   group; // extern integer that gives the order group
    extern int  firstArgument; // give the miun type for the first argument
    extern int  secondArgument; // give the miun type for the second argument
    extern char  *externName; // the extern name

// making the moves struct
typedef struct {
    char name[5];
    char opCode[5];
    char funcCode[5];
    int group;
}moves;
// sturcture for all the moves for part two
static moves allMoveso[]=
{   {"mov\0","0000","0000",1},
    {"cmp\0","0001","0000",1},
    {"add\0","0010","1010",1},
    {"sub\0","0010","1011",1},
    {"lea\0","0100","0000",1},
    {"clr\0","0101","1010",2},
    {"not\0","0101","1011",2},
    {"inc\0'","0101","1100",2},
    {"dec\0","0101","1101",2},
    {"jmp\0","1001","1010",2},
    {"bne\0","1001","1011",2},
    {"jsr\0","1001","1100",2},
    {"red\0","1100","0000",2},
    {"prn\0","1101","0000",2},
    {"rts\0","1110","0000",3},
    {"stop\0","1111","0000",3}
};
// make the registrs struct
typedef struct{
    char name[3];
    char fullCode[13];
}ogersa;
// making all the registers code with the struct ogers for part two
static ogersa ogerso[8] = 
{
    {"r0\0","000000000001"},
    {"r1\0","000000000010"},
    {"r2\0","000000000100"},
    {"r3\0","000000001000"},
    {"r4\0","000000010000"},
    {"r5\0","000000100000"},
    {"r6\0","000001000000"},
    {"r7\0","000010000000"}
};

void testFirstRun(char * , row *,simbols *,simbols *); // function that start to work on the first run
void firstRun(char **,int, char *,row *,simbols *,simbols *); // the first run method of the file
char * isItALable(char *); // a function that check if there is a lable and take care of it
void secondRun(row * ,simbols *); //the second run method
char * getTheLableCode(char * ,simbols * ,int,int,row*); // function that give the lable 12 bit code for second run

// a function that complate the data by adding the lables and type % orders
void secondRun(row * lableRow,simbols * smlb)
{
    simbols * head = smlb; // to keep the head
    for (int i =0;i<n;i++) // moving throw all the assembler orders
    {
        if (!(strcmp(lableRow->machineCode,"w"))) // its a % move
        strcpy(lableRow->machineCode,getTheLableCode(lableRow->name,smlb,lableRow->adress,1,lableRow)); // get the code
        else
        if (!(strcmp(lableRow->machineCode,"?"))) // extern argument
        strcpy(lableRow->machineCode,getTheLableCode(lableRow->name,smlb,lableRow->adress,2,lableRow)); // get the code
        else
            lableRow->aRE = 'A'; // its a regular order
        
        lableRow = lableRow->newRow; // getting to the next lable row
    }
}

// a function that return 12 bit of lable code according to the memory place
char * getTheLableCode(char * ch,simbols * smlb,int num,int n,row * lableRow)
{
    for ( int i =0; i<smb;i++) // moving throw the lables struct
    {
        if (!(strcmp(smlb->name,ch))) // equal to lable
        {
            if (n == 1) // 'w' 
            {
                lableRow->aRE = 'A'; 
                 return addZeroes(tensToBinarry(smlb->adress - num)); // add the 12 bit number of how fur the lable
            }
            else //"?"
            {
                
               if (smlb->aRE == 'e') // its extern lable
                lableRow->aRE = 'E'; 
                else
                   lableRow->aRE = 'R';    // not extern
            return addZeroes(tensToBinarry(smlb->adress)); // give the place of the lable with 12 bit
            }
        }
        smlb = smlb->newSimbol; // get to the next lable
    }
    printf ("unkown lable name %s \n",ch);
    errors++;
    return "0";
}

// a function that work on the first run of the file
void firstRun(char **argv,int arg, char * fullLine,row *lableRow,simbols * smlb,simbols * head)
{
    int value = 0; // value
    int lables = 0; // counter of lables
     for (int p =1;p<arg;p++) // going throw the number of file included
     {
        char *fileName =malloc(sizeof(argv[p]+4));// +4 for the end of the file type
        if (fileName==NULL)
        printf("cant allocate memory");
        strcpy(fileName,argv[p]);
        strcat(fileName,".as\0");
        FILE *fp = fopen(fileName,"r"); // open the file
        if (fp == NULL)
        printf("unable to open the files its not .as file\n"); // not exist
        else
        
        while (fgets(fullLine,80,fp)!=NULL) // going throw every line
        {
            fileLine++;
			if (*(deleteSpaceAndTab(fullLine))=='\n'||*(deleteSpaceAndTab(fullLine))==';') // check for blank line or ';' line
			continue;
            if (*(fullLine+strlen(fullLine)-1)=='\n')
                *(fullLine+strlen(fullLine)-1)='\0'; // change the end of the line to null insted of new line
            testFirstRun(fullLine, lableRow, smlb,head);
            for (;value<n;value++) // for to get the end of the struct
            {
            if (value==n-1)
                lableRow->newRow= malloc(sizeof(row));
                lableRow = lableRow->newRow;
            }
            for (;lables<smb;lables++) // for to get the end of the struct
            {
            if (lables==smb-1)
                 smlb->newSimbol= malloc(sizeof(row));
                 smlb = smlb->newSimbol;
            }
        }
        free(fileName); // free the memory
     }
}

void testFirstRun(char * ch, row * firstRow,simbols * smlb,simbols * head)
{
    simbols * oneEarlier = smlb; // for lables with exern or entry orders
    int lableBforeExternOrEntry=0; //counter for extern or entrys
    
   if (isItALable(ch)!="0") // check if its a lable, if it is add the lable to the 
    {   
        if (checkIfTheExternExist(isItALable(ch),head) == 0) //check that its not exist
        {
        smlb->adress = line; // add the line
        strcpy(smlb->name,isItALable(ch)); // copy the lable name
        ch = deleteTheWord(ch);// delete spaces
        smlb->newSimbol = calloc(sizeof(simbols),1); // get to the next row at lables table
        smlb = smlb->newSimbol; // get to the next lable
        smb++;
        lableBforeExternOrEntry=1;
        }
        else
        {
            printf("the lable is already exist on line %d \n",fileLine);
            errors++;
        }
        
    }
    firstRow->adress = line; // add the line adress to the machone code table
    firstRow = getTheMoveName(ch,firstRow,head); // get the code for the order (the argument will get later)
    if (group == 4) // extern order
    {
        smlb = oneEarlier; // unimportent lable name
        if (checkIfTheExternExist(externName,head) == 0) // not exist
        {
        strcpy(smlb->name,externName); // copy yhe name
        smlb->adress = 0;
        smlb->aRE = 'e'; // flag its extern lable
        smlb->newSimbol = calloc(sizeof(simbols),1); // get to the next lable
        smlb = smlb->newSimbol;
        if(lableBforeExternOrEntry!=0)
            smb--;
        smb++;
        
        free(externName);
        }
        n--; // discount because its extern
    }
    if (group == 5) // entry order, will take care at second run
    {
        if(lableBforeExternOrEntry!=0) // if exist will ignore
        {
            smlb = oneEarlier;
            smb--;
        }
    }
    ch = deleteTheWord(ch);
    
    if (group ==2 || group == 1) // two or one argument order
    {
        n++;
        firstRow->newRow = malloc(sizeof(row)); // new row at the machine code table
        firstRow =firstRow->newRow;
        firstRow->adress = line; // add the line
        
        strcpy(firstRow->machineCode,getTheArgCode(getTheArgument(ch),firstArgument));
        if (!(strcmp(firstRow->machineCode,"?"))) // its an lable or extern
        strcpy(firstRow->name,getTheArgument(ch));

        if (!(strcmp(firstRow->machineCode,"w"))) // its a % argument
        strcpy(firstRow->name,getTheArgument(ch)+1);
        ch = deleteTheWord(ch);
        line ++; //inc the line
    
        if (group == 1) // two argument order
        {
            n++;
            if ((ch=chekForPsic(ch))=="0") // check if there is a coma
            {
            printf ("error with coma :%s: on line %d \n",ch,fileLine); //error
            errors++;
            }
            firstRow->newRow = malloc(sizeof(row));  // adding the second argument code
            firstRow =firstRow->newRow;
            firstRow->adress = line;
            strcpy(firstRow->machineCode,getTheArgCode(getTheArgument(ch),secondArgument));

             if (!(strcmp(firstRow->machineCode,"?"))) // extern or lable
            strcpy(firstRow->name,getTheArgument(ch));

            if (!(strcmp(firstRow->machineCode,"w"))) // % move
           strcpy(firstRow->name,getTheArgument(ch)+1);
            line++;

        }
    }
    n++; // inc the code by one
    group = 0;
    firstArgument =0;
    secondArgument = 0;
    lableFlag=0;

}
//function that return if there is a lable, if there is it will return the lable, if not returns '0'
char * isItALable(char * ch)
{
    char * newCh = malloc(sizeof(char)*80); // max size of lable;
    if (newCh==NULL)
        printf("cant allocate memory");
    char * lable = malloc(sizeof(char)*80);
    if (lable==NULL)
        printf("cant allocate memory");
    int i=0; // index
    strcpy(newCh,ch); // copy the text
    newCh = deleteSpaceAndTab(newCh);
    if (*(newCh)>47&&*(newCh)<58&&lableFlag==0) // check if it start with number - error
    {
        if (lableFlag ==0) // only once
        printf("ilegal lable name, cant start with number %son line %d \n",newCh,fileLine);
        lableFlag++;
        errors++;
    }
    if (chekForDoublePoints(newCh)==1) // check if its a lable
    {   
        
        while (*(newCh+i)!= 32 ||*(newCh+i)!=9) // getting the lable name
        {
            if (*(newCh+i)==':') // end of the lable
            {
                if (*(newCh+i+1)!=9 && *(newCh+i+1)!=32) // space or tab after the : - error if not
                 if (lableFlag == 0)  // flag to not repeat its ilegal lable name
                 {
                    printf ("ilegale lable name on line %d \n",fileLine);
                    errors++;
                    lableFlag++;
                       break;}
            if (lableFlag==0)
                for (int j=0;j<16;j++) // check if its a saved name
               {
                   if (!(strcmp(lable,allMoveso[j].name))) // all the orders
                   {
                       printf ("ilegale lable name, its a saved word %s on line %d \n",lable,fileLine);
                       errors++;
                       lableFlag++;
                       break;}
            
                   if (!(strcmp(lable,ogerso[j].name))) // all the registrs name
                   {
                        printf ("ilegale lable name, its register saved name %s on line %d \n",lable,fileLine);
                        errors++;
                        lableFlag++;
                        break;}
               }
            return lable; // return the lable
            }
            *(lable+i) = *(newCh+i); // copy the name of the lable
            i++;

        }
    }
    return "0"; // not a lable
}

