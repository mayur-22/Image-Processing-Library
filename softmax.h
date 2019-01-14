/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   softmax.h
 * Author: mohd.kamal asraf
 *
 * Created on 13 January, 2019, 11:01 AM
 */

#ifndef SOFTMAX_H
#define SOFTMAX_H
#include <vector>
#include "Matrix.h"

class softmax
 {
 public:
 	softmax();
 	~softmax();
 	Matrix soft_max(std::vector<float> v);
 	
 }; 



#endif /* SOFTMAX_H */

