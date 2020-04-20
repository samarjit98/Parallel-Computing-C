#include <omp.h>
#include <stdio.h>

int main(){
	int flag1=0, flag2=0; // shared variables

	#pragma omp parallel
	{
		if( omp_get_thread_num()==0 )flag1 = 1;
		else flag2 = 1;

		if( omp_get_thread_num()==0 && flag2==0 )printf("Thread 1 wins!\n");
		else if( omp_get_thread_num()==1 && flag1==0 )printf("Thread 2 wins!\n");
	}
	return 0;
}