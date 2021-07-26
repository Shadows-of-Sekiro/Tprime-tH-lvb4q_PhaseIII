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
cd CMSSW_10_6_8/src/Phase_III_Analysis_with_NanoAOD/NANO_AOD_Analyzer
scramv1 b ProjectRename
eval `scram runtime -sh`


ls
echo "============================================"
./PUPPI.exe $*

echo "PWD: "$PWD
echo "====> List output files : " 

#ls TEST/*.root 

#xrdcp -f *.root  root://eosuser.cern.ch//eos/user/a/achhetri/TTbar_UL16_test.root
xrdcp -f ../Analyzed_Files_Nano_AOD/UL_TTbar/root_text_files_list/TT*.root  root://eosuser.cern.ch//eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_TTbar_Files/
xrdcp -f ../Analyzed_Files_Nano_AOD/UL17_Bkg/root_file_list/QCD*.root        root://eosuser.cern.ch//eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_QCD_MuEnr_Files/
# xrdcp -f ../Analyzed_Files_Nano_AOD/UL17_Bkg/root_file_list/WJets_LNu*.root        root://eosuser.cern.ch//eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_Wjets_To_LNu_Files/
# xrdcp -f ../Analyzed_Files_Nano_AOD/UL17_Bkg/root_file_list/DYJetsToLL_*.root        root://eosuser.cern.ch//eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_DYjetsTo_LL_Files/

cd ${_CONDOR_SCRATCH_DIR}
rm -rf CMSSW_10_6_8

date

# Queue filename matching files ../Analyzed_Files_Nano_AOD/UL_TTbar/root_text_files_list/TTbar_UL17_*.txt
# Queue filename matching files ../Analyzed_Files_Nano_AOD/UL17_Bkg/root_file_list/QCD_*UL17_*.txt
# Queue filename matching files ../Analyzed_Files_Nano_AOD/UL17_Bkg/root_file_list/WJets_*UL17_*.txt
# Queue filename matching files ../Analyzed_Files_Nano_AOD/UL17_Bkg/root_file_list/DYJets*UL17_*.txt

















# ///////////////////////////////////////LXplus Flavor Details for Condor Job///////////////////////////////////////////////////////////////
# name 				max 	
# espresso 			20min 	
# microcentury		1h 	
# longlunch 		2h 	
# workday 			8h 	
# tomorrow 			1d 	
# testmatch 		3d 	
# nextweek 			1w 






