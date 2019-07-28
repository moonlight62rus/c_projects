/*This is file of parsing function*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parse.h"
#include <limits.h>
#include <ctype.h>

void parse(char *name, char *symb, char *params, int count, char *arange)
{
    FILE *f1;        //For open CSV File
    char text[10000];		//For reading line from text
    char *rtext;            //Fragment from textline
    char *estr;             //Link to textline
    int range[2];			//Range of cols
	int avrange[2];			//Range of cols for averaging
	int linecnt = 0;
	int s = 0;
	
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

        if (strcmp(arange, "no") == 0)
		{
			printf("\nWithout moving average\n");        	
			estr = fgets(text,sizeof(text),f1);
        	while (estr !=NULL)
        	{
            	rtext = strtok(text,symb);
            	for (int cnt = 0; cnt<range[0]-1; ++cnt)
                	rtext = strtok(NULL,";");

            	for (int cnt = range[0]; cnt<range[1]+1; ++cnt)
            	{
                	printf("%30s|",rtext);
                	rtext = strtok(NULL,";");
            	}
            	printf("\n");
            	estr = fgets(text, 1000, f1);
        	}
		}
		/*Parsing with average cols and moving average*/		
		else
		{
			printf("\nWith Moving Average\n");			
			float outnum = 0.0;			
			float number[avrange[1]][count];			
			rtext = strtok(arange,"-");
	        avrange[0] = atoi(rtext);
	        rtext = strtok(NULL,"-");
	        avrange[1] = atoi(rtext);
			estr = fgets(text,sizeof(text),f1);			
			while (estr != NULL)
			{
				++linecnt;				
				rtext = strtok(text,symb);				
				for (int cnt = 0; cnt<range[0]-1;cnt++)	//before range cols
						{rtext = strtok(NULL,symb);}				
				
				for (int cnt = range[0]; cnt<=range[1]; cnt++)	//inside rcols 
            	{
					if (cnt>= (avrange[0]) && (cnt <= avrange[1]))
					{
						if (linecnt == 1)
						{						
							char word[50];						
							strncpy(word,rtext,strlen(rtext));							
							strncat(word," (mean)",7);
							printf("%30s|",word);
							rtext = strtok(NULL,symb);
						}
						else
						{
							if (linecnt > count+1)
								s = count;							
							
							char word[50] = "";
							strncpy(word,rtext,strlen(rtext));
							number[s][cnt] = atof(word);
							
							if (linecnt < count+1)
								{
									printf("%30.2f|",number[s][cnt]);
								}							
							else
							{
								for (int i = 1; i <= s; ++i)
									{
										outnum += number[i][cnt];
										//printf("%f",outnum);
									}
								outnum /= count;	
								printf("%24.2f(mean)|",outnum);
								outnum = 0;
								for (int i = 1; i <= s; i++)
        							{number[i-1][cnt] = number[i][cnt];}
							}		
							rtext = strtok(NULL,symb);
						}
					}                 		
					else
					{						
						printf("%30s|",rtext);
						outnum = 0;
                		rtext = strtok(NULL,";");
					}
            	}
				printf("\n");
				++s;				
				estr = fgets(text,sizeof(text),f1);
			}
		}    
	}
	else
    /*Parsing CSV file without range*/
	if (strcmp(arange, "no") == 0)    
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
	/*Parsing without cols range and with moving average */	
	else
	{
		rtext = strtok(arange,"-");
	    avrange[0] = atoi(rtext);
	    rtext = strtok(NULL,"-");
	    avrange[1] = atoi(rtext);

		float outnum = 0.0;			
		float number[avrange[1]][count];
		linecnt = 0;
		estr = fgets(text,sizeof(text),f1);	
		
		while (estr != NULL)
			{	
				rtext = strtok(text,symb);				
				++linecnt;    				
				for (int cnt = 0; cnt<avrange[0]-1;cnt++)
				{
					printf("%30s|", rtext);
	                rtext = strtok(NULL,symb);						
				}
				for (int cnt = avrange[0]-1; cnt<avrange[1];cnt++)
				{
					if (linecnt == 1)
					{
						char word[50];						
						strncpy(word,rtext,strlen(rtext));							
						strncat(word," (mean)",7);
						printf("%30s|",word);
						rtext = strtok(NULL,symb);
					}
					else
					{
						if (linecnt > count+1)
							{s = count;}							
						
						char word[50] = "";
						strncpy(word,rtext,strlen(rtext));
						number[s][cnt] = atof(word);
						
						if (linecnt < count+1)
							{
								printf("%30.2f|",number[s][cnt]);
							}							
						else
						{
							for (int i = 1; i <= s; ++i)
								{outnum += number[i][cnt];}
							outnum /= count;	
							printf("%24.2f(mean)|",outnum);
							outnum = 0;
							
							for (int i = 1; i <= s; i++)
        						{number[i-1][cnt] = number[i][cnt];}
						}
						rtext = strtok(NULL,symb);
					}
				}
				while (rtext != NULL)
				{
					printf("%30s|", rtext);
	                rtext = strtok(NULL,symb);
				}
	            printf("\n");
				++s;
	            estr = fgets(text, 1000, f1);								
			}    
	}	
}
