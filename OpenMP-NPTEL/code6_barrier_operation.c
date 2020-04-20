#include <omp.h>
#include <stdio.h>
#include <unistd.h>

int main(){
	int numt, tid; 

	#pragma omp parallel private( tid )
	{
		tid = omp_get_thread_num();

		if( tid==0 ){
			sleep(2);
			numt = omp_get_num_threads();
		}

		#pragma omp barrier  // all threads must hit this barrier before going forward

		printf("[%d %d %d]\n", omp_get_thread_num(), tid, numt);
	}

	return 0;
}