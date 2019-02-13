#include "softmax.h"
#include <cmath>

//constructor for sigmoid
sigmoid::sigmoid(){
    
}

//deconstructor for sigmoid
sigmoid::~sigmoid(){
    
}

//will return the sigmoid of data
Matrix sigmoid::sig_moid(std::vector<float> v){
	std::vector<float> ans;
	for (std::vector<float>::iterator i = v.begin(); i != v.end(); ++i){
		ans.push_back(1.0/(1+exp(-*i)));
	}

	return Matrix(ans);
}