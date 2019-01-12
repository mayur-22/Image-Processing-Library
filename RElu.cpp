/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RElu.cpp
 * Author: mohd.kamal asraf
 * 
 * Created on 12 January, 2019, 9:21 AM
 */

#include "RElu.h"
#include "cmath"
#include "vector"

RElu::RElu() {
}

float *RElu::Relu_vec(float *input,int rows, int columns){
    float *ret=new float[columns*rows];
    float *r=ret;
    int lim=columns*rows;
    for(int i=0;i<lim;i++)
        *(ret++)=*(input+i);
    return ret;
}

vector<float> RElu::Relu(vector<float> input){
    vector<float> rest;
    vector<float>::iterator iter;
    for(iter=input.begin();iter<input.end();iter++)
        if(*iter<0)
            rest.push_back(0);
        else
            rest.push_back(*iter);
    return rest;
}

