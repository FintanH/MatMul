#include <stdlib.h>
#include <stdio.h>
#include <time.h>
 
void matmulA(double **a, double **b, double **c, int a_row, int common, int b_col)
{
    for (int i = 0; i < a_row; i++)
    {
        for (int j = 0; j < common; j++)
        {
            double sum = 0;
            for (int k = 0; k < b_col; k++)
            {
                sum += a[i][k] * b[k][j];
            }
            c[i][j] = sum;
        }
    }
}
 
void matmulB(double **a, double **b, double **c, int a_row, int common, int b_col)
{
    for (int i = 0; i != a_row; ++i)
    {
        for (int j = 0; j != common; ++j)
        {
            double sum = 0;
            for (int k = 0; k < b_col; k++)
            {
                sum += a[i][k] * b[k][j];
            }
            c[i][j] = sum;
        }
    }
}
 
int main(int argsc, char** argv)
{
    int a_row = 20;
    int common = 40;
    int b_col = 40;

    double ** a = malloc(sizeof(double*)*a_row);
    for(int i = 0; i < a_row; i++)
    {
        a[i] = malloc(sizeof(double)*common);
    }

    double ** b = malloc(sizeof(double*)*common);
    for(int i = 0; i < common; i++)
    {
        b[i] = malloc(sizeof(double)*b_col);
    }

    double ** c = malloc(sizeof(double*)*a_row);
    for(int i = 0; i < a_row; i++)
    {
        c[i] = malloc(sizeof(double)*b_col);
    }
        

    clock_t start = clock();
    for(int i = 0; i < 100; i++)
        if(argv[1][0] == 'A')
            matmulA(a,b,c,a_row,common,b_col);
        else
            matmulB(a,b,c,a_row,common,b_col);

    printf("Time for consumer %lu\n", clock()-start);


    
}

