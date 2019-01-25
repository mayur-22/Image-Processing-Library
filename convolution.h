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
	Matrix* mkl_mult(Matrix& A, Matrix& B);
	Matrix* mkl_mult_padded(Matrix& A, Matrix& B);
	Matrix conv_withoutpadding(Matrix &A,Matrix &B);
	Matrix conv_withpadding(Matrix &A, Matrix &B);
	Matrix *conv_mult_withpadding_threaded(Matrix& A, Matrix& B);
	Matrix *conv_mult_withoutpadding_threaded(Matrix& A, Matrix& B);
	static void *mult_matrix_threaded_helper(void *con);
	static void *to_toeplitz_threaded_helper(void *con);
	void * mult_matrix_threaded(void *arguments);
	void * to_toeplitz_threaded(void * arg);
        Matrix* conv_mult_withoutpadding(Matrix &A,Matrix &B);
        Matrix* conv_mult_withpadding(Matrix &A,Matrix &B);
        Matrix* to_toeplitz_padded(Matrix &A, int m);
        Matrix* to_toeplitz(Matrix &A, int m);
	~convolution();
	
};

#endif /* CONVOLUTION_H */

