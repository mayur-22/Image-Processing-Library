#ifndef LETNET
#define LETNET
#include "Matrix.h"

using namespace std;
class LetNet{
	public:
		LetNet();
		~LetNet();
		Matrix **Convolution1(Matrix &image);
		Matrix **Convolution2(Matrix **image);
		void Pool1(Matrix **inputchannels);
		void Pool2(Matrix **inputchannels);
		void ReluAll(Matrix **inputchannels);
		Matrix **FullyConnected1(Matrix **image);
		Matrix **FullyConnected2(Matrix **image);
};
#endif