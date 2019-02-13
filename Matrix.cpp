/*
 * The Matrix class has been defined to encapsulate all the matrix and vector operations. 
 * This class includes all the methods for reading matrices and vectors from files, storing the data as standard C++ vectors for vector
 * data and contiguous array for matrices,printing the data to console output in row-major format, data manipulation functions and accessor
 * fucntions.
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
    num_rows=num_columns=0;
}

//copy constructor
Matrix::Matrix(const Matrix &A){
    vec=A.vec;
    matrix=A.matrix;
    num_rows=A.num_rows;
    num_columns=A.num_columns;
}


//constructor for creating an empty matrix with given rows and columns
Matrix::Matrix(int size,int rows,int columns){
    matrix=new float[size];
    num_rows=rows;
    num_columns=columns;
}

//constructor for creating empty square matrix
Matrix::Matrix(int size,int rows){
    matrix=new float[size];
    num_rows=rows;
    num_columns=rows;
}

/*
 * This constructor reads data from file file_name and 
 * stores as a matrix with given values of rows and columns in a row-major format.
*/
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
            for(int j=0;j<rows;j++){
                infile>>x;
                matrix[i*rows+j]=x;
            }
        }
    }
    infile.close();  
}

/*
  * This constructor reads data from file file_name and 
  * stores as a square matrix with given order.
*/
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
           for(int j=0;j<rows;j++){
                infile>>x;
                matrix[j*rows+i]=x;
            }
        }
    }
    infile.close();
}


Matrix::Matrix(char* file_name, int rows,bool t){
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
           for(int j=0;j<rows;j++){
                infile>>x;
                matrix[i*rows+j]=1-(x/255);
            }
        }
    }
    infile.close();
}

//stores the input as a vector taken from the parameter 
Matrix::Matrix(vector <float> v){
    vec=v;
    num_rows=v.size();
    num_columns=1;
    matrix=nullptr;
}

//stores the data pointed by ptr as a suqare matrix of order rows assuming data to be row-major.
Matrix::Matrix(float *ptr,int rows){
    matrix=ptr;
    num_rows=num_columns=rows;
}

//stores the data pointed by ptr as a matrix with given rows and columns assuming data to be row-major.
Matrix::Matrix(float *ptr,int rows,int columns){
    matrix=ptr;
    num_rows=rows;
    num_columns=columns;
}

//redas file file_name and stores the data as a vector
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

//Destructor function
Matrix::~Matrix() {
    //if(matrix!=nullptr)
      //  delete matrix;
}

/*
 * Function for printing the data to console output
 * vectors--prints each value in one line
 * matrices--prints in row-major order with each line containing values from one row separated by spaces
*/
  
void Matrix::print_matrix(){
    int x=0;
    if(matrix!=nullptr){
        for(int i=0;i<num_columns;i++){
            for(int j=0;j<num_rows;j++)
                cout<<matrix[x++]<<" ";
            cout<<endl;
        }
    }
    else{
        for(long long unsigned int i=0;i<vec.size();i++){
            cout<<vec[i]<<" ";
        }
    }
}

void Matrix::set_Matrix(float* ptr){
    matrix=ptr;
}


inline void Matrix::add_Element(float x,int i,int j){
    matrix[i*num_columns+j]=x;
}

//Returns element stored at x-th row and y-th column in the matrix without any check
float Matrix::get_Element(int x, int y){
    return matrix[x*num_columns+y];
}

/*
 * Returns element stored at x-th row and y-th column in the matrix
 * --if exc is true : exception is thrown for out of bounds access
 * --if exc is false : returns 0 when out of bounds access
*/
float Matrix::get_Element(int x, int y,bool exc){
    if(x>=num_rows||y>=num_columns||x<0||y<0){
        if(exc)
            throw "Illegal matrix access";
        else
            return 0;
    }
    return matrix[x*num_columns+y];
}

// returns x-th entry in the vector or the matrix (row-major)
float Matrix::get_Element(int x){
    if(matrix==nullptr)
        return vec[x];
    return matrix[x];
}

//returns the pointer to matrix
float *Matrix::get_Matrix(){
    return this->matrix;
}

//returns the vector data
vector<float> Matrix::get_Vec(){
    return this->vec;
}

//returns the number row of matrix or the number of elements in the vector
int Matrix::get_sizeofrow(){
    return num_rows;
}

//returns the number of columns
int Matrix::get_sizeofcolumn(){
    return num_columns;
}

//simple multiplication of matrices A and B
Matrix *Matrix::mult_matrix(Matrix& A, Matrix& B){

    int r1=A.get_sizeofrow();
    int c1=A.get_sizeofcolumn();

    int r2=B.get_sizeofrow();
    int c2=B.get_sizeofcolumn();
    if(c1!=r2)
        throw DtException("Matrices incompatible for multiplication");
    float *result=new float[r1*c2];
    int inc=0;
    for(int i=0;i<r1;i++)
        for(int j=0;j<c2;j++){
            result[inc]=0;
            for(int k=0;k<c1;k++)
                result[inc]+=(A.get_Element(i,k))*(B.get_Element(k,j));
            inc++;
        }
    Matrix *ret=new Matrix(result,r1,c2);
    return ret;
    
}



void Matrix::add_bias(float bias){
    matrix[num_rows*num_columns];
    for(int i=0;i<num_rows*num_columns;i++){
        matrix[i]+=bias;
    }
}

void Matrix::add_matrix(Matrix &x){
    float *ptr = x.get_Matrix();
    for(int i=0;i<num_columns*num_rows;i++){
        matrix[i]+=ptr[i];
    }
}