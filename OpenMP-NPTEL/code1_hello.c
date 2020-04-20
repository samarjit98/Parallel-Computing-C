#include <omp.h>
#include <stdio.h>

int main(int argc, char* argv[]){
	
	#pragma omp parallel
	{
		if(omp_get_num_threads() - 1 == omp_get_thread_num())
			printf("Num threads: %d\n", omp_get_num_threads());
		else
			printf("Hello from %d\n", omp_get_thread_num());
	}
	return 0;
}