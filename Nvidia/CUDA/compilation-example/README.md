
This is a prototipe for compilation cuda and .c code.

/////
Be aweare that the nvcc use C++ compiler!!!
So one need to include /extern "C"/ in function that are in plain C.
In both header files and source files. 
/////

Cuda files .cu generates .o files with comand
nvcc -c file.cu

Link header to cuda file using -I or -include
nvcc -c file.c -include header.h

Generate object file using gcc 
gcc -c main.c

Link header usind -include or -I
gcc -c main.c -include header.h

Link all togerher
gcc main.o file.o -L/usr/local/cuda/lib64 -lcudart -lstdc++
// -L/usr/local/cuda/lib64 is for find cudart library



