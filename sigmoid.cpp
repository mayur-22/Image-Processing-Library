#include "sigmoid.h"
#include <cmath>

std::vector<float> sigmoid::sig_moid(std::vector<float> v){
	std::vector<float> ans;
	for (std::vector<float>::iterator i = v.begin(); i != v.end(); ++i){
		ans.push_back(1.0/(1+exp(*i)));
	}

	return ans;
}