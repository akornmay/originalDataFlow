#!/bin/bash

if [ $# -lt 1 ]
then
    echo "No arguments supplied"
    echo "Usage: /runningscript.sh [xray/particle]"
    exit
fi

if [ $1 != "xray" ] && [ $1 != "particle" ]
then
    echo "You're an idiot!"
    exit
fi


#delete everything in scratch

rm -r ../scratch/*
START=$(date +"%Y%m%d_%H%M%S")
echo "Starting time $START "
#we run the simulation with all the differnt steering files

#for ii in 99 150 175 200 225
for ii in 156 99 200
#for ii in 156

do
    echo "Running for WBC ${ii}"

    mkdir /Users/Andreas/Work/simulationTB/originalDataFlow/scratch/WBC${ii}

    for kk in 1 10 25 50 75 100 125 150 175 200 225 250
#    for kk in 25

    do
	echo "Rate ${kk}MHz"
	if [ $1 == "xray" ]
	then
	    ../DataFlow ../steer/WBC${ii}/xray${kk}MHz.steer > ../scratch/WBC${ii}/out${kk}MHz.txt
	fi

	if [ $1 == "particle" ]
	then
	    ../DataFlow ../steer/WBC${ii}/particle${kk}MHz.steer > ../scratch/WBC${ii}/out${kk}MHz.txt
	fi

    done

    cp /Users/Andreas/Work/simulationTB/originalDataFlow/scripts/maketable.sh /Users/Andreas/Work/simulationTB/originalDataFlow/scratch/WBC${ii}/
    cp /Users/Andreas/Work/simulationTB/originalDataFlow/scripts/plottable.cpp /Users/Andreas/Work/simulationTB/originalDataFlow/scratch/WBC${ii}/
    cp /Users/Andreas/Work/simulationTB/originalDataFlow/scripts/CodeResultComparison.cpp /Users/Andreas/Work/simulationTB/originalDataFlow/scratch/WBC${ii}/

    cd /Users/Andreas/Work/simulationTB/originalDataFlow/scratch/WBC${ii}/
    ./maketable.sh WBC${ii}.txt ${ii} $1
    cd -

    cp -r /Users/Andreas/Work/simulationTB/originalDataFlow/scratch/WBC${ii}/ /Users/Andreas/Work/simulationTB/originalDataFlow/results/WBC${ii}_$START/

    echo "WBC ${ii} done"

done


