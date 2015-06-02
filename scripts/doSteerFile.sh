#!/bin/bash

for ii in 99 150 175 200 225

do

    echo "For WBC = ${ii}"

    for kk in 25 50 75 100 125 150 175 200 225 250

    do
    steerfile="../steer/WBC${ii}/xray${kk}MHz.steer"

    echo "In $steerfile"

    echo "Setting WBC to ${ii} (just to be sure)"
    sed -i -e "/^[^#]/ s%.*WBC.*%        WBC = ${ii} %" $steerfile


    signalfilename="/Users/Andreas/Work/simulationTB/originalDataFlow/data/XrayData${kk}MHz.root"
    echo "Setting SIGNAL_FILENAME to $signalfilename"
    sed -i -e "/^[^#]/ s%.*SIGNAL_FILENAME.*%        SIGNAL_FILENAME = $signalfilename %" $steerfile

    outfilename="/Users/Andreas/Work/simulationTB/originalDataFlow/scratch/WBC${ii}/Xray${kk}MHz.root"
    echo "Setting OUTPUT_FILENAME to $outfilename"
    sed -i -e "/^[^#]/ s%.*OUTPUT_FILENAME.*%        OUTPUT_FILENAME = $outfilename %" $steerfile


    done

done



