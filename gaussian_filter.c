#include <stdio.h>
#include <math.h>
#define N 300 // image size
#define KS 5 // kernel size
#define HKS 2 // half kernel size

void generate_filter (double gaussian_kernel[][KS]);
void read_pgm (char image[][N]);
void save_pgm (char image[][N]);
void image_padding (char input_image[][N], char padded_image[][N+4]);
void apply_gaussian(char padded_image[][N+4], double gaussian_kernel[][KS], char output_image[][N]);

int main(){
	double gaussian_kernel[KS][KS];
	char input_image[N][N];
	char padded_image[N+4][N+4];
	char output_image[N][N];
	int x,y;
	
	generate_filter(gaussian_kernel);
	// print filter
	for(y=0; y<5; y++){
		for(x=0; x<5; x++)
			printf("%8f ",gaussian_kernel[x][y]);
		printf("\n");
	}
	read_pgm(input_image);
	image_padding(input_image, padded_image);
	apply_gaussian(padded_image, gaussian_kernel, output_image);
	save_pgm(output_image);

	return 0;
}

void generate_filter (double gaussian_kernel[][KS]){
	double stdv = 1.0;
	double r, s = 2.0*stdv*stdv; // assign standard deviation to 1.0
	double sum = 0.0; // init normalization
	int x, y;
	
	// generate kernel
	for (x=-HKS; x<=HKS; x++){
		for (y=-HKS; y<=HKS; y++){
			r = sqrt(x*x + y*y);
			gaussian_kernel[x+HKS][y+HKS] = (exp(-(r*r)/s))/(M_PI*s);
			sum+= gaussian_kernel[x+HKS][y+HKS];
		}	
	}
	// normalize kernel
	for (x=0; x<KS; x++)
		for (y=0; y<KS; y++)
			gaussian_kernel[x][y] /= sum;
}

void read_pgm (char image[][N]){
	char ch;
	int x,y;
	FILE* fp = fopen("lena_bin.pgm","r");
	
	// read header
	do{
		ch = fgetc(fp);
		putchar (ch);
	} while (ch != '\n');
	
	// save data to image[][]
	for(y=0; y<N; y++)
		for(x=0; x<N; x++)
			image[x][y] = fgetc(fp);
	fclose(fp);
}

void image_padding (char input_image[][N], char padded_image[][N+4]){
	int x, y;
	// pad 2 pixels with zero each on the borders for gaussain filter
	for (x=0; x<N+4; x++){
		padded_image[x][0] = 0;
		padded_image[x][1] = 0;
		padded_image[x][N+2] = 0;
		padded_image[x][N+3] = 0;
	}
	for (y=0; y<N+4; y++){
		padded_image[0][y] = 0;
		padded_image[1][y] = 0;
		padded_image[N+2][y] = 0;
		padded_image[N+3][y] = 0;
	}
	for (y=0; y<N; y++)
		for (x=0; x<N; x++)
			padded_image[x+2][y+2] = input_image[x][y];
}

void apply_gaussian(char padded_image[][N+4], double gaussian_kernel[][KS], char output_image[][N]){
	int x,y, gx,gy;
	double sum = 0.0;
	for (y=0; y<N; y++){
		for (x=0; x<N; x++){
			for (gy=0; gy<KS; gy++){
				for (gx=0; gx<KS; gx++){
					sum+=(double)padded_image[x+gx][y+gy]*gaussian_kernel[gx][gy];
				}
			}
			output_image[x][y] = (char)sum;
			sum = 0.0;
		}
	}	
}

void save_pgm (char image[][N]){
	FILE* fp = fopen("lena_gaussian.pgm","w");
	int x, y;	
	// write header - PGM ASCII with 300x300 size, 255bits for each pixel
	fprintf(fp, "P2 300 300 255\n");

	// write pixels
	for (y=0; y<N; y++){
		for (x=0; x<N; x++){
			fprintf(fp, "%d",image[x][y]);
			if (x!=(N-1))
				fprintf(fp, " ");
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
}
