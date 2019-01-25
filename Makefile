# CXXFLAGS = -Wall -g -I~/intel/mkl/include
# PATH = -L~/intel/mkl/lib/intel64 -Wl,--no-as-needed ~/intel/mkl/lib/intel64/libmkl_scalapack_lp64.a ~/intel/mkl/lib/intel64/libmkl_intel_lp64.a ~/intel/mkl/lib/intel64/libmkl_gnu_thread.a ~/intel/mkl/lib/intel64/libmkl_core.a ~/intel/mkl/lib/intel64/libmkl_blacs_intelmpi_lp64.a -lgomp -lpthread -lm -ldl

# main : main.o DtException.o convolution.o Matrix.o Tanh.o pooling.o softmax.o sigmoid.o RElu.o
# 	g++	 main.o DtException.o convolution.o Matrix.o Tanh.o pooling.o softmax.o sigmoid.o RElu.o -o main -Wall -g 

# main.o: main.cpp DtException.h Matrix.h tanh.h softmax.h pooling.h convolution.h
# 	g++ -c main.cpp -m64 $(CXXFLAGS) $(PATH) -o $@

# DtException.o: DtException.cpp DtException.h
# 	g++ -c DtException.cpp  $(CXXFLAGS) -o $@

# Matrix.o: Matrix.cpp Matrix.h
# 	g++ -c Matrix.cpp  $(CXXFLAGS) -o $@

# Tanh.o : Tanh.cpp tanh.h
# 	g++ -c Tanh.cpp  $(CXXFLAGS) -o $@

# RElu.o: RElu.cpp RElu.h
# 	g++ -c RElu.cpp  $(CXXFLAGS) -o $@

# convolution.o: convolution.cpp convolution.h 
# 	g++ -c convolution.cpp -m64 $(CXXFLAGS) $(PATH) -o $@

# softmax.o : softmax.cpp softmax.h
# 	g++ -c softmax.cpp  $(CXXFLAGS) -o $@

# sigmoid.o: sigmoid.cpp sigmoid.h
# 	g++ -c sigmoid.cpp  $(CXXFLAGS) -o $@

# pooling.o: pooling.cpp pooling.h
# 	g++ -c pooling.cpp  $(CXXFLAGS) -o $@




CXX = g++ -pthread 
CXXFLAGS = -g -m64 -I ~/intel/mkl/include -L~/intel/mkl/lib/intel64 -Wl,--no-as-needed ~/intel/mkl/lib/intel64/libmkl_scalapack_lp64.a ~/intel/mkl/lib/intel64/libmkl_intel_lp64.a ~/intel/mkl/lib/intel64/libmkl_gnu_thread.a ~/intel/mkl/lib/intel64/libmkl_core.a ~/intel/mkl/lib/intel64/libmkl_blacs_intelmpi_lp64.a -lgomp -lpthread -lm -ldl


main: main.o DtException.o convolution.o Matrix.o Tanh.o pooling.o softmax.o sigmoid.o RElu.o 
	$(CXX) $(CXXFLAGS) -o main main.o DtException.o convolution.o Matrix.o Tanh.o pooling.o softmax.o sigmoid.o RElu.o -m64 -I ~/intel/mkl/include -L~/intel/mkl/lib/intel64 -Wl,--no-as-needed ~/intel/mkl/lib/intel64/libmkl_scalapack_lp64.a ~/intel/mkl/lib/intel64/libmkl_intel_lp64.a ~/intel/mkl/lib/intel64/libmkl_gnu_thread.a ~/intel/mkl/lib/intel64/libmkl_core.a ~/intel/mkl/lib/intel64/libmkl_blacs_intelmpi_lp64.a -lgomp -lpthread -lm -ldl

main.o: DtException.h Matrix.h tanh.h softmax.h pooling.h convolution.h

DtException.o: DtException.h

Matrix.o: Matrix.h

Tanh.o : tanh.h

RElu.o: RElu.h

convolution.o: convolution.h 

softmax.o : softmax.h

sigmoid.o: sigmoid.h

pooling.o: pooling.h
