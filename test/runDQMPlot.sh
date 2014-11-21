#!/bin/bash
#cmsRun CTP7ToDigi_cfg.py >& logcapture& 
cmsRun CTP7DQM_cfg.py   >& dqm.log 
root -b -q fastplotter.C >& plots.log 
 
mkdir -p ~/www/CTP7DQMTESTS/newdirectory
mv *png *log  ~/www/CTP7DQMTESTS/newdirectory 
mv CTP7DQM.root  ~/www/CTP7DQMTESTS/newdirectory
rm DQM_V0001_R000000001__L1TMonitor__Calo__CTP7.root
