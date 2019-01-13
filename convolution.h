#ifndef CONVOLUTION_H
#define CONVOLUTION_H
#include "Matrix.h"

class convolution
{
public:
	convolution();
	std::vector<float> conv_withoutpadding(Matrix &A,Matrix &B);
	std::vector<float> conv_withpadding(Matrix &A, Matrix &B);
	~convolution();
	
};

#endif