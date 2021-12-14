#!/bin/bash

# compilation using nvc++
nvc++ main.cpp

# generate profiler files using Nsight System
nsys profile -t nvtx --stats=true -f true -o report ./a.out
