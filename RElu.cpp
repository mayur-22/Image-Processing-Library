/*
 * This class contains the functions for returning the ReLU activated values for a matrix input given 
 * as an object of Matrix class.
*/


#include "RElu.h"
#include "cmath"
#include "vector"
#include "Matrix.h"
using namespace std;

RElu::RElu() {
}


Matrix RElu::Relu_mat(Matrix &A){
    float *r=Relu(A);
    Matrix B(r,A.get_sizeofrow(),A.get_sizeofcolumn());
    return B;
}            

//returns the matrix after applying ReLU on each element
float *RElu::Relu(Matrix &A){
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

//performs ReLU on each input of a given vector
vector <float> RElu::Relu(vector <float> input){
    vector <float> rest;
    vector <float>::iterator iter;
    for(iter=input.begin();iter<input.end();iter++)
        if(*iter<0)
            rest.push_back(0);
        else
            rest.push_back(*iter);
    return rest;
}

