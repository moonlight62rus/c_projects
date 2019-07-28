/*This program intended for parsing csv file
Made by Vyacheslav Vorobyev*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>   
#include <unistd.h>   //For getwd
#include "parse.h"    //For parse.c

char fname[20];         //File name for parse
char params[10];        //cols in csv file
char symb[2];	 	//Symbol for parse
char PathName[200];//buffer for directory
char PN;                //pointer for PathName
int cnts;		//counts for mean_aver
char averrange[10];

int main(int argc, char *argv[])
{
    int c;
    /*GETOPT*/
    while((c=getopt(argc, argv, "ndrm"))!=-1)
    {
        switch(c)
        {
            case 'n':
    		printf("Enter file name - '/NAME':\n");
    		scanf("%s", fname);
    		strncat(fname,".csv",4);
    		PN = getwd(PathName);
    		strncat(PathName,fname,strlen(fname));
    		printf("%s\n",PathName);

		strcpy(symb,";\0");
		strcpy(params,"no\0");
		strcpy(averrange, "1-2");
		cnts = 2;
            break;

            case 'd':
                 printf("Enter separator symbol:\n");
    		 scanf("%s",symb);
            break;

            case 'r':
    		 printf("[OPTIONAL!!!] Enter parameters a-x or press 'no' if no use parameters\n");
    		 scanf("%s", params);
	    break;

	    case 'm':
		 printf("Enter the number of counts\n");
		 scanf("%s",averrange);
		 cnts = atoi(averrange);
		 printf("Enter the range of columns to calculate the moving average\n");
		 scanf("%s", averrange);
            break;
	    
            default:
                fprintf(stderr,"This function needs argument -n");
        }
    }

    /*Parsing file function*/
    parse(PathName,symb,params,cnts,averrange);

    return 0;
}
