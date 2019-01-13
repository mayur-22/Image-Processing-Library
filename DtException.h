/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DtException.h
 * Author: mohd.kamal asraf
 *
 * Created on 12 January, 2019, 3:17 PM
 */

#ifndef DTEXCEPTION_H
#define DTEXCEPTION_H
#include "exception"
using namespace std;
class DtException : public exception{
public:
    char *message;
    DtException();
    DtException(char *);
    const char * what () const throw ();
    void getMessage();
private:

};

#endif /* DTEXCEPTION_H */

