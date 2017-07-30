/*

This program will numerically compute the integral of

                  4/(1+x*x) 
				  
from 0 to 1.  The value of this integral is pi -- which 
is great since it gives us an easy way to check the answer.

The is the original sequential program.  It uses the timer
from the OpenMP runtime library

History: Written by Tim Mattson, 11/99.

*/
#include <stdio.h>
#include <omp.h>
#define NUM_THREADS 4
#define PADDING 8
static long num_steps = 100000000;
double step;
int main ()
{

	  double  pi = 0;
	  double start_time, run_time;
	  step = 1.0/(double) num_steps;

        	 
	  start_time = omp_get_wtime();
      int block_len = num_steps/NUM_THREADS;
      double sum[NUM_THREADS][PADDING];
      #pragma omp parallel num_threads(NUM_THREADS)
      {
          
          int i;
          int ID = omp_get_thread_num();
          sum[ID][0] = 0.0;
          int start = ID * block_len;
          int end = start + block_len;
          double x;
          
		  for (i = start + 1; i <= end; i++){
			  x = (i-0.5)*step;
			  sum[ID][0] = sum[ID][0] + 4.0/(1.0+x*x);
		  }
		  
      }
      int j;
      for(j = 0; j < NUM_THREADS; j++)
          pi += step * sum[j][0];
	  //pi = step * sum;
	  run_time = omp_get_wtime() - start_time;
	  printf("\n pi with %ld steps is %lf in %lf seconds\n ",num_steps,pi,run_time);
}	  





