#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv)
{
	if(argc != 4){
		fprintf(stderr,
			"Wrong number of command-line arguments\n");
		fprintf(stderr,
			"Usage: transpif matrix_height matrix_width block_width\n");
		return -1;
	}

	struct timeval tv_start, tv_end;
	float *matrix; // The original matrix
	float *tmatrix; // The transposed matrix
	int N = atoi(argv[1]); // N is the height of the matrix
	int M = atoi(argv[2]); // M is the width of the matrix
	int blockWidth = atoi(argv[3]);

	/* Allocate memory for the matrices */
	matrix = (float*)malloc(N*M*sizeof(float));
	tmatrix = (float*)malloc(N*M*sizeof(float));

	/* Seed with the current time */
	srand(time(NULL));

	/* Randomly initialize the input matrix */
	for(int i=0; i<(N*M); i++)
		matrix[i] = (((float)rand())/RAND_MAX)*200; // Range: [0-200]

	int tempHeight = blockWidth; // temp variable to store block width
	int tempWidth = blockWidth; // temp variable to store block height

	gettimeofday(&tv_start, NULL); // Record start time

	/* Perform transposition */
	for(int i=0; i<M; i+=tempHeight){
		if((tempHeight + i) > M)
			tempHeight = (M - i);
		for(int j=0; j<N; j+=tempWidth){
			if((tempWidth + j) > N)
				tempWidth = (N - j);
			for(int k=i; k<tempHeight + i; k++){
				for(int l=j; l<tempWidth + j; l++){
					tmatrix[l+(k*N)] = matrix[k+(l*M)];
				}
			}
			tempWidth = blockWidth; // Reset tempWidth
		}
		tempHeight = blockWidth; // Reset tempWidth
	}

	gettimeofday(&tv_end, NULL); // Record end time

	/* Compute elapsed time in milliseconds */
	double elapsed = (tv_end.tv_sec - tv_start.tv_sec) * 1000.0;
	elapsed += (tv_end.tv_usec - tv_start.tv_usec) / 1000.0;

	/* Print elapsed time */
	printf("\nTRANSFORMATION COMPLETE\n");
	printf("Elapsed time (milliseconds): %.3f\n\n", elapsed);

	/* Deallocate allocated memory */
	free(matrix);
	free(tmatrix);

}