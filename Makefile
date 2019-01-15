
CXX = g++
CXXFLAGS = -Wall -g


main: main.o DtException.o Matrix.o Tanh.o pooling.o convolution.o softmax.o sigmoid.o RElu.o
	$(CXX) $(CXXFLAGS) -o main main.o DtException.o Matrix.o Tanh.o pooling.o convolution.o softmax.o sigmoid.o RElu.o

main.o: DtException.h Matrix.h tanh.h softmax.h pooling.h convolution.h

DtException.o: DtException.h

Matrix.o: Matrix.h

Tanh.o : tanh.h

RElu.o: tanh.h

convolution.o: convolution.h

softmax.o : softmax.h

sigmoid.o: softmax.h

pooling.o: pooling.h
