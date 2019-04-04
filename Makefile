all: pthread openmp_dot openmp_matrix_method1 openmp_matrix_method2

pthread: src/part1_pthread.c
			gcc -o build/pthread_dot src/part1_pthread.c -lpthread

openmp_dot: src/openmp_thread.c
			gcc -o build/openmp_dot src/openmp_thread.c -fopenmp

openmp_matrix_method1: src/openmp_matrix_method1.c
			gcc -o build/openmp_matrix_method1 src/openmp_matrix_method1.c -fopenmp

openmp_matrix_method2: src/openmp_matrix_method2.c
			gcc -o build/openmp_matrix_method2 src/openmp_matrix_method2.c -fopenmp