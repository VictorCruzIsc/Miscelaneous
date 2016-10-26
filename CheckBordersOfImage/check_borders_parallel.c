/*
* Nelson Victor Cruz Hernandez
* MS70513
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <pthread.h>
#include <pthread.h>

#define DIF 16
#define NUM_THREADS 4

// File to process
char filename[] = "imagen.bmp";

#pragma pack(2) // Pack of two byte
typedef struct{
	unsigned char magic1;
	unsigned char magic2;
	unsigned int size;
	unsigned short int reserved1, reserved2;
	unsigned int pixelOffset;
} HEADER;

#pragma pack() // Defaul pack
typedef struct{
	unsigned int size;
	int cols, rows;
	unsigned short int planes;
	unsigned short int bitsPerPixel;
	unsigned int compression;
	unsigned int cmpSize;
	int xScale, yScale;
	unsigned int numColors;
	unsigned int importantColors;
} INFOHEADER;

typedef struct{
	unsigned char red;
	unsigned char green;
	unsigned char blue;
} PIXEL;

typedef struct{
	HEADER header;
	INFOHEADER infoheader;
	PIXEL *pixel; // Pointer to a memory direction where a Pixel struct is located
} IMAGE;

typedef struct{
	int startProcessing;
	int finishProcessing;
	IMAGE *imagefte;
	IMAGE *imagedst;
} PARALLEL_STRUCT;

IMAGE imagenfte, imagendst;

/**
* loadBMP
* Method that receives a pointer where the filename is located and
* a pointer where an IMAGE struct is located
**/
int loadBMP(char *filename, IMAGE *image){
	FILE *fin;

	int i = 0;
	int totpixs = 0;

	fin = fopen(filename, "rb+");

	//If files does not exists
	if(fin == NULL){
		printf("File does not exists\n");
		return -1;
	}

	// Reading header and add it to the *image struct
	fread(&image->header, sizeof(HEADER), 1, fin);

	//Check if it is a BMP file
	if(!((image->header.magic1 == 'B') && (image->header.magic2 == 'M'))){
		printf("It is not a BMP file\n");
		return -1;
	}

	// Reading infoheader and add it to the *image struct
	fread(&image->infoheader, sizeof(INFOHEADER), 1, fin);

	// Check if it is a 24 bits BMP file not compacted
	if(!((image->infoheader.bitsPerPixel == 24) && !image->infoheader.compression)){
		printf("It is not a 24 bits\n");
		return -1;
	}

	//Allocation for every pixel size of image->pixel = PIXEL_sc malloc ize * image_columns * image_rows
	image->pixel = (PIXEL *)malloc(sizeof(PIXEL) * image->infoheader.cols * image->infoheader.rows);

	//Defining total pixels in image
	totpixs=image->infoheader.rows*image->infoheader.cols;
	
	//Reading each pixel
	while(i < totpixs){
		fread(image->pixel+i, sizeof(PIXEL), 512, fin);
		i+=512;
	}

	fclose(fin);
}

/**
* saveBMP
* Method that saves the new BMP created
**/
int saveBMP(char *filename, IMAGE *image){
	FILE *fout;
	int i, totpix;

	fout = fopen(filename, "wb");
	if(fout == NULL)
		return -1;

	//Write header
	fwrite(&image->header, sizeof(HEADER), 1, fout);

	//Write infoheader
	fwrite(&image->infoheader, sizeof(INFOHEADER), 1, fout);

	i = 0;
	totpix = image->infoheader.rows * image->infoheader.cols;
	while(i < totpix){
		fwrite(image->pixel+i, sizeof(PIXEL), 512, fout);
		i+=512;
	}

	fclose(fout);
}

unsigned char blackAndWhite(PIXEL p){
	return ((unsigned char)(0.3*((float)p.red) + 0.59*((float)p.green) + 0.11*((float)p.blue)));
}

