import os


#Tb_tH_LH_M1000_merged.sh
#Tb_tH_LH_M1000_merged.jdl

#TTbar_mcbkg_test_python.txt

QCD_dataset = {
   'QCD_Pt80to120'                : '/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_QCD_MuEnr_Files/QCD_Pt*UL17'  ,
   # 'QCD_Pt120to170'               : '/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_QCD_MuEnr_Files/QCD_Pt120to170' ,
   # 'QCD_Pt170to300'               : '/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_QCD_MuEnr_Files/QCD_Pt170to300' ,
   # 'QCD_Pt300to470'               : '/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_QCD_MuEnr_Files/QCD_Pt300to470' ,
   # 'QCD_Pt470to600'               : '/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_QCD_MuEnr_Files/QCD_Pt470to600' ,
   # 'QCD_Pt600to800'               : '/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_QCD_MuEnr_Files/QCD_Pt600to800' ,
   # 'QCD_Pt800to1000'              : '/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_QCD_MuEnr_Files/QCD_Pt800to1000',
   # 'QCD_Pt1000toInf'              : '/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_QCD_MuEnr_Files/QCD_Pt1000toInf',
   }


WJetsToLNu_dataset = {   
   'WJetsToLNu'                   : '/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_Wjets_To_LNu_Files/WJets_LNu_UL17', 

  }

DYJetsToLL_dataset = {   
   'DYJetsToLL'                   : '/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_DYjetsTo_LL_Files/',
   }

SingleTop_dataset = {   
   's-channel'                    : '/eos/uscms/store/user/achhetri/PhaseII_MainTree/Background_v3_Samples/ST_s-channel_4f_leptonDecays_v3/ST_s-channel_4f_leptonDecays'  ,
   't-channel_antitop'            : '/eos/uscms/store/user/achhetri/PhaseII_MainTree/Background_v3_Samples/ST_t-channel_antitop_4f_inclusiveDecays_v3/ST_t-channel_antitop_4f_inclusiveDecays'  ,
   't-channel_top'                : '/eos/uscms/store/user/achhetri/PhaseII_MainTree/Background_v3_Samples/ST_t-channel_top_4f_inclusiveDecays_v3/ST_t-channel_top_4f_inclusiveDecays'  ,
   'tW_antitop'                   : '/eos/uscms/store/user/achhetri/PhaseII_MainTree/Background_v3_Samples/ST_tW_antitop_5f_inclusiveDecays_v3/ST_tW_antitop_5f_inclusiveDecays'  ,
   'tW_top'                       : '/eos/uscms/store/user/achhetri/PhaseII_MainTree/Background_v3_Samples/ST_tW_top_5f_inclusiveDecays_v3/ST_tW_top_5f_inclusiveDecays' ,   
   }

TTbarDataset = {
   
    'TTbar'                            : '/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_TTbar_Files/' ,
    'TT_to_Hadronic'                   : '/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_TTbar_Files/' ,
    'TT_to_SemiLeptonic'               : '/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_TTbar_Files/' ,
    'TT_to_2L2Nu'                      : '/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_TTbar_Files/' ,
}

QCDSamples = [
   'QCD_Pt80to120',        
   # 'QCD_Pt120to170',        
   # 'QCD_Pt170to300',        
   # 'QCD_Pt300to470',        
   # 'QCD_Pt470to600', 
   # 'QCD_Pt600to800',
   # 'QCD_Pt800to1000',      
   # 'QCD_Pt1000toInf',
    ]
WjetsToLNuSamples = [
   'WJetsToLNu'  
   ]
   
DYJetsToLLSamples = [
   'DYJetsToLL'  
   ]

SingleTopSamples = [
   's-channel' ,
   't-channel_antitop' ,
   't-channel_top' ,
   'tW_antitop' ,
   'tW_top' ,        
   ]

TTbarSamples = [

  'TTbar',
  'TT_to_Hadronic'     ,
  'TT_to_SemiLeptonic' ,
  'TT_to_2L2Nu'        ,
 ]













