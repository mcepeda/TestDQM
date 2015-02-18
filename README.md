TestRCTOfflineDQM
=================

Monitoring standalone the status of RCT, from a file with digis

a) Install
----------
```bash 
scram pro -n dqmTests CMSSW CMSSW_7_3_0_pre2
git cms-init
git clone --recursive https://github.com/mcepeda/TestDQM.git  RCTOfflineTests/RCTOfflineDQM/
export USER_CXXFLAGS="-Wno-error=unused-but-set-variable -Wno-error=unused-variable -Wno-error=sign-compare"
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
