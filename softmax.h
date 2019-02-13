#ifndef SOFTMAX_H
#define SOFTMAX_H
#include <vector>
#include "Matrix.h"

class softmax
 {
 public:
 	softmax();
 	~softmax();
 	Matrix soft_max(std::vector<float> v);
 	
 }; 

 class sigmoid
{
public:
	sigmoid();
	~sigmoid();

	Matrix sig_moid(std::vector<float> v);
	
};



#endif /* SOFTMAX_H */

