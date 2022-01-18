#include "slow_function.h"


void slow_function(void){
	printf("Hello from slow function\n");
	int b = 0;
	for(int i = 0; i != INT_MAX; i++){
		b = b + i - i + i - i + 1;
	}
}

