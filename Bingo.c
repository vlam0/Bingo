/********DO NOT MODIFY THIS SECTION************
 * 
 * EECS 22 : Advanced C Programming
 * Winter 2020, Prof. Quoc-Viet Dang
 * 
 * HW1  : Bingo Simulator
 * Template file : Bingo.c
 * 
 * Created on Jan 5, 2020, 10:56 PM by Bo Tsai <bo.tsai@uci.edu>
 */
/**********************************************
 
// Enter your name, last name and UCInet ID below://
 * 
 * *****************************
 * First Name: Vivian 
 * Last Name: Lam
 * UCInet ID: vlam8
 *
 */

#include <stdio.h>

/*Declare your function definitions in the section below*/
/*You may add other functions if needed*/
/*********************************************************/
int checkrow(int p, int m, int pmatrix[p][m][m],int matrix[m*m],int round);
int checkcolumn(int p, int m, int pmatrix[p][m][m],int matrix[m*m],int round);
int checkdiagonal(int n, int m, int pmatrix[n][m][m],int matrix[],int round,int p);
/*********************************************************/

/*Declare your global variables below (if any)*/
/**************************************************/



/**************************************************/

/*Colors (you can add or remove from this list*/
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#include <stdio.h>
#include <string.h>



int main(int argc, char** argv)
{
        FILE *fp;
        int n, m, row, column;
        int bingoNumbers, numberOfPeople;


        fp = fopen("BingoSampleInput1.txt", "r");

        if (fp == NULL)
        {
                fprintf(stderr, "Can't open input file!\n");

        }

        if (fp != NULL)
        {
                fscanf(fp,"%d %d",&n,&m);

                char names[n][100];
                int matrix[n][m][m];

                printf("\nStart the game\n");

                for (numberOfPeople=0; numberOfPeople<n; numberOfPeople++)
                {

                        fscanf(fp,"%s",names[numberOfPeople]);

                        printf("*** %s ***\n",names[numberOfPeople]);

                        for (row=0; row<m; row++)
                        {
                                for (column=0; column<m; column++)
                                {
                                        fscanf(fp,"%d",&bingoNumbers);
                                        matrix[numberOfPeople][row][column] = bingoNumbers;
                                        printf("%d ",matrix[numberOfPeople][row][column]);

                                }
                                printf("\n");
                        }
                }

                printf("\n");

                int valueCalled[m*m];
                int p, i=0;

                while ((fscanf(fp,"%d",&valueCalled[i])==1)&&(i<m*m))
                {
                        i++;
                }

                int round=0;
                int atleast=0;
                int winner[n];
                int x, j, repeat;

                for (x=0; x<n; x++)
                {
                    winner[x]=0;
                }


                for (round=0; round<m*m; round++)
                {
                    for (p=0; p<n; p++)
                    {
                        if (checkrow(p, m, matrix, valueCalled, round)||
                            checkcolumn(p, m, matrix, valueCalled, round)||
                            checkdiagonal(n, m, matrix, valueCalled, round, p))
                        {
                            printf("*** %s Bingo! ***\n", names[p]);
                            winner[p]++;

                            atleast++;
                            for (int r=0; r<m; r++)
                            {
                                for (int c=0; c<m; c++)
                                {
 				    repeat = 1;

				    if (valueCalled[round] == matrix[p][r][c])
                                    	printf(KGRN "%d " KNRM, matrix[p][r][c]);

				    else
				    {   
					for (j=0; j<round; j++)
					{
						if (valueCalled[j] == matrix[p][r][c])
                                                {
                                                        if (repeat == 1)
                                                        {
                                                                printf(KRED "%d " KNRM, matrix[p][r][c]);
                                                                repeat++;
                                                        }

                                                }
                                        }
                                        if (repeat == 1)
                                        {
                                                printf("%d ", matrix[p][r][c]);
                                                repeat++;
                                        }

				    }

                                }
                                printf("\n");

                            }
                        }

                        else
                        {
                            printf("*** %s ***\n", names[p]);

                            for(int r=0; r<m; r++)
                            {
                                for(int c=0; c<m; c++)
                                {
				    repeat = 1;				    

				    if (valueCalled[round] == matrix[p][r][c])
                                        printf(KGRN "%d " KNRM, matrix[p][r][c]);

                                    else
                                    {
					for (j=0; j<round; j++)
					{
                                        	if (valueCalled[j] == matrix[p][r][c])
						{
                                                	if (repeat == 1)
							{
								printf(KRED "%d " KNRM, matrix[p][r][c]);
								repeat++;
							}
							
						}
					}
					if (repeat == 1)
					{	
                                       		printf("%d ", matrix[p][r][c]);
						repeat++;	
					}

                                    }
                                }
                                printf("\n");
                            }
                        }

                        if ((p==n-1) && (atleast>=1))
                        {
                            printf("The game result:\n");
                            for (i=0; i<n; i++)
                            {
                                if (winner[i]==1)
                                    printf("%s ", names[i]);


                            }
			    printf("\n");
                            return 0;

                        }

                    }


                    printf ("\n");
                }

    }
        fclose(fp);

    return 0;
}

int checkrow(int p, int m, int pmatrix[p][m][m],int matrix[m*m],int round)
{
    int win=0;
    int r, c, i;

    for(r=0;r<m;r++)
    {
        for(c=0;c<m;c++)
        {
            for(i=0; i<=round;i++)
            {
                if(pmatrix[p][r][c]==matrix[i])
                {
                    win++;
                    if(win==3)
                    {
                        return 1;
                    }
                }
            }
        }
        win=0;
    }
    return 0;
}

int checkcolumn(int p, int m, int pmatrix[p][m][m],int matrix[m*m],int round)
{
    int win=0;
    int c, r, i;

    for(c=0;c<m;c++)
    {
        for(r=0;r<m;r++)
        {
            for(i=0; i<=round;i++)
            {
                if(pmatrix[p][r][c]==matrix[i])
                {
                    win++;
                    if(win==3)
                    {
                        return 1;
                    }
                }
            }
        }
        win=0;
    }
    return 0;
}

int checkdiagonal(int n, int m, int pmatrix[n][m][m],int matrix[],int round,int p)
{
    int win=0;
    for(int d =0;d<m;d++)
    {
        for(int i=0;i<=round;i++)
        {
            if(pmatrix[p][d][d]==matrix[i])
            {
                win++;
                if(win==3)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}
