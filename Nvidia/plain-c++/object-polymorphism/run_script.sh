#!/bin/bash

nvc++ main.cpp

nsys profile -t nvtx --stats=true -f true -o report ./a.out


