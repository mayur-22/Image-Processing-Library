/*
 * This class contains all the functions for generating the convolution of a matrix with given kernel.
 * --One as direct convolution with and without padding.
 * --Other using toeplpitz matrices and matrix multiplication to do the same with and without padding.
 */


#include "convolution.h"
#include "DtException.h"
#include "Matrix.h"
#include "cmath"
#include "vector"
#include <cstdlib>
#include <pthread.h>

using namespace std;

typedef struct All
{
	Matrix *mat;
	int start,m;
	std::vector<float> result;
	
}all;

typedef struct Two_matrix{
    Matrix *mat1;
    Matrix *mat2;
    int start;
    std::vector<float> result;
    
}two_matrix;

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

//Function to convert a matrix to corresponding toeplitz matrix using the given kernel order without any padding
// Matrix convolution::to_toeplitz(Matrix &A, int m, int n){  //n =A.get_sizeofrow();
	void * convolution::to_toeplitz_threaded(void * arg){
    
    all * arguments = (all *)arg;
    Matrix *A = (arguments->mat);		
    int s = arguments->start;
    int m = arguments->m;
    int n = s+m;

	std::vector<float> ans;
	
        int r=0;
	for (int i = s; i < n ; ++i){
		for (int j = 0; j < n; ++j){
			for (int u = 0; u < m; ++u){
               try{
				for (int v = 0; v < m; ++v){
					ans.push_back(A->get_Element(i+u,j+v,true));
                                        r++;
				}
               }
               catch(const char *msg){
                 continue;
               }
			}
		}
	}
        // Matrix R(&ans[0],r/(m*m),(m*m));
        arguments->result = ans;
        pthread_exit(0);

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
	int m = B.get_sizeofrow(), n = A.get_sizeofrow();
    int no_of_threads = n-m+1;
    // Matrix C=to_toeplitz(A,m,m);

    //Thread ids
    pthread_t ids[no_of_threads];
    all inputs[no_of_threads];

    // void* (*f) (void*) = &convolution::to_toeplitz_threaded;

    for (int i = 0; i < no_of_threads; ++i){
    	inputs[i].mat = &A;
    	inputs[i].start = i;
    	inputs[i].m = m;
    	pthread_create(&ids[i],NULL,&to_toeplitz_threaded,&inputs[i]);

    }

    pthread_join(ids[0],NULL);
    std::vector<float> final_vector = inputs[0].result;
    for (int i = 1; i < no_of_threads; ++i){
    	pthread_join(ids[i],NULL);
    	final_vector.insert(final_vector.end(),inputs[i].result.begin(),inputs[i].result.end());
    }

    //now  inputs[i].ans will contain all vectors
    /*construct a matrix to make a matrix out of it*/
    //constructing matrix C
    Matrix C = Matrix(&final_vector[0],(n-m+1)*(n-m+1),m*m);


    Matrix D=to_toeplitz(B,m);
    D=Matrix(D.get_Matrix(),m*m,1);

    //multithreading for matrix multiplication

    no_of_threads = no_of_threads/10;
    pthread_t thread_id[no_of_threads]; 
    two_matrix inpt[no_of_threads];
    for (int i = 0; i < no_of_threads; ++i){
    	inpt[i].mat1=&C;
    	inpt[i].mat2=&D;
    	inpt[i].start= i*10;
    	pthread_create(&thread_id[i],NULL,mult_matrix_threaded,&inpt[i]);
    }

    pthread_join(thread_id[0],NULL);
    std::vector<float> result_vector = inpt[0].result;
    for (int i = 1; i < no_of_threads; ++i){
    	pthread_join(thread_id[i],NULL);
    	result_vector.insert(result_vector.end(),inpt[i].result.begin(),inpt[i].result.end());
    }

    return Matrix(&result_vector[0],n-m+1);	//bad implementation
    //now inpt[i].result will contain all vectors 
    /* Construct a matrix using this*/


    // return Matrix((C.mult_matrix(C,D)).get_Matrix(),n-m+1);
}


//Function to perform convolution of a matrix using matrix multiplication with zero padding to preserve size
//--First it calls to_toeplitz_padded and then calls mat_mult fiunction of Matrix class to form the resultant matrix
Matrix convolution::conv_mult_withpadding(Matrix& A, Matrix& B){
    Matrix C=to_toeplitz_padded(A,B.get_sizeofrow());
    Matrix D=to_toeplitz(B,B.get_sizeofrow());
    D=Matrix(D.get_Matrix(),B.get_sizeofrow()*B.get_sizeofrow(),1);
    return Matrix((C.mult_matrix(C,D)).get_Matrix(),A.get_sizeofrow());
}


//threaded multiplication
void * convolution::mult_matrix_threaded(void *arguments){

    two_matrix *args = (two_matrix *)arguments;
     Matrix *A = args->mat1;
     Matrix *B = args->mat2;
    // int start = args->start;

    // float *ptr1=A.get_Matrix();
    int r1_start=args->start;
    int r1_end=r1_start+10;
    int c1=A->get_sizeofcolumn();
    // float *ptr2=B.get_Matrix();
    int r2=B->get_sizeofrow();
    int c2=B->get_sizeofcolumn();
    if(c1!=r2)
        throw DtException("Matrices incompatible for multiplication");
    // float *result=new float[(r1_end-r1_start)*c2];
    std::vector<float> result;
    float temp = 0.0;

    // float *r=result;
    // int inc=0;
    for(int i=r1_start;i<r1_end;i++){
        for(int j=0;j<c2;j++){
            // result[inc]=0;
            temp = 0.0;
            for(int k=0;k<c1;k++)
                temp+=(A->get_Element(i,k))*(B->get_Element(k,j));
            // inc++;
            result.push_back(temp);
        }
    }
    // Matrix ret(result,r1,c2);
    // return ret;
   		args->result = result;
        pthread_exit(0);

}

