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
#include "string"

using namespace std;
class DtException : public exception{
public:
    string message;
    DtException();
    DtException(string);
    const char * what () const throw ();
    void getMessage();
private:

};

#endif /* DTEXCEPTION_H */

