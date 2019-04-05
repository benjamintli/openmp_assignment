
# $0 = thread count $1 = row count $2 = col count $3 = vector size
echo "Test Data:"
echo "Number of threads is "$1
echo $2" x "$3" matrix"
echo $4 "element vector length"
echo ""
for i in 1 2 3 
do
echo "running pthread...."
build/pthread_dot $4 $1
echo "-----------------------------"
echo "running openmp dot product...."
build/openmp_dot.exe $4 $1
echo "-----------------------------"
echo "running openmp matrix method 1...."
build/openmp_matrix_method1.exe $2 $3 $1
echo "-----------------------------"
echo "running openmp matrix method 2...."
build/openmp_matrix_method2.exe $2 $3 $1
echo "============================="
done
