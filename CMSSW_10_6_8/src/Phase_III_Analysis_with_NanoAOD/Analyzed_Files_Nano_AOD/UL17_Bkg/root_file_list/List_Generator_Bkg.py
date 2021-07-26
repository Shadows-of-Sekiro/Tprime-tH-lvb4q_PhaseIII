#!/bin/python
import os


#Tb_tH_LH_M1000_merged.sh
#Tb_tH_LH_M1000_merged.jdl

#TTbar_mcbkg_test_python.txt

dataset = {
   'QCD_Pt80to120'                     : '/afs/cern.ch/work/a/achhetri/NANO_AOD/CMSSW_10_6_8/src/Phase_III_Analysis_with_NanoAOD/List_of_NANO_AOD_paths/QCD_Pt-80to120_MuEnr_UL17_v2.txt',   
   'QCD_Pt120to170'                    : '/afs/cern.ch/work/a/achhetri/NANO_AOD/CMSSW_10_6_8/src/Phase_III_Analysis_with_NanoAOD/List_of_NANO_AOD_paths/QCD_Pt-120to170_MuEnr_UL17_v2.txt',   
   'QCD_Pt170to300'                    : '/afs/cern.ch/work/a/achhetri/NANO_AOD/CMSSW_10_6_8/src/Phase_III_Analysis_with_NanoAOD/List_of_NANO_AOD_paths/QCD_Pt-170to300_MuEnr_UL17_v2.txt',   
   'QCD_Pt300to470'                    : '/afs/cern.ch/work/a/achhetri/NANO_AOD/CMSSW_10_6_8/src/Phase_III_Analysis_with_NanoAOD/List_of_NANO_AOD_paths/QCD_Pt-300to470_MuEnr_UL17_v2.txt',   
   'QCD_Pt470to600'                    : '/afs/cern.ch/work/a/achhetri/NANO_AOD/CMSSW_10_6_8/src/Phase_III_Analysis_with_NanoAOD/List_of_NANO_AOD_paths/QCD_Pt-470to600_MuEnr_UL17_v2.txt',   
   'QCD_Pt600to800'                    : '/afs/cern.ch/work/a/achhetri/NANO_AOD/CMSSW_10_6_8/src/Phase_III_Analysis_with_NanoAOD/List_of_NANO_AOD_paths/QCD_Pt-600to800_MuEnr_UL17_v2.txt',   
   'QCD_Pt800to1000'                   : '/afs/cern.ch/work/a/achhetri/NANO_AOD/CMSSW_10_6_8/src/Phase_III_Analysis_with_NanoAOD/List_of_NANO_AOD_paths/QCD_Pt-800to1000_MuEnr_UL17_v2.txt',   
   'QCD_Pt1000toInf'                   : '/afs/cern.ch/work/a/achhetri/NANO_AOD/CMSSW_10_6_8/src/Phase_III_Analysis_with_NanoAOD/List_of_NANO_AOD_paths/QCD_Pt-1000toInf_MuEnr_UL17_v2.txt',   
   'WJetsToLNu'                        : '/afs/cern.ch/work/a/achhetri/NANO_AOD/CMSSW_10_6_8/src/Phase_III_Analysis_with_NanoAOD/List_of_NANO_AOD_paths/WJetsToLNu_UL17_v2.txt',   
   'DYJetsToLL'                        : '/afs/cern.ch/work/a/achhetri/NANO_AOD/CMSSW_10_6_8/src/Phase_III_Analysis_with_NanoAOD/List_of_NANO_AOD_paths/DYJetsToLL_UL17_v2.txt',   
   'QCD_Pt-50to80_EMEnr_UL17_v2'       :'/afs/cern.ch/work/a/achhetri/NANO_AOD/CMSSW_10_6_8/src/Phase_III_Analysis_with_NanoAOD/List_of_NANO_AOD_paths/QCD_Pt-50to80_EMEnr_UL17_v2.txt',
   'QCD_Pt-80to120_EMEnr_UL17_v2'      :'/afs/cern.ch/work/a/achhetri/NANO_AOD/CMSSW_10_6_8/src/Phase_III_Analysis_with_NanoAOD/List_of_NANO_AOD_paths/QCD_Pt-80to120_EMEnr_UL17_v2.txt',
   'QCD_Pt-120to170_EMEnr_UL17_v2'     :'/afs/cern.ch/work/a/achhetri/NANO_AOD/CMSSW_10_6_8/src/Phase_III_Analysis_with_NanoAOD/List_of_NANO_AOD_paths/QCD_Pt-120to170_EMEnr_UL17_v2.txt',
   'QCD_Pt-170to300_EMEnr_UL17_v2'     :'/afs/cern.ch/work/a/achhetri/NANO_AOD/CMSSW_10_6_8/src/Phase_III_Analysis_with_NanoAOD/List_of_NANO_AOD_paths/QCD_Pt-170to300_EMEnr_UL17_v2.txt',
   'QCD_Pt-300toInf_EMEnr_UL17_v2'     :'/afs/cern.ch/work/a/achhetri/NANO_AOD/CMSSW_10_6_8/src/Phase_III_Analysis_with_NanoAOD/List_of_NANO_AOD_paths/QCD_Pt-300toInf_EMEnr_UL17_v2.txt',


   's-channel'                         : '/afs/cern.ch/work/a/achhetri/NANO_AOD/CMSSW_10_6_8/src/Phase_III_Analysis_with_NanoAOD/List_of_NANO_AOD_paths/ST_s-channel_4f_leptonDecays_UL17_v2.txt',   
   't-channel_antitop'                 : '/afs/cern.ch/work/a/achhetri/NANO_AOD/CMSSW_10_6_8/src/Phase_III_Analysis_with_NanoAOD/List_of_NANO_AOD_paths/ST_t-channel_antitop_4f_inclusiveDecays_UL17_v2.txt',   
   't-channel_top'                     : '/afs/cern.ch/work/a/achhetri/NANO_AOD/CMSSW_10_6_8/src/Phase_III_Analysis_with_NanoAOD/List_of_NANO_AOD_paths/ST_t-channel_top_4f_inclusiveDecays_UL17_v2.txt',   
   'tW_antitop'                        : '/afs/cern.ch/work/a/achhetri/NANO_AOD/CMSSW_10_6_8/src/Phase_III_Analysis_with_NanoAOD/List_of_NANO_AOD_paths/ST_tW_antitop_5f_inclusiveDecays_UL17_v2.txt',   
   'tW_top'                            : '/afs/cern.ch/work/a/achhetri/NANO_AOD/CMSSW_10_6_8/src/Phase_III_Analysis_with_NanoAOD/List_of_NANO_AOD_paths/ST_tW_top_5f_inclusiveDecays_UL17_v2.txt',   

   'WJets_LNu_HT-100To200'                 : '/afs/cern.ch/work/a/achhetri/NANO_AOD/CMSSW_10_6_8/src/Phase_III_Analysis_with_NanoAOD/List_of_NANO_AOD_paths/WJets_LNu_HT-100To200_UL17_v2.txt',   
   'WJets_LNu_HT-200To400'                 : '/afs/cern.ch/work/a/achhetri/NANO_AOD/CMSSW_10_6_8/src/Phase_III_Analysis_with_NanoAOD/List_of_NANO_AOD_paths/WJets_LNu_HT-200To400_UL17_v2.txt',   
   
   'DYJetsToLL_M-50_HT-100To200'              : '/afs/cern.ch/work/a/achhetri/NANO_AOD/CMSSW_10_6_8/src/Phase_III_Analysis_with_NanoAOD/List_of_NANO_AOD_paths/DYJetsToLL_M-50_HT-100To200_UL17_v2.txt',      
   'DYJetsToLL_M-50_HT-600To800'              : '/afs/cern.ch/work/a/achhetri/NANO_AOD/CMSSW_10_6_8/src/Phase_III_Analysis_with_NanoAOD/List_of_NANO_AOD_paths/DYJetsToLL_M-50_HT-600To800_UL17_v2.txt',      

   }


