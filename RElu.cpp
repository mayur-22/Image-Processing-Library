#include "cmath"
#include "vector"
#include "Matrix.h"
#include "RElu.h"
using namespace std;



Matrix *Relu_mat(Matrix &A){
    float *r=Relu(A);
    Matrix *B=new Matrix(r,A.get_sizeofrow(),A.get_sizeofcolumn());
    return B;
}            

//returns the matrix after applying ReLU on each element
float *Relu(Matrix &A){
        float *mat=A.get_Matrix();
        int rows=A.get_sizeofrow();
        int columns=A.get_sizeofcolumn();
    float *matret=new float[rows*columns];
    for(int i=0;i<rows*columns;i++)
            if(mat[i]>0)
                matret[i]=mat[i];
            else
                matret[i]=0;
    return matret;
}