#ifndef POOLING_H
#define POOLING_H
#include <vector>
#include "Matrix.h"

class pooling{
public:
	pooling();
	~pooling();
	std::vector<float> max_pooling(Matrix A,Matrix B);
	std::vector<float> average_pooling(Matrix A,Matrix B);
	
};

#endif