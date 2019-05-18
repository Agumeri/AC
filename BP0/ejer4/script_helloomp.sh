#!/bin/bash
#Todos los scripts que se hagan para atcgrid deben incluir lo siguiente:
#1. Se asigna al trabajo el nombre helloomp
#PBS -N helloomp
#2. Se asigna el trabajo a la cola ac
#PBS -q ac   
#3. Se imprime información del trabajo usando variables de entorno de PBS
echo "Id. usuario del trabajo: $PBS_O_LOGNAME"
echo "Id.  del trabajo: $PBS_JOBID"
echo "Nombre  del trabajo especificado por usuario: $PBS_JOBNAME"
echo "Directorio en el que se ha ejecutado qsub: $PBS_O_WORKDIR"
echo "Directorio de trabajo: $PBS_JOBDIR"
echo "Cola: $PBS_QUEUE"
echo "Nodo que ejecuta qsub: $PBS_O_HOST"
echo "Nodos asignados al trabajo:"
cat $PBS_NODEFILE
# FIN del trozo que deben incluir todos los scripts

#Se fija a 12 el nº de threads máximo (tantas como cores en un nodo)
export OMP_THREAD_LIMIT=12
echo "Nº de threads inicial: $OMP_THREAD_LIMIT"
#Se ejecuta HelloOMP que está en el directorio hello con distinto nº de threads
export PBS_JOBDIR=$PBS_O_WORKDIR
echo "Directorio de trabajo: $PBS_JOBDIR"
for ((P=OMP_THREAD_LIMIT;P>0;P=P/2))
do
   export OMP_NUM_THREADS=$P
   echo -e "\n1.Para $OMP_NUM_THREADS threads:"
	$PBS_O_WORKDIR/HelloOMP2
      #$PBS_O_WORKDIR/HelloOMP2
done
