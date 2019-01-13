/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
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
    message=errmsg;
}
const char *DtException:: what () const throw () {
      return "Data Error";
   }
void DtException::getMessage () {
    cout<<message;
   }


