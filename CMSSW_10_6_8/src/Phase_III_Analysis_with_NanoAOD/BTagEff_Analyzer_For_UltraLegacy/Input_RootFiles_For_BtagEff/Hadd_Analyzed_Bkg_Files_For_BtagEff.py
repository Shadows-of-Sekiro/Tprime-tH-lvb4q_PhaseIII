import os


#Tb_tH_LH_M1000_merged.sh
#Tb_tH_LH_M1000_merged.jdl

#TTbar_mcbkg_test_python.txt

QCDMuEnr_dataset = {
   'QCD_EMEnr_UL17'                : '/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_QCD_MuEnr_Files/QCD_Pt*EMEnr_*UL17'  ,


   'QCD_Pt-80_MuEnr'                : '/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_QCD_MuEnr_Files/QCD_Pt-80_MuEnr'  ,
   'QCD_Pt-120_MuEnr'               : '/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_QCD_MuEnr_Files/QCD_Pt-120_MuEnr' ,
   'QCD_Pt-170_MuEnr'               : '/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_QCD_MuEnr_Files/QCD_Pt-170_MuEnr' ,
   'QCD_Pt-300_MuEnr'               : '/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_QCD_MuEnr_Files/QCD_Pt-300_MuEnr' ,
   'QCD_Pt-470_MuEnr'               : '/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_QCD_MuEnr_Files/QCD_Pt-470_MuEnr' ,
   'QCD_Pt-600_MuEnr'               : '/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_QCD_MuEnr_Files/QCD_Pt-600_MuEnr' ,
   'QCD_Pt-800_MuEnr'               : '/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_QCD_MuEnr_Files/QCD_Pt-800_MuEnr',
   'QCD_Pt-1000_MuEnr'              : '/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_QCD_MuEnr_Files/QCD_Pt-1000_MuEnr',
   }




QCDMuEnr_Samples = [

    'QCD_Pt-80_MuEnr' ,   
    'QCD_Pt-120_MuEnr',  
    'QCD_Pt-170_MuEnr',  
    'QCD_Pt-300_MuEnr',  
    'QCD_Pt-470_MuEnr',  
    'QCD_Pt-600_MuEnr',  
    'QCD_Pt-800_MuEnr',  
    'QCD_Pt-1000_MuEnr', 

   
    ]


QCDEMEnr_dataset = {

   'QCD_Pt-50_EMEnr'                : '/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_QCD_MuEnr_Files/QCD_Pt-50_EMEnr' ,
   'QCD_Pt-80_EMEnr'                : '/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_QCD_MuEnr_Files/QCD_Pt-80_EMEnr' ,
   'QCD_Pt-120_EMEnr'               : '/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_QCD_MuEnr_Files/QCD_Pt-120_EMEnr',
   'QCD_Pt-170_EMEnr'               : '/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_QCD_MuEnr_Files/QCD_Pt-170_EMEnr',
   'QCD_Pt-300_EMEnr'               : '/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_QCD_MuEnr_Files/QCD_Pt-300_EMEnr',
   
   }



QCDEMEnr_Samples = [

     'QCD_Pt-50_EMEnr'  ,
     'QCD_Pt-80_EMEnr'  ,
     'QCD_Pt-120_EMEnr' ,
     'QCD_Pt-170_EMEnr' ,
     'QCD_Pt-300_EMEnr' ,

    ]


TTbarDataset = {
   
    'TTbar'                            : '/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_TTbar_Files/' ,
    'TT_to_Hadronic'                   : '/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_TTbar_Files/' ,
    'TT_to_SemiLeptonic'               : '/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_TTbar_Files/' ,
    'TT_to_2L2Nu'                      : '/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_TTbar_Files/' ,
    'TTbar_Incl'                       : '/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_TTbar_Files/TT_to_' ,
}
   

TTbarSamples = [

  # 'TTbar',
  'TT_to_Hadronic'     ,
  'TT_to_SemiLeptonic' ,
  'TT_to_2L2Nu'        ,
  # 'TTbar_Incl'          ,
 ]


