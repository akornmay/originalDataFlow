#!/bin/bash


rm $1

for ii in 1 10 25 50 75 100 125 150 175 200 225 250

do
    file=out${ii}MHz.txt
    grep -A 8 Total $file | head -9 > .tempdata
    
    aa=`awk 'NR==1 {print $5" "}' .tempdata`
    bb=`awk 'NR==2 {print $3" "}' .tempdata`
    cc=`awk 'NR==3 {print $6" "}' .tempdata`
    dd=`awk 'NR==4 {print $5" "}' .tempdata`
    ee=`awk 'NR==5 {print $4" "}' .tempdata`
    ff=`awk 'NR==6 {print $5" "}' .tempdata`
    gg=`awk 'NR==7 {print $4" "}' .tempdata`
    hh=`awk 'NR==9 {print $3" "}' .tempdata`
    
    echo $aa $bb $cc $dd $ee $ff $gg $hh >> $1
    
    rm .tempdata

done

root -q -b "plottable.cpp(\"$1\",${2})"

if [ $3 == "particle" ]
then
    root -q -b "CodeResultComparison.cpp(\"$1\",\"../../PythonData/ParticleWBC${2}.dat\",${2})"
fi
if [ $3 == "xray" ]
then
    root -q -b "CodeResultComparison.cpp(\"$1\",\"../../PythonData/XrayWBC${2}.dat\",${2})"
fi
open Ineff_Detail_WBC${2}.pdf

open Code_Comparison_WBC${2}.pdf


