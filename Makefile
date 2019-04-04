all: pthread openmp_dot openmp_matrix

pthread: src/part1_pthread.c
			gcc -o build/pthread_dot src/part1_pthread.c -lpthread

openmp_dot: src/openmp_thread.c
			gcc -o build/openmp_dot src/openmp_thread.c -fopenmp

openmp_matrix: src/openmp_matrix.c
			gcc -o build/openmp_matrix src/openmp_matrix.c -fopenmp