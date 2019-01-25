#include <cblas.h>
#include <stdio.h>
#include "Matrix.h"
#include "DtException.h"
#include "convolution.h"
#include "iostream"
#include <chrono>
#include "string.h"
using namespace std;


int main(int argc, char** argv) {
  
  if(argc==6){
            try{

	if(strcmp(argv[1],"convolution_openblas_unpadded")==0){
            Matrix A(argv[2],stoi(argv[3]));
            Matrix B(argv[4],stoi(argv[5]));
            convolution conv;
            auto start = std::chrono::high_resolution_clock::now();
            Matrix* C(conv.openblas_mult(A,B));
            auto finish = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = finish - start;
            C->print_matrix();
            std::cout << endl<<"Elapsed time: " << elapsed.count()*1000 << endl;
	}
	else if(strcmp(argv[1],"convolution_openblas_padded")==0){
            Matrix A(argv[2],stoi(argv[3]));
            Matrix B(argv[4],stoi(argv[5]));
            convolution conv;
            auto start = std::chrono::high_resolution_clock::now();
            Matrix* C(conv.openblas_mult_padded(A,B));
            auto finish = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = finish - start;
            C->print_matrix();
            std::cout << endl<<"Elapsed time: " << elapsed.count()*1000 << endl;
	}
 	else{

	cout<<"Invalid command\n"
                <<"For convolution using openblas the command line argumnets should be as follows:\n"
                <<"\tFor unpadded: ./main convolution_openblas_unpadded data_Matrix_File data_Matrix_Size kernel_Matrix_File 				kernel_Matrix_Size\n"
		<<"\tFor padded: ./main convolution_openblas_padded data_Matrix_File data_Matrix_Size kernel_Matrix_File 				kernel_Matrix_Size\n";
}

            }catch(DtException& e){
                e.getMessage();
                
            }
            catch(exception& e){
                cout<<"Standard Exception: "<<endl;
            }
        }
        else{
            cout<<"Invalid command line arguments\nRefer to the Readme File for correct format";
        }
  return 0;
}
