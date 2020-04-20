#include <omp.h>
#include <stdio.h>
#include <unistd.h>

int main(){
	int numt, tid; 

	#pragma omp parallel private( tid )
	{
		tid = omp_get_thread_num();

		#pragma omp single
		{
			sleep(2);
			numt = omp_get_num_threads();
			printf("This should executes once by %d!\n", omp_get_thread_num());
		} // only one thread executes whatever is inside and also provides synchronization across all thread by hitting this point as barrier

		printf("1: [%d %d %d]\n", omp_get_thread_num(), tid, numt);
	}

	int numt2;
	#pragma omp parallel private( tid )
	{
		tid = omp_get_thread_num();

		#pragma omp single nowait
		{
			sleep(2);
			numt2 = omp_get_num_threads();
			printf("This should executes once by %d!\n", omp_get_thread_num());
		} // no synchronization

		printf("2: [%d %d %d]\n", omp_get_thread_num(), tid, numt2);
	}

	int numt3;
	#pragma omp parallel private( tid )
	{
		tid = omp_get_thread_num();

		#pragma omp master
		{
			sleep(2);
			numt3 = omp_get_num_threads();
			printf("This should executes once by %d!\n", omp_get_thread_num());
		} // only executed by master
		#pragma omp barrier

		printf("3: [%d %d %d]\n", omp_get_thread_num(), tid, numt3);
	}

	return 0;
}