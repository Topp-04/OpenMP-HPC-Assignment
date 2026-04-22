#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define N 100000
#define max_iter 1000
#define lr 1e-6

int main()
{
    double x[N], y[N];
    double a=0.0, b=0.0;

    //generating data for actual model y=3x+1+noise
    for (int i=0; i<N; i++){
        x[i] = (double)i / N;
        y[i] = 3*x[i] + 1 + ((double)rand()/ RAND_MAX - 0.5);
    }

    for(int iter=0; iter < max_iter; iter++){
        double grad_a = 0.0;
        double grad_b = 0.0;

        #pragma omp parallel for reduction(+:grad_a, grad_b)
        for (int i=0; i<N; i++){
            double pred = a*x[i] + b;
            double residual = y[i] - pred;

            grad_a+= -2.0*x[i]*residual;
            grad_b+= -2.0*residual;
        }

        //updating the parameters
        a -= lr*grad_a;
        b -= lr*grad_b;

        if (iter % 100 == 0){
            printf("Iter %d: a = %f, b = %f\n", iter, a, b);
        }

    }
     printf("Final: a = %f, b = %f\n", a, b);
     return 0;

}