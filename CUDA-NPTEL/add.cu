#include "stdio.h"

__global__ void add(int *a, int *b, int *c, int *N){
	 int tID = blockIdx.x;
	 if (tID < *N){
	 	c[tID] = a[tID] + b[tID];
	 }
}

int main(int argc, char* argv[]){

	int N = atoi(argv[1]);
	int *a, *b, *c, *n;
	int *dev_a, *dev_b, *dev_c, *dev_n;

	 a = (int*)malloc(N*sizeof(int));
	 b = (int*)malloc(N*sizeof(int));
	 c = (int*)malloc(N*sizeof(int));
	 n = (int*)malloc(sizeof(int));

	 cudaMalloc((void **) &dev_a, N*sizeof(int));
	 cudaMalloc((void **) &dev_b, N*sizeof(int));
	 cudaMalloc((void **) &dev_c, N*sizeof(int));
	 cudaMalloc((void **) &dev_n, sizeof(int));
	 // Fill Arrays
	 for (int i = 0; i < N; i++)
	 {
		 a[i] = rand()%10000;
		 b[i] = rand()%10000;
	 }
	 *n = N;

	 cudaMemcpy(dev_a, a, N*sizeof(int), cudaMemcpyHostToDevice);
	 cudaMemcpy(dev_b, b, N*sizeof(int), cudaMemcpyHostToDevice);
	 cudaMemcpy(dev_n, n, sizeof(int), cudaMemcpyHostToDevice);

	 add<<<N,1>>>(dev_a, dev_b, dev_c, dev_n);

	 cudaMemcpy(c, dev_c, N*sizeof(int), cudaMemcpyDeviceToHost);

	 for (int i = 0; i < N; i++){
	 	printf("%d + %d = %d\n", a[i], b[i], c[i]);
	 }

	 return 0;
}