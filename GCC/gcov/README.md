
First create .gcno from source file using

gcc -fprofile-arcs -ftest-coverage main.c

Second run executable file "a.out"

Than the .gcda will be created

Third use command gcov on source file "main.c"

This will create a main.c.gcov file
That contain an annotated source with provided info 
