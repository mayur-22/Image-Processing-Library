/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   convolution.h
 * Author: mohd.kamal asraf
 *
 * Created on 13 January, 2019, 6:47 PM
 */

#ifndef CONVOLUTION_H
#define CONVOLUTION_H
#include "Matrix.h"

class convolution
{
public:
	convolution();
	Matrix conv_withoutpadding(Matrix &A,Matrix &B);
	Matrix conv_withpadding(Matrix &A, Matrix &B);
	~convolution();
	
};

#endif /* CONVOLUTION_H */

