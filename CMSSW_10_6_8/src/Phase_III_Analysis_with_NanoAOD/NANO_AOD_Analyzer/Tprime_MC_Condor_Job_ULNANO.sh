#!/bin/bash

echo "Starting job on " `date`
echo "Running on: `uname -a`"
echo "System software: `cat /etc/redhat-release`"
source /cvmfs/cms.cern.ch/cmsset_default.sh

echo "PWD: "$PWD
export SCRAM_ARCH=slc7_amd64_gcc700


xrdcp -f  root://eosuser.cern.ch//eos/user/a/achhetri/CMSSW_10_68_tprime.tgz .
tar -xf CMSSW_10_68_tprime.tgz
rm CMSSW_10_68_tprime.tgz
cd CMSSW_10_6_8/src/Phase_III_Analysis_with_NanoAOD/NANO_AOD_Analyzer
scramv1 b ProjectRename
eval `scram runtime -sh`


ls
echo "============================================"
./PUPPI.exe $*

echo "PWD: "$PWD
echo "====> List output files : " 

#ls TEST/*.root 


xrdcp -f ../Analyzed_Files_Nano_AOD/Tprime_UL17/Signal_Root_Files_List_UL17/Tprime_*_UL17_v2_*.root  root://eosuser.cern.ch///eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Signal_UL17/



####=-=-=-=-=-=-=-=-==-=-=---###=-=-=-=-=-=-=-=-==-=-=---###=-=-=-=-=-=-=-=-==-=-=---###=-=-=-=-=-=-=-=-==-=-=---###=-=-=-=-=-=-=-=-==-=-=---###=-=-=-=-=-=-=-=-==-=-=---###=-=-=-=-=-=-=-=-==-=-=---###



cd ${_CONDOR_SCRATCH_DIR}
rm -rf CMSSW_10_6_8

date

# Queue filename matching files ../Analyzed_Files_Nano_AOD/UL_TTbar/root_text_files_list/TTbar_UL17_*.txt
# Queue filename matching files ../Analyzed_Files_Nano_AOD/UL_TTbar/root_text_files_list/TT_to*.txt
# Queue filename matching files ../Analyzed_Files_Nano_AOD/UL17_Bkg/root_file_list/QCD_*UL17_*.txt
# Queue filename matching files ../Analyzed_Files_Nano_AOD/UL17_Bkg/root_file_list/WJets_*UL17_*.txt
# Queue filename matching files ../Analyzed_Files_Nano_AOD/UL17_Bkg/root_file_list/DYJets*UL17_*.txt
# Queue filename matching files ../Analyzed_Files_Nano_AOD/UL17_Bkg/root_file_list/WJets_LNu_HT*UL17_*.txt
# Queue filename matching files ../Analyzed_Files_Nano_AOD/UL17_Bkg/root_file_list/DYJetsToLL_M-50_HT*UL17_*.txt


# ///////////////////////////////////////LXplus Flavor Details for Condor Job///////////////////////////////////////////////////////////////
# name 				max 	
# espresso 			20min 	
# microcentury		1h 	
# longlunch 		2h 	
# workday 			8h 	
# tomorrow 			1d 	
# testmatch 		3d 	
# nextweek 			1w 






