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
    Matrix(int size,int rows,int columns);
    Matrix(int size,int rows);
    Matrix(float *ptr,int rows);
    Matrix(float *ptr,int rows,int columns);
    Matrix(std:: vector<float> v);
    Matrix(const Matrix &A);
    float *get_Matrix();
    void set_Matrix(float *ptr);
    std::vector<float> get_Vec();
    Matrix mult_matrix(Matrix &A,Matrix &B);
    void print_matrix();
    float get_Element(int x,int y);
    float get_Element(int x, int y,bool exc);
    float get_Element(int x);
    void add_Element(float x,int i,int j);
    int get_sizeofrow();
    int get_sizeofcolumn();
    virtual ~Matrix();
private:
    std::vector<float> vec;
    float *matrix;
    int num_rows;
    int num_columns;
};

#endif /* MATRIX_H */

