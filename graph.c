#include <stdlib.h>
#include <stdio.h>
#include "star.h"

//The frame buffer stored as a character grid
char fbr[MaxRow][MaxCol];	

//This function clears the frame buffer, i.e. fill all positions with the space character
void clearBuffer ()
{
    for(int i=0;i<MaxRow;i++)
	{
		for(int j=0;j<MaxCol;j++)
		{
			fbr[i][j]=' ';
		}
	}
}

//This function plots a character into the frame buffer, i.e. store the character in the frame buffer at location row, col.
void plot (int row, int col, char c)
{
    if(row<0 || col<0)
		return;
	if(row<MaxRow && col<MaxCol)
		fbr[row][col]=c;
}

//This function is used to peek at the frame buffer's location given by row and column indices
char peek (int row, int col)
{
    if(row<0 || col<0 || row>=MaxRow|| col>=MaxCol)
			return 0;
	else
		return fbr[row][col];

}

//This function writes a string into the frame buffer starting at location row, col.
//The string is written horizontally starting at location row,col
void writeAt (int row, int col, char str[])
{
	if(row>=0 && col>=0 && row<MaxRow && col<MaxCol)
	{
		int k=0,j=0;
		j=col;
		while(j<MaxCol && (int) strlen(str))
		{
			fbr[row][col]=str[k];
			col++;
			k++;
			j++;

		}

	}
}

//This function displays the whole frame buffer on the screen
void showBuffer ()
{
	for(int i=0;i<MaxRow;i++)
	{
		for(int j=0;j<MaxCol;j++)
		{
			printf("%c",fbr[i][j]);
		}
		printf("\n");
	}
}
