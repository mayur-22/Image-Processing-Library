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
#inlcude "Matrix.h"
class tanh {
public:
    tanh();
    float *Tanh_mat(float *mat,int rows,int columns);
    virtual ~tanh();
private:
    Matrix *B;
};

#endif /* TANH_H */

