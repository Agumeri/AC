for((N=16284; N<67108865; N=N*2))
do
    time $PBS_O_WORKDIR/SumaVectores_5 $N
done