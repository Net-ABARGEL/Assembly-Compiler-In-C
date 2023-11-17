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

static int group = 0; // value for the move groups acording to the numbers of argument of any move
static   int firstArgument = 0; // miun type of the first argument
static  int  secondArgument = 0;// miun type of the second argument
static int line =100; // file line
 int n = 0; // file lines counter
static int smb = 0; // lables counter
 int dataAndStringCounter=0; // how many data orders counter
static int externsVlues = 0; // extern order counter
static int enrtyValues = 0; // entry values counter
static char *externName; //extern name
int precentGroup = 0; // changed if its precent able order
extern int fileLine;
extern int errors;

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



//structure for a move
typedef struct {
    char name[5];
    char opCode[5];
    char funcCode[5];
    int group;
}move;
// sturcture for all the moves
static move allMoves[]=
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

typedef struct{
    char name[3];
    char fullCode[13];
}ogers;
// making all the registers code with the struct ogers
static ogers oger[8] = 
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

// function that delete the spaces and tabs
char * deleteSpaceAndTab(char * ch)
{
   
    int i = 0;
    if (*(ch)==NULL) // the end of the arr
    return ch;
     while (*(ch+i) == 32 || *(ch+i) == 9) // check if its tab or space 
            i++;

     return ch+i; // return without tab and spaces
    
}
// function that converts a number from 10th to binary
char * tensToBinarry(int num) 
{
    int i =0,n;
    char  ch[32]; //= malloc(sizeof(int)*32);
    if (num<0)
    num = 65536 + num; // convert two's completion
    while (num!=0)
    {
        *(ch+i) = num % 2 +'0'; // insert the bit from the end
        num/=2;
        i++;
    }
    n=i;
    if (n>12) // max number possible with 12 bit
    {
        i=12;
        n=12;
    }
    
    char * newch= malloc(sizeof(char)*13); // max size of binary 12 bit nubmber
    if (newch==NULL)
        printf("cant allocate memory");
    for (int j=0;j<n;j++) // replace the oposite bit on a new arr
    {  
        newch[j] = ch[i-1];
        i--;
    }

    return newch; // returning the binarry number
}

