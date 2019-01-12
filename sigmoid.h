#ifndef SIGMOID_H
#define SIGMOID_H
#include <vector>

class sigmoid
{
public:
	sigmoid();
	~sigmoid();

	std::vector<float> sig_moid(std::vector<float> v);
	
};

#endif