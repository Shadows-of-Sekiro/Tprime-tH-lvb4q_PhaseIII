#!/bin/bash

echo "Starting job on " `date`
echo "Running on: `uname -a`"
echo "System software: `cat /etc/redhat-release`"
source /cvmfs/cms.cern.ch/cmsset_default.sh

echo "PWD: "$PWD
export SCRAM_ARCH=slc7_amd64_gcc700

xrdcp -f  root://eosuser.cern.ch//eos/user/a/achhetri/CMSSW_10_68.tgz .
tar -xf CMSSW_10_68.tgz
rm CMSSW_10_68.tgz
cd CMSSW_10_6_8/src/WTopScalefactorProducer/Skimmer 
scramv1 b ProjectRename
eval `scram runtime -sh`

ls
echo "============================================"
python  doSkim.py

echo "PWD: "$PWD
echo "====> List output files : " 

#ls TEST/*.root 

#xrdcp -f *.root  root://eosuser.cern.ch//eos/user/a/achhetri/TTbar_UL16_test.root
xrdcp -f *.root  root://eosuser.cern.ch//eos/user/a/achhetri/Tprime_M15oo_UL16_test.root

# /afs/cern.ch/user/a/achhetri/NANO_AOD/CMSSW_10_6_8/src/WTopScalefactorProducer/TEST/

#cd ${_CONDOR_SCRATCH_DIR}

date
