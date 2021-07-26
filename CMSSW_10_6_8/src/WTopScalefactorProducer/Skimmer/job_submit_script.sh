#!/bin/tcsh

rm output_log/condor_*


#eosrm -r /eos/uscms/store/user/achhetri/PhaseII_MainTree/Background_v3_Samples/Bkg_QCD_Pt-80to120_MuEnr_v3/ 
#eosrm -r /eos/uscms/store/user/achhetri/PhaseII_MainTree/Background_v3_Samples/Bkg_QCD_Pt-120to170_MuEnr_v3/

#eosls  /eos/uscms/store/user/achhetri/

#eosmkdir /eos/uscms/store/user/achhetri/PhaseII_MainTree/Background_v3_Samples/Bkg_QCD_Pt-80to120_MuEnr_v3 
#eosmkdir /eos/uscms/store/user/achhetri/PhaseII_MainTree/Background_v3_Samples/Bkg_QCD_Pt-120to170_MuEnr_v3


cd ../../../../

rm CMSSW_10_68.tgz

tar  --exclude=tmp --exclude=.git --exclude=NANOAOD  --exclude=DAS_Root --exclude=NANO_crab -zcvf CMSSW_10_68.tgz CMSSW_10_6_8

#eosrm  /eos/uscms/store/user/achhetri/CMSSW_10_68.tgz

xrdcp -f CMSSW_10_68.tgz root://eosuser.cern.ch//eos/user/a/achhetri/.

ls -ltrh

cd -

# condor_submit condor_test_Nano_AOD.jdl
# # condor_submit test.jdl
# # 
# condor_q

# eosls -ltrh /eos/uscms/store/user/achhetri/PhaseII_MainTree/Background_v3_Samples/
ls -ltrh
