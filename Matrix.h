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
    float *get_Matrix();
    std::vector<float> get_Vec();
    Matrix mult_matrix(Matrix &A,Matrix &B);
    inline float get_Element(int x,int y);
    inline float get_Element(int x);
    inline void add_Element(float x,int i,int j);
    inline int get_sizeofrow();
    inline int get_sizeofcolumn();
    virtual ~Matrix();
private:
    std::vector<float> vec;
    float *matrix;
    int num_rows;
    int num_columns;
};

#endif /* MATRIX_H */

