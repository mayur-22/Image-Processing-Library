#ifndef SOFTMAX_H
#define SOFTMAX_H
#include <vector>

class softmax
 {
 public:
 	softmax();
 	~softmax();
 	std::vector<float> soft_max(std::vector<float> v);
 	
 }; 
#endif