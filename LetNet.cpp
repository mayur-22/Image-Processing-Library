
#include "Matrix.h"
#include "convolution.h"
#include "pooling.h"
#include "RElu.h"
#include "LetNet.h"

LetNet::LetNet(){
    
}

LetNet::~LetNet(){
    
}


Matrix ** LetNet::Convolution1(Matrix &image){
	Matrix **result = new Matrix*[20];
	Matrix C("conv1.txt",1,520);
	float *ptr=C.get_Matrix();
	convolution conv;
	for(int i=0;i<20;i++){
		Matrix R((ptr+(i*25)),5);
		// R.print_matrix();
		// image.print_matrix();
		result[i] = conv.conv_mult_withoutpadding(image,R);
		// result[i]->print_matrix();
		int x = result[i]->get_sizeofrow();
		int y = result[i]->get_sizeofcolumn();
		result[i]->add_bias(C.get_Element(0,500+i));
		// result[i]->print_matrix();
	}
	return result;
}

void LetNet::Pool1(Matrix **inputchannels){
	for(int i=0;i<20;i++){
			// inputchannels[i]->print_matrix();
			int n=inputchannels[i]->get_sizeofcolumn();
			inputchannels[i] = max_pooling(*(inputchannels[i]),2,2);
			// inputchannels[i]->print_matrix();
		}

}

Matrix **LetNet::Convolution2(Matrix **image){
	Matrix **result = new Matrix*[50];
	Matrix C("conv2.txt",1,25050);
	float *ptr=C.get_Matrix();
	convolution conv;
	for(int i=0;i<50;i++){
		Matrix R(ptr+(i*500),5);
		// image[0]->print_matrix();
		result[i]=conv.conv_mult_withoutpadding(*(image[0]),R);
		for(int j=1;j<20;j++){
			Matrix kernel(ptr+(i*500)+(j*25),5);
			Matrix *S=conv.conv_mult_withoutpadding(*(image[j]),kernel);
			// result[i]->print_matrix();
			(result[i])->add_matrix(*S);
		}
		// result[i]->print_matrix();
		result[i]->add_bias(C.get_Element(0,25000+i));

	}
	int x =result[0]->get_sizeofrow();
	return result;
}


void LetNet::Pool2(Matrix **inputchannels){
	for(int i=0;i<50;i++){
			inputchannels[i] = max_pooling(*(inputchannels[i]),2,2);
		}

}

void LetNet::ReluAll(Matrix **inputchannels){
	for(int i=0;i<500;i++){
			inputchannels[i] = Relu_mat(*(inputchannels[i]));
		}
}

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
			// kernel.print_matrix();
			// image[j]->print_matrix();
			Matrix *S=conv.conv_mult_withoutpadding(*(image[j]),kernel);
			//S->print_matrix();
			result[i]->add_matrix(*S);
		}
		result[i]->add_bias(C.get_Element(0,5000+i));
		// result[i]->print_matrix();
	}
	return result;
}