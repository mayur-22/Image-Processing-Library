/*
 * This class contains all the functions for generating the convolution of a matrix with given kernel.
 * --One as direct convolution with and without padding.
 * --Other using toeplpitz matrices and matrix multiplication to do the same with and without padding.
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

//Function that takes two matrices data as Matrix objects and then performs covolution without padding
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

//Function that takes two matrices data as Matrix objects and then performs covolution with zero padding and 
//returns the resultant matrix as a Matrix object
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

//Function to convert a matrix to corresponding toeplitz matrix using the given kernel order without any padding
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

//Function to convert a matrix to corresponding toeplitz matrix using the given kernel order with zero padding to preserve the sizes
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

//Function to perform convolution of a matrix using matrix multiplication
//--First it calls to_toeplitz and then calls mat_mult fiunction of Matrix class to form the resultant matrix
Matrix convolution::conv_mult_withoutpadding(Matrix& A, Matrix& B){
    Matrix C=to_toeplitz(A,B.get_sizeofrow());
    Matrix D=to_toeplitz(B,B.get_sizeofrow());
    D=Matrix(D.get_Matrix(),B.get_sizeofrow()*B.get_sizeofrow(),1);
    return Matrix((C.mult_matrix(C,D)).get_Matrix(),A.get_sizeofrow()-B.get_sizeofrow()+1);
}


//Function to perform convolution of a matrix using matrix multiplication with zero padding to preserve size
//--First it calls to_toeplitz_padded and then calls mat_mult fiunction of Matrix class to form the resultant matrix
Matrix convolution::conv_mult_withpadding(Matrix& A, Matrix& B){
    Matrix C=to_toeplitz_padded(A,B.get_sizeofrow());
    Matrix D=to_toeplitz(B,B.get_sizeofrow());
    D=Matrix(D.get_Matrix(),B.get_sizeofrow()*B.get_sizeofrow(),1);
    return Matrix((C.mult_matrix(C,D)).get_Matrix(),A.get_sizeofrow());
}
