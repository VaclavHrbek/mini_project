SHELL = /bin/sh

.SUFFIXES:


file_dir = .
build_dir = $(file_dir)/build
c_src_dir = $(file_dir)/src/c
openacc_src_dir = $(file_dir)/src/openacc
cuda_src_dir = $(file_dir)/src/cuda
app_dir = $(file_dir)/app
include_c_dir = $(file_dir)/include

c_src_files := $(wildcard $(c_src_dir)/*.c)
c_obj_files := $(patsubst $(c_src_dir)/%.c, $(build_dir)/%.o, $(c_src_files))

CC = gcc -O
CFLAGS = -I$(include_c_dir)
NCC = nvcc

all: $(build_dir) main

$(build_dir)/%.o: $(c_src_dir)/%.c
	$(CC) -c $(CFLAGS) $< -o $@

main: main.o $(c_obj_files)
	$(CC)  $(build_dir)/$^ -o $(build_dir)/$@

main.o: $(app_dir)/main.c 
	$(CC) -c $<  $(CFLAGS) -o $(build_dir)/$@

$(build_dir):
	mkdir -p $(file_dir)/build

.PHONY:
	clean

clean:
	rm -rf $(file_dir)/build


