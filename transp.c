#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv)
{
	if(argc != 3){
		fprintf(stderr,
			"Wrong number of command-line arguments\n");
		fprintf(stderr,
			"Usage: transp matrix_width block_width\n");
		return -1;
	}

	struct timeval tv_start, tv_end;

	float *matrix; // The original matrix
	float *tmatrix; // The transposed matrix
	int N = atoi(argv[1]); // N is the width of the matrix
	int blockWidth = atoi(argv[2]);

	/* Allocate memory for the matrices */
	matrix = (float*)malloc(N*N*sizeof(float));
	tmatrix = (float*)malloc(N*N*sizeof(float));

	/* Seed with the current time */
	srand(time(NULL));

	/* Randomly initialize the input matrix */
	for(int i=0; i<(N*N); i++)
		matrix[i] = (((float)rand())/RAND_MAX)*200; // Range: [0-200]

	gettimeofday(&tv_start, NULL); // Record start time

	/* Perform transposition */
	for(int i=0; i<N; i+=blockWidth){
		for(int j=0; j<N; j+=blockWidth){
			for(int k=i; k<(i+blockWidth); ++k){
				for(int l=j; l<(j+blockWidth); ++l){
					tmatrix[k+(l*N)] = matrix[l+(k*N)];
				}
			}
		}
	}

	gettimeofday(&tv_end, NULL); // Record end time

	/* Compute elapsed time in milliseconds */
	double elapsed = (tv_end.tv_sec - tv_start.tv_sec) * 1000.0;
	elapsed += (tv_end.tv_usec - tv_start.tv_usec) / 1000.0;

	/* Print elapsed time */
	printf("TRANSFORMATION COMPLETE\n");
	printf("Elapsed time (milliseconds): %.3f\n\n", elapsed);

	/* Verify resulting matrix */
	int correct_transposed = 1;
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			if(tmatrix[j+i*N] != matrix[i+j*N])
				correct_transposed = 0;
		}
	}
	if(!correct_transposed)
		printf("\nNOT CORRECTLY TRANSPOSED!\n");
	else
		printf("\nCORRECTLY TRANSPOSED\n");

	/* Deallocate allocated memory */
	free(matrix);
	free(tmatrix);

}