#pragma once

#ifdef __cplusplus 
extern "C" {
#endif

#include <stdio.h>
#include "c/file_1.h"
void cuda_function(int var);

#ifdef __cplusplus 
}
#endif

void cuda_function_call_c_function();

