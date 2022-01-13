SHELL = /bin/sh

.SUFFIXES:

CC = gcc 
CFLAGS = -I$(include_dir) -O
LDFLAGS = -L/usr/local/cuda/lib64 -lcudart -lstdc++
NVCC = nvcc
NVCFLAGS = -I$(include_dir) 

file_dir = .
build_dir = $(file_dir)/build
src_dir = $(file_dir)/src
build_sub_dirs = $(patsubst $(src_dir)/%, %, $(wildcard $(src_dir)/*))
c_src_dir = $(file_dir)/src/c
#openacc_src_dir = $(file_dir)/src/openacc
cuda_src_dir = $(file_dir)/src/cuda
app_dir = $(file_dir)/app
include_dir = $(file_dir)/include

c_src_files := $(wildcard $(c_src_dir)/*.c)
app_src_files := $(wildcard $(app_dir)/*.c)
#openacc_src_files := $(wildcard $(openacc_src_dir)/*.c) 
cuda_src_files := $(wildcard $(cuda_src_dir)/*.cu)

cuda_obj_files := $(patsubst %.cu, %.o ,$(patsubst $(src_dir)/%, $(build_dir)/%, $(cuda_src_files)))

c_obj_files := $(patsubst %.c, %.o ,$(patsubst $(src_dir)/%, $(build_dir)/%, $(c_src_files)))
c_obj_files += $(patsubst $(app_dir)/%.c, $(build_dir)/%.o, $(app_src_files))

all: executable

debug: CFLAGS += -g
debug: NVCFLAGS += -g -G
debug: executable

executable: $(c_obj_files)  main

$(c_obj_files): | $(build_dir)

$(build_dir)/c/%.o: $(c_src_dir)/%.c
	$(CC) -c $(CFLAGS) $< -o $@
	
$(build_dir)/%.o: $(app_dir)/%.c
	$(CC) -c $(CFLAGS) $< -o $@

$(build_dir)/cuda/%.o: $(cuda_src_dir)/%.cu
	$(NVCC) -c $(NVCFLAGS) $< -o $@

main: $(c_obj_files) $(cuda_obj_files)
	$(CC) $^ -o $(build_dir)/$@ $(LDFLAGS)

$(build_dir):
	$(foreach i, $(build_sub_dirs), $(shell mkdir -p  $(build_dir)/$(i)))

.PHONY:
	clean

clean:
	rm -rf $(file_dir)/build


