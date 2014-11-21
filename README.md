TestDQM
=======

First attempt at monitoring 

a) Install

scram pro -n dqmTests CMSSW CMSSW_7_3_0_pre2
cd dqmTests/src
# Setup your CMSSW environment
cmsenv
# You might want to run this before doing ANYTHING else in src:
git cms-init

#Download the CTP7ToDigi package:
git clone --recursive https://github.com/uwcms/CTP7ToDigi.git CTP7Tests/CTP7ToDigi

#Download the DQM modules (different folder to facilitate potential integration with the official DQM one day):
git clone --recursive https://github.com/mcepeda/TestDQM.git CTP7Tests/CTP7DQM

scramv1 -j 8   

b) Run

Running is split in three sequences now (capture - dqm - plot), using  CTP7ToDigi_cfg.py and  CTP7DQM_cfg.py plus finally a preliminary plotting macro (fastplotter)
that will evolve to a executable.

cd test

b1) for running capture and then DQM 
bash test/runCaptureDQMPlot.sh

b2) for running only the DQM - plotting sequence
bash test/runDQMPlot.sh





  