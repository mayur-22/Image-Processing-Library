/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   newmain.cpp
 * Author: mohd.kamal asraf
 *
 * Created on 9 January, 2019, 9:45 PM
 */
#include "iostream"
#include "string"
#include "Matrix.h"
#include "DtException.h"
#include "RElu.h"
#include "tanh.h"
#include "softmax.h"
#include "sigmoid.h"
#include "cstring"
#include "pooling.h"
#include "convolution.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    if(strcmp(argv[1],"ReLU")==0){
        if(argc==4){
            try{
            Matrix A(argv[2],atoi(argv[3]));
            RElu relu_activate;
            Matrix B(relu_activate.Relu_mat(A));
            B.print_matrix();
            }catch(DtException& e){
                e.getMessage();
                cout<<e.what()<<"\n--Matrix cannot be read--\n";
            }
            catch(exception& e){
                cout<<"Standard Exception: "<<e.what()<<endl;
            }
        }
        else if (argc==5){
            try{
            Matrix A(argv[2],std::atoi(argv[3]),atoi(argv[4]));
            RElu relu_activate;
            Matrix B(relu_activate.Relu_mat(A));
            B.print_matrix();
            }catch(DtException& e){
                e.getMessage();
                cout<<e.what()<<"\n--Matrix cannot be read--\n";
            }
            catch(exception& e){
                cout<<"Standard Exception: "<<e.what()<<endl;
            }
        }
        else{
            cout<<"Inavlid command\nCommand line form for ReLU is: \n--for square matrices of dimension dim\n"
                <<"./main.o ReLU matFileName  num_rows\n"
                <<"--for other matrices of any dimension\n"
                <<"./main.o ReLU matFileName num_rows num_columns\n";
        }
    }
    else if(strcmp(argv[1],"tanh")==0){
        if(argc==4){
            try{
            Tanh tanh_activate;
            Matrix A(argv[2],atoi(argv[3]));
            Matrix B(tanh_activate.Tanh_mat(A));
            B.print_matrix();
            }catch(DtException& e){
                e.getMessage();
                cout<<e.what()<<"\n--Matrix cannot be read--\n";
            }
            catch(exception& e){
                cout<<"Standard Exception: "<<e.what()<<endl;
            }
        }
        else if (argc==5){
            try{
            Tanh tanh_activate;
            Matrix A(argv[2],atoi(argv[3]),atoi(argv[4]));
            Matrix B(tanh_activate.Tanh_mat(A));
            B.print_matrix();
            }catch(DtException& e){
                e.getMessage();
                cout<<e.what()<<"\n--Matrix cannot be read--\n";
            }
            catch(exception& e){
                cout<<"Standard Exception: "<<e.what()<<endl;
            }
        }
        else{
            cout<<"Inavlid command\nCommand line form for tanh is: \n--for square matrices of dimension dim\n"
                <<"./main.o tanh matFileName  num_rows\n"
                <<"--for other matrices of any dimension\n"
                <<"./main.o tanh matFileName num_rows num_columns\n";
        }
    }
    else if(strcmp(argv[1],"softmax")==0){
        if(argc==3){
            try{
            Matrix A(argv[2]);
            softmax s;
            Matrix B(s.soft_max(A.get_Vec()));
            }catch(DtException& e){
                e.getMessage();
                cout<<e.what()<<"\n--Vector cannot be read--\n";
            }
            catch(exception& e){
                cout<<"Standard Exception: "<<e.what()<<endl;
            }
        }
        else{
            cout<<"Invalid command\nCommand line form for softmax should be:\n"
                <<"./main.o softmax vecFileName\n";
            
        }
    }
    else if(strcmp(argv[1],"sigmoid")==0){
        try{
        if(argc==3){
            
            Matrix A(argv[2]);
            sigmoid s;
            Matrix B(s.sig_moid(A.get_Vec()));
            
        }
        else{
            cerr<<"Invalid command\nCommand line form for sigmoid should be:\n"
                "./main.o sigmoid vecFileName\n";
            
        }
        
        }catch(DtException& e){
                e.getMessage();
                cout<<e.what()<<"\n--Matrix cannot be read--\n";
            }
            catch(exception& e){
                cout<<"Standard Exception: "<<e.what()<<endl;
            }
    }
    else if(strcmp(argv[1],"max_pool")==0){
        try{
        if(argc==6){
            Matrix A(argv[2],atoi(argv[3]));
            pooling pool_red;
            Matrix C(pool_red.max_pooling(A,atoi(argv[4]),atoi(argv[5])));
            C.print_matrix();
            
        }
        else if(argc==6){
            
            Matrix A(argv[2],atoi(argv[3]));
            pooling pool_red;
            Matrix C(pool_red.max_pooling(A,atoi(argv[4])));
            C.print_matrix();
        }
        else{
            cout<<"Invalid command"
                <<"#for maxpooling with given stride command line should be as follows assuming square matrices\n"
                <<"./main.o max_pool data_Matrix_File data_Matrix_Size kernel_Size stride\n"
                <<"--for default stride(equal to kernel order)\n"
                <<"./main.o max_pool data_Matrix_File data_Matrix_Size kernel_Size\n";
        }
        }catch(DtException& e){
                e.getMessage();
                cout<<e.what()<<"\n--Matrix cannot be read--\n";
            }
            catch(exception& e){
                cout<<"Standard Exception: "<<e.what()<<endl;
            }
    }
    else if(strcmp(argv[1],"average_pool")==0){
        try{
        if(argc==6){
            Matrix A(argv[2],atoi(argv[3]));
            pooling pool_red;
            Matrix C(pool_red.average_pooling(A,atoi(argv[4]),atoi(argv[5])));
            C.print_matrix();
        }
        else if(argc==5){
            Matrix A(argv[2],atoi(argv[3]));
            Matrix B(argv[4],atoi(argv[5]));
            pooling pool_red;
            Matrix C(pool_red.average_pooling(A,atoi(argv[4])));
            C.print_matrix();
        }
        else{
            cout<<"Invalid command\n"
                <<"#for averagepooling with given stride command line should be as follows assuming square matrices\n"
                <<"./main.o average_pool data_Matrix_File data_Matrix_Size kernel_Size stride\n"
                <<"--for default stride(equal to kernel order)\n"
                <<"./main.o average_pool data_Matrix_File data_Matrix_Size kernel_Size\n";
        }
        }catch(DtException& e){
                cout<<e.what()<<"\n--Matrix cannot be read--\n";
            }
            catch(exception& e){
                cout<<"Standard Exception: "<<e.what()<<endl;
            }
    }
    else if(strcmp(argv[1],"convolution_without_padding")==0){
        if(argc==6){
            Matrix A(argv[2],stoi(argv[3]));
            Matrix B(argv[4],stoi(argv[5]));
            convolution conv;
            Matrix C(conv.conv_withoutpadding(A,B));
            C.print_matrix();
        }
        else{
            cout<<"Invalid command\n"
                <<"#convolution without padding--(without flipping the kernel and assuming square input matrices)\n"
                <<"./main.o convolution_without_padding data_Matrix_File data_Matrix_Size kernel_Matrix_File kernel_Matrix_Size\n";
        }
    }
    else if(strcmp(argv[1],"convolution_with_padding")==0){
        if(argc==6){
            Matrix A(argv[2],stoi(argv[3]));
            Matrix B(argv[4],stoi(argv[5]));
            convolution conv;
            Matrix C(conv.conv_withpadding(A,B));
            C.print_matrix();
        }
        else{
            cout<<"Invalid command\n"
                <<"#convolution with padding--(without flipping the kernel and assuming square input matrices)\n"
                <<"./main.o convolution_with_padding data_Matrix_File data_Matrix_Size kernel_Matrix_File kernel_Matrix_Size\n";
        }
    }
    else if(strcmp(argv[1],"convolution_as_matrix_multiplication_without_padding")==0){
        
    }
    else if(strcmp(argv[1],"convolution_as_matrix_multiplication_without_padding")==0){
        
    }
    else{
        
    }
    
    return 0;
}

