/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RElu.h
 * Author: mohd.kamal asraf
 *
 * Created on 12 January, 2019, 9:21 AM
 */

#ifndef RELU_H
#define RELU_H
#include <vector>
#include "Matrix.h"

class RElu {
public:
    RElu();
    //float *Relu_vec(float *,int,int);
    //float *Relu_vec(float *input,int rows);
    float * Relu_mat(Matrix &A);
    std::vector <float> Relu(std::vector <float>);
    
private:  
    
};

#endif /* RELU_H */

