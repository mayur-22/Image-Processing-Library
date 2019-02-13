/*
 * This class contains the functions for applying tanh to data given in form of a Matrix object.
 */

#include "tanh.h"
#include "cmath"
#include "Matrix.h"
Tanh::Tanh() {
}

float *Tanh::Tanh_mat(float *mat,int rows,int columns){
	float *matret=new float[rows*columns];
	for(int i=0;i<rows*columns;i++)
		matret[i]=tanh(mat[i]);
	return matret;
}

float *Tanh::Tanh_internal(Matrix &A){
        float *mat=A.get_Matrix();
        int rows=A.get_sizeofrow();
        int columns=A.get_sizeofcolumn();
	float *matret=new float[rows*columns];
	for(int i=0;i<rows*columns;i++)
		matret[i]=tanh(mat[i]);
	return matret;
}

//public function that takes a matrix object and returns a matrix after applying tanh to each data element
Matrix *Tanh::Tanh_mat(Matrix &A){
    float *r=Tanh_internal(A);
    Matrix *B=new Matrix(r,A.get_sizeofrow(),A.get_sizeofcolumn());
    return B;
}            


Tanh::~Tanh() {
}
