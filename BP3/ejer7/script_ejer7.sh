!/bin/bash
#Se asigna al trabajo el nombre pmtv-OpenMP
#PBS -N pmtv-OpenMP
#Se asigna al trabajo la cola ac
#PBS -q ac

#Asignamos 12 threads y ejecutamos pmtv-OpenMP en static
export OMP_NUM_THREADS=12
export OMP_SCHEDULE="static"
$PBS_O_WORKDIR/pmtv-OpenMP 20000
export OMP_SCHEDULE="static, 1"
$PBS_O_WORKDIR/pmtv-OpenMP 20000
export OMP_SCHEDULE="static, 64"
$PBS_O_WORKDIR/pmtv-OpenMP 20000

#Asignamos 12 threads y ejecutamos pmtv-OpenMP en dynamic
export OMP_NUM_THREADS=12
export OMP_SCHEDULE="dynamic"
$PBS_O_WORKDIR/pmtv-OpenMP 20000
export OMP_SCHEDULE="dynamic, 1"
$PBS_O_WORKDIR/pmtv-OpenMP 20000
export OMP_SCHEDULE="dynamic, 64"
$PBS_O_WORKDIR/pmtv-OpenMP 20000

#Asignamos 12 threads y ejecutamos pmtv-OpenMP en guided
export OMP_NUM_THREADS=12
export OMP_SCHEDULE="guided"
$PBS_O_WORKDIR/pmtv-OpenMP 20000
export OMP_SCHEDULE="guided, 1"
$PBS_O_WORKDIR/pmtv-OpenMP 20000
export OMP_SCHEDULE="guided, 64"
$PBS_O_WORKDIR/pmtv-OpenMP 20000