// a function that get a move and return the full Code
char * getTheOpCode(char * ch)
{
    char * fullCode = malloc(sizeof(char)*12); // all the code of the move
    if (fullCode==NULL)
        printf("cant allocate memory");
    for (int i = 0; i<16;i++)
        if (!(strcmp(ch,allMoves[i].name))) // if its the same as one of the moves
        {
            strcpy(fullCode,allMoves[i].opCode); // add the opCode
            strcat(fullCode,allMoves[i].funcCode); // add the funcCode
            return fullCode; // change it in the future;
        }
    return "0"; // change it in the future
}
// a function that check if there is two points to know if there is a lable
int chekForDoublePoints(char * ch)
{
    int i =0;  // index
    ch = deleteSpaceAndTab(ch); // delete sapces from the ch
    while (*(ch+i)!= 32 &&*(ch+i)!=9)
    {
        if (*(ch+i)==':')  // if its ';'
        return 1; // true 
        i++;
    }
    //back to space
    return 0;  // there is not ';'
}
// a function that check for the psic for common moves
char * chekForPsic(char * ch)
{
    int i =0;
    ch = deleteSpaceAndTab(ch); // delete spaces and tab
    do
    {
        if (*(ch+i)==',') // check if Psic
        return ch+i+1; // return onr after the Psic
        i++;

    } while (*(ch+i)== 32 ||*(ch+i)==9); // continue untile the space or tab
    return "0"; // error
}
// Function that delete the ; and the rest of the row
char * deleteDotPsic(char *ch)
{
    char *ch2 = malloc(sizeof(char)*80); // max size of row is 80
    if (ch2==NULL)
        printf("cant allocate memory");
    strcpy(ch2,ch); // copy the char * to a new one
    int i=0; //index
   while (*(ch2+i)!=NULL) // check until the end of the row
    {
        if (*(ch2+i)==';') // if it equal to ';' 
        {
            *(ch2+i)='\0'; // maje it the end of the line
            return ch2; // return the text.
        }
        i++;
    }
   // free(ch2);
    return ch; // there is no ';' so return the full row
}
// function that return the miun code acording the grop of the comment and the arguments
char * checkTheMiunType(char * ch, int arg)
{
    if (*ch == '#') // first miun way
    {
        if (arg == 1) // firstArgument
         firstArgument = 1;  
         else secondArgument =1;
      return "00";
    }

    if (*ch == '%') // third miun way
    {
        if (precentGroup != 1)
        {
            printf ("error: wrong argument for that move on line %d \n",fileLine);
            errors++;
        }
        if (arg == 1)// firstArgument
         firstArgument = 3;  
         else secondArgument =3;
       return "10";
    }

    for (int i =0;i<8;i++) // check for second miun way
    if (!(strcmp(ch,oger[i].name))) // if its the same as one of the R's
    {
        if (arg == 1) // firstArgument
         firstArgument = 4;  
         else secondArgument =4;
        return "11";
    }
    if (arg == 1) // firstArgument
         firstArgument = 2;  
        else secondArgument =2;

    
    return "01"; // its a label
}
// a function that return the move full code
row * getTheMoveName(char * ch , row * firstRow, simbols * head)
{
    char * newCh = malloc (sizeof(char)*80); // max size of a row
    if (newCh==NULL)
        printf("cant allocate memory");
    char  * fullCode = malloc(sizeof(char)* 13);  // the full code for move
    if (fullCode==NULL)
        printf("cant allocate memory");
    ch = deleteSpaceAndTab(ch); // deletet the spaces
    strcpy(newCh,ch); // copy the char *
    int i=0; // index
    while (*(newCh+i)!=NULL) // check until the end of the new char*
   {
        if (*(newCh+i)==32 || *(newCh+i)==9) // if its space
        {
            *(newCh+i) = '\0';
            break;
        }
        i++;
    }
    int j =0; // new index
    for (;j<16;j++)
    {
        if (!(strcmp(newCh,allMoves[j].name))) // compare if the newCh is equal to the moves table
        {
            group = allMoves[j].group; // update the group of the move
            if (j == 9|| j == 10 || j ==11) // bne, jmp or jsr move
                precentGroup =1;
            char * argument = malloc(sizeof(ch)); // new char *
            if (argument==NULL)
            printf("cant allocate memory");
            fullCode = getTheOpCode(newCh); // calling the function to get the move code
            if (group == 1) // the first group with two argument
            {
                argument = getTheArgument (ch+i); // get the first argument
                strcat(fullCode,checkTheMiunType(argument,1)); // check witch type of miun with the argumnet
                ch = deleteTheWord(ch+i);// delete the argument
                ch = chekForPsic(ch); // check for coma because its the group with two arguments
                if (*(ch)=='0')
                {
                    printf("missing argument on line %d \n",fileLine); // missed argument
                    errors++;
                }
                ch = deleteSpaceAndTab(ch);
                argument = getTheArgument (ch);
                strcat(fullCode,checkTheMiunType(argument,2)); // add the code of the second argument code
                // checking that its the end of the line if not show error
                
                ch = deleteTheWord(ch);
                ch = deleteSpaceAndTab(ch);
                if (*(ch)!= '\0')
                {
                 printf ("too many arguments :%s:on line %d \n",ch,fileLine);
                 errors++;
                }

            }
            if (group == 2) // group with one argument
            {
                strcat(fullCode,"00"); // add the miun code for non makor argument
                argument = getTheArgument (ch+i); // get the argument
                strcat(fullCode,checkTheMiunType(argument, 1)); // add the miun code for the argument
                precentGroup = 0;
                // checking that its the end of the line if not show error
                ch = deleteTheWord(ch+i);
                ch = deleteSpaceAndTab(ch);
                if (*(ch)!= '\0')
                {
                 printf ("too many arguments :%s:on line %d \n",ch,fileLine); //error
                 errors++;
                }
            }
            if (group == 3)
            {
                strcat(fullCode,"0000");
                // checking that its the end of the line if not show error
                ch = deleteTheWord(ch);
                ch = deleteSpaceAndTab(ch);
                if (*(ch)!= '\0')
                {
                printf ("too many arguments :%s:on line %d \n",ch,fileLine); // error
                errors++;
                }
            }
            strcpy(firstRow->machineCode,fullCode); // adding the full code to the table of the machine codes
            line++;
           // free(argument);
        }
    }
    //free(fullCode);
    if (!(strcmp(newCh,".data"))) // .data order
    {    free(newCh);
        return dataOpCode(ch+i,firstRow);
    }

    if (!(strcmp(newCh,".string"))) // .srting order
        {free(newCh);
        return stringOpCode(ch+i,firstRow);
    }
    

// for entry we need to creat the file and add the data, if will be an error it will delete
    if (!(strcmp(newCh,".entry"))) //.entry order
    {
        group = 5;
        free(newCh);
        return addEntry(ch+i,firstRow,head);
    }
    
    if (!(strcmp(newCh,".extern"))) // .extern order
    {
        group=4; // influensing on the continue
        free(newCh);
    return addExtern(ch+i,firstRow);
    }
    if (group == 4)
    {
    printf ("unkown order command on line %d \n",fileLine);
    errors;
    }
    free(newCh);
    if (group == 0)
    {
        printf("unkown order at line %d \n",fileLine);
        errors++;
    }
    return firstRow; // not a move
    
}
// a function that write all the entry command lables on a new file, at the end of the program the file will be deleted
row * addEntry(char * ch,row * firstRow,simbols * head)
{
    simbols *copyHead = head;
    ch = deleteSpaceAndTab(ch); // delete the spaces
    if   (checkIfLableExist(ch)==1) // if the lable is already exist 
    {
        n--; // dec n by one
        return firstRow; // return the first row
    }
    if (checkIfTheExternExist(ch,copyHead)==2) // check if the lable is already extrned
    {
        printf("the lable is already externed :%s on line %d \n",ch,fileLine);
        errors++;
    }
    FILE *fp = fopen("entry","a"); // creat and write
    if (fp == NULL)
    printf("error opening the entry file"); // error
    fprintf(fp,"%s\n",ch); // print the lable with \n
    fclose(fp); // close the file
    enrtyValues++; // count the entry values number
    n--; // not a move to the table of commands
    return firstRow;
}
// a function that check if the entry is already showed, if so it will do nothing
int checkIfLableExist(char * ch)
{
    FILE *fp = fopen("entry","r"); // trying to read the file
    if (fp == NULL) // no file
        return 0;
    char * fullLine = malloc(sizeof(char)*80);//max size of row
    if (fullLine==NULL)
        printf("cant allocate memory");
   while( fgets(fullLine,80,fp)!=NULL) // check every entry that already been
   {
       
       if (*(fullLine+strlen(fullLine)-1)=='\n') // delete the new row at the end of the line
			*(fullLine+strlen(fullLine)-1)='\0';

       if(!strcmp(fullLine,ch)) // if its equal
       {
           fclose(fp);
           free(fullLine);
            return 1;
       }

   }
   fclose(fp); // not equal / not exist
   free(fullLine);
   return 0;
}
//function that check if the extern argument is exist
// works too on lables
int checkIfTheExternExist(char *ch,simbols *smlb)
{

    for (int i =0;i<smb;i++) // going throw all the lables table
    {
        if (!strcmp(ch,smlb->name))//equal
        {
            if(smlb->aRE=='e') // equal and extern
                return 2; // an extern
            return 1;//just equal
        }
        smlb = smlb->newSimbol; // get tot the next
    }
    return 0; // not exist
}
// a function that add extern value to the lables table
row * addExtern(char * ch,row * firstRow)
{
    externName = calloc(sizeof(char),32); // it will free at partTwo
    ch = deleteSpaceAndTab(ch); // delete spaces and tab
    strcpy(externName,ch); // copy the name to a global variable
    if (checkIfLableExist(externName)==1)
    {
        printf("error: the argument is already entried on line %d \n",fileLine);
        errors++;
    }
    externsVlues++; // add the external counter 1
    return firstRow;
}

