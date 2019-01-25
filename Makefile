CXX = g++ -pthread 
CXXFLAGS = -g -I /home/watson/OpenBLAS/include/ -L/home/watson/OpenBLAS/lib -lopenblas -lpthread -lgfortran


main: main.o DtException.o convolution.o Matrix.o
	$(CXX) $(CXXFLAGS) -o main main.o DtException.o convolution.o Matrix.o  -I /home/watson/OpenBLAS/include/ -L/home/watson/OpenBLAS/lib -lopenblas -lpthread -lgfortran

main.o: DtException.h Matrix.h  convolution.h

DtException.o: DtException.h

Matrix.o: Matrix.h

convolution.o: convolution.h