SingleTopSamples = [

   'ST_s-channel' ,
   'ST_t-channel_antitop' ,
   'ST_t-channel_top' ,
   'ST_tW_antitop' ,
   'ST_tW_top' ,        
   ]




SingleTop_dataset = {   
   
   'ST_s-channel'               : '/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_SingleTop_Files/ST_s-channel_4f_leptonDecays'         ,
   'ST_t-channel_antitop'       : '/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_SingleTop_Files/ST_t-channel_antitop_4f_inclusiveDecays' ,
   'ST_t-channel_top'           : '/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_SingleTop_Files/ST_t-channel_top_4f_inclusiveDecays'     ,
   'ST_tW_antitop'              : '/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_SingleTop_Files/ST_tW_antitop_5f_inclusiveDecays'        ,
   'ST_tW_top'                  : '/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_SingleTop_Files/ST_tW_top_5f_inclusiveDecays'            , 
   
   }

DYJetsToLL_HTbin_Dataset = {
'DYJetsToLL_M-50_HT-70To100'         :'/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_DYjetsTo_LL_Files/DYJetsToLL_M-50_HT-70To100',
'DYJetsToLL_M-50_HT-100To200'        :'/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_DYjetsTo_LL_Files/DYJetsToLL_M-50_HT-100To200',
'DYJetsToLL_M-50_HT-200To400'        :'/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_DYjetsTo_LL_Files/DYJetsToLL_M-50_HT-200To400',
'DYJetsToLL_M-50_HT-400To600'        :'/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_DYjetsTo_LL_Files/DYJetsToLL_M-50_HT-400To600',
'DYJetsToLL_M-50_HT-600To800'        :'/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_DYjetsTo_LL_Files/DYJetsToLL_M-50_HT-600To800',
'DYJetsToLL_M-50_HT-800To1200'       :'/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_DYjetsTo_LL_Files/DYJetsToLL_M-50_HT-800To1200',
'DYJetsToLL_M-50_HT-1200To2500'      :'/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_DYjetsTo_LL_Files/DYJetsToLL_M-50_HT-1200To2500',
'DYJetsToLL_M-50_HT-2500ToInf'       :'/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_DYjetsTo_LL_Files/DYJetsToLL_M-50_HT-2500ToInf',

}




DYJetsToLL_HTbin_Samples = [
'DYJetsToLL_M-50_HT-70To100'      ,
'DYJetsToLL_M-50_HT-100To200'     ,
'DYJetsToLL_M-50_HT-200To400'     ,
'DYJetsToLL_M-50_HT-400To600'     ,
'DYJetsToLL_M-50_HT-600To800'     ,
'DYJetsToLL_M-50_HT-800To1200'    ,
'DYJetsToLL_M-50_HT-1200To2500'   ,
'DYJetsToLL_M-50_HT-2500ToInf'    ,

]



WJetsToLNu_dataset  = {
'WJets_LNu_HT-70To100'         :'/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_Wjets_To_LNu_Files/WJets_LNu_HT-70To100'   ,
'WJets_LNu_HT-100To200'        :'/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_Wjets_To_LNu_Files/WJets_LNu_HT-100To200'  ,
'WJets_LNu_HT-200To400'        :'/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_Wjets_To_LNu_Files/WJets_LNu_HT-200To400'  ,
'WJets_LNu_HT-400To600'        :'/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_Wjets_To_LNu_Files/WJets_LNu_HT-400To600'  ,
'WJets_LNu_HT-600To800'        :'/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_Wjets_To_LNu_Files/WJets_LNu_HT-600To800'  ,
'WJets_LNu_HT-800To1200'       :'/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_Wjets_To_LNu_Files/WJets_LNu_HT-800To1200' ,
'WJets_LNu_HT-1200To2500'      :'/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_Wjets_To_LNu_Files/WJets_LNu_HT-1200To2500',
'WJets_LNu_HT-2500ToInf'       :'/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_Wjets_To_LNu_Files/WJets_LNu_HT-2500ToInf' ,

}

