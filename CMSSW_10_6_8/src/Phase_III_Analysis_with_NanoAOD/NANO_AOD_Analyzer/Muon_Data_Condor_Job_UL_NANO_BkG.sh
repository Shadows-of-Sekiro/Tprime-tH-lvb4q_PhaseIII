#!/bin/bash

echo "Starting job on " `date`
echo "Running on: `uname -a`"
echo "System software: `cat /etc/redhat-release`"
source /cvmfs/cms.cern.ch/cmsset_default.sh

echo "PWD: "$PWD
export SCRAM_ARCH=slc7_amd64_gcc700


xrdcp -f  root://eosuser.cern.ch//eos/user/a/achhetri/CMSSW_10_68_data_mu.tgz .
tar -xf CMSSW_10_68_data_mu.tgz
rm CMSSW_10_68_data_mu.tgz
cd CMSSW_10_6_8/src/Phase_III_Analysis_with_NanoAOD/NANO_AOD_Analyzer
scramv1 b ProjectRename
eval `scram runtime -sh`


ls
echo "============================================"
./PUPPI.exe $*

echo "PWD: "$PWD
echo "====> List output files : " 

#ls TEST/*.root 

#For Data
xrdcp -f ../../Large_Data_Files_Listing/Muon_Era*.root     root://eosuser.cern.ch///eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Data_UL17/Muon_Single/



cd ${_CONDOR_SCRATCH_DIR}
rm -rf CMSSW_10_6_8

date


# Queue filename matching files ../../Large_Data_Files_Listing/Electron_Era*.txt
# Queue filename matching files ../../Large_Data_Files_Listing/Muon_Era*.txt

















# ///////////////////////////////////////LXplus Flavor Details for Condor Job///////////////////////////////////////////////////////////////
# name 				max 	
# espresso 			20min 	
# microcentury		1h 	
# longlunch 		2h 	
# workday 			8h 	
# tomorrow 			1d 	
# testmatch 		3d 	
# nextweek 			1w 






