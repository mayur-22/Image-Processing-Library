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
    matrix=nullptr;
}

Matrix::Matrix(const Matrix &A){
    vec=A.vec;
    matrix=A.matrix;
    num_rows=A.num_rows;
    num_columns=A.num_columns;
}

Matrix::Matrix(vector<float> v){
    num_rows=0;
    num_columns=0;
    vec=v;
}

Matrix::Matrix(int size,int rows,int columns){
    matrix=new float[size];
    num_rows=rows;
    num_columns=columns;
}

Matrix::Matrix(int size,int rows){
    matrix=new float[size];
    num_rows=rows;
    num_columns=rows;
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
    matrix=nullptr;
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
        num_rows=vec.size();
        num_columns=1;
    }
}

Matrix::~Matrix() {
    if(matrix!=nullptr)
        delete matrix;
}

void Matrix::print_matrix(){
    for(int i=0;i<num_columns;i++){
     for(int j=0;j<num_rows;j++)
         cout<<matrix[i*num_rows+num_columns]<<" ";
     cout<<endl;
    }
}

void Matrix::set_Matrix(float* ptr){
    matrix=ptr;
}
inline void Matrix::add_Element(float x,int i,int j){
    matrix[i*num_rows+j]=x;
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

int Matrix::get_sizeofrow(){
    return num_rows;
}

int Matrix::get_sizeofcolumn(){
    return num_columns;
}