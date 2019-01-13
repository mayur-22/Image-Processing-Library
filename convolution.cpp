/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   convolution.cpp
 * Author: mohd.kamal asraf
 * 
 * Created on 13 January, 2019, 6:47 PM
 */

#include "convolution.h"
#include "Matrix.h"
#include "cmath"
#include "vector"
using namespace std;

convolution::convolution(){
    
}

convolution::~convolution(){
    
}

Matrix convolution::conv_withoutpadding(Matrix &A, Matrix &B){
	std::vector<float> ans;
	int n = A.get_sizeofrow();
	int m = B.get_sizeofrow();
	
	if(m%2==0){			//if m is even
		for (int x = 0; x < n; ++x){
			for (int y = 0; y < n; ++y){
				try{
				int sum = 0.00;
				for (int u = -(m-1)/2; u <= m/2; ++u){
					for (int v = -(m-1)/2; v <= m/2; ++v){
						sum+=A.get_Element(x+u,v+u,true)*B.get_Element(u+(m/2),v+(m/2));
					}
				}
				ans.push_back(sum);
				}
				catch(char *msg){}
			}
		}
	}

	else{
		for (int x = 0; x < n; ++x){
			for (int y = 0; y < n; ++y){
				try{
				int sum = 0.00;
				for (int u = -m/2; u <= (m-1)/2; ++u){
					for (int v = -m/2; v <= (m-1)/2; ++v){
						sum+=A.get_Element(x+u,v+u,true)*B.get_Element(u+(m/2),v+(m/2));
					}
				}
				ans.push_back(sum);
				}
				catch(char *msg){}
			}
		}

	}
        Matrix R(&ans[0],sqrt(ans.size()));
	return R;
}

Matrix convolution::conv_withpadding(Matrix &A, Matrix &B){
	std::vector<float> ans;
	int n = A.get_sizeofrow();
	int m = B.get_sizeofrow();
	
	if(m%2==0){			//if m is even
		for (int x = 0; x < n; ++x){
			for (int y = 0; y < n; ++y){
				int sum = 0.00;
				for (int u = -(m-1)/2; u <= m/2; ++u){
					for (int v = -(m-1)/2; v <= m/2; ++v){
						sum+=A.get_Element(x+u,v+u,false)*B.get_Element(u+(m/2),v+(m/2));
					}
				}
				ans.push_back(sum);
			}
		}
	}

	else{
		for (int x = 0; x < n; ++x){
			for (int y = 0; y < n; ++y){
				int sum = 0.00;
				for (int u = -m/2; u <= (m-1)/2; ++u){
					for (int v = -m/2; v <= (m-1)/2; ++v){
						sum+=A.get_Element(x+u,v+u,false)*B.get_Element(u+(m/2),v+(m/2));
					}
				}
				ans.push_back(sum);
			}
		}

	}
	Matrix R(&ans[0],sqrt(ans.size()));
	return R;
}
