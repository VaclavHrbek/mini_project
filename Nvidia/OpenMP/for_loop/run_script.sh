#!/bin/bash

# compilation using nvc++
nvc++ -Minfo=mp -mp=gpu -gpu=cc70   main.cpp

# generate profiler files using Nsight System
nsys profile -t nvtx,openmp --stats=true -f true -o report_with_pragmas ./a.out
