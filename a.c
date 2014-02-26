#include <stdlib.h>
#include <stdio.h>
 
void matmulA(double **a, double **b, double **c, int a_row, int common, int b_col)
{
    #pragma omp parallel for
    for (int i = 0; i < a_row; i++)
    {
        for (int j = 0; j < b_col; j+=2)
        {
            double sum = 0;
            for (int k = 0; k < common; k++)
            {
                sum += a[i][k] * b[k][j];
            }
            c[i][j] = sum;
            sum = 0; 
            for (int k = common-1; k >= 0; k--)
            {
                sum += a[i][k] * b[k][j+1];
            }
            c[i][j+1] = sum;
        }
    }
}
 
void matmulB(double ** a, double ** b, double ** c, int a_row, int common, int b_col)
{
    #pragma omp parallel for
    for (int i = 0; i < a_row; i++)
    {
        for (int j = 0; j < b_col; j+=2)
        {
            double sum = 0;
            for (int k = 0; k < common; k++)
            {
                sum += a[i][k] * b[k][j];
            }
            c[i][j] = sum;
            sum = 0; 
            for (int k = common-1; k >= 0; k--)
            {
                sum += a[i][k] * b[k][j+1];
            }
            c[i][j+1] = sum;
        }
    }
}

double ** g_to_d(gsl_matrix* matrix)
{
    double ** retval = malloc(sizeof(double*)*matrix->size1);
    for(int i = 0; i < matrix->size1; i++)
    {
        retval[i] = (double*)&matrix->data[i*matrix->tda];
    }
    return retval;
}
 
int main(int argsc, char** argv)
{
    int a_row = 2000;
    int common = 400;
    int b_col = 300;
    
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

    for(int i = 0; i < 100; i++)
        if(argv[1][0] == 'A')
            matmulA(a,b,c,a_row,common,b_col);
        else
            matmulB(a,b,c,a_row,common,b_col);
}

