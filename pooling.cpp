/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "pooling.h"
#include "vector"
#include "limits"
#include "Matrix.h"
#include "cmath"

using namespace std;

pooling::pooling(){
    
}

pooling::~pooling(){
    
}
Matrix pooling::max_pooling(Matrix &A, int m,int stride){
        int n = A.get_sizeofrow();
        if(stride==0)
            stride=m;
        int lim=ceil((n-m)/stride);
	vector<float> ans;		//column priority
	float max = 0.00;
	//assuming i,j will give element of ith row and jth column
        
	for(int y=0;y<n;y+=stride){
		for(int x=0;x<n;x+=stride){
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
        Matrix R(&ans[0],lim);
	return R;

}

Matrix pooling:: average_pooling(Matrix &A, int m,int stride){
	int n = A.get_sizeofrow();
	if(stride==0)
            stride=m;
        int lim=ceil((n-m)/stride);
	vector<float> ans;		//column priority
	float sum = 0.00;
	
	//assuming i,j will give element of ith row and jth column

	for(int y=0;y<n;y+=stride){
		for(int x=0;x<n;x+=stride){
			sum = 0.00;
			for (int i = 0; i < m; ++i){
				for (int j = 0; j < m; ++j){
					sum += A.get_Element(j+y,i+x);
				}
			}
			ans.push_back(sum/(m*m));
		}
	}
        Matrix R(&ans[0],lim);
	return R;

}