WjetsToLNuSamples = [

'WJets_LNu_HT-70To100' ,
'WJets_LNu_HT-100To200' ,
'WJets_LNu_HT-200To400' ,
'WJets_LNu_HT-400To600' ,
'WJets_LNu_HT-600To800' ,
'WJets_LNu_HT-800To1200' ,
'WJets_LNu_HT-1200To2500' ,
'WJets_LNu_HT-2500ToInf' ,


]



dataset = {

'1'      : '*BtagEff_2DPtEta_02-Aug-21.root' ,

# '1'     : '*Electronic_HiggsDeepMD_2DLepIso_EvntLvlv2_02-Apr-21.root' ,
# '2'     : '*Electronic_HiggsDeepMD_2DLepIso_L1VFP_02-Apr-21.root' ,
# '3'     : '*Electronic_HiggsDeepMD_2DLepIso_MCSampleWithPileUp692_02-Apr-21.root' ,
# '4'     : '*Electronic_HiggsDeepMD_2DLepIso_MCSampleWithPileUp724_02-Apr-21.root' ,
# '5'     : '*Electronic_HiggsDeepMD_2DLepIso__EvntW_02-Apr-21.root' ,
# '6'     : '*Muonic_HiggsDeepMD_2DLepIso_EvntLvlv2_02-Apr-21.root' ,
# '7'     : '*Muonic_HiggsDeepMD_2DLepIso_L1VFP_02-Apr-21.root' ,
# '8'     : '*Muonic_HiggsDeepMD_2DLepIso_MCSampleWithPileUp692_02-Apr-21.root' ,
# '9'     : '*Muonic_HiggsDeepMD_2DLepIso_MCSampleWithPileUp724_02-Apr-21.root' ,
# '10'    : '*Muonic_HiggsDeepMD_2DLepIso__EvntW_02-Apr-21.root' ,

   }





#nevents = -1 
eventsPerJob = {
'1'      : 'BtagEff_2DPtEta_02-Aug-21.root' ,

# '1'     : 'Electronic_HiggsDeepMD_2DLepIso_EvntLvlv2_02-Apr-21.root' ,
# '2'     : 'Electronic_HiggsDeepMD_2DLepIso_L1VFP_02-Apr-21.root' ,
# '3'     : 'Electronic_HiggsDeepMD_2DLepIso_MCSampleWithPileUp692_02-Apr-21.root' ,
# '4'     : 'Electronic_HiggsDeepMD_2DLepIso_MCSampleWithPileUp724_02-Apr-21.root' ,
# '5'     : 'Electronic_HiggsDeepMD_2DLepIso__EvntW_02-Apr-21.root' ,
# '6'     : 'Muonic_HiggsDeepMD_2DLepIso_EvntLvlv2_02-Apr-21.root' ,
# '7'     : 'Muonic_HiggsDeepMD_2DLepIso_L1VFP_02-Apr-21.root' ,
# '8'     : 'Muonic_HiggsDeepMD_2DLepIso_MCSampleWithPileUp692_02-Apr-21.root' ,
# '9'     : 'Muonic_HiggsDeepMD_2DLepIso_MCSampleWithPileUp724_02-Apr-21.root' ,
# '10'    : 'Muonic_HiggsDeepMD_2DLepIso__EvntW_02-Apr-21.root' ,

      }


listOfSamples = [
    '1'  ,
    # '2'  ,
    # '3'  ,
    # '4'  ,
    # '5'  ,
    # '6'  ,
    # '7'  ,
    # '8'  ,
    # '9'  ,
    # '10' ,
  # '13' ,
  # '14' ,
  # '15' ,
  # '16' ,
  # '17' ,
  # '18' ,
  # '19' ,
  # '20' ,  
  # '21' ,
  # '22' ,
  # '23' ,
  # '24' ,
   ]


listOfSamples.reverse()
# os.system ("rm *Hadd.sh")

     # InputTextFile = open (dataset[samples])S
     # lines = InputTextFile.readlines()
     
     # count=0
     # textfileNumber = 0


