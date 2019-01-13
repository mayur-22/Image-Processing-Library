/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   tanh.h
 * Author: mohd.kamal asraf
 *
 * Created on 13 January, 2019, 10:43 AM
 */

#ifndef TANH_H
#define TANH_H
#include "Matrix.h"
#include "cmath"
class Tanh {
public:
    Tanh();
    float *Tanh_mat(float *mat,int rows,int columns);
    Matrix Tanh_mat(Matrix &A);
    virtual ~Tanh();
private:
    float* Tanh_internal(Matrix &A);
};

#endif /* TANH_H */

