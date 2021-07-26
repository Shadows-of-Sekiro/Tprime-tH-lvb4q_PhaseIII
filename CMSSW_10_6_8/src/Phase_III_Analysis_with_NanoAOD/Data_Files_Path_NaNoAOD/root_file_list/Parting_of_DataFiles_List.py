#!/bin/python
import os


#Tb_tH_LH_M1000_merged.sh
#Tb_tH_LH_M1000_merged.jdl

#TTbar_mcbkg_test_python.txt

dataset = {
   'EraB_Muon'               : '/afs/cern.ch/work/a/achhetri/NANO_AOD/CMSSW_10_6_8/src/Phase_III_Analysis_with_NanoAOD/Data_Files_Path_NaNoAOD/EraB_Muon_v2.txt',   
   'EraD_Muon'               : '/afs/cern.ch/work/a/achhetri/NANO_AOD/CMSSW_10_6_8/src/Phase_III_Analysis_with_NanoAOD/Data_Files_Path_NaNoAOD/EraD_Muon_v2.txt',   
   'EraE_Muon'               : '/afs/cern.ch/work/a/achhetri/NANO_AOD/CMSSW_10_6_8/src/Phase_III_Analysis_with_NanoAOD/Data_Files_Path_NaNoAOD/EraE_Muon_v2.txt',   
   'EraF_Muon'               : '/afs/cern.ch/work/a/achhetri/NANO_AOD/CMSSW_10_6_8/src/Phase_III_Analysis_with_NanoAOD/Data_Files_Path_NaNoAOD/EraF_Muon_v2.txt',   
   
   }










#nevents = -1 
eventsPerJob = {
   'EraB_Muon'               : 'Muon_EraB_Data_UL17_v2_',        
   'EraD_Muon'               : 'Muon_EraD_Data_UL17_v2_',        
   'EraE_Muon'               : 'Muon_EraE_Data_UL17_v2_',        
   'EraF_Muon'               : 'Muon_EraF_Data_UL17_v2_', 
   }

listOfSamples = [
   'EraB_Muon',        
   'EraD_Muon',        
   'EraE_Muon',        
   'EraF_Muon', 
   ]


listOfSamples.reverse()
os.system ("rm *UL*.txt")
for samples in listOfSamples :
     
     InputTextFile = open (dataset[samples])
     lines = InputTextFile.readlines()
     totalFiles = len(lines)
     
     count=0
     textfileNumber = 0
     rootFileList = []
     for line in lines : 
         count+=1
         check = count % 5
         rootFileList.append(line)
         if (check == 0) :
            textfileNumber += 1
            filename = eventsPerJob[samples]+str(textfileNumber)+".txt"

            with open(filename, 'a') as f:
                 for rootFile in rootFileList :
                     f.write(rootFile)                     
            del rootFileList[:]
         if (count == totalFiles) :
            textfileNumber += 1
            filename = eventsPerJob[samples]+str(textfileNumber)+".txt"
            with open(filename, 'a') as f:
                 for rootFile in rootFileList :
                     f.write(rootFile)
            del rootFileList[:]
#InputTextFile = open ("../Bkg_TTbar_v3_0.txt")
#InputTextFile = open ("../Bkg_QCD_Pt-80to120_MuEnr_v3.txt")
#InputTextFile = open ("../Bkg_QCD_Pt-120to170_MuEnr_v3.txt")
#InputTextFile = open ("../Bkg_QCD_Pt-170to300_MuEnr_v3.txt")
#InputTextFile = open ("../Bkg_QCD_Pt-300to470_MuEnr_v3.txt")
#InputTextFile = open ("../Bkg_QCD_Pt-470to600_MuEnr_v3.txt")
#InputTextFile = open ("../Bkg_QCD_Pt-600to800_MuEnr_v3.txt")
#InputTextFile = open ("../Bkg_QCD_Pt-800to1000_MuEnr_v3.txt")
#InputTextFile = open ("../Bkg_QCD_Pt-1000toInf_MuEnr_v3.txt")
#InputTextFile = open ("../Bkg_WJets_LNu_HT-100To200_v3.txt")
#InputTextFile = open ("../Bkg_WJets_LNu_HT-200To400_v3.txt")
#InputTextFile = open ("../Bkg_WJets_LNu_HT-400To600_v3.txt")
#InputTextFile = open ("../Bkg_WJets_LNu_HT-600To800_v3.txt")
#InputTextFile = open ("../Bkg_WJets_LNu_HT-800To1200_v3.txt")
#InputTextFile = open ("../Bkg_WJets_LNu_HT-1200To2500_v3.txt")
#InputTextFile = open ("../Bkg_WJets_LNu_HT-2500ToInf_v3.txt")




