/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Matrix.h
 * Author: mohd.kamal asraf
 *
 * Created on 12 January, 2019, 10:40 AM
 */

#ifndef MATRIX_H
#define MATRIX_H
#include "vector"

class Matrix {
    
public:
    Matrix();
    Matrix(char *file_name,int rows,int columns);
    Matrix(char *file_name,int rows);
    Matrix(char *file_name);
    std::vector<std::vector<float>> get_Matrix();
    std::vector<float> get_Vec();
    Matrix mult_matrix(Matrix &A,Matrix &B);
    inline float get_Element(int x,int y);
    inline float get_Element(int x);
    virtual ~Matrix();
private:
    std::vector<float> vec;
    std::vector<std::vector<float>> matrix;
};

#endif /* MATRIX_H */

