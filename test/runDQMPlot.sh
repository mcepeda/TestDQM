#!/bin/bash 
# Run CMSSW Programs
cmsRun RCTOfflineDQMForCommissioning_cfg.py   >& dqm.log 

# Plot
root -b -q macros/fastplotterMC.C >& plots.log 

# Format for web
foldername="TestFromDigis"_$(date +_%Y%m%d_%H%M%S)
echo Creating $foldername

mkdir -p "$foldername" 
mv *png  "$foldername"
mv *log "$foldername"
cp templates/indexMC.html "$foldername"/index.html
cp templates/*Details.html "$foldername"

mv RCTOfflineDQMMC.root  "$foldername"
rm DQM_*__L1TMonitor__Calo__RCTOffline.root

#    If you have access to a www folder you can do this     
#    mkdir -p ~/www/RCTOfflineDQMTESTS/testforIsobel
#    cp  "$foldername"/* ~/www/RCTOfflineDQMTESTS/testforIsobel/
    

    
