#include <stdlib.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_blas.h>
#include <stdio.h>
#include <time.h>
 
void matmulA(double **a, double **b, double **c, int a_row, int common, int b_col)
{
    for (int i = 0; i < a_row; i++)
    {
        for (int j = 0; j < b_col; j++)
        {
            double sum = 0;
            for (int k = 0; k < common; k++)
            {
                sum += a[i][k] * b[k][j];
            }
            c[i][j] = sum;
        }
    }
}
 
void matmulB(double ** a, double ** b, double ** c, int a_row, int common, int b_col)
{
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
            for (int k = common-1; k >=0; k--)
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
    int a_row = 200;
    int common = 400;
    int b_col = 300;

    gsl_matrix * a = gsl_matrix_alloc(a_row,common);
    double ** dA = g_to_d(a);

    gsl_matrix * b = gsl_matrix_alloc(common,b_col);
    double ** dB = g_to_d(b);

    gsl_matrix * c = gsl_matrix_alloc(a_row,b_col);        
    double ** dC = g_to_d(c);

    clock_t start = clock();
    for(int i = 0; i < 100; i++)
        if(argv[1][0] == 'A')
            matmulA(dA,dB,dC,a_row,common,b_col);
        else if(argv[1][0] == 'B')
            matmulB(dA,dB,dC,a_row,common,b_col);
        else if(argv[1][0] == 'C')
            gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, a, b, 0.0, c);

    printf("Time for consumer %lu\n", clock()-start);

}

