
#include "pooling.h"
#include "vector"
#include "limits"
#include "Matrix.h"
#include "cmath"

using namespace std;

//constructor for pooling
pooling::pooling(){
    
}

//deconstructor for pooling
pooling::~pooling(){
    
}

/*
This will return the max pooling of matrix A if kernel size is m and given stride length is "stride"
*/
Matrix pooling::max_pooling(Matrix &A, int m,int stride){
        int n = A.get_sizeofrow();	
        if(stride==0)	//to avoid the infinite loop
            stride=1;
        int lim=ceil((n-m)/stride);
	vector<float> ans;		//max_pool data is stored in this vector
	float max = 0.00;		//assuming maximum is not negative
        

	for(int y=0;(y<n)&&(y+m<=n);y+=stride){
		for(int x=0;(x<n)&&(x+m<=n);x+=stride){
			max = numeric_limits<float>::min();
			for (int i = 0; (i < m)&&((i+x)<n); ++i){
				for (int j = 0; (j < m)&&((j+y)<n); ++j){
					if(max<A.get_Element(j+y,i+x))
						max = A.get_Element(j+y,i+x);
				}
			}
			ans.push_back(max);
		}
	}

	 
    Matrix R(&ans[0],lim+1);	//matrix to be returned made from vector
	return R;

}

/*
This will return the average pooling of matrix A if kernel size is m and given stride length is "stride"
*/
Matrix pooling:: average_pooling(Matrix &A, int m,int stride){
	int n = A.get_sizeofrow();
	if(stride==0)	//to avoid the infinite loop
            stride=1;
        int lim=ceil((n-m)/stride);
	vector<float> ans;	
	float sum = 0.00;	
	

	for(int y=0;(y<n)&&(y+m<=n);y+=stride){
		for(int x=0;(x<n)&&(x+m<=n);x+=stride){
			sum = 0.00;										//initialize sum to zero
			for (int i = 0; (i < m)&&((i+x)<n); ++i){
				for (int j = 0; (j < m)&&((j+y)<n); ++j){
					sum += A.get_Element(j+y,i+x);
				}
			}
			ans.push_back(sum/(m*m));						//this vector will contain result
		}
	}
        Matrix R(&ans[0],lim+1);							//matrix to be returned made form vector "ans"
	return R;

}