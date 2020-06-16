#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define ELEM(M,r,c) (M->elem[(M->cols)*r+c])

typedef struct{
	unsigned int rows;
	unsigned int cols;
	float *elem;
}MAT;

MAT* mat_create_with_type(unsigned int rows, unsigned int cols){
	MAT* m=(MAT*)malloc(sizeof(MAT)); 
	if (m == NULL){
		return NULL;
	}                               
	m->elem=(float*)malloc(sizeof(float)*rows*cols);
		
	if (m->elem == NULL){
		return NULL;
	}           
	return m;
}

void mat_destroy(MAT *mat){
	free(mat);
	free(mat->elem);
}

void mat_random(MAT *mat){
	int i,j;
	for (i=0;i<mat->rows;i++){
	
	for (j=0;j<mat->cols;j++){
			ELEM(mat,i,j)=(rand()/(float)(RAND_MAX)) *2 -1;
	}
	}
}

void mat_unit(MAT *mat){
	int i,j;
	for (i=0;i<mat->rows;i++){
	
	for (j=0;j<mat->cols;j++){
	
	if (i==j)
		ELEM(mat,i,j)=1;
	else
		ELEM(mat,i,j)=0;
	}
	}
}

void mat_print(MAT *mat){
	int i,j;
	
	for (i=0;i<mat->rows;i++){
	
	for (j=0;j<mat->cols;j++){
			if (ELEM(mat,i,j)-(int)(ELEM(mat,i,j))==0){
				printf(" ");
				printf("%d ",(int)(ELEM(mat,i,j)));
			}
			else{
					
			if (ELEM(mat,i,j)<0)
				printf("%.3f ",ELEM(mat,i,j));	
			else
				printf(" %.3f ",ELEM(mat,i,j));
			}		
	}
			printf("\n");
	}
	printf("\n");
}



float mat_permanent(MAT *mat){
	int i,j,r;
	float perm=0;

	if (mat->cols==1 && mat->rows==1)
		perm=ELEM(mat,0,0);
	else
	if (mat->cols==2 && mat->rows==2)
		perm=ELEM(mat,0,0)*ELEM(mat,1,1)+ELEM(mat,0,1)*ELEM(mat,1,0);	
	
	else{
		for (r=0;r<mat->cols;r++){    //posuvanie po stlpcoch
			MAT *mensiaMat;
			mensiaMat= mat_create_with_type(mat->rows-1,mat->cols-1);
			
			for (i=0;i<mat->cols;i++){
	
			for (j=0;j<mat->rows;j++){
				if (j!=r){
					ELEM(mensiaMat,i,j)=ELEM(mat,i+1,j+1);
				}
			}
			}
		mat_print(mensiaMat);
	
	
	perm+=ELEM(mat,0,r)*mat_permanent(mensiaMat);
	mat_destroy(mensiaMat);
		}
	}
	return perm;
}


main(){
	srand(time(NULL));
	MAT* m;
	unsigned int x,y;
	float a;
	printf("Zadaj pocet riadkov a pocet stlpcov:");
	scanf("%d %d",&x,&y);
	m=mat_create_with_type(x,y);
	m->rows=x;
	m->cols=y;
	
	mat_unit(m);
	mat_print(m);
	mat_random(m);
	mat_print(m);
	
	
	if (m->cols==m->rows){
		printf ("Permanent matice je: %.3f",mat_permanent(m));
		return 0;
	}
	
	else{
		printf ("Permanent matice viem urcit iba z matice nxn!\n"); 
		return 1;
	}
}
