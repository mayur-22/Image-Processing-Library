
#ifndef TANH_H
#define TANH_H
#include "Matrix.h"
#include <vector>
#include "cmath"

class Tanh {
public:
    Tanh();
    float *Tanh_mat(float *mat,int rows,int columns);
    Matrix *Tanh_mat(Matrix &A);
    virtual ~Tanh();
private:
    float* Tanh_internal(Matrix &A);
};


#endif /* TANH_H */
