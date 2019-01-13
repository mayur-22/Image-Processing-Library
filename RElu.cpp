/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RElu.cpp
 * Author: mohd.kamal asraf
 * 
 * Created on 12 January, 2019, 9:21 AM
 */

#include "RElu.h"
#include "cmath"
#include "vector"
#include "Matrix.h"
using namespace std;

RElu::RElu() {
}
/*
float *RElu::Relu_vec(float *input,int rows, int columns){
    float *ret=new float[columns*rows];
    float *r=ret;
    int lim=columns*rows;
    for(int i=0;i<lim;i++)
        *(ret++)=*(input+i);
    return ret;
}

float *RElu::Relu_vec(float *input,int rows){
    float *ret=new float[rows*rows];
    float *r=ret;
    int lim=rows*rows;
    for(int i=0;i<lim;i++)
        *(ret++)=*(input+i);
    return ret;
}
*/
Matrix RElu::Relu_mat(Matrix &A){
    float *r=Relu(A);
    Matrix B(r,A.get_sizeofrow(),A.get_sizeofcolumn());
    return B;
}            

float *RElu::Relu(Matrix &A){
        float *mat=A.get_Matrix();
        int rows=A.get_sizeofrow();
        int columns=A.get_sizeofcolumn();
	float *matret=new float[rows*columns];
	for(int i=0;i<rows*columns;i++)
		matret[i]=fabs(mat[i]);
	return matret;
}
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

