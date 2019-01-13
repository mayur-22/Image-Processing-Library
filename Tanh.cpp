/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   tanh.cpp
 * Author: mohd.kamal asraf
 * 
 * Created on 13 January, 2019, 10:43 AM
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

Matrix Tanh::Tanh_mat(Matrix &A){
    float *r=Tanh_internal(A);
    Matrix B(r,A.get_sizeofrow(),A.get_sizeofcolumn());
    return B;
}            


Tanh::~Tanh() {
}

