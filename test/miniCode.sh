#!/bin/bash

#prepare the files
source ../../MP7text.sh rx_summary.txt tx_summary.txt

# Run CMSSW Programs
cmsRun ../../runUnpackerEmulatorAnalyzer.py  >& dqm.log  
cmsRun ../../runUnpackerEmulatorAnalyzerPLOTEMU.py >& dqmemu.log

# Format for web
foldername="Take1V2"
echo Creating $foldername

mkdir -p "$foldername"
mv *.root "$foldername"
