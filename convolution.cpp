/*
 * This class contains all the functions for generating the convolution of a matrix with given kernel.
 * --One as direct convolution with and without padding.
 * --Other using toeplpitz matrices and matrix multiplication to do the same with and without padding.
 */


#include "convolution.h"
#include "Matrix.h"
#include "cmath"
#include "vector"
#include <cstdlib>
#include <pthread.h>
#include "iostream"
#include "mkl.h"
using namespace std;

struct all
{
	convolution helper;
	Matrix *mat;
	int start,m;
	std::vector<float> result;
	
};

struct two_matrix{
	convolution helper;
    Matrix *mat1;
    Matrix *mat2;
    int start, no_thread;
    float *data;
    int initiate;
    
};

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
Matrix *convolution::to_toeplitz(Matrix &A, int m){
	float *ans=new float[(A.get_sizeofrow()-m+1)*(A.get_sizeofrow()-m+1)*m*m];
	int n = A.get_sizeofrow();
        int r=0;
	for (int i = 0; i < n-m+1 ; ++i){
		for (int j = 0; j < n-m+1; ++j){
			for (int u = 0; u < m; ++u){
                            try{
				for (int v = 0; v < m; ++v){
					ans[r]=(A.get_Element(i+u,j+v,true));
                                        r++;
				}
                            }
                            catch(const char *msg){
                                continue;
                            }
			}
		}
	}
        Matrix * R= new Matrix(ans,r/(m*m),(m*m));

        return R;

}

//Function to convert a matrix to corresponding toeplitz matrix using the given kernel order with zero padding to preserve the sizes
Matrix *convolution::to_toeplitz_padded(Matrix &A, int m){
	float *ans=new float[A.get_sizeofrow()*A.get_sizeofrow()*m*m];
	int n = A.get_sizeofrow();
        int r=0;
	if(m%2!=0){			//if m is even
		for (int x = 0; x < n; ++x){
			for (int y = 0; y < n; ++y){
				for (int u = -(m-1)/2; u <= m/2; ++u){
					for (int v = -(m-1)/2; v <= m/2; ++v){
						ans[r] = A.get_Element(x+u,v+y,false);
                                                r++;
					}
				}
			}
		}
	}

	else{
		for (int x = 0; x < n; ++x){
			for (int y = 0; y < n; ++y){
					for (int u = -m/2; u <= (m-1)/2; ++u){
					for (int v = -m/2; v <= (m-1)/2; ++v){
						ans[r] = A.get_Element(x+u,v+y,false);
                                                r++;
					}
				}
			}
		}

	}
         Matrix * R= new Matrix(ans,r/(m*m),(m*m));

        return R;

}

//Function to perform convolution of a matrix using matrix multiplication
//--First it calls to_toeplitz and then calls mat_mult fiunction of Matrix class to form the resultant matrix
Matrix *convolution::conv_mult_withoutpadding(Matrix& A, Matrix& B){
    Matrix *C=to_toeplitz(A,B.get_sizeofrow());
    Matrix *D=to_toeplitz(B,B.get_sizeofrow());
    Matrix *s= new Matrix(D->get_Matrix(),B.get_sizeofrow()*B.get_sizeofrow(),1);
    Matrix *result= new Matrix((C->mult_matrix(*C,*s))->get_Matrix(),A.get_sizeofrow()-B.get_sizeofrow()+1);
    return result;
}

