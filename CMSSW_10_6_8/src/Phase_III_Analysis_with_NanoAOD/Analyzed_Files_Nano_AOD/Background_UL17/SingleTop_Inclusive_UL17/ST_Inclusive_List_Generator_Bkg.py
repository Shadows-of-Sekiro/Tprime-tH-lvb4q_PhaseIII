#!/bin/python
import os


#Tb_tH_LH_M1000_merged.sh
#Tb_tH_LH_M1000_merged.jdl

#TTbar_mcbkg_test_python.txt

dataset = {


   's-channel'                         : '/afs/cern.ch/work/a/achhetri/Tprime-tH-lvb4q_PhaseIII/CMSSW_10_6_8/src/Phase_III_Analysis_with_NanoAOD/List_of_NANO_AOD_paths/ST_s-channel_4f_leptonDecays_UL17_v2.txt',   
   't-channel_antitop'                 : '/afs/cern.ch/work/a/achhetri/Tprime-tH-lvb4q_PhaseIII/CMSSW_10_6_8/src/Phase_III_Analysis_with_NanoAOD/List_of_NANO_AOD_paths/ST_t-channel_antitop_4f_inclusiveDecays_UL17_v2.txt',   
   't-channel_top'                     : '/afs/cern.ch/work/a/achhetri/Tprime-tH-lvb4q_PhaseIII/CMSSW_10_6_8/src/Phase_III_Analysis_with_NanoAOD/List_of_NANO_AOD_paths/ST_t-channel_top_4f_inclusiveDecays_UL17_v2.txt',   
   'tW_antitop'                        : '/afs/cern.ch/work/a/achhetri/Tprime-tH-lvb4q_PhaseIII/CMSSW_10_6_8/src/Phase_III_Analysis_with_NanoAOD/List_of_NANO_AOD_paths/ST_tW_antitop_5f_inclusiveDecays_UL17_v2.txt',   
   'tW_top'                            : '/afs/cern.ch/work/a/achhetri/Tprime-tH-lvb4q_PhaseIII/CMSSW_10_6_8/src/Phase_III_Analysis_with_NanoAOD/List_of_NANO_AOD_paths/ST_tW_top_5f_inclusiveDecays_UL17_v2.txt',   


   }


# HERE ESPECIALLY FOR  DYJetsToLL_M-50_HT-600To800,SAMPLE FILES ARE FIRST PARTED INTO 10 FILES SET AND THEN FURTHER DIVIDED INTO SINGLE FILE LIST
# DUE TO NON UNIFORM FILE SIZES IN SAMPLES nTUPLES



#nevents = -1 
eventsPerJob = {


   's-channel'                         : 'ST_s-channel_4f_leptonDecays_UL17_v2_'       ,
   't-channel_antitop'                 : 'ST_t-channel_antitop_4f_inclusiveDecays_UL17_v2_'       ,
   't-channel_top'                     : 'ST_t-channel_top_4f_inclusiveDecays_UL17_v2_'       ,
   'tW_antitop'                        : 'ST_tW_antitop_5f_inclusiveDecays_UL17_v2_'       ,
   'tW_top'                            : 'ST_tW_top_5f_inclusiveDecays_UL17_v2_'       ,


   }

TotalUnitsPerJob = {  

   's-channel'                         : 4,
   't-channel_antitop'                 : 4,
   't-channel_top'                     : 4,
   'tW_antitop'                        : 4,
   'tW_top'                            : 3,

   }   


listOfSamples = [

   's-channel' ,
   't-channel_antitop' ,
   't-channel_top' ,
   'tW_antitop' ,
   'tW_top' ,   


   
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




