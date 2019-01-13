/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "sigmoid.h"
#include <cmath>

sigmoid::sigmoid(){
    
}

sigmoid::~sigmoid(){
    
}
std::vector<float> sigmoid::sig_moid(std::vector<float> v){
	std::vector<float> ans;
	for (std::vector<float>::iterator i = v.begin(); i != v.end(); ++i){
		ans.push_back(1.0/(1+exp(*i)));
	}

	return ans;
}