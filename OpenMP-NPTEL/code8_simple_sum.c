#include <omp.h>
#include <stdio.h>
#include <string.h>
#define ARR_SIZE 1000000

typedef long long ll;

int main(){
	ll i, tid, numt, sum=0, psum;
	double t1, t2;

	ll arr[ARR_SIZE];
	for(i=0; i<ARR_SIZE; i++)
		arr[i] = 1;

	t1 = omp_get_wtime();

	for(i=0; i<ARR_SIZE; i++)
		sum += arr[i];

	t2 = omp_get_wtime();

	printf("Sequential Sum: %lld Time: %g\n", sum, t2-t1);

	sum = 0;
	t1 = omp_get_wtime();
	#pragma omp parallel private( i, tid, numt, psum )
	{
		ll lower, upper;
		psum = 0;
		tid = omp_get_thread_num();
		numt = omp_get_num_threads();
		lower = ( ARR_SIZE/numt )*tid;
		upper = ( ARR_SIZE/numt )*( tid+1 ) - 1;
		if( tid==numt-1 )
			upper = ARR_SIZE-1;

		for(i=lower; i<=upper; i++)
			psum += arr[i];

		#pragma omp critical
			sum += psum;
	}
	t2 = omp_get_wtime();

	printf("Parallel Sum: %lld Time: %g\n", sum, t2-t1);

	sum = 0;
	t1 = omp_get_wtime();
	#pragma omp parallel private( i, psum ) // no need to set i to be private, omp sets loop counter as private for "for" loops
	{	
		psum = 0;

		#pragma omp for
		for(i=0; i<ARR_SIZE; i++)
			psum += arr[i];

		#pragma omp critical
			sum += psum;
	}
	t2 = omp_get_wtime();

	printf("Parallel For Sum: %lld Time: %g\n", sum, t2-t1);

	sum = 0;
	t1 = omp_get_wtime();
	#pragma omp parallel reduction( +: sum )
	{	
		#pragma omp for
		for(i=0; i<ARR_SIZE; i++)
			sum += arr[i];
	}
	t2 = omp_get_wtime();

	printf("Parallel Reduction 1 For Sum: %lld Time: %g\n", sum, t2-t1);

	sum = 0;
	t1 = omp_get_wtime();
	#pragma omp parallel 
	{	
		#pragma omp for reduction( +: sum )
		for(i=0; i<ARR_SIZE; i++)
			sum += arr[i];
	}
	t2 = omp_get_wtime();

	printf("Parallel Reduction 2 For Sum: %lld Time: %g\n", sum, t2-t1);

	sum = 0;
	t1 = omp_get_wtime();

	#pragma omp parallel for reduction( +: sum )
		for(i=0; i<ARR_SIZE; i++)
			sum += arr[i];

	t2 = omp_get_wtime();

	printf("Parallel Final For Sum: %lld Time: %g\n", sum, t2-t1);

	return 0;
}