dataset = {
'1'  : '*Electronic_HiggsPT300SD90-160Deep10_2DLepIso_dR_04_OR_dPt_40_24-Feb-21.root' ,
'2'  : '*Muonic_HiggsPT300SD90-160Deep10_2DLepIso_dR_04_OR_dPt_40_24-Feb-21.root' ,
# '3'  : '*Lep_HiggsPT350SD80-160_11-Feb-21.root' ,
# '4'  : '*Lep_HiggsPT350SD90-160_11-Feb-21.root' ,
# '5'  : '*Lep_HiggsPT400SD70-160_11-Feb-21.root' ,
# '6'  : '*Muonic_LepIso_11-Feb-21.root' ,

# '7'  : '*GenStudyHiggsPT400SD70-160_20-01-21.root' ,
# '8'  : '*GenStudyHiggsPT400SD80-160_20-01-21.root' ,
# '9'  : '*GenStudyHiggsPT400SD90-160_20-01-21.root' ,
# '10' : '*GenStudyHiggsPT450SD70-160_20-01-21.root' ,
# '11' : '*GenStudyHiggsPT450SD80-160_20-01-21.root' ,
# '12' : '*GenStudyHiggsPT450SD90-160_20-01-21.root' ,


# '13' : '*HiggsPT300SD80-160Tau80MuIso_2D_dR_03_OR_dPt_20_14-01-21.root' ,
# '14' : '*HiggsPT300SD80-160Tau80MuIso_MiniIsoTight_14-01-21.root' ,
# '15' : '*HiggsPT300SD90-160NoMuIso_14-01-21.root' ,
# '16' : '*HiggsPT350SD70-160NoMuIso_14-01-21.root' ,
# '17' : '*HiggsPT350SD80-160NoMuIso_14-01-21.root' ,
# '18' : '*HiggsPT350SD90-160NoMuIso_14-01-21.root' ,
# '19' : '*HiggsPT400SD70-160NoMuIso_14-01-21.root' ,
# '20' : '*HiggsPT400SD80-160NoMuIso_14-01-21.root' ,
# '21' : '*HiggsPT400SD90-160NoMuIso_14-01-21.root' ,

# '22' : '*HiggsPT300SD80-160Tau80MuIso_2D_dR_02_OR_dPt_20_14-01-21.root' ,
# '23' : '*HiggsPT300SD80-160Tau80MuIso_2D_dR_03_OR_dPt_20_14-01-21.root' ,
# '24' : '*HiggsPT300SD80-160Tau80MuIso_MiniIsoTight_14-01-21.root' ,
   }





#nevents = -1 
eventsPerJob = {
'1'  : 'Electronic_HiggsPT300SD90-160Deep10_2DLepIso_dR_04_OR_dPt_40_24-Feb-21.root' ,
'2'  : 'Muonic_HiggsPT300SD90-160Deep10_2DLepIso_dR_04_OR_dPt_40_24-Feb-21.root' ,
# '3'  : 'Lep_HiggsPT350SD80-160_11-Feb-21.root' ,
# '4'  : 'Lep_HiggsPT350SD90-160_11-Feb-21.root' ,
# '5'  : 'Lep_HiggsPT400SD70-160_11-Feb-21.root' ,
# '6'  : 'Muonic_LepIso_11-Feb-21.root' ,
# '6'  : 'GenStudyHiggsPT350SD90-160_20-01-21.root' ,
# '7'  : 'GenStudyHiggsPT400SD70-160_20-01-21.root' ,
# '8'  : 'GenStudyHiggsPT400SD80-160_20-01-21.root' ,
# '9'  : 'GenStudyHiggsPT400SD90-160_20-01-21.root' ,
# '10' : 'GenStudyHiggsPT450SD70-160_20-01-21.root' ,
# '11' : 'GenStudyHiggsPT450SD80-160_20-01-21.root' ,
# '12' : 'GenStudyHiggsPT450SD90-160_20-01-21.root' ,

# '11' : 'HiggsPT300SD80-160NoMuIso_14-01-21.root' ,
# '12' : 'HiggsPT300SD80-160Tau80MuIso_2D_dR_02_OR_dPt_20_14-01-21.root' ,
# '13' : 'HiggsPT300SD80-160Tau80MuIso_2D_dR_03_OR_dPt_20_14-01-21.root' ,
# '14' : 'HiggsPT300SD80-160Tau80MuIso_MiniIsoTight_14-01-21.root' ,
# '15' : 'HiggsPT300SD90-160NoMuIso_14-01-21.root' ,
# '16' : 'HiggsPT350SD70-160NoMuIso_14-01-21.root' ,
# '17' : 'HiggsPT350SD80-160NoMuIso_14-01-21.root' ,
# '18' : 'HiggsPT350SD90-160NoMuIso_14-01-21.root' ,
# '19' : 'HiggsPT400SD70-160NoMuIso_14-01-21.root' ,
# '20' : 'HiggsPT400SD80-160NoMuIso_14-01-21.root' ,
# '21' : 'HiggsPT400SD90-160NoMuIso_14-01-21.root' ,
# '22' : 'HiggsPT300SD80-160Tau80MuIso_2D_dR_02_OR_dPt_20_14-01-21.root' ,
# '23' : 'HiggsPT300SD80-160Tau80MuIso_2D_dR_03_OR_dPt_20_14-01-21.root' ,
# '24' : 'HiggsPT300SD80-160Tau80MuIso_MiniIsoTight_14-01-21.root' ,

      }


