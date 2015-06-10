#!/bin/bash

#for ii in 99 150 156 175 200 225
for ii in 156

do

    echo "For WBC = ${ii}"

    for kk in 25 50 75 100 125 150 175 200 225 250

    do
    steerfile="../steer/WBC${ii}/xray${kk}MHz.steer"

    echo "In $steerfile"

    if ! [ -f $steerfile ]
    then
       echo "ERROR File does not exist"
       exit
    fi


    echo "Setting WBC to ${ii} (just to be sure)"
    sed -i -e "/^[^#]/ s%[[:space:]]WBC.*% WBC = ${ii} %" $steerfile


    signalfilename="/Users/Andreas/Work/simulationTB/originalDataFlow/data/XrayData${kk}MHz.root"
    echo "Setting SIGNAL_FILENAME to $signalfilename"
    sed -i -e "/^[^#]/ s%.*SIGNAL_FILENAME.*%        SIGNAL_FILENAME = $signalfilename %" $steerfile

    outfilename="/Users/Andreas/Work/simulationTB/originalDataFlow/scratch/WBC${ii}/Xray${kk}MHz.root"
    echo "Setting OUTPUT_FILENAME to $outfilename"
    sed -i -e "/^[^#]/ s%.*OUTPUT_FILENAME.*%        OUTPUT_FILENAME = $outfilename %" $steerfile

    done

    for kk in 1 10 25 50 75 100 125 150 175 200 225 250

    do
    particlesteerfile="../steer/WBC${ii}/particle${kk}MHz.steer"

    echo "In $particlesteerfile"
    if ! [ -f $particlesteerfile ]
    then
       echo "ERROR File does not exist"
       exit
    fi
 
    echo "Setting WBC to ${ii} (just to be sure)"
    sed -i -e "/^[^#]/ s%[[:space:]]WBC.*% WBC = ${ii} %" $particlesteerfile

    signalfilename="/Users/Andreas/Work/simulationTB/originalDataFlow/data/ParticleData${kk}MHz.root"
    echo "Setting SIGNAL_FILENAME to $signalfilename"
    sed -i -e "/^[^#]/ s%.*SIGNAL_FILENAME.*%        SIGNAL_FILENAME = $signalfilename %" $particlesteerfile

    outfilename="/Users/Andreas/Work/simulationTB/originalDataFlow/scratch/WBC${ii}/Particle${kk}MHz.root"
    echo "Setting OUTPUT_FILENAME to $outfilename"
    sed -i -e "/^[^#]/ s%.*OUTPUT_FILENAME.*%        OUTPUT_FILENAME = $outfilename %" $particlesteerfile


    done

done



