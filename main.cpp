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
#include <chrono>
#include "string"
#include "Matrix.h"
#include "DtException.h"
#include "tanh.h"
#include "softmax.h"
#include "cstring"
#include "pooling.h"
#include "convolution.h"
#include <cstdlib>
#include <pthread.h>
#include "mkl.h"
#include "RElu.h"
#include "LetNet.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    if(argc<=2){
        cout<<"Invalid command line\n Refer to ReadMe file for instructions\n";
    }

    else if(strcmp(argv[1],"Recognise_digit")==0){
        LetNet obj;
        Matrix A(argv[2],28,true);
        // A.print_matrix();
        Matrix **B = obj.Convolution1(A);
        // B[0]->print_matrix();
        obj.Pool1(B);
        // B[0]->print_matrix();
        Matrix **C = obj.Convolution2(B);
        delete B;
        // C[0]->print_matrix();
        obj.Pool2(C);
        // C[0]->print_matrix();
        Matrix **D = obj.FullyConnected1(C);
        obj.ReluAll(D);
        
        Matrix **Result = obj.FullyConnected2(D);
        // for(int i=0;i<10;i++)
            // Result[i]->print_matrix();
        delete D;
        delete C;
        std::vector<float> v;
        for(int i=0;i<10;i++)
            v.push_back(Result[i]->get_Element(0,0));

        softmax soft;
        Matrix E(soft.soft_max(v));
        std::vector<float> prob_vec = E.get_Vec();
        int array[10] = {0,1,2,3,4,5,6,7,8,9};
        for(int i=0;i<10;i++){
            int start = i;
            for(int j=i+1;j<10;j++)
                if(prob_vec[j]>prob_vec[start])
                    start =j;
            array[i]=start;
            float temp=prob_vec[i];
            prob_vec[i]=prob_vec[start];
            prob_vec[start]=temp;
            
            
        }

        for(int i=0;i<5;i++){
            cout<<"Digit "<<array[i]<<" : "<<prob_vec[i]<<endl;
        }
        
        
        

    }
    
    else if(strcmp(argv[1],"ReLU")==0){
        if(argc==4){
            try{
            Matrix A(argv[2],atoi(argv[3]));
            Matrix *B=Relu_mat(A);
            B->print_matrix();
            delete B;
            }catch(DtException& e){
                e.getMessage();
                cout<<"\n--Matrix cannot be read--\n";
            }
            catch(exception& e){
                cout<<"Standard Exception: "<<endl;
            }
        }
        else if (argc==5){
            try{
            Matrix A(argv[2],atoi(argv[3]));
            Matrix *B=Relu_mat(A);
            B->print_matrix();
            delete B;
            }catch(DtException& e){
                e.getMessage();
                cout<<"\n--Matrix cannot be read--\n";
            }
            catch(exception& e){
                cout<<"Standard Exception: "<<endl;
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
            Matrix *B=(tanh_activate.Tanh_mat(A));
            B->print_matrix();
            delete B;
            }catch(DtException& e){
                e.getMessage();
                cout<<"\n--Matrix cannot be read--\n";
            }
            catch(exception& e){
                cout<<"Standard Exception: "<<endl;
            }
        }
        else if (argc==5){
            try{
            Tanh tanh_activate;
            Matrix A(argv[2],atoi(argv[3]),atoi(argv[4]));
            Matrix *B=(tanh_activate.Tanh_mat(A));
            B->print_matrix();
            delete B;
            }catch(DtException& e){
                e.getMessage();
                cout<<"\n--Matrix cannot be read--\n";
            }
            catch(exception& e){
                cout<<"Standard Exception: "<<endl;
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
            B.print_matrix();
            }catch(DtException& e){
                e.getMessage();
                cout<<"\n--Vector cannot be read--\n";
            }
            catch(exception& e){
                cout<<"Standard Exception: "<<endl;
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
            B.print_matrix();
            
        }
        else{
            cerr<<"Invalid command\nCommand line form for sigmoid should be:\n"
                "./main.o sigmoid vecFileName\n";
            
        }
        
        }catch(DtException& e){
                e.getMessage();
                cout<<"\n--Vector cannot be read--\n";
            }
            catch(exception& e){
                cout<<"Standard Exception: "<<endl;
            }
    }
    else if(strcmp(argv[1],"max_pool")==0){
        try{
        if(argc==6){
            Matrix A(argv[2],atoi(argv[3]));
            Matrix *C= max_pooling(A,atoi(argv[4]),atoi(argv[5]));
            C->print_matrix();
            delete C;
            
        }
        else if(argc==5){
            
            Matrix A(argv[2],atoi(argv[3]));
            Matrix *C=(max_pooling(A,atoi(argv[4])));
            C->print_matrix();
            delete C;
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
                cout<<"\n--Matrix cannot be read--\n";
            }
            catch(exception& e){
                cout<<"Standard Exception: "<<endl;
            }
    }
    else if(strcmp(argv[1],"average_pool")==0){
        try{
        if(argc==6){
            Matrix A(argv[2],atoi(argv[3]));
            Matrix *C=(average_pooling(A,atoi(argv[4]),atoi(argv[5])));
            C->print_matrix();
            delete C;
        }
        else if(argc==5){
            Matrix A(argv[2],atoi(argv[3]));
            Matrix *C=(average_pooling(A,atoi(argv[4])));
            C->print_matrix();
            delete C;
        }
        else{
            cout<<"Invalid command\n"
                <<"#for averagepooling with given stride command line should be as follows assuming square matrices\n"
                <<"./main.o average_pool data_Matrix_File data_Matrix_Size kernel_Size stride\n"
                <<"--for default stride(equal to kernel order)\n"
                <<"./main.o average_pool data_Matrix_File data_Matrix_Size kernel_Size\n";
        }
        }catch(DtException& e){
                e.getMessage();
                cout<<"\n--Matrix cannot be read--\n";
            }
            catch(exception& e){
                cout<<"Standard Exception: "<<endl;
            }
    }
    else if(strcmp(argv[1],"convolution_without_padding")==0){
        if(argc==6){
            try{
            Matrix A(argv[2],stoi(argv[3]));
            Matrix B(argv[4],stoi(argv[5]));
            convolution conv;
            Matrix C(conv.conv_withoutpadding(A,B));
            C.print_matrix();
            }catch(DtException& e){
                e.getMessage();
                
            }
            catch(exception& e){
                cout<<"Standard Exception: "<<endl;
            }
        }
        else{
            cout<<"Invalid command\n"
                <<"#convolution without padding--(without flipping the kernel and assuming square input matrices)\n"
                <<"./main.o convolution_without_padding data_Matrix_File data_Matrix_Size kernel_Matrix_File kernel_Matrix_Size\n";
        }
    }
    else if(strcmp(argv[1],"convolution_with_padding")==0){
        if(argc==6){
            try{
            Matrix A(argv[2],stoi(argv[3]));
            Matrix B(argv[4],stoi(argv[5]));
            convolution conv;
            Matrix C(conv.conv_withpadding(A,B));
            C.print_matrix();
                }catch(DtException& e){
                e.getMessage();
                
            }
            catch(exception& e){
                cout<<"Standard Exception: "<<endl;
            }
        }
        else{
            cout<<"Invalid command\n"
                <<"#convolution with padding--(without flipping the kernel and assuming square input matrices)\n"
                <<"./main.o convolution_with_padding data_Matrix_File data_Matrix_Size kernel_Matrix_File kernel_Matrix_Size\n";
        }
    }
    else if(strcmp(argv[1],"convolution_as_matrix_multiplication_without_padding")==0){
        if(argc==6){
            try{
            Matrix A(argv[2],stoi(argv[3]));
            Matrix B(argv[4],stoi(argv[5]));
            convolution conv;
            auto start = std::chrono::high_resolution_clock::now();
            Matrix *C=conv.conv_mult_withoutpadding(A,B);
            auto finish = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = finish - start;
            C->print_matrix();
            std::cout << endl<<"Elapsed time: " << elapsed.count()*1000 << endl;
            }catch(DtException& e){
                e.getMessage();
                
            }
            catch(exception& e){
                cout<<"Standard Exception: "<<endl;
            }
        }
        else{
            cout<<"Invalid command\n"
                <<"#convolution as matrix multiplication without padding--(without flipping the kernel and assuming square input matrices)\n"
                <<"./main.o convolution_as_matrix_multiplication_without_padding data_Matrix_File data_Matrix_Size kernel_Matrix_File kernel_Matrix_Size\n";
        }
    }
    else if(strcmp(argv[1],"convolution_pthreads_unpadded")==0){
        if(argc==6){
            try{
            Matrix A(argv[2],stoi(argv[3]));
            Matrix B(argv[4],stoi(argv[5]));
            convolution conv;
            auto start = std::chrono::high_resolution_clock::now();
            Matrix *C=conv.conv_mult_withoutpadding_threaded(A,B);
            auto finish = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = finish - start;
            C->print_matrix();
            std::cout << endl<<"Elapsed time: " << elapsed.count()*1000 << endl;
            }catch(DtException& e){
                e.getMessage();
                
            }
            catch(exception& e){
                cout<<"Standard Exception: "<<endl;
            }
        }
        else{
            cout<<"Invalid command\n"
                <<"For convolution using pthreads library the arguments should be of following form:\n"
                <<"./main convolution_pthreads_unpadded data_Matrix_File data_Matrix_Size kernel_Matrix_File kernel_Matrix_Size\n";
        }
    }
else if(strcmp(argv[1],"convolution_pthreads_padded")==0){
        if(argc==6){
            try{
            Matrix A(argv[2],stoi(argv[3]));
            Matrix B(argv[4],stoi(argv[5]));
            convolution conv;
            auto start = std::chrono::high_resolution_clock::now();
            Matrix *C=conv.conv_mult_withpadding_threaded(A,B);
            auto finish = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = finish - start;
            C->print_matrix();
            std::cout << endl<<"Elapsed time: " << elapsed.count()*1000 << endl;
            }catch(DtException& e){
                e.getMessage();
                
            }
            catch(exception& e){
                cout<<"Standard Exception: "<<endl;
            }
        }
        else{
                        cout<<"Invalid command\n"
                <<"For convolution using pthreads the arguments should be of following form:\n"
                <<"./main convolution_pthreads_padded data_Matrix_File data_Matrix_Size kernel_Matrix_File kernel_Matrix_Size\n";

        }
    }
     else if(strcmp(argv[1],"convolution_mkl_unpadded")==0){
        if(argc==6){
            try{
            Matrix A(argv[2],stoi(argv[3]));
            Matrix B(argv[4],stoi(argv[5]));
            convolution conv;

            auto start = std::chrono::high_resolution_clock::now();
            Matrix* C(conv.mkl_mult(A,B));
            auto finish = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = finish - start;
            C->print_matrix();
            std::cout << endl<<"Elapsed time: " << elapsed.count()*1000 << endl;
            }catch(DtException& e){
                e.getMessage();
                
            }
            catch(exception& e){
                cout<<"Standard Exception: "<<endl;
            }
        }
        else{
            cout<<"Invalid command\n"
                <<"For convolution using MKL library the arguments should be of following form:\n"
                <<"./main convolution_mkl_unpadded data_Matrix_File data_Matrix_Size kernel_Matrix_File kernel_Matrix_Size\n";
        }
    }
    else if(strcmp(argv[1],"convolution_mkl_padded")==0){
        if(argc==6){
            try{
            Matrix A(argv[2],stoi(argv[3]));
            Matrix B(argv[4],stoi(argv[5]));
            convolution conv;
            auto start = std::chrono::high_resolution_clock::now();
            Matrix* C(conv.mkl_mult_padded(A,B));
            auto finish = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = finish - start;
            C->print_matrix();
            std::cout << endl<<"Elapsed time: " << elapsed.count()*1000 << endl;
            }catch(DtException& e){
                e.getMessage();
                
            }
            catch(exception& e){
                cout<<"Standard Exception: "<<endl;
            }
        }
        else{
                        cout<<"Invalid command\n"
                <<"For convolution using MKL library the arguments should be of following form:\n"
                <<"./main convolution_mkl_padded data_Matrix_File data_Matrix_Size kernel_Matrix_File kernel_Matrix_Size\n";

        }
    }
    else if(strcmp(argv[1],"convolution_as_matrix_multiplication_with_padding")==0){
        if(argc==6){
            try{
            Matrix A(argv[2],stoi(argv[3]));
            Matrix B(argv[4],stoi(argv[5]));
            convolution conv;
            auto start = std::chrono::high_resolution_clock::now();
            Matrix *C=conv.conv_mult_withpadding(A,B);
            auto finish = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = finish - start;
            C->print_matrix();
            std::cout << endl<<"Elapsed time: " << elapsed.count()*1000 << endl;
            }catch(DtException& e){
                e.getMessage();
                
            }
            catch(exception& e){
                cout<<"Standard Exception: "<<endl;
            }
        }
        else{
            cout<<"Invalid command\n"
                <<"#convolution as matrix multiplication with padding--(without flipping the kernel and assuming square input matrices)\n"
                <<"./main.o convolution_as_matrix_multiplication_with_padding data_Matrix_File data_Matrix_Size kernel_Matrix_File kernel_Matrix_Size\n";
        }
    }
    else{
        cout<<"Invalid command line\n Refer to ReadMe file for instructions\n";
    }
    
    return 0;
}

