!/bin/bash

for((N=1; N<5; N=N+1))
do
    export OMP_NUM_THREADS=$N
    ./pmm-OpenMP 100
done

for ((N=1; N<5; N=N+1))
do
    export OMP_NUM_THREADS=$N
    ./pmm-OpenMP 1500
done
