/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   sigmoid.h
 * Author: mohd.kamal asraf
 *
 * Created on 13 January, 2019, 11:05 AM
 */

#ifndef SIGMOID_H
#define SIGMOID_H
#include <vector>

class sigmoid
{
public:
	sigmoid();
	~sigmoid();

	std::vector<float> sig_moid(std::vector<float> v);
	
};


#endif /* SIGMOID_H */

