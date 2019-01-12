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
#include "vector"
#include "string"
#include "sstream"

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
        num_rows=rows;
        num_columns=columns;
        matrix=new float[rows*columns];
        string str;
        float x;
        for(int i=0;i<columns;i++){
            getline(infile,str);
            stringstream fstr(str);
            for(int j=0;j<rows;j++){
                fstr>>x;
                matrix[i*rows+j]=x;
            }
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
        string str;
        float x;
        for(int i=0;i<rows;i++){
            getline(infile,str);
            stringstream fstr(str);
            for(int j=0;j<rows;j++){
                fstr>>x;
                matrix[i*rows+j]=x;
            }
        }
    }
    infile.close();
}



Matrix::Matrix(char *file_name) {
    ifstream infile;
    infile.open(file_name,ios::binary|ios::in);
    num_rows=num_columns=0;
    if(!infile){
        throw "File not found";
    }
    else{
        float x;
        while(!infile.eof()){
            infile>>x; 
            vec.push_back(x);
        }
        infile.close();
    }
}

Matrix::~Matrix() {
    
}

float Matrix::get_Element(int x, int y){
    return matrix[x*num_rows+y];
}

float Matrix::get_Element(int x){
    return vec[x];
}

float *Matrix::get_Matrix(){
    return this->matrix;
}

vector<float> Matrix::get_Vec(){
    return this->vec;
}

