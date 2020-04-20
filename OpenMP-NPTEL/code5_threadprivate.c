#include <omp.h>
#include <stdio.h>
#include <unistd.h>

int tid;
#pragma omp threadprivate( tid )  // persistent across all threads of same id
// threadprivate can be declared only to file scope vars, not on variables on the stack (eg. within functions)

int main(){
	int numt; 

	#pragma omp parallel 
	{
		tid = omp_get_thread_num();

		if( tid==0 ){
			sleep(2);
			numt = omp_get_num_threads();
		}
	}
	// The above is a barrier operation, implicit barrier leveraging fork-join
	#pragma omp parallel  // using #pragma as a point of synchronization explicitly, using the nature of the fork-join model
		printf("[%d %d %d]\n", omp_get_thread_num(), tid, numt);

	printf("Main Thread: [%d %d %d]\n", omp_get_thread_num(), tid, numt);

	return 0;
}