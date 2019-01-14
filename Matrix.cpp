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
#include "DtException.h"


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
        throw DtException("File not found");
    }
    else{
        matrix=new float[rows*rows];
        num_rows=num_columns=rows;
        string str;
        float x;
        for(int i=0;i<rows;i++){
            getline(infile,str);
            stringstream fstr(str);
            for(int j=0;j<rows;j++){
                fstr>>x;
                matrix[j*rows+i]=x;
            }
        }
    }
    infile.close();
}

Matrix::Matrix(vector <float> v){
    vec=v;
    num_rows=v.size();
    num_columns=1;
    matrix=nullptr;
}
Matrix::Matrix(float *ptr,int rows){
    matrix=ptr;
    num_rows=num_columns=rows;
}

Matrix::Matrix(float *ptr,int rows,int columns){
    matrix=ptr;
    num_rows=rows;
    num_columns=columns;
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
    int x=0;
    if(matrix!=nullptr)
        for(int i=0;i<num_columns;i++){
            for(int j=0;j<num_rows;j++)
                cout<<matrix[x++]<<" ";
                cout<<endl;
        }
    else{
        for(int i=0;i<vec.size();i++){
            cout<<vec[i]<<" ";
        }
    }
}

void Matrix::set_Matrix(float* ptr){
    matrix=ptr;
}
inline void Matrix::add_Element(float x,int i,int j){
    matrix[i*num_rows+j]=x;
}
float Matrix::get_Element(int x, int y){
    return matrix[x*num_columns+y];
}

float Matrix::get_Element(int x, int y,bool exc){
    if(x>=num_rows||y>=num_columns||x<0||y<0){
        if(exc)
            throw "Illegal matrix access";
        else
            return 0;
    }
    return matrix[x*num_rows+y];
}


float Matrix::get_Element(int x){
    if(matrix==nullptr)
        return vec[x];
    return matrix[x];
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

Matrix Matrix::mult_matrix(Matrix& A, Matrix& B){
    float *ptr1=A.get_Matrix();
    int r1=A.get_sizeofrow();
    int c1=A.get_sizeofcolumn();
    float *ptr2=B.get_Matrix();
    int r2=B.get_sizeofrow();
    int c2=B.get_sizeofcolumn();
    if(c1!=r2)
        throw "Matrices incompatible for multiplication";
    float *result=new float[r1*c2];
    float *r=result;
    /*for(int i=0;i<r1;i++)
        ptr1=A.get_Matrix()+i;
        for(int j=0;j<c1;j++){
            ptr2=B.get_Matrix()+j*r2;
            *r=0;
            for(int k=0;k<c1;k++){
                (*r)+=(*(ptr2++))*(*ptr1);
                ptr1+=c1;
                r++;
            }
            
        }   */
    int inc=0;
    for(int i=0;i<r1;i++)
        for(int j=0;j<c2;j++){
            result[inc]=0;
            for(int k=0;k<c1;k++)
                result[inc]+=(A.get_Element(i,k))*(B.get_Element(k,j));
            inc++;
        }
    Matrix ret(result,r1,c2);
    return ret;
    
}