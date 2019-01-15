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
	
	if(m%2!=0){			//if m is even
		for (int x = 0; x < n; ++x){
			for (int y = 0; y < n; ++y){
				try{
				float sum = 0.00;
				for (int u = -(m-1)/2; u <= m/2; ++u){
					for (int v = -(m-1)/2; v <= m/2; ++v){
						sum+=A.get_Element(x+u,v+y,true)*B.get_Element(u+(m/2),v+(m/2));
					}
				}
				ans.push_back(sum);
				}
				catch(const char *msg){
                                    continue;
                                }
			}
		}
	}

	else{
		for (int x = 0; x < n; ++x){
			for (int y = 0; y < n; ++y){
				try{
				float sum = 0.00;
				for (int u = -m/2; u <= (m-1)/2; ++u){
					for (int v = -m/2; v <= (m-1)/2; ++v){
						sum+=A.get_Element(x+u,v+y,true)*B.get_Element(u+(m/2),v+(m/2));
					}
				}
				ans.push_back(sum);
				}
				catch(const char *msg){
                                    continue;
                                }
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
	
	if(m%2!=0){			//if m is even
		for (int x = 0; x < n; ++x){
			for (int y = 0; y < n; ++y){
				float sum = 0.00;
				for (int u = -(m-1)/2; u <= m/2; ++u){
					for (int v = -(m-1)/2; v <= m/2; ++v){
						sum+=A.get_Element(x+u,v+y,false)*B.get_Element(u+(m/2),v+(m/2));
					}
				}
				ans.push_back(sum);
			}
		}
	}

	else{
		for (int x = 0; x < n; ++x){
			for (int y = 0; y < n; ++y){
				float sum = 0.00;
				for (int u = -m/2; u <= (m-1)/2; ++u){
					for (int v = -m/2; v <= (m-1)/2; ++v){
						sum+=A.get_Element(x+u,v+y,false)*B.get_Element(u+(m/2),v+(m/2));
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
                            try{
				for (int v = 0; v < m; ++v){
					ans.push_back(A.get_Element(i+u,j+v,true));
                                        r++;
				}
                            }
                            catch(const char *msg){
                                continue;
                            }
			}
		}
	}
        Matrix R(&ans[0],r/(m*m),(m*m));
        return R;

}

Matrix convolution::to_toeplitz_padded(Matrix &A, int m){
	std::vector<float> ans;
	int n = A.get_sizeofrow();
        int r=0;
	if(m%2!=0){			//if m is even
		for (int x = 0; x < n; ++x){
			for (int y = 0; y < n; ++y){
				for (int u = -(m-1)/2; u <= m/2; ++u){
					for (int v = -(m-1)/2; v <= m/2; ++v){
						ans.push_back(A.get_Element(x+u,v+y,false));
                                                r++;
					}
				}
			}
		}
	}

	else{
		for (int x = 0; x < n; ++x){
			for (int y = 0; y < n; ++y){
				float sum = 0.00;
				for (int u = -m/2; u <= (m-1)/2; ++u){
					for (int v = -m/2; v <= (m-1)/2; ++v){
						ans.push_back(A.get_Element(x+u,v+y,false));
                                                r++;
					}
				}
			}
		}

	}
        Matrix R(&ans[0],r/(m*m),(m*m));
	return R;

}

Matrix convolution::conv_mult_withoutpadding(Matrix& A, Matrix& B){
    Matrix C=to_toeplitz(A,B.get_sizeofrow());
    Matrix D=to_toeplitz(B,B.get_sizeofrow());
    D=Matrix(D.get_Matrix(),B.get_sizeofrow()*B.get_sizeofrow(),1);
    return Matrix((C.mult_matrix(C,D)).get_Matrix(),A.get_sizeofrow()-B.get_sizeofrow()+1);
}

Matrix convolution::conv_mult_withpadding(Matrix& A, Matrix& B){
    Matrix C=to_toeplitz_padded(A,B.get_sizeofrow());
    Matrix D=to_toeplitz(B,B.get_sizeofrow());
    D=Matrix(D.get_Matrix(),B.get_sizeofrow()*B.get_sizeofrow(),1);
    return Matrix((C.mult_matrix(C,D)).get_Matrix(),A.get_sizeofrow());
}