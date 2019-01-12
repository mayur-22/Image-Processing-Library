/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Matrix.cpp
 * Author: mohd.kamal asraf
 * 
 * Created on 12 January, 2019, 10:40 AM
 */

#include "Matrix.h"
#include "fstream"
#include "iostream"
using namespace std;

Matrix::Matrix() {
}

Matrix::Matrix(char* file_name, int rows, int columns){
    ifstream infile;
    infile.open(file_name,ios::binary|ios::in);
    if(!infile){
        throw "File not found";
    }
    else{
        matrix=new float[columns*rows];
        float *ele=matrix;
        while(!infile.eof()){
            infile>>*(ele++);
        }
    }
    infile.close();
    
}

Matrix::Matrix(char* file_name, int rows){
    ifstream infile;
    infile.open(file_name,ios::binary|ios::in);
    if(!infile){
        throw "File not found";
    }
    else{
        matrix=new float[rows*rows];
        float *ele=matrix;
        while(!infile.eof()){
            infile>>*(ele++);
        }
        infile.close();
    }
}


Matrix::Matrix(const Matrix& orig) {
}

Matrix::~Matrix() {
    delete matrix;
}

float *Matrix::get_Data(){
    return this->matrix;
}