Matrix *convolution::conv_mult_withoutpadding_threaded(Matrix& A, Matrix& B){
	int m = B.get_sizeofrow(), n = A.get_sizeofrow();
	/*int no_of_threads = n-m+1;

	pthread_t ids[no_of_threads];
    struct all inputs[no_of_threads];


    for (int i = 0; i < no_of_threads; ++i){
    	inputs[i].mat = &A;
    	inputs[i].start = i;
    	inputs[i].m = m;
    	pthread_attr_t attr;
		pthread_attr_init(&attr);
    	pthread_create(&ids[i],&attr,to_toeplitz_threaded_helper,&inputs[i]);

    }

    pthread_join(ids[0],NULL);
    std::vector<float> final_vector = inputs[0].result;
    for (int i = 1; i < no_of_threads; ++i){
    	pthread_join(ids[i],NULL);
    	final_vector.insert(final_vector.end(),inputs[i].result.begin(),inputs[i].result.end());
    }

    Matrix C = Matrix(&final_vector[0],(n-m+1)*(n-m+1),m*m);
    // for(int i = 0;i<final_vector.size();i++){
    	// cout<< final_vector[i]<<" ";
    // }
    // cout<<endl;
 */
	Matrix* temp1_matrix=to_toeplitz(A,m);
	Matrix* C = new Matrix(temp1_matrix->get_Matrix(),(n-m+1)*(n-m+1),m*m);
    Matrix* temp_matrix=to_toeplitz(B,m);
    // cout<<D;
    Matrix* D=new Matrix(temp_matrix->get_Matrix(),1,m*m);
    // D->print_matrix();
    // cout<<D.get;
    // for(int i=0;i<D->get_Vec().size();i++){
    // 	cout<<D->get_Vec()[i]<<" ";
    // }

    //multithreading for matrix multiplication
    int no_of_threads = n-m+1; 
    pthread_t threadid[no_of_threads];
    struct two_matrix inpt[no_of_threads];
    float *answer = new float[(n-m+1)*(n-m+1)];
    // cout<<"C: "<<C.get_Element(0,0)<<" D: "<<D.get_Element(0,0)<<endl;
    // for (int i = 0; i < no_of_threads*no_of_threads; ++i){
    for (int i = 0; i < no_of_threads; ++i){
    	inpt[i].mat1=C;
    	inpt[i].mat2=D;
    	inpt[i].start= i*no_of_threads;
    	inpt[i].data = answer;
    	inpt[i].initiate = i*no_of_threads;
    	inpt[i].no_thread = no_of_threads;
    	pthread_attr_t attr;
		pthread_attr_init(&attr);
    	pthread_create(&threadid[i],NULL,mult_matrix_threaded_helper,&inpt[i]);
    	}

    // pthread_join(threadid[0],NULL);
    // std::vector<float> result_vector = inpt[0].result;
    for (int i = 0; i < no_of_threads; ++i){
    	pthread_join(threadid[i],NULL);
    	// result_vector.insert(result_vector.end(),inpt[i].result.begin(),inpt[i].result.end());
    }

    // cout<<"Print:";
    // for(int i = 0;i<result_vector.size();i++){
    	// cout<< result_vector[i]<<" ";
    // }
    // for(int i=0;i<(n-m+1)*(n-m+1);i++)
    	// cout<<answer[i]<<" ";
    // cout <<endl;


    // return &Matrix(&result_vector[0],n-m+1);		//bad implement
    Matrix *final_matrix = new Matrix(answer,n-m+1,n-m+1); //have to implement this.....
    return final_matrix;
}

Matrix *convolution::conv_mult_withpadding_threaded(Matrix& A, Matrix& B){
	int m = B.get_sizeofrow(), n = A.get_sizeofrow();
	
	Matrix* temp1_matrix=to_toeplitz_padded(A,m);
	Matrix* C = new Matrix(temp1_matrix->get_Matrix(),(n)*(n),m*m);
    Matrix* temp_matrix=to_toeplitz(B,m);
    
    Matrix* D=new Matrix(temp_matrix->get_Matrix(),1,m*m);
    
    int no_of_threads = n; 
    pthread_t threadid[no_of_threads];
    struct two_matrix inpt[no_of_threads];
    float *answer = new float[(n)*(n)];
    
    for (int i = 0; i < no_of_threads; ++i){
    	inpt[i].mat1=C;
    	inpt[i].mat2=D;
    	inpt[i].start= i*no_of_threads;
    	inpt[i].data = answer;
    	inpt[i].initiate = i*no_of_threads;
    	inpt[i].no_thread = no_of_threads;
    	pthread_attr_t attr;
		pthread_attr_init(&attr);
    	pthread_create(&threadid[i],NULL,mult_matrix_threaded_helper,&inpt[i]);
    	}

    
    for (int i = 0; i < no_of_threads; ++i){
    	pthread_join(threadid[i],NULL);
    
    }
    delete temp_matrix;
    delete D; delete temp1_matrix; delete C;
    Matrix *final_matrix = new Matrix(answer,n,n); //have to implement this.....
    return final_matrix;
}


//Function to perform convolution of a matrix using matrix multiplication with zero padding to preserve size
//--First it calls to_toeplitz_padded and then calls mat_mult fiunction of Matrix class to form the resultant matrix
Matrix *convolution::conv_mult_withpadding(Matrix& A, Matrix& B){
    Matrix *C=to_toeplitz_padded(A,B.get_sizeofrow());
    Matrix *D=to_toeplitz(B,B.get_sizeofrow());
    Matrix *s= new Matrix(D->get_Matrix(),B.get_sizeofrow()*B.get_sizeofrow(),1);
    Matrix* result= new Matrix((C->mult_matrix(*C,*s))->get_Matrix(),A.get_sizeofrow());
    return result;
}


void * convolution::to_toeplitz_threaded_helper(void *con){
	struct all *temp = (struct all *)con;
	return temp->helper.to_toeplitz_threaded(con);
}

