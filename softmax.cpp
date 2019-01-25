#include "softmax.h"
#include <cmath>
#include "Matrix.h"

//constructor for softmax
softmax::softmax(){
    
}

//deconstructor for softmax
softmax::~softmax(){
    
}


Matrix softmax::soft_max(std::vector<float> v){

	std::vector<float> ans;
	std::vector<float> expo;		//this vector will contain the exponential value of individual data 
	float sum = 0.0;
	for (std::vector<float>::iterator i = v.begin(); i != v.end(); ++i){
		float temp = exp(*i);
		expo.push_back(temp);		
		sum += temp;				//will calculate the sum of all exponentials
	}

	for (std::vector<float>::iterator i = expo.begin(); i != expo.end(); ++i){
		ans.push_back(*i/sum);	
	}
        Matrix R(ans);
	return R;
}