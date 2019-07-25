/*This is file of parsing function*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parse.h"
#include <ctype.h>

void parse(char *name, char *symb, char *params)
{
    FILE *f1;        //For open CSV File
    char text[10000];		//For reading line from text
    char *rtext;            //Fragment from textline
    char *estr;             //Link to textline
    int range[2];			//Range of cols


    /*Opening file*/
    f1 = fopen(name, "r");
    printf("\n File is open\n");

    /*Parsing CSV file with input range*/
    if (strcmp(params, "no"))
    {
        rtext = strtok(params,"-");
        range[0] = atoi(rtext);
        rtext = strtok(NULL,"-");
        range[1] = atoi(rtext);

        estr = fgets(text,sizeof(text),f1);
        while (estr !=NULL)
        {
            rtext = strtok(text,";");
            for (int cnt = 0; cnt<range[0]-1; ++cnt)
                rtext = strtok(NULL,";");

            for (int cnt = range[0]; cnt<range[1]+1; ++cnt)
            {
                printf("%25s|",rtext);
                rtext = strtok(NULL,";");
            }
            printf("\n");
            estr = fgets(text, 1000, f1);
        }
    }
    else
    /*Parsing CSV file without range*/
    {
        estr = fgets(text,sizeof(text),f1);
        while (estr !=NULL)
        {
            rtext = strtok(text,symb);
            while(rtext != NULL)
            {
                printf("%25s|", rtext);
                rtext = strtok(NULL,symb);
            }
            printf("\n");
            estr = fgets(text, 1000, f1);
        }
    }
}
