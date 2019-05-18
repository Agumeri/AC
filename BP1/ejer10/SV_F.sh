export OMP_DYNAMIC=FALSE
export OMP_NUM_THREADS=4
for((N=16384; N<67108865; N=N*2))
do
    ./SumaVectoresF $N
done