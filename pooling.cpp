#include "pooling.h"
#include "vector"
#include "limits"
#include "Matrix.h"
#include "cmath"

using namespace std;



/*
This will return the max pooling of matrix A if kernel size is m and given stride length is "stride"
*/
Matrix *max_pooling(Matrix &A, int m,int stride){
        int n = A.get_sizeofrow();	
        if(stride==0)	//to avoid the infinite loop
            stride=1;
        int lim=((n-m)/stride);
	float *ans=new float[(lim+1)*(lim+1)];		//max_pool data is stored in this vector
	float max = 0.00;		//assuming maximum is not negative
    float *t=ans;
    // A.print_matrix();
	for(int y=0;(y<n)&&(y+m<=n);y+=stride){
		for(int x=0;(x<n)&&(x+m<=n);x+=stride){
			max = -50000;
			for (int i = 0; (i < m)&&((i+x)<n); ++i){
				for (int j = 0; (j < m)&&((j+y)<n); ++j){
					if(max<A.get_Element(j+y,i+x))
						max = A.get_Element(j+y,i+x);
				}
			}
			*t=max;
			t++;
		}
	}

	 
    Matrix *R=new Matrix(ans,lim+1);	//matrix to be returned made from vector
	return R;

}

/*
This will return the average pooling of matrix A if kernel size is m and given stride length is "stride"
*/
Matrix *average_pooling(Matrix &A, int m,int stride){
	int n = A.get_sizeofrow();
	if(stride==0)	//to avoid the infinite loop
            stride=1;
        int lim=ceil((n-m)/stride);
	float *ans=new float[lim+1];
	float sum = 0.00;	
	float *t=ans;

	for(int y=0;(y<n)&&(y+m<=n);y+=stride){
		for(int x=0;(x<n)&&(x+m<=n);x+=stride){
			sum = 0.00;										//initialize sum to zero
			for (int i = 0; (i < m)&&((i+x)<n); ++i){
				for (int j = 0; (j < m)&&((j+y)<n); ++j){
					sum += A.get_Element(j+y,i+x);
				}
			}
			*t=(sum/(m*m));						//this vector will contain result
			t++;
		}
	}
    Matrix *R=new Matrix(ans,lim+1);							//matrix to be returned made form vector "ans"
	return R;

}