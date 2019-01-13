/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   newmain.cpp
 * Author: mohd.kamal asraf
 *
 * Created on 9 January, 2019, 9:45 PM
 */
#include "iostream"
#include "string"
#include <Matrix.h>
#include <RElu.h>
#include <tanh.h>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    if(strcmp(argv[1],"ReLU")==0){
        if(argc==4){
            Matrix A=Matrix(argv[2],argv[3]);
            RElu relu_activate;
            Matrix B=Matrix(relu_activate.Relu_mat(&A));
        }
        else if (argc==5){
            Matrix A=Matrix(argv[2],argv[3],argv[4]);
            RElu relu_activate;
            Matrix B=Matrix(relu_activate.Relu_mat(&A));
        }
        else{
            cerr<<"Command line form for ReLU is: \n--for square matrices of dimension dim"
                "./main.o ReLU matFileName  num_rows""
                "--for other matrices of any dimension""
                "./main.o ReLU matFileName num_rows num_columns\n";
        }
    }
    else if(strcmp(argv[1],"tanh")==0){
        if(argc==4){
            Matrix A=Matrix(argv[2],argv[3]);
            tanh tanh_activate;
            Matrix B=Matrix(tanh_activate.Tanh_mat(&A));
        }
        else if (argc==5){
            Matrix A=Matrix(argv[2],argv[3],argv[4]);
            tanh tanh_activate;
            Matrix B=Matrix(tanh_activate.Tanh_mat(&A));
        }
        else{
            cerr<<"Command line form for tanh is: \n--for square matrices of dimension dim"
                "./main.o tanh matFileName  num_rows""
                "--for other matrices of any dimension""
                "./main.o tanh matFileName num_rows num_columns\n";
        }
    }
    else if(strcmp(argv[1],"soft_max")==0){
        
    }
    else if(strcmp(argv[1],"sigmoid")==0){
        
    }
    else if(strcmp(argv[1],"max_pooling")==0){
        
    }
    else if(strcmp(argv[1],"average_pooling")==0){
        
    }
    else if(strcmp(argv[1],"convolution_without_padding")==0){
        
    }
    else if(strcmp(argv[1],"convlution_with_padding")==0){
        
    }
    else if(strcmp(argv[1],"convolution_as_matrix_multiplication_without_padding")==0){
        
    }
    else if(strcmp(argv[1],"convolution_as_matrix_multiplication_without_padding")==0){
        
    }
    else{
        
    }
    return 0;
}

