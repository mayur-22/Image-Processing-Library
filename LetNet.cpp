
#include "Matrix.h"
#include "convolution.h"
#include "pooling.h"
#include "RElu.h"
#include "LetNet.h"

LetNet::LetNet(){
    
}

LetNet::~LetNet(){
    
}

/*
 This function provides the output for the first convolutional layer.
 It takes as input a single channel image as input, reads the weights and biases from the file
 "conv1.txt" and then generates the 20 output channels by calling conv_mult_withoutpadding for performing
 the convolution and subsequently add_bias for adding the biases.
 
 The output is provided as pointer to an array of pointers to dynamically allocated Matrix objects where each object represents
 one output channel.

*/
Matrix ** LetNet::Convolution1(Matrix &image){
	Matrix **result = new Matrix*[20];
	Matrix C("conv1.txt",1,520);
	float *ptr=C.get_Matrix();
	convolution conv;
	for(int i=0;i<20;i++){
		Matrix R((ptr+(i*25)),5);
		result[i] = conv.conv_mult_withoutpadding(image,R);
		int x = result[i]->get_sizeofrow();
		int y = result[i]->get_sizeofcolumn();
		result[i]->add_bias(C.get_Element(0,500+i));
		
	}
	return result;
}

/*
 This function defines the first max_pooling layer.
 It takes as input the array of pointers to the Matrix objects that are effectively the distinct units of the input channel.
 It then modifies the objects by allocating to them the output matrix objects from application of max_pooling with kernel size 2
 and stride parameter 2.

*/

void LetNet::Pool1(Matrix **inputchannels){
	for(int i=0;i<20;i++){
			int n=inputchannels[i]->get_sizeofcolumn();
			inputchannels[i] = max_pooling(*(inputchannels[i]),2,2);
			
		}

}

/*
 This function provides the output for the first convolutional layer.
 It takes as input an array of pointers to Matrix objects, each one of which represent, one input channel,reads the weights and biases from the file
 "conv2.txt" and then generates the 500 output channels by calling conv_mult_withoutpadding for performing
 the convolution and subsequently add_bias for adding the biases.
 
 The output is provided as pointer to an array of pointers to dynamically allocated Matrix objects where each object represents
 one output channel.

*/
Matrix **LetNet::Convolution2(Matrix **image){
	Matrix **result = new Matrix*[50];
	Matrix C("conv2.txt",1,25050);
	float *ptr=C.get_Matrix();
	convolution conv;
	for(int i=0;i<50;i++){
		Matrix R(ptr+(i*500),5);
		result[i]=conv.conv_mult_withoutpadding(*(image[0]),R);
		for(int j=1;j<20;j++){
			Matrix kernel(ptr+(i*500)+(j*25),5);
			Matrix *S=conv.conv_mult_withoutpadding(*(image[j]),kernel);
			(result[i])->add_matrix(*S);
		}
		result[i]->add_bias(C.get_Element(0,25000+i));

	}
	return result;
}



/*
 This function defines the second max_pooling layer.
 It takes as input the array of pointers to the Matrix objects that are effectively the distinct units of the input channel.
 It then modifies the objects by allocating to them the output matrix objects from application of max_pooling with kernel size 2
 and stride parameter 2.

*/
void LetNet::Pool2(Matrix **inputchannels){
	for(int i=0;i<50;i++){
			inputchannels[i] = max_pooling(*(inputchannels[i]),2,2);
		}

}

/*
 This function is simply used for the ReLU layer and just modifies each channel in the input by applying ReLU to each object.
*/

void LetNet::ReluAll(Matrix **inputchannels){
	for(int i=0;i<500;i++){
			inputchannels[i] = Relu_mat(*(inputchannels[i]));
		}
}

/*
 This function forms the first fully connected convolutional layer.
 Though this could have been implemented much more simply we have maintained the same set of abstractions that were used for
 the first tow convolutional layers.
 
 There are 500 input channels and the same nummber of output channes associated with this layer.
*/

Matrix **LetNet::FullyConnected1(Matrix **image){
	Matrix **result = new Matrix*[500];
	Matrix C("fc1.txt",1,400500);
	float *ptr=C.get_Matrix();
	convolution conv;
	for(int i=0;i<500;i++){
		Matrix R(ptr+(i*800),4);
		result[i]=conv.conv_mult_withoutpadding(*(image[0]),R);
		for(int j=1;j<50;j++){
			Matrix kernel(ptr+(i*800)+(j*16),4);
			Matrix *S=conv.conv_mult_withoutpadding(*(image[j]),kernel);
			result[i]->add_matrix(*S);
		}
		(result[i])->add_bias(C.get_Element(0,400000+i));
	}
	return result;
}


/*
 This function forms the second fully connected convolutional layer.
 Though this could have been implemented much more simply we have maintained the same set of abstractions that were used for
 the first tow convolutional layers.
 
 There are 500 input channels and 10 output channes associated with this layer where each output channel corresponds to one digit.
*/


Matrix **LetNet::FullyConnected2(Matrix **image){
	Matrix **result = new Matrix*[10];
	Matrix C("fc2.txt",1,5010);
	float *ptr=C.get_Matrix();
	convolution conv;
	for(int i=0;i<10;i++){
		Matrix R(ptr+(i*500),1);
		result[i]=conv.conv_mult_withoutpadding(*(image[0]),R);
		for(int j=1;j<500;j++){
			Matrix kernel(ptr+(i*500)+j,1);
			Matrix *S=conv.conv_mult_withoutpadding(*(image[j]),kernel);
			result[i]->add_matrix(*S);
		}
		result[i]->add_bias(C.get_Element(0,5000+i));
	}
	return result;
}
