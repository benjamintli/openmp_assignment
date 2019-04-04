thread=1
row=10
col=10
vec=1000

# $0 = thread count $1 = row count $2 = col count $3 = vector size
for i in 1 2 3 
do
echo "iteration $i"
echo "running pthread...."
build/pthread_dot $0 $3
echo "-----------------------------"
echo "running openmp dot product...."
build/openmp_dot $0 $3
echo "-----------------------------"
echo "running openmp matrix method 1...."
build/openmp_matrix_method1 $1 $2 $0
echo "-----------------------------"
echo "running openmp matrix method 2...."
build/openmp_matrix_method2 $1 $2 $0
echo "============================="
done
