#!/bin/bash

nvc++ -acc -g -Minfo=accel -gpu=cc61 main.cpp

nsys profile -t nvtx,openacc --stats=true -f true -o report ./a.out