# HERE ESPECIALLY FOR  DYJetsToLL_M-50_HT-600To800,SAMPLE FILES ARE FIRST PARTED INTO 10 FILES SET AND THEN FURTHER DIVIDED INTO SINGLE FILE LIST
# DUE TO NON UNIFORM FILE SIZES IN SAMPLES nTUPLES



#nevents = -1 
eventsPerJob = {
   'QCD_Pt80to120'                : 'QCD_Pt-80_MuEnr_UL17_v2_',        
   'QCD_Pt120to170'               : 'QCD_Pt-120_MuEnr_UL17_v2_',        
   'QCD_Pt170to300'               : 'QCD_Pt-170_MuEnr_UL17_v2_',        
   'QCD_Pt300to470'               : 'QCD_Pt-300_MuEnr_UL17_v2_',        
   'QCD_Pt470to600'               : 'QCD_Pt-470_MuEnr_UL17_v2_', 
   'QCD_Pt600to800'               : 'QCD_Pt-600_MuEnr_UL17_v2_',
   'QCD_Pt800to1000'              : 'QCD_Pt-800_MuEnr_UL17_v2_',      
   'QCD_Pt1000toInf'              : 'QCD_Pt-1000_MuEnr_UL17_v2_',
   'WJetsToLNu'                   : 'WJets_LNu_UL17_v2_',
   'DYJetsToLL'                   : 'DYJetsToLL_UL17_v2_',

   'QCD_Pt-50to80_EMEnr_UL17_v2'       : 'QCD_Pt-50_EMEnr_UL17_v2_'      ,
   'QCD_Pt-80to120_EMEnr_UL17_v2'      : 'QCD_Pt-80_EMEnr_UL17_v2_'     ,
   'QCD_Pt-120to170_EMEnr_UL17_v2'     : 'QCD_Pt-120_EMEnr_UL17_v2_'    ,
   'QCD_Pt-170to300_EMEnr_UL17_v2'     : 'QCD_Pt-170_EMEnr_UL17_v2_'    ,
   'QCD_Pt-300toInf_EMEnr_UL17_v2'     : 'QCD_Pt-300_EMEnr_UL17_v2_'       ,

   's-channel'                         : 'ST_s-channel_4f_leptonDecays_UL17_v2_'       ,
   't-channel_antitop'                 : 'ST_t-channel_antitop_4f_inclusiveDecays_UL17_v2_'       ,
   't-channel_top'                     : 'ST_t-channel_top_4f_inclusiveDecays_UL17_v2_'       ,
   'tW_antitop'                        : 'ST_tW_antitop_5f_inclusiveDecays_UL17_v2_'       ,
   'tW_top'                            : 'ST_tW_top_5f_inclusiveDecays_UL17_v2_'       ,

   'WJets_LNu_HT-100To200'                 : 'WJets_LNu_HT-100To200_UL17_v2_'  ,   
   'WJets_LNu_HT-200To400'                 : 'WJets_LNu_HT-200To400_UL17_v2_',   

   'DYJetsToLL_M-50_HT-100To200'              : 'DYJetsToLL_M-50_HT-100To200_UL17_v2_',      
   'DYJetsToLL_M-50_HT-600To800'              : 'DYJetsToLL_M-50_HT-600To800_UL17_v2_',      

   }

listOfSamples = [
   # 'QCD_Pt80to120',        
   # 'QCD_Pt120to170',        
   # 'QCD_Pt170to300',        
   # 'QCD_Pt300to470',        
   # 'QCD_Pt470to600', 
   # 'QCD_Pt600to800',
   # 'QCD_Pt800to1000',      
   # 'QCD_Pt1000toInf',
   # 'WJetsToLNu' ,  
   # 'DYJetsToLL' ,  
   # 'QCD_Pt-50to80_EMEnr_UL17_v2'  , 
   # 'QCD_Pt-80to120_EMEnr_UL17_v2' ,
   # 'QCD_Pt-120to170_EMEnr_UL17_v2',
   # 'QCD_Pt-170to300_EMEnr_UL17_v2',
   # 'QCD_Pt-300toInf_EMEnr_UL17_v2',

   # 's-channel' ,
   # 't-channel_antitop' ,
   # 't-channel_top' ,
   # 'tW_antitop' ,
   # 'tW_top' ,   

   # 'WJets_LNu_HT-100To200' ,
   # 'WJets_LNu_HT-200To400' ,          

   # 'DYJetsToLL_M-50_HT-100To200',    
   'DYJetsToLL_M-50_HT-600To800',    
   
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
         check = count % 10
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




