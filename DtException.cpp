/*
 * This is an exception class defined for catching the exceptions when unable to open the files or some other errors.
 */

/* 
 * File:   DtException.cpp
 * Author: mohd.kamal asraf
 * 
 * Created on 12 January, 2019, 3:17 PM
 */

#include "DtException.h"
#include "iostream"
#include "exception"
#include "string"
DtException::DtException() {
}

DtException::DtException(string errmsg) {
    file_n="";
    message=errmsg;
}

DtException::DtException(string errmsg,char *filename) {
    file_n=filename;
    message=errmsg;
}
const char *DtException:: what () const throw () {
      return "Data Error";
   }
void DtException::getMessage () {
    cout<<message<<" "<<file_n;
   }


