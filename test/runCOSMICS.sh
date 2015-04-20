#!/bin/bash 

while read line
do
     name=$line
     echo "Text read from file - $name"
     ls $name/*
     cp $name/* . 

     #prepare the files
     source MP7text.sh rx_summary.txt tx_summary.txt 
     
     # Run CMSSW Programs
     cmsRun runUnpackerEmulatorAnalyzer.py  >& dqm.log
     cmsRun runUnpackerEmulatorAnalyzerPLOTEMU.py >& dqmemu.log
 
     # Format for web
     foldername=$name"/Take1"
     echo Creating $foldername
     
     mkdir -p "$foldername" 
     mv *.root "$foldername"   
        
done < $1
 