//Function to convert a matrix to corresponding toeplitz matrix using the given kernel order without any padding
// Matrix convolution::to_toeplitz(Matrix &A, int m, int n){  //n =A.get_sizeofrow();
void * convolution::to_toeplitz_threaded(void * arg){
    struct all * arguments = (struct all *)arg;
    Matrix *A = (arguments->mat);		
    int s = arguments->start;
    int m = arguments->m;
    int n = s+m;

	// std::vector<float> ans;
	
        int r=0;
	for (int i = s; i < n ; ++i){
		for (int j = 0; j < n; ++j){
			for (int u = 0; u < m; ++u){
               try{
				for (int v = 0; v < m; ++v){
					arguments->result.push_back(A->get_Element(i+u,j+v,true));
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
        // arguments->result = ans;
        pthread_exit(0);

}

void * convolution::mult_matrix_threaded_helper(void *con){

	struct two_matrix *temp = (struct two_matrix *)con;
	return temp->helper.mult_matrix_threaded(con);
}


//threaded multiplication
void * convolution::mult_matrix_threaded(void *arguments){

	// cout<<"Inside mult_matrix_threaded: "<<endl;
     struct two_matrix *args = (struct two_matrix *)arguments;
     Matrix *A = args->mat1;
     Matrix *B = args->mat2;
     // cout<<"A: "<<A->get_Element(0,0)<<" B: "<<B->get_Element(0,0)<<endl;
     
     
    // int start = args->start;

    // float *ptr1=A.get_Matrix();
    int r1_start=args->start;
    int r1_end=r1_start+args->no_thread;
    int c1=A->get_sizeofcolumn();
    // float *ptr2=B.get_Matrix();
    int r2=B->get_sizeofrow();
    int c2=B->get_sizeofcolumn();
    // cout<<A->get_Element(0,0);
    // cout<<"A: "<<r1_start<<" "<<r1_end<<" "<<"B: "<<r2<<" "<<c2<<endl;
    // if(c1!=r2)
        // throw DtException("Matrices incompatible for multiplication");
    // float *result=new float[(r1_end-r1_start)*c2];
    // std::vector<float> result;
    float temp = 0.0;
    // cout<<"size: "<<A->get_Vec().size()<<" "<<A->get_Vec().size()<<endl;
    // float *r=result;
    int inc=args->initiate;

    for(int i=r1_start;i<r1_end;i++){
        for(int j=0;j<r2;j++){
            // result[inc]=0;
            temp = 0.0;
            try{
            for(int k=0;k<c2;k++){
            	// cout<<i<<" "<<j<<" "<<k<<endl;
            	// cout<<"Getting A: "<<A->get_Element(i,k)<<endl;
            	// cout<<"Getting B: "<<B->get_Element(k,j)<<endl;
                temp+=((A->get_Element(i,k))*(B->get_Element(j,k)));
                // cout<<temp<<" ";
            // inc++;
            }}
            catch(const char *msg){continue;}
            args->data[inc]= temp;
            inc++;
        }
    }
    // cout<<endl;
    // cout<<args->data[inc];
    // Matrix ret(result,r1,c2);
    // return ret;
    	// 0cout<<result.size()<<endl;
   		// args->result = result;
    pthread_exit(0);

}

/*same for openblas*/
Matrix* convolution::mkl_mult(Matrix& A, Matrix& B){
	int m = B.get_sizeofrow(), n = A.get_sizeofrow();
	Matrix* temp1_matrix=to_toeplitz(A,m);
	Matrix* C = new Matrix(temp1_matrix->get_Matrix(),(n-m+1)*(n-m+1),m*m);
	float* X = C->get_Matrix();
    Matrix* temp_matrix=to_toeplitz(B,m);
    Matrix* D=new Matrix(temp_matrix->get_Matrix(),1,m*m);
    float* Y = D->get_Matrix();
    float* Z = new float[(n-m+1)*(n-m+1)];
    // cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 
                // m, n, k, 1, A, k, B, n, 0, C, n);
    /*m=(n-m+1)*(n-m+1) k=m*m n =1 */
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 			
                (n-m+1)*(n-m+1), 1, m*m, 1, X, m*m, Y, 1, 0, Z,1);		

    Matrix *final_matrix = new Matrix(Z,n-m+1,n-m+1); //have to implement this.....
    return final_matrix;

}

Matrix* convolution::mkl_mult_padded(Matrix& A, Matrix& B){
    cout<<"Inside Function:"<<endl;
	int m = B.get_sizeofrow(), n = A.get_sizeofrow();
	Matrix* temp1_matrix=to_toeplitz_padded(A,m);
	Matrix* C = new Matrix(temp1_matrix->get_Matrix(),(n)*(n),m*m);
	float* X = C->get_Matrix();
    Matrix* temp_matrix=to_toeplitz(B,m);
    Matrix* D=new Matrix(temp_matrix->get_Matrix(),1,m*m);
    float* Y = D->get_Matrix();
    float* Z = new float[n*n];
    // cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 
                // m, n, k, 1, A, k, B, n, 0, C, n);
    /*m=(n-m+1)*(n-m+1) k=m*m n =1 */
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 			
                n*n, 1, m*m, 1, X, m*m, Y, 1, 0, Z,1);		

    Matrix *final_matrix = new Matrix(Z,n,n); //have to implement this.....
    return final_matrix;

}

