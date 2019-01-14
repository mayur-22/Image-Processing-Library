/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "softmax.h"
#include <cmath>
#include "Matrix.h"

softmax::softmax(){
    
}

softmax::~softmax(){
    
}
Matrix softmax::soft_max(std::vector<float> v){

	std::vector<float> ans;
	std::vector<float> expo;
	float sum = 0.0;
	for (std::vector<float>::iterator i = v.begin(); i != v.end(); ++i){
		float temp = exp(*i);
		expo.push_back(temp);
		sum += temp;
	}

	for (std::vector<float>::iterator i = expo.begin(); i != expo.end(); ++i){
		ans.push_back(*i/sum);
	}
        Matrix R(ans);
	return R;
}