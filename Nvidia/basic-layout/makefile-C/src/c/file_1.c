#include "c/file_1.h"

void c_function(int par){
	for(int i = 0; i != par; ++i){
		printf("From .c source file var = %d\n", i);
	}
}
