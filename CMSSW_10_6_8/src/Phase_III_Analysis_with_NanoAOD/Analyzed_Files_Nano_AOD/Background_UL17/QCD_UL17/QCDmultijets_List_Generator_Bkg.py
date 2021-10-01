#!/bin/python
import os


#Tb_tH_LH_M1000_merged.sh
#Tb_tH_LH_M1000_merged.jdl

#TTbar_mcbkg_test_python.txt

dataset = {

   'QCD_Pt170to300'                    : '/afs/cern.ch/work/a/achhetri/Tprime-tH-lvb4q_PhaseIII/CMSSW_10_6_8/src/Phase_III_Analysis_with_NanoAOD/List_of_NANO_AOD_paths/QCD_Pt-170to300_MuEnr_UL17_v2.txt',   
   'QCD_Pt300to470'                    : '/afs/cern.ch/work/a/achhetri/Tprime-tH-lvb4q_PhaseIII/CMSSW_10_6_8/src/Phase_III_Analysis_with_NanoAOD/List_of_NANO_AOD_paths/QCD_Pt-300to470_MuEnr_UL17_v2.txt',   
   'QCD_Pt470to600'                    : '/afs/cern.ch/work/a/achhetri/Tprime-tH-lvb4q_PhaseIII/CMSSW_10_6_8/src/Phase_III_Analysis_with_NanoAOD/List_of_NANO_AOD_paths/QCD_Pt-470to600_MuEnr_UL17_v2.txt',   
   'QCD_Pt600to800'                    : '/afs/cern.ch/work/a/achhetri/Tprime-tH-lvb4q_PhaseIII/CMSSW_10_6_8/src/Phase_III_Analysis_with_NanoAOD/List_of_NANO_AOD_paths/QCD_Pt-600to800_MuEnr_UL17_v2.txt',   
   'QCD_Pt800to1000'                   : '/afs/cern.ch/work/a/achhetri/Tprime-tH-lvb4q_PhaseIII/CMSSW_10_6_8/src/Phase_III_Analysis_with_NanoAOD/List_of_NANO_AOD_paths/QCD_Pt-800to1000_MuEnr_UL17_v2.txt',   
   'QCD_Pt1000toInf'                   : '/afs/cern.ch/work/a/achhetri/Tprime-tH-lvb4q_PhaseIII/CMSSW_10_6_8/src/Phase_III_Analysis_with_NanoAOD/List_of_NANO_AOD_paths/QCD_Pt-1000toInf_MuEnr_UL17_v2.txt',   




   # 'QCD_Pt-170to300_EMEnr_UL17_v2'     :'/afs/cern.ch/work/a/achhetri/Tprime-tH-lvb4q_PhaseIII/CMSSW_10_6_8/src/Phase_III_Analysis_with_NanoAOD/List_of_NANO_AOD_paths/QCD_Pt-170to300_EMEnr_UL17_v2.txt',
   'QCD_Pt-300toInf_EMEnr_UL17_v2'     :'/afs/cern.ch/work/a/achhetri/Tprime-tH-lvb4q_PhaseIII/CMSSW_10_6_8/src/Phase_III_Analysis_with_NanoAOD/List_of_NANO_AOD_paths/QCD_Pt-300toInf_EMEnr_UL17_v2.txt',


   }


# HERE ESPECIALLY FOR  DYJetsToLL_M-50_HT-600To800,SAMPLE FILES ARE FIRST PARTED INTO 10 FILES SET AND THEN FURTHER DIVIDED INTO SINGLE FILE LIST
# DUE TO NON UNIFORM FILE SIZES IN SAMPLES nTUPLES



#nevents = -1 
eventsPerJob = {


   'QCD_Pt170to300'               : 'QCD_Pt-170_MuEnr_UL17_v2_',        
   'QCD_Pt300to470'               : 'QCD_Pt-300_MuEnr_UL17_v2_',        
   'QCD_Pt470to600'               : 'QCD_Pt-470_MuEnr_UL17_v2_', 
   'QCD_Pt600to800'               : 'QCD_Pt-600_MuEnr_UL17_v2_',
   'QCD_Pt800to1000'              : 'QCD_Pt-800_MuEnr_UL17_v2_',      
   'QCD_Pt1000toInf'              : 'QCD_Pt-1000_MuEnr_UL17_v2_',


   # 'QCD_Pt-170to300_EMEnr_UL17_v2'     : 'QCD_Pt-170_EMEnr_UL17_v2_'    ,
   
   'QCD_Pt-300toInf_EMEnr_UL17_v2'     : 'QCD_Pt-300_EMEnr_UL17_v2_'       ,


   }

TotalUnitsPerJob = {  

   'QCD_Pt170to300'               : 3,        
   'QCD_Pt300to470'               : 5,        
   'QCD_Pt470to600'               : 2, 
   'QCD_Pt600to800'               : 3,
   'QCD_Pt800to1000'              : 3,      
   'QCD_Pt1000toInf'              : 3,


   # 'QCD_Pt-170to300_EMEnr_UL17_v2'     : 'QCD_Pt-170_EMEnr_UL17_v2_'    ,
   
   'QCD_Pt-300toInf_EMEnr_UL17_v2'     : 4       ,
   }   

listOfSamples = [


   'QCD_Pt170to300',        
   'QCD_Pt300to470',        
   'QCD_Pt470to600', 
   'QCD_Pt600to800',
   'QCD_Pt800to1000',      
   'QCD_Pt1000toInf',



   # 'QCD_Pt-170to300_EMEnr_UL17_v2',
   'QCD_Pt-300toInf_EMEnr_UL17_v2',


   
   ]


listOfSamples.reverse()
# os.system ("rm WJets*UL*.txt")
# os.system ("rm DY*UL*.txt")
# os.system ("rm QCD*UL*.txt")
# os.system ("rm ST*UL*.txt")

for samples in listOfSamples :
     
     InputTextFile = open (dataset[samples])
     lines = InputTextFile.readlines()
     totalFiles = len(lines)
     
     count=0
     textfileNumber = 0
     rootFileList = []
     for line in lines : 
         count+=1
         check = count % TotalUnitsPerJob[samples]
         rootFileList.append(line)
         if (check == 0) :
            textfileNumber += 1
            filename = eventsPerJob[samples]+str(textfileNumber)+".txt"

            with open(filename, 'w+') as f:
                 for rootFile in rootFileList :
                     f.write(rootFile)                     
            del rootFileList[:]
         if (count == totalFiles) :
            textfileNumber += 1
            filename = eventsPerJob[samples]+str(textfileNumber)+".txt"
            with open(filename, 'w+') as f:
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




