# Muon 2017 UL SFs 

## Files description

* RunBCDEF_SF_ISO.root, RunBCDEF_SF_ID.root: Iso and Id Scale-Factors with statistical uncertainties. 
histo->GetBinContent(i,j) returns the Scale-factor value while  histo->GetBinError(i,j) returns the statistical uncertaty of the (i,j) bin
* RunBCDEF_Eff_ISO.root, RunBCDEF_Eff_ID.root: Iso and Id efficiencies with statistical uncertainties
* RunBCDEF_SYS_ID.root : Id Scale-Factors with systematic uncertainties. In this case histo->GetBinError(i,j) returns the systematic uncertainty of each bin
* RunBCDEF_SYS_ISO.root : Iso Scale-Factors with systematic uncertainties. 