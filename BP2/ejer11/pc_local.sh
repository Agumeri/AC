#!/bin/bash

for ((N=1;N<5;N=N+1))
do
   export OMP_NUM_THREADS=$N
   ./pmv-OpenMP-b 1000
done

for ((N=1;N<5;N=N+1))
do
   export OMP_NUM_THREADS=$N
   ./pmv-OpenMP-b 100000
done