// functiont that return the argument (can used for word)
char * getTheArgument(char * ch)
{
    int i= 0; // index
    ch = deleteSpaceAndTab(ch); // delete spaces
    char * newCh = malloc(sizeof(ch)); // allocate memory
    if (newCh==NULL)
        printf("cant allocate memory");
    while (*(ch+i)!=9&&*(ch+i)!=32&&*(ch+i)!=',') // until space,tab or coma
    {
        *(newCh+i)= *(ch+i);
        i++;
    }
    *(newCh+i) = '\0';
    return newCh; // returning the full agrument
}
// function that return the argument code
char * getTheArgCode(char * ch, int arg)
{
     int num;
    if (group == 1) // two argument command
    {
       if (arg == 1) // # type of argument
       {
           num = atoi(ch+1);
           return addZeroes(tensToBinarry(num)); // return the number affter the # in binnary code
       }
       if ( arg == 2) // lable or extern
       return "?";
       if (arg == 3) // % type of argument
       {
        printf("not the right argument for the move on line %d \n",fileLine); // not able to that group
        errors++;
        return "0";
       }
       if ( arg == 4) // oger argument
       return getTheOgerCode(ch);
    }

    if (group == 2) // one argument command
    {
       if (arg == 1) // # type of argument
       {
           num = atoi(ch+1);
           return addZeroes(tensToBinarry(num));
       }
       if ( arg == 2) // extern or lable
       return "?";
       if (arg == 3) // lable
        return "w";
       if ( arg == 4)  // oger argument
       {
          return getTheOgerCode(ch);
       }
    }
    return "0";
}


