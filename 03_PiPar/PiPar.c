#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[])
{
    const size_t N = 100000000;
    double step;

    double pi, sum = 0.;

    step = 1. / (double)N;

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < N; ++i)
    {
        double x = (i + 0.5) * step;
        sum += 4.0 / (1. + x * x);
    }

    pi = step * sum;

    printf("pi = %.16f\n", pi);

    return 0;
}