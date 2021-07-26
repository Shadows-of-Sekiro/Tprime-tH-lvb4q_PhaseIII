#!/bin/bash

echo "Starting job on " `date`
echo "Running on: `uname -a`"
echo "System software: `cat /etc/redhat-release`"
source /cvmfs/cms.cern.ch/cmsset_default.sh

echo "PWD: "$PWD
export SCRAM_ARCH=slc7_amd64_gcc700
eval `scramv1 project CMSSW CMSSW_10_6_8`

xrdcp -r /afs/cern.ch/user/a/achhetri/NANO_AOD/CMSSW_10_6_8/src/PhysicsTools/  CMSSW_10_6_8/src/
xrdcp -r /afs/cern.ch/user/a/achhetri/NANO_AOD/CMSSW_10_6_8/src/WTopScalefactorProducer/  CMSSW_10_6_8/src/


cd CMSSW_10_6_8/src/
 ### copy the input root files if they are needed only if you require local reading

scramv1 b ProjectRename
eval `scram runtime -sh`


ls
echo "============================================"

#python   /afs/cern.ch/user/a/achhetri/NANO_AOD/CMSSW_10_6_8/src/WTopScalefactorProducer/Skimmer/doSkim.py
python  WTopScalefactorProducer/Skimmer/doSkim.py

echo "PWD: "$PWD
echo "====> List output files : " 

#cd ${_CONDOR_SCRATCH_DIR}

date
