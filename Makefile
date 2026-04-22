CC=gcc
CXX=g++
CFLAGS=-fopenmp -O2
CXXFLAGS=-fopenmp -O2


all: bugreduction bugparfor pipar axisb leastsquares car

bugreduction:
	$(CC) 01_BugReduction/BugReduction.c -o bugreduction $(CFLAGS)

bugparfor:
	$(CC) 02_BugParFor/BugParFor.c -o bugparfor $(CFLAGS)

pipar:
	$(CC) 03_PiPar/PiPar.c -o pipar $(CFLAGS)

axisb:
	$(CC) 04_Axisb_Jacobi/Axisb.c -o axisb $(CFLAGS)

leastsquares:
	$(CC) 05_LeastSquares/LeastSquares.c -o leastsquares $(CFLAGS)

car:
	$(CXX) 06_CarAnimation/CarPar.cpp -o car $(CXXFLAGS)

clean:
	rm -f bugreduction bugparfor pipar axisb leastsquares carpar