Steps:

1) Compile with:
gcc main.c quick_function.c slow_function.c -O0 -pg -g

2) Run:
./a.out

3) Run gprof:
gprof

4) (Optional) Display brief information
gprof -b a.out

5) (Optional) Display annotated file:
gprof -A a.out