// return the code for numbers by convert to binary
row * dataOpCode(char * ch,row * firstRow)
{
    int i=0 ; // index
    int  num; // the number to convert to binary

    do 
    {
        char * newCh = calloc(sizeof(char),80); 
            if (newCh == NULL)
            printf("unable to allocate memory");
        ch = deleteSpaceAndTab(ch);
        while ((*(ch+i)>47 && *(ch+i)<=57)|| *(ch+i)==45 || *(ch+i)==43) // if its number or '-' or '+'
        {
            newCh[i] = *(ch+i);
            i++;
        }

        num = atoi(newCh); // convert to number
    
        char * str = calloc(sizeof(char),12); // to convert the number
        str = tensToBinarry(num); // convert to binary
        str =  addZeroes(str); // add zero to make 12 bit number
        strcpy(firstRow->machineCode,str); // insert the code to the table with the machine codes
        line++; // inc line by one
        ch = deleteTheWord(ch); // check for the next number if exist
        ch = chekForPsic(ch);
            dataAndStringCounter++; 
        if (*(ch)!='0') // there is a next argument number
        {
        firstRow->newRow = malloc(sizeof(row)); // new allocate memory
            if (firstRow == NULL)
            printf("unable to allocate memory");
        firstRow = firstRow->newRow; // getting to the next row
        firstRow->adress = line; // insert the line number
        n++;
        i=0;
        }
       // free (newCh); // free the memory
       // free (str); // free the dinamic memory of str
    } while (*(ch)!='0'); // do it until the end of the row

    return firstRow;

    
}
// a function that add zeroes to make the number a 12 bit number
char * addZeroes(char * ch)
{
    ch = strrev(ch); // rev the string
    while (strlen(ch)<12) 
    {
    *(ch+strlen(ch))='0'; // add 0 until length 12
    *(ch+strlen(ch)+1)='\0';
    }
    ch = strrev(ch); //rev again
    return ch; // return the number (string format)
}
// a function that return the Oger fullCode;
char * getTheOgerCode(char * ch)
{
    for (int i =0;i<8;i++) // check for second miun way
    if (!(strcmp(ch,oger[i].name))) // if its the same as one of the R's
       return oger[i].fullCode;
    return "0"; // not oger code
}

// a function that delete a full word
char * deleteTheWord(char * ch)
{
    ch = deleteSpaceAndTab(ch); // delete the spaces
    int i=0; // index
    while (*(ch+i)!=9 &&*(ch+i)!=32 && *(ch+i)!=','&& *(ch+i)!='\0') // not space, or tab or coma
    i++;
    return ch+i; // return the place after the word
}
row * stringOpCode(char * ch, row * firstRow)
{
    char *newCh = malloc(sizeof(80));// new row with max size
    if (newCh==NULL)
        printf("cant allocate memory");
   char *str = malloc(sizeof(char)*12);; // array of array for the
   if (str==NULL)
        printf("cant allocate memory");
    char asciArr[12]; // arr for askiCode;
    ch = deleteSpaceAndTab(ch); // delete the spaces of the line
    int i = 1;

    if (*ch != 34)
    {
    printf("error: its not string type on line %d \n",fileLine); // error if its not "xxx" type
    errors++;
    }
    
    else
    {
        while (*(ch+i)!=34)// if its good so keep going until the next ";
        {
            *(newCh+i-1)= *(ch+i); // put it in a new arr
            i++;
        }
        *(newCh+i)='\0'; // end of array
    }

    int num;
    for (int j =0;j<i-1;j++) // movinf throw any char in the array
    {
    sprintf(asciArr,"%u",*(newCh+j)); // convert to asci number in decimal base
    num = atoi(asciArr); // convert to int
    str = tensToBinarry(num); // convert to binarry
    str = addZeroes(str); // add zeros to 12 bit number
    strcpy(firstRow->machineCode,str); // copy the code to machine code table
    
    line ++; // inc lines by one
    firstRow->newRow = malloc(sizeof(row)); // allocate memory for the next row
    firstRow = firstRow->newRow; // get to the next row
    firstRow->adress = line; // insert the addres to the new row
    n++;
    dataAndStringCounter++;//inc the data and string counter for theobj file
    }
    strcpy(firstRow->machineCode,"000000000000"); // add the  '\0' code
    line++; // inc line by one
    dataAndStringCounter++;
    free(newCh);
  //  free(str);
    return firstRow; // changable

}

// function that revers a string;
char *strrev(char *str)
{
      char *p1, *p2;

      if (! str || ! *str)
            return str;
      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
      {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
      return str;
}
