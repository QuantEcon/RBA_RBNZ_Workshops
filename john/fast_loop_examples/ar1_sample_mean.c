#include <stdio.h>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <time.h>
     

double ar1_ts (double * params, int n, gsl_rng * r)
{
    double beta = params[0];
    double alpha = params[1];
    double s = params[2];

    int i;
    double x = beta / (1 - alpha);  // Start at mean of stationary dist
    double sum = 0;
    for (i = 1; i <= n; i++) {
        sum += x;
        x = beta + alpha * x + gsl_ran_gaussian(r, s);
     }

    return sum / n;
}

int main(void)
{
    clock_t start, end;
    double cpu_time_used;

    int N = 1e7;
    double beta = 1.0;
    double alpha = 0.9;
    double s = 1;
    double params[3] = {beta, alpha, s};

    /* create a generator via GSL_RNG_TYPE */
    const gsl_rng_type * T;
    gsl_rng * r;
    gsl_rng_env_setup();
    T = gsl_rng_default;
    r = gsl_rng_alloc(T);
    gsl_rng_set(r, 1);  

    start = clock();
    double sample_mean = ar1_ts(params, N, r);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    gsl_rng_free (r);

    printf("mean = %g\n", sample_mean);
    printf("time elapsed = %g seconds\n", cpu_time_used);
    return 0;
}

