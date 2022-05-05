NVC = nvcc
NVCFLAG = -g -G -pg --expt-extended-lambda 
NVLDFLAG = -lnvToolsExt 

all: main.o
	$(NVC) $(NVLDFLAG) $^ -o app
	
%.o: %.cu
	$(NVC) -c $(NVCFLAG) $< -o $@

run:
	./app

profile:
	nsys profile ./app 