listOfSamples = [
    '1'  ,
    '2'  ,
    # '3'  ,
    # '4'  ,
    # '5'  ,
    # '6'  ,
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
fr=open("QCDmultijetFiles_Hadd.sh", "w+") 
fr.write("#!/bin/bash" + "\n\n")
for samples in listOfSamples :      
            rootFileList.append(samples)
            for rootFile in rootFileList :
                         fr.write("\n\n" + "hadd -f Background_analyzed_root_files/QCD_MUEnr_UL17/QCD_MuEnr_UL17_v2_" + eventsPerJob[samples] + "   ")
                         for QCD in QCDSamples :
                             fr.write( QCD_dataset[QCD]  + dataset[samples] + "    " )
            del rootFileList[:]                                            



rootFileList = []    
fr=open("WjetsToLNuFiles_Hadd.sh", "w+") 
fr.write("#!/bin/bash" + "\n\n")
for samples in listOfSamples :      
            rootFileList.append(samples)
            for rootFile in rootFileList :
                         fr.write("\n\n" + "hadd -f Background_analyzed_root_files/Wjets_LNu_UL17/Wjets_LNu_UL17_" + eventsPerJob[samples] + "   ")
                         for Wjets in WjetsToLNuSamples :
                             fr.write( WJetsToLNu_dataset[Wjets]  + dataset[samples] + "    " )
            del rootFileList[:]   



rootFileList = []    
fr=open("DYJetsToLLFiles_Hadd.sh", "w+") 
fr.write("#!/bin/bash" + "\n\n")
for samples in listOfSamples :      
            rootFileList.append(samples)
            for rootFile in rootFileList :
                         fr.write("\n\n" + "hadd -f Background_analyzed_root_files/DYjets_LL_UL17/DYJetsToLL_UL17_" + eventsPerJob[samples] + "   ")
                         for DYJets in DYJetsToLLSamples :
                             fr.write( DYJetsToLL_dataset[DYJets]  + dataset[samples] + "    " )
            del rootFileList[:]   


 
rootFileList = []    
fr=open("SingleTopFiles_Hadd.sh", "w+") 
fr.write("#!/bin/bash" + "\n\n")
for samples in listOfSamples :      
            rootFileList.append(samples)
            for rootFile in rootFileList :
                         fr.write("\n\n" + "hadd SingleTop_" + eventsPerJob[samples] + "   ")
                         for STop in SingleTopSamples :
                             fr.write( SingleTop_dataset[STop]  + dataset[samples] + "    " )
            del rootFileList[:]   


rootFileList = []    
fr=open("TTbar_UL_Files_Hadd.sh", "w+") 
fr.write("#!/bin/bash" + "\n\n")
for samples in listOfSamples :      
            rootFileList.append(samples)
            for rootFile in rootFileList :
                         # fr.write("\n\n" + "hadd -f ../../Analyzed_Files_Nano_AOD/UL_TTbar/analyzed_root_files/TTbar_UL17_v2_" + eventsPerJob[samples] + "   ")
                         for Top in TTbarSamples :
                             fr.write("\n\n" + "hadd -f ../../Analyzed_Files_Nano_AOD/UL_TTbar/analyzed_root_files/" + Top + "_UL17_v2_" + eventsPerJob[samples] + "   ")
                             fr.write( TTbarDataset[Top]  + Top + dataset[samples] + "    " )
            del rootFileList[:]  