#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include "star.h"

//a counter to create unique star numbers (identifiers)
int SerNum=0;
//the actual number of stars in the universe
int numStars = 0;
//the number of named pairs
int numPairs = 0;

Star *stars[MaxStar];		
Pair *pairs[MaxPair];	


//This function is used to find a star through its coordinates.
//The first two parameters are the coordinates of the star we are looking for.
//The 3rd parameter to this function is a very small number (e.g. 0.00000001) called the tolerance.
Star* findStarByXY  (double x , double y, double tolerance)
{
	int i, flag = 0;
	double dx, dy;
	for(i = 0; i < numStars; i++)
	{
		dx = fabs(x - stars[i]->x);
		dy = fabs(y - stars[i]->y);
		if((dx < tolerance) && (dy < tolerance))
		{
			flag = 1;
			break;
		}
	}
	if(flag == 1)
	{
		return stars[i];
	}
	else
	{
		return 0;
	}
}

//This function is used to create a new universe containing stars only.
//The number of stars in this new universe is given by the parameter n_stars.
//The stars should be randomly scattered within the universe i.e each star should be assigned a random value for its x and y coordinates
//The maximum number of stars in a completely filled universe that is 60 lights years long and 30 light years wide
//The minimum number of stars in a universe is 1.
int bigBang (int n_stars)
{
	if (n_stars < 1 || n_stars > MaxStar)
	{
		return 0;
	}
	numStars = n_stars;
	numPairs = 0;
	int index[n_stars], x, y, id;
	int count;
	for (SerNum = 0; SerNum < n_stars; SerNum++)
	{
		count = 0;
		while(count == 0)
		{
			x = rand() % MaxX;
			y = rand() % MaxY;
			count = 1;
			for (int i = 0; i < SerNum; i++)
			{
				if(stars[i]->x == x && stars[i]->y == y)
				{
					count = 0;
				}
			}
		}
		
		Star *elem = (Star *) malloc(sizeof(Star));
		elem->id = SerNum;
		elem->x = x;
		elem->y = y;
		strcpy(elem->name,"");
		elem->named = 0;
		stars[SerNum] = elem;
	}
	return 1;
}


//This function is used to compute the distance between two points in a Cartesian plane.
//The coordinates of the first point are considered to be x1 & y1.
//The coordinates of the second point are considered to be x2 & y2.
//The function returns the distance between the two points.
double pointDistance (double x1, double y1, double x2, double y2)
{
    return sqrt(((x2 - x1) * (x2 - x1)) + ((y2-y1) * (y2-y1)));
}


//This function is used to find the closest pair of stars that have not been named yet.
Pair* closestPair ()
{
	int i, j, hindex, windex;
	double d;
	Pair *p = (Pair*)malloc(sizeof(Pair));
	p->d = 2147483647;
	if(numStars < 2)
	{
		return 0;
	}
	for(i = 0; i < numStars; i++)
	{
		for(j = i+1; j < numStars; j++)
		{
			if((stars[i]->named == 0) && (stars[j]->named == 0))
			{
				d = pointDistance(stars[i]->x, stars[i]->y, stars[j]->x, stars[j]->y);
				if(d < p->d)
				{
					p->d = d;
					hindex = i;
					windex = j;
				}
			}
		}
	}
	p->h = stars[hindex];
	p->w = stars[windex];
	return p;
}

//This function is used to assign the name of a person to a star.
//The first parameter is a pointer to the star to be named.
//The second parameter is the first name of the person.
//The third parameter is the surname of the person.
int nameStar (Star *s, char* first_name, char* sur_name)
{
	int l1, l2, l3;
	if(s && first_name && sur_name)
	{
		l3 = strlen(first_name) + strlen(sur_name) + 1;
		if(l3 >= 30)
		{
			return 0;
		}
		s->named = 1;
		strcpy(s->name, first_name);
		strcat(s->name, " ");
		strcat(s->name, sur_name);
		return 1;
	}
	else
	{
		return 0;
	}
}


//This function is used to find a pair by the name of either spouse i.e. one of the owners of the pair
//The parameter to this function is the full name of a person.
Pair* findPairByName (char* name)
{
	int i, flag=0;
	if(name)
	{
		for(i = 0; i < numPairs; i++)
		{
			if((strcmp(pairs[i]->h->name, name) == 0) || (strcmp(pairs[i]->w->name, name) == 0))
			{
				flag = 1;
				break;
			}
		}
		if(flag == 1)
		{
			return pairs[i];
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}

//This function is used to save all the data of the program to a binary file called "universe.bin".
int saveUniverse ()
{
	FILE *p;
	p = fopen("universe.bin", "wb");
	if(p == NULL)
	{
		return 0;
	}
	fwrite(&numStars, sizeof(int), 1, p);
	fwrite(&numPairs, sizeof(int), 1, p);
	fwrite(&stars, sizeof(stars), 1, p);
	fwrite(&pairs, sizeof(pairs), 1, p);
	fclose(p);
	return 1;
}



//This function is used to load a universe from a binary file called "universe.bin".
int loadUniverse ()
{
	FILE *p;
	p = fopen("universe.bin", "rb");
	if(p == NULL)
	{
		return 0;
	}
	fread(&numStars, sizeof(int), 1, p);
	fread(&numPairs, sizeof(int), 1, p);
	fread(&stars, sizeof(stars), 1, p);
	fread(&pairs, sizeof(stars), 1, p);
	fclose(p);
	return 1;
}
