#include <omp.h>
#include <stdio.h>
#include <unistd.h>

int main(){
	int numt1, tid1; // see example code2

	#pragma omp parallel private( tid1 ) shared( numt1 ) // default is shared behaviour
	{
		int numt2, tid2; // local to thread

		numt1 = omp_get_num_threads();
		tid1 = omp_get_thread_num(); // this operation is atomic since now tid1 is private local

		sleep(2);

		printf("[Shared: %d %d %d]\n", omp_get_thread_num(), tid1, numt1);

		numt2 = omp_get_num_threads();
		tid2 = omp_get_thread_num(); // done on local copy

		printf("[Local: %d %d %d]\n", omp_get_thread_num(), tid2, numt2);
	}
	return 0;
}