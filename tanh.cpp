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

tanh::tanh() {
}

float *tanh::Tanh_mat(float *mat,int rows,int columns){
	float *matret=new float[rows*columns];
	for(int i=0;i<rows*columns;i++)
		matret[i]=tanh(mat[i]);
	return matret;
}

Matrix tanh::Tanh_mat(Matrix &A){
    B=new Matrix(A.get_sizeofrow()*A.get_sizeofcolumn(),A.get_sizeofrow(),A.get_sizeofcolumn());
    float *r=Tanh_mat(A.get_Matrix(),A.get_sizeofrow(),A.get_sizeofcolumn());
    B->set_Matrix(r);
}            


tanh::~tanh() {
}

