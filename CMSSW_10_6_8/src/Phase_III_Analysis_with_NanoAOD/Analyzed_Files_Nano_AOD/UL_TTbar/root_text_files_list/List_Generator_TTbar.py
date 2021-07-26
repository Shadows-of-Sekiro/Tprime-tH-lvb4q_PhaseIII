#!/bin/python
import os


#Tb_tH_LH_M1000_merged.sh
#Tb_tH_LH_M1000_merged.jdl

#TTbar_mcbkg_test_python.txt

dataset = {
   # 'TTbar_v3'                         : '/afs/cern.ch/work/a/achhetri/NANO_AOD/CMSSW_10_6_8/src/Phase_III_Analysis_with_NanoAOD/List_of_NANO_AOD_paths/TTbar_UL16.txt',   
   'TTbar_Nanov2'                     : '/afs/cern.ch/work/a/achhetri/NANO_AOD/CMSSW_10_6_8/src/Phase_III_Analysis_with_NanoAOD/List_of_NANO_AOD_paths/TTbar_UL17_v2.txt',
   'TT_to_Hadronic'                   : '/afs/cern.ch/work/a/achhetri/NANO_AOD/CMSSW_10_6_8/src/Phase_III_Analysis_with_NanoAOD/List_of_NANO_AOD_paths/TT_to_Hadronic_UL17.txt',
   'TT_to_SemiLeptonic'               : '/afs/cern.ch/work/a/achhetri/NANO_AOD/CMSSW_10_6_8/src/Phase_III_Analysis_with_NanoAOD/List_of_NANO_AOD_paths/TT_to_SemiLeptonic_UL17.txt',
   'TT_to_2L2Nu'                      : '/afs/cern.ch/work/a/achhetri/NANO_AOD/CMSSW_10_6_8/src/Phase_III_Analysis_with_NanoAOD/List_of_NANO_AOD_paths/TT_to_2L2Nu_UL17.txt',  
   }


#nevents = -1 
eventsPerJob = {
   # 'TTbar_v3'                     : 'TTbar_UL17_',
   'TTbar_Nanov2'                     : 'TTbar_UL17_v2_',
   'TT_to_Hadronic'                   : 'TT_to_Hadronic_UL17_v2_'    , 
   'TT_to_SemiLeptonic'               : 'TT_to_SemiLeptonic_UL17_v2_', 
   'TT_to_2L2Nu'                      : 'TT_to_2L2Nu_UL17_v2_'       ,    
  }

listOfSamples = [   
   # 'TTbar_v3' , 
   'TTbar_Nanov2',  
   'TT_to_Hadronic'                   ,
   'TT_to_SemiLeptonic'               ,
   'TT_to_2L2Nu'                      ,          
   ]


listOfSamples.reverse()
os.system ("rm *UL*.txt")
os.system ("rm *.root")
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



