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

class Matrix {
    
public:
    Matrix();
    Matrix(char *file_name,int rows,int columns);
    Matrix(char *file_name,int rows);
    Matrix(const Matrix& orig);
    float *get_Data();
    virtual ~Matrix();
private:
    float *matrix;
};

#endif /* MATRIX_H */

