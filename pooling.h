/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   pooling.h
 * Author: mohd.kamal asraf
 *
 * Created on 13 January, 2019, 1:09 PM
 */

#ifndef POOLING_H
#define POOLING_H
#include "Matrix.h"


	Matrix *max_pooling(Matrix&,int,int =0);
	Matrix *average_pooling(Matrix&,int,int =0);
	



#endif /* POOLING_H */