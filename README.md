TestRCTOfflineDQM
=================

Monitoring standalone the status of RCT, from a file with digis

This is almost *identical* to <a href="https://github.com/cms-sw/cmssw/blob/CMSSW_7_4_X/DQM/L1TMonitor/src/L1TRCT.cc"> RCT DQM module in CMSSW </a> , it just runs standalone. 

A example of a <a href="https://cmsweb.cern.ch/dqm/online/start?runnr=193556;dataset=/Global/Online/ALL;sampletype=online_data;filter=all;referencepos=overlay;referenceshow=customise;referenceobj1=refobj;referenceobj2=none;referenceobj3=none;referenceobj4=none;search=;striptype=object;stripruns=;stripaxis=run;stripomit=none;workspace=L1T;size=M;root=L1T/L1TRCT;focus=;zoom=no">good 2012 run for reference</a>. 

(Note: there is another instance of this code in the RCT Offline DQM that Pam or the RCT oncall run regularly on the already collected raw data for our weekly RCT certification. The plots are identical in format.)

a) Install
----------
```bash 
scram pro -n dqmTests CMSSW CMSSW_7_4_0_pre5
git cms-init
git clone --recursive https://github.com/mcepeda/TestDQM.git  RCTOfflineTests/RCTOfflineDQM/
export USER_CXXFLAGS="-Wno-error=unused-but-set-variable -Wno-error=unused-variable"
scram b
cd RCTOfflineTests/RCTOfflineDQM/test
```

b) Run
------
edit  RCTOfflineDQMForCommissioning_cfg.py to include your MC/Emulation file & check that the 
name of the rctDigis is the correct one (can be simRctDigis or  caloStage1Digis  or similar collection)

```bash 
bash runDQMPlot.sh
```

This creates a folder with plots & with the .html files needed to display this in a webbrowser. If you have access to a webpage from your userarea, just copy the folder.
