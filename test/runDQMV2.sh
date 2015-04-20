#!/bin/bash 

#scp get the files
#TO BE IMPLEMENTED

#prepare the files
source MP7text.sh rx_summary.txt tx_summary.txt 

# Run CMSSW Programs
cmsRun runUnpackerEmulatorAnalyzer.py  
cmsRun runUnpackerEmulatorAnalyzerPLOTEMU.py 

root -b -q macros/fastplotterMC.C    
root -b -q macros/fastplotterGCT.C   
root -b -q macros/fastplotterGCTEMU.C
root -b -q macros/comparisonGCT.C    

# Format for web
foldername="TestFromDigis"_$(date +_%Y%m%d_%H%M%S)
echo Creating $foldername

mkdir -p "$foldername" 
mv *png  "$foldername"
mv *log "$foldername"
cp templates/indexMC.html "$foldername"/index.html
cp templates/*Details*.html "$foldername"/
cp rx_summary_final.txt tx_summary_final.txt  "$foldername"

mv RCTOfflineDQMMC*.root  "$foldername"
mv L1UpgradeAnalyzer.root "$foldername" 

#    If you have access to a www folder you can do this     
cp  "$foldername"/*png ~/www/stage1dqm/
cp -r "$foldername" ~/www/stage1dqm/    

    
