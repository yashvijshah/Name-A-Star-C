#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "star.h"

//This function is used to print the details of a star
void printStar (Star* s)
{
    printf("star %i\n", s->id);
    if(s->named == 1)
    {
        printf("name: %s\n", s->name);
    }
    printf("coords: (%.3f,%.3f)\n",s->x,s->y);
}

//This function is used to display a list of all stars in the universe
void listStars ()
{
    int i;
	for(i=0;i<numStars;i++)
	{
		printStar(stars[i]);
	}
}

//Thsi function is used to list all named pairs
void listPairs ()
{
	for(int i = 0;i < numPairs; i++)
	{
		printf("Pair %i:\n",i);
		printf("distance: %f\n",pairs[i]->d);
		printStar(pairs[i]->h);
		printStar(pairs[i]->w);
		printf("*************************\n");
	}
}

//This function is used to draw the entire universe
void drawUniverse ()
{
    int i;
	char ch;

	for(i=0;i<numStars;i++)
	{
		if(stars[i]->named==1)
        {
			ch='*';
        }
		else
        {
			ch='.';
        }
		plot(stars[i]->y,stars[i]->x,ch);

	}
}

//This function is used to tag a named pair of stars by writing a string comprising the names of the couple that own the pair
//Calling this function will NOT cause the frame buffer to be redisplayed on the screen, if you need to show the frame buffer, you must call showBuffer
void tagPair (Pair* p)
{
    int pos,x;
	char *str=(char*)malloc(strlen(p->h->name)+strlen(p->w->name)+4);
	strcpy(str,p->h->name);
	strcat(str," & ");
	strcat(str,p->w->name);
	pos=strlen(str)/2;
	if((p->h->x)-pos>=0)
    {
		x=p->h->x-pos;
    }
	else
    {
		x=p->h->x;
    }
	writeAt(p->h->y+1,x,str);
}


int  main (int argc, char* argv[])
{
  char cmd[100];
	int nStar,i;
	Pair *p;
	char hfname[30],hsurname[30],fullname[30];
	char wfname[30],wsurname[30];
	char ch,temp;
	while(1)
	{
		printf(">>>");
		scanf("%s",cmd);
		if(strcmp(cmd,"bang")==0)
			scanf("%d",&nStar);
		if(strcmp(cmd,"bang")==0)
		{
			if(bigBang(nStar))
			{
				printf("The Big Bang has occurred!\n");
			}
			else
			{
				printf("Sorry, unable to bang!\n");
			}
		}
		else if(strcmp(cmd,"list")==0)
		{
			listStars();
		}
		else if(strcmp(cmd,"draw")==0)
		{
			clearBuffer();
			drawUniverse();
			showBuffer();
		}
		else if(strcmp(cmd,"name")==0)
		{
			p=closestPair();
			if(p)
			{
				printf("The closest pair of stars are no. %i and %i\n",p->h->id,p->w->id);
				printf("They are %.3f light years apart\n",p->d);
				printf("Would you like to name this pair (y/n)?");
				scanf(" %c",&ch);
				if(ch=='y')
				{
					printf("Enter your full name:");
					scanf("%s%s",hfname,hsurname);
					printf("Enter your spouse full name:");
					scanf("%s%s",wfname,wsurname);
					nameStar(p->h,hfname,hsurname);
					nameStar(p->w,wfname,wsurname);
					pairs[numPairs]=p;
					numPairs++;
					printf("Congratulations a pair of stars has been named after you and your spouse\n");
				}
			}
			else
				printf("Sorry no pairs were found!\nWish you a better luck in the next universe\n");
		}
		else if(strcmp(cmd,"pairs")==0)
		{
			listPairs();
		}
		else if(strcmp(cmd,"show")==0)
		{
			printf("Enter your full name:");
			scanf("%c",&temp);
			scanf("%[^\n]",fullname);
			p=findPairByName(fullname);
			if(p)
			{
				clearBuffer();
				drawUniverse();
				tagPair(p);
			}
			showBuffer();
		}
		else if(strcmp(cmd,"save")==0)
		{

			if(saveUniverse())
				printf("Thanks, you have saved the universe!\n");
		}
		else if(strcmp(cmd,"load")==0)
		{
			if(loadUniverse())
				printf("Congratulations, your saved universe was restored!\n");
		}
		else if(strcmp(cmd,"quit")==0)
		{
			break;
		}
		else
		{
			printf("This command has not been implemented.\n");

		}
		continue;
	}
	return 0;
}
