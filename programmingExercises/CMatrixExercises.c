#include <stdio.h>
#include <stdlib.h>

//Intel
//Implement matrix multiplication
int ** multiplyMatrix2DFormat(int m, int n, int p, int a[][n], int b[][p]){
	if(a == NULL || b == NULL){
		printf("Empty matrix \n");
		return;
	}
	int f,c,x;

	// Result matrix
	int **resultMatrix = (int**) malloc(m * sizeof(int *));
	for(f=0; f<m; f++){
		resultMatrix[f] = (int*) calloc(n, sizeof(int));
	}

	for(f=0; f<m; f++){
		for(c=0; c<p; c++){
			for(x=0; x<p; x++){
				resultMatrix[f][c] += a[f][x] * b[x][c];
			}
		}
	}

	return resultMatrix;
}

//Oracle
//Implement matrix multiplication, both matrix are provided as an array od one dimension
int * multiplyMatrixLinearFormat(int m, int n, int p, int *a, int *b){
	if(a == NULL || b == NULL){
		printf("Empty matrix \n");
		return;
	}
	int f,c,x;

	// Result matrix
	int *resultMatrix = (int*) calloc((m*n), sizeof(int ));

	for(f=0; f<m; f++){
		for(c=0; c<p; c++){
			for(x=0; x<n; x++){
				*(resultMatrix + f*p + c) += ((*(a + f*n + x)) * (*(b + x*p + c)));
			}
		}
	}
	return resultMatrix;
}

void multiplyMatrixLinearFormatPassingByReference(int m, int n, int p, int *a, int *b, int **result){
	if(a == NULL || b == NULL){
		printf("Empty matrix \n");
		return;
	}
	int f,c,x;

	// Result matrix
	int *resultMatrix = (int*) calloc((m*n), sizeof(int ));

	for(f=0; f<m; f++){
		for(c=0; c<p; c++){
			for(x=0; x<n; x++){
				*(resultMatrix + f*p + c) += ((*(a + f*n + x)) * (*(b + x*p + c)));
			}
		}
	}
	*result = resultMatrix;
}

//Intel
//Given a matrix, every time you find a 0 substitute all its column and row with 0’s 
void substituteCerosRowsColumns(int **matrix, int rows, int columns){
	if(matrix == NULL){
		return;
	}
	int *rowsArray = (int *)calloc(rows, sizeof(int));
	int *colsArray = (int *)calloc(columns, sizeof(int));
	int r,c;
	for(r=0; r<rows; r++){
		for(c=0; c<columns; c++){
			if(matrix[r][c] == 0){
				rowsArray[r] = 1;
				colsArray[c] = 1;
			}
		}
	}

	for(r=0; r<rows; r++){
		for(c=0; c<columns; c++){
			if( rowsArray[r] == 1 || colsArray[c] == 1){
				matrix[r][c] = 0;
			}
		}
	}
}

int main(){
	int f,c, m=2, n=2, o=2, p=3;
	int a[2][2];
	int b[2][3];

	a[0][0]=4;
	a[0][1]=3;
	a[1][0]=2;
	a[1][1]=1;

	b[0][0]=1;
	b[0][1]=2;
	b[0][2]=3;
	b[1][0]=4;
	b[1][1]=5;
	b[1][2]=6;

	int **result = multiplyMatrix2DFormat(m, n, p, a, b);
	for(f=0; f<m; f++){
		for(c=0; c<p; c++){
			printf("%d ", result[f][c]);
		}
		printf("\n");
	}

	int *aP = (int*) calloc((m*n), sizeof(int));
	int *bP = (int*) calloc((o*p), sizeof(int));
	
	aP[0]=4;
	aP[1]=3;
	aP[2]=2;
	aP[3]=1;

	bP[0]=1;
	bP[1]=2;
	bP[2]=3;
	bP[3]=4;
	bP[4]=5;
	bP[5]=6;

	int *secondResult = multiplyMatrixLinearFormat(m, n,p, aP, bP);
	for(f=0; f<(m*p); f++){
		printf("%d ",secondResult[f]);
	}
	printf("\n");

	int *passing;
	multiplyMatrixLinearFormatPassingByReference(m, n,p, aP, bP, &passing);
	for(f=0; f<(m*p); f++){
		printf("%d ",passing[f]);
	}
	printf("\n");	
	
	result[0][0] = 0;
	//result[1][2] = 0;
	printf("Print of matrix for 0's substitution\n");
	for(f=0; f<m; f++){
		for(c=0; c<p; c++){
			printf("%d ", result[f][c]);
		}
		printf("\n");
	}
	substituteCerosRowsColumns(result, m, p);
	printf("Matrix modfied with 0's substitution\n");
	for(f=0; f<m; f++){
		for(c=0; c<p; c++){
			printf("%d ", result[f][c]);
		}
		printf("\n");
	}

	return 0;
}
