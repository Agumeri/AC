export OMP_DYNAMIC=FALSE
export OMP_NUM_THREADS=12
for((N=16284; N<67108865; N=N*2))
do
    time $PBS_O_WORKDIR/SumaVectores_7 $N
done