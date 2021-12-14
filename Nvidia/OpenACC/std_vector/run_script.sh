#!/bin/bash

# compilation using nvc++
nvc++ -acc  -ta=tesla:managed main.cpp

# generate profiler files using Nsight System
nsys profile -t nvtx,openacc --stats=true -f true -o report_with_pragmas ./a.out
