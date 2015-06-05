#!/bin/bash

#delete everything in scratch

rm -r ../scratch/*

#we run the simulation with all the differnt steering files

#for ii in 99 150 175 200 225
for ii in 156

do
    echo "Running for WBC ${ii}"

    mkdir /Users/Andreas/Work/simulationTB/originalDataFlow/scratch/WBC${ii}

    for kk in 25 50 75 100 125 150 175 200 225 250
#    for kk in 25

    do
	echo "Rate ${kk}MHz"
	../DataFlow ../steer/WBC${ii}/xray${kk}MHz.steer > ../scratch/WBC${ii}/out${kk}MHz.txt

    done

    cp /Users/Andreas/Work/simulationTB/originalDataFlow/scripts/maketable.sh /Users/Andreas/Work/simulationTB/originalDataFlow/scratch/WBC${ii}/
    cp /Users/Andreas/Work/simulationTB/originalDataFlow/scripts/plottable.cpp /Users/Andreas/Work/simulationTB/originalDataFlow/scratch/WBC${ii}/

    cd /Users/Andreas/Work/simulationTB/originalDataFlow/scratch/WBC${ii}/
    ./maketable.sh WBC${ii}.txt ${ii}
    cd -

    echo "WBC ${ii} done"

done


