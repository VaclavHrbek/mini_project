#include <vector>
#include <iostream>
#include <algorithm>
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <nvToolsExt.h>

class Data {
	int _val;
	public:
	Data(int a) : _val(a) {}
	__device__
	void plus_one() {
		_val += 1;
	};
	int val(){
		return _val;
	}
};

struct printf_functor
{
  __host__ __device__
  void operator()(int x)
  {
    // note that using printf in a __device__ function requires
    // code compiled for a GPU with compute capability 2.0 or
    // higher (nvcc --arch=sm_20)
    printf("%d\n", x);
  }
};

int main(){
	thrust::host_vector<Data> vec;
	nvtxRangePush("Seq init data");
	for(size_t i = 0; i != 10000; i++){
		vec.push_back(Data(i));	
	}
	nvtxRangePop();

	nvtxRangePush("Copy data to device + malloc on device");
	thrust::device_vector<Data> d_vec = vec;
	nvtxRangePop();

	nvtxRangePush("Call data on GPU");
	thrust::for_each(thrust::device, d_vec.begin(), d_vec.end(), []__device__ (Data &x){x.plus_one();});
	cudaDeviceSynchronize();
	nvtxRangePop();
	//thrust::copy(d_vec.begin(), d_vec.end(), vec.begin());
	nvtxRangePush("Copy data to host");
	vec = d_vec;
	nvtxRangePop();
//	for(auto i : vec){
//		std::cout << i.val() << ' ';
//	}

	return 0;
}