/*
* processBMPParallel
* Method that checks the boundaries of the image
* parallel way
*/
void *processBMPParallel(void *arg){
	PARALLEL_STRUCT parallel_struct = *((PARALLEL_STRUCT *) arg);
	
	int sp = parallel_struct.startProcessing;
	int fp = parallel_struct.finishProcessing;
	int i,j;
	int count = 0;
	int imageRows, imageCols;

	PIXEL *pfte, *pdst;
	PIXEL *v0, *v1, *v2, *v3, *v4, *v5, *v6, *v7;

	//printf("Los datos donde empiezan son: %d fp:%d\n", sp, fp);

	memcpy(parallel_struct.imagedst, parallel_struct.imagefte, sizeof(IMAGE)-sizeof(PIXEL *));

	imageRows = parallel_struct.imagefte->infoheader.rows;
	imageCols = parallel_struct.imagefte->infoheader.cols;

	parallel_struct.imagedst->pixel = (PIXEL *)(malloc(sizeof(PIXEL) * imageRows * imageCols));

	for(i=sp; i<fp; i++){
		for(j=1; j<imageCols-1; j++){
			pfte = parallel_struct.imagefte->pixel + imageCols * i + j;
			
			// Down pixels
			v0=pfte-imageCols-1;
			v1=pfte-imageCols;
			v2=pfte-imageCols+1;
			
			// Left pixel
			v3=pfte-1;

			// Right pixel
			v4=pfte+1;

			// Up pixels
			v5=pfte+imageCols-1;
			v6=pfte+imageCols;
			v7=pfte+imageCols+1;

			pdst=parallel_struct.imagedst->pixel+imageCols*i+j;

			if(abs(blackAndWhite(*pfte)-blackAndWhite(*v0))>=DIF ||
				abs(blackAndWhite(*pfte)-blackAndWhite(*v1))>=DIF ||
				abs(blackAndWhite(*pfte)-blackAndWhite(*v2))>=DIF ||
				abs(blackAndWhite(*pfte)-blackAndWhite(*v3))>=DIF ||
				abs(blackAndWhite(*pfte)-blackAndWhite(*v4))>=DIF ||
				abs(blackAndWhite(*pfte)-blackAndWhite(*v5))>=DIF ||
				abs(blackAndWhite(*pfte)-blackAndWhite(*v6))>=DIF ||
				abs(blackAndWhite(*pfte)-blackAndWhite(*v7))>=DIF)
			{
				pdst->red=0;
				pdst->green=0;
				pdst->blue=0;

			}else{
				pdst->red=255;
				pdst->green=255;
				pdst->blue=255;
			}
		}
	}
}

int main(){
	int res;
	int totalRows;
	int totalProcessing;
	int struct_counter = 0;
	int thread_counter = 0;
	int thread_join = 0;

	long long start_ts;
	long long stop_ts;
	long long elapsed_time;
	long lElapsedTime;
	
	struct timeval ts;

	pthread_t threads[NUM_THREADS];

	char namedest[80];

	PARALLEL_STRUCT struct_array[NUM_THREADS];

	gettimeofday(&ts, NULL);
	start_ts = ts.tv_sec * 1000000 + ts.tv_sec; //Initial time

	strcpy(namedest, strtok(filename,"."));
	strcat(filename, ".bmp");
	strcat(namedest, "_P.bmp");

	printf("Archivo fuente: %s\n", filename);
	printf("Archivo destino: %s\n", namedest);

	res = loadBMP(filename, &imagenfte);
	if(res == -1){
		fprintf(stderr, "Error al abrir la imagen\n");
		exit(1);
	}

	totalRows = imagenfte.infoheader.rows;
	totalProcessing = totalRows/NUM_THREADS;

	for(struct_counter; struct_counter<NUM_THREADS; struct_counter++){
		struct_array[struct_counter].startProcessing = totalProcessing * struct_counter;
		struct_array[struct_counter].finishProcessing = struct_array[struct_counter].startProcessing + totalProcessing;
		struct_array[struct_counter].imagefte = &imagenfte;
		struct_array[struct_counter].imagedst = &imagendst;
	}

	printf("Procesando imagen...\n renglones: %d\n columnas: %d\n", imagenfte.infoheader.rows, imagenfte.infoheader.cols);

	for(thread_counter; thread_counter<NUM_THREADS; thread_counter++){
		pthread_create(&threads[thread_counter], NULL, processBMPParallel, &struct_array[thread_counter]);
	}

	for(thread_join; thread_join<NUM_THREADS; thread_join++){
		pthread_join(threads[thread_join], NULL);
	}

	printf("Finish processBMP\n");

	res = saveBMP(namedest, &imagendst);
	if(res == -1){
		fprintf(stderr, "Error al guardar la imagen \n");
		exit(1);
	}

	printf("Finish saveBMP\n");
	
	gettimeofday(&ts, NULL);
	stop_ts = ts.tv_sec * 1000000 + ts.tv_usec; // Tiempo final
	elapsed_time = stop_ts - start_ts;
	printf("Tiempo = %4.2f segundos\n",(float)elapsed_time/1000000);
}