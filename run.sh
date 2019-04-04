echo "for $OMP_NUM_THREADS"
for i in 1 2 3 
do
echo "iteration $i"
echo "running pthread...."
build/pthread_dot
echo "-----------------------------"
echo "running openmp dot product...."
build/openmp_dot
echo "-----------------------------"
echo "running openmp matrix mult...."
build/openmp_matrix
echo "============================="
done