rootFileList = []    
fr=open("QCDmultijet_MuEnrFiles_Hadd.sh", "w+") 
fr.write("#!/bin/bash" + "\n\n")
for samples in listOfSamples :      
            rootFileList.append(samples)
            for rootFile in rootFileList :
                         for QCD in QCDMuEnr_Samples :
                             fr.write("\n\n" + "hadd -f " + QCD  + "_UL17_v2_" + eventsPerJob[samples] + "   ")                           
                             fr.write( QCDMuEnr_dataset[QCD]  + dataset[samples] + "    " )
            del rootFileList[:]                                            




rootFileList = []    
fr=open("QCDmultijet_EMEnrFiles_Hadd.sh", "w+") 
fr.write("#!/bin/bash" + "\n\n")
for samples in listOfSamples :      
            rootFileList.append(samples)
            for rootFile in rootFileList :
                         for QCD in QCDEMEnr_Samples :
                             fr.write("\n\n" + "hadd -f " + QCD  + "_UL17_v2_" + eventsPerJob[samples] + "   ")                           
                             fr.write( QCDEMEnr_dataset[QCD]  + dataset[samples] + "    " )
            del rootFileList[:]                                            


 

rootFileList = []    
fr=open("TTbar_UL_Files_Hadd.sh", "w+") 
fr.write("#!/bin/bash" + "\n\n")
for samples in listOfSamples :      
            rootFileList.append(samples)
            for rootFile in rootFileList :
                         # fr.write("\n\n" + "hadd -f ../../Analyzed_Files_Nano_AOD/UL_TTbar/analyzed_root_files/TTbar_UL17_v2_" + eventsPerJob[samples] + "   ")
                         for Top in TTbarSamples :                           
                             if Top.find("Incl") != -1 :
                                fr.write("\n\n" + "hadd -f " + Top + "_UL17_v2_" + eventsPerJob[samples] + "   ")
                                fr.write( TTbarDataset[Top]  + dataset[samples] + "    " )
                             else  :
                                fr.write("\n\n" + "hadd -f " + Top + "_UL17_v2_" + eventsPerJob[samples] + "   ")
                                fr.write( TTbarDataset[Top]  + Top + dataset[samples] + "    " )
            del rootFileList[:]  


rootFileList = []    
fr=open("DYJetsToLL_SingleFiles_Hadd.sh", "w+") 
fr.write("#!/bin/bash" + "\n\n")
for samples in listOfSamples :      
            rootFileList.append(samples)
            for rootFile in rootFileList :
                         for DYJets in DYJetsToLL_HTbin_Samples :
                               fr.write("\n\n" + "hadd -f " + DYJets + "_UL17_v2_" + eventsPerJob[samples] + "   ")
                               fr.write( DYJetsToLL_HTbin_Dataset[DYJets]  + dataset[samples] + "    " )

            del rootFileList[:]               


rootFileList = []    
fr=open("WjetsToLNuFiles_Hadd.sh", "w+") 
fr.write("#!/bin/bash" + "\n\n")
for samples in listOfSamples :      
            rootFileList.append(samples)
            for rootFile in rootFileList :
                         for Wjets in WjetsToLNuSamples :
                             fr.write("\n\n" + "hadd -f " + Wjets + "_UL17_v2_" + eventsPerJob[samples] + "   ")
                             fr.write( WJetsToLNu_dataset[Wjets]  + dataset[samples] + "    " )
            del rootFileList[:]  

rootFileList = []    
fr=open("SingleTopFiles_Hadd.sh", "w+") 
fr.write("#!/bin/bash" + "\n\n")
for samples in listOfSamples :      
            rootFileList.append(samples)
            for rootFile in rootFileList :
                         for STop in SingleTopSamples :
                             fr.write("\n\n" + "hadd -f " + STop + "_UL17_v2_" + eventsPerJob[samples] + "   ")
                             fr.write( SingleTop_dataset[STop]  + dataset[samples] + "    " )
            del rootFileList[:]                