#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define N 100
#define max_iter 1000000000
#define Tol 1e-5

int main(int argc, char *argv[])
{
    double A[N][N], b[N], x[N], x_new[N];
    double error;

    //initializing
    for(int i=0; i< N; i++){
        b[i] = i;
        x[i] = 0.0;
        for(int j=0; j<N; j++){
            if (i == j){
                A[i][j] = (double)N + 1; //A[i][i] > summation of all A[i][j]
            }
            else{
                A[i][j] = 1.0;
            }
             
        }
    }
    
    for(long k=0; k<max_iter; k++){

        error = 0;

        #pragma omp parallel for reduction(+:error)
        for(int i=0; i<N; i++){
            double sum = 0.0;
            for (int j=0; j<N; j++){
                if (i!=j)
                    sum += A[i][j]*x[j];
                
            }
        
            x_new[i] = (b[i] - sum)/A[i][i];
            error += fabs(x_new[i] - x[i]);
        }
        
        //updating x
        for(int i=0; i<N; i++){
            x[i] = x_new[i];
        }
        if(error < Tol) {
            printf("Converged at iter %ld\n", k);
            break;

        }
    }
    printf("Soln sample: x[0] = %f\n", x[0]);
    return 0;

}
