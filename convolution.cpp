/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   convolution.cpp
 * Author: mohd.kamal asraf
 * 
 * Created on 13 January, 2019, 6:47 PM
 */

#include "convolution.h"
#include "Matrix.h"
#include "cmath"
#include "vector"
using namespace std;

convolution::convolution(){
    
}

convolution::~convolution(){
    
}

Matrix convolution::conv_withoutpadding(Matrix &A, Matrix &B){
	std::vector<float> ans;
	int n = A.get_sizeofrow();
	int m = B.get_sizeofrow();
	
	if(m%2==0){			//if m is even
		for (int x = 0; x < n; ++x){
			for (int y = 0; y < n; ++y){
				try{
				int sum = 0.00;
				for (int u = -(m-1)/2; u <= m/2; ++u){
					for (int v = -(m-1)/2; v <= m/2; ++v){
						sum+=A.get_Element(v+u,x+u,true)*B.get_Element(v+(m/2),u+(m/2));
					}
				}
				ans.push_back(sum);
				}
				catch(char *msg){}
			}
		}
	}

	else{
		for (int x = 0; x < n; ++x){
			for (int y = 0; y < n; ++y){
				try{
				int sum = 0.00;
				for (int u = -m/2; u <= (m-1)/2; ++u){
					for (int v = -m/2; v <= (m-1)/2; ++v){
						sum+=A.get_Element(v+u,x+u,true)*B.get_Element(v+(m/2),u+(m/2));
					}
				}
				ans.push_back(sum);
				}
				catch(char *msg){}
			}
		}

	}
        Matrix R(&ans[0],sqrt(ans.size()));
	return R;
}

Matrix convolution::conv_withpadding(Matrix &A, Matrix &B){
	std::vector<float> ans;
	int n = A.get_sizeofrow();
	int m = B.get_sizeofrow();
	
	if(m%2==0){			//if m is even
		for (int x = 0; x < n; ++x){
			for (int y = 0; y < n; ++y){
				int sum = 0.00;
				for (int u = -(m-1)/2; u <= m/2; ++u){
					for (int v = -(m-1)/2; v <= m/2; ++v){
						sum+=A.get_Element(v+u,x+u,false)*B.get_Element(v+(m/2),u+(m/2));
					}
				}
				ans.push_back(sum);
			}
		}
	}

	else{
		for (int x = 0; x < n; ++x){
			for (int y = 0; y < n; ++y){
				int sum = 0.00;
				for (int u = -m/2; u <= (m-1)/2; ++u){
					for (int v = -m/2; v <= (m-1)/2; ++v){
						sum+=A.get_Element(v+u,x+u,false)*B.get_Element(v+(m/2),u+(m/2));
					}
				}
				ans.push_back(sum);
			}
		}

	}
	Matrix R(&ans[0],sqrt(ans.size()));
	return R;
}

Matrix convolution::to_toeplitz(Matrix &A, int m){
	std::vector<float> ans;
	int n = A.get_sizeofrow();
        int r=0;
	for (int i = 0; i < n-m+1 ; ++i){
		for (int j = 0; j < n-m+1; ++j){
			for (int u = 0; u < m; ++u){
				for (int v = 0; v < m; ++v){
					ans.push_back(A.get_Element(j+v,i+u));
                                        r++;
				}
			}
		}
	}
        Matrix R(&ans[0],m,r/m);
	return R;

}

Matrix convolution::to_toeplitz_padded(Matrix &A, int m){
	std::vector<float> ans;
	int n = A.get_sizeofrow();
        int r=0;
	if(m%2==0){			//if m is even
		for (int x = 0; x < n; ++x){
			for (int y = 0; y < n; ++y){
				for (int u = -(m-1)/2; u <= m/2; ++u){
					for (int v = -(m-1)/2; v <= m/2; ++v){
						ans.push_back(A.get_Element(v+u,x+u,false));
					}
				}
			}
		}
	}

	else{
		for (int x = 0; x < n; ++x){
			for (int y = 0; y < n; ++y){
				int sum = 0.00;
				for (int u = -m/2; u <= (m-1)/2; ++u){
					for (int v = -m/2; v <= (m-1)/2; ++v){
						ans.push_back(A.get_Element(v+u,x+u,false));
					}
				}
			}
		}

	}
        Matrix R(&ans[0],m,r/m);
	return R;

}

Matrix convolution::conv_mult_withoutpadding(Matrix& A, Matrix& B){
    Matrix C=to_toeplitz(A,B.get_sizeofrow());
    Matrix D=to_toeplitz(B,B.get_sizeofrow());
    return C.mult_matrix(C,D);
}

Matrix convolution::conv_mult_withpadding(Matrix& A, Matrix& B){
    Matrix C=to_toeplitz_padded(A,B.get_sizeofrow());
    Matrix D=to_toeplitz(B,B.get_sizeofrow());
    return C.mult_matrix(C,D);
}