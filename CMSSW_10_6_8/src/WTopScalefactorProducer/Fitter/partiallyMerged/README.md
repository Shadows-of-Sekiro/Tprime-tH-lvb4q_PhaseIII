
### How to run the W-tagging scalefactor code of partially merged W-jets ###

In this code you will fit the semi-leptonic tt mass spectrum failing and passing a tagger and a tagger cut as you define.
The first step is to compile some needed Higgs Tool RooPDFs:

```
python Automatic_Setup.py 

```
You are now all set up to run. The basic script to be run is runSF.py. It takes as input the list of files produced by your nanoAOD skim. 
Please pass the correct input folderand change the filenames if needed in initialeFits.
There are a variety of command line options to pass. In the simlest case, to run simply type
```
python runSF.py -b #Run with default settings (corrected softdrop mass, cuts HP=0.35 and LP=0.75) and no x11 windows (-b)
python runSF.py --workspace workspace_chspruned --massvar jetAK8_chs_pruned_mass --xtitle "CHS pruned jet mass (GeV)" --doWS --doBinned
```
First time you run you need to create your workspace with your input datasets. The code will check whether a workspace exists or not,
then create it if it does not. You can also force the creation of a new workspace by
```
python runSF.py -doWS
```
If you wish to give the workspace a specific name, do
```
python runSF.py -doWS --workspace workspace_puppiSD # a workspace will be created with the name workspace_puppiSD.root
```
Some other examples of run options:
```
python runSF.py --workspace workspace_chspruned --massvar jetAK8_chs_pruned_mass --xtitle "CHS pruned jet mass (GeV)" --doWS --doBinned #fit CHS pruned mass, do binned (more stable)instead of unbinned fit
python runSF_sframe.py --workspace workspace_ddt --tagger ddt --doWS --doBinned --HP 0.57 #Do scalefactor for different tagger and workingpoint (DDT<0.57)
```
The only files you will need to edit except the runSF.py steering script are:
```
../python/fitutils.py --> Where all the fit functions are being defined (fit_mj_single_MC for minor background, ScaleFactorTTbarControlSampleFit for full distribution)
                          Also where the final pass/pail distributions are drawn. Cosmetics can be changed in DrawScaleFactorTTbarControlSample 
../python/makepdf.py  --> Where ALL PDFs are defined. All fit tweaking is done HERE

```
The output is a txt file with all the numbers you need, which are also printed on the sceen. The last print out is a table in LateX format for simple copy/paste
into .tex files

Commands used for current fitting:

```
python runSF_nanoAOD.py -b --doBinned --tagger SelectedJet_tau21 --workspace workspace_tau21_0p35_0p75 --HP 0.35 --LP 0.75 --doWS &
python runSF_nanoAOD.py -b --doBinned --tagger SelectedJet_tau21 --workspace workspace_tau21_0p35_0p75_topPt --HP 0.35 --LP 0.75 --topPt --doWS &
python runSF_nanoAOD.py -b --doBinned --tagger SelectedJet_tau21 --workspace workspace_tau21_0p35_0p75_topGen --HP 0.35 --LP 0.75 --topGen --doWS &
python runSF_nanoAOD.py -b --doBinned --tagger SelectedJet_tau21 --workspace workspace_tau21_0p35_0p75_topShower --HP 0.35 --LP 0.75 --topShower --doWS &

python runSF_nanoAOD.py -b --doBinned --tagger SelectedJet_tau21 --workspace workspace_tau21_0p45_0p75 --HP 0.45 --LP 0.75 --doWS &
python runSF_nanoAOD.py -b --doBinned --tagger SelectedJet_tau21 --workspace workspace_tau21_0p45_0p75_topPt --HP 0.45 --LP 0.75 --topPt --doWS &
python runSF_nanoAOD.py -b --doBinned --tagger SelectedJet_tau21 --workspace workspace_tau21_0p45_0p75_topGen --HP 0.45 --LP 0.75 --topGen --doWS &
python runSF_nanoAOD.py -b --doBinned --tagger SelectedJet_tau21 --workspace workspace_tau21_0p45_0p75_topShower --HP 0.45 --LP 0.75 --topShower --doWS &


python runSF_nanoAOD.py -b --doBinned --tagger SelectedJet_tau21_ddt_retune --workspace workspace_tau21ddt_0p43_0p79 --HP 0.43 --LP 0.79 --doWS &
python runSF_nanoAOD.py -b --doBinned --tagger SelectedJet_tau21_ddt_retune --workspace workspace_tau21ddt_0p43_0p79_topPt --HP 0.43 --LP 0.79 --topPt --doWS &
python runSF_nanoAOD.py -b --doBinned --tagger SelectedJet_tau21_ddt_retune --workspace workspace_tau21ddt_0p43_0p79_topGen --HP 0.43 --LP 0.79 --topGen --doWS &
python runSF_nanoAOD.py -b --doBinned --tagger SelectedJet_tau21_ddt_retune --workspace workspace_tau21ddt_0p43_0p79_topShower --HP 0.43 --LP 0.79 --topShower --doWS &

python runSF_nanoAOD.py -b --doBinned --tagger SelectedJet_tau21_ddt_retune --workspace workspace_tau21ddt_0p43_0p82 --HP 0.43 --LP 0.82 --doWS &

python runSF_nanoAOD.py -b --doBinned --tagger SelectedJet_tau21_ddt_retune --workspace workspace_tau21ddt_0p50_0p80 --HP 0.50 --LP 0.80 --doWS &
python runSF_nanoAOD.py -b --doBinned --tagger SelectedJet_tau21_ddt_retune --workspace workspace_tau21ddt_0p50_0p80_topPt --HP 0.50 --LP 0.80 --topPt --doWS &
python runSF_nanoAOD.py -b --doBinned --tagger SelectedJet_tau21_ddt_retune --workspace workspace_tau21ddt_0p50_0p80_topGen --HP 0.50 --LP 0.80 --topGen --doWS &
python runSF_nanoAOD.py -b --doBinned --tagger SelectedJet_tau21_ddt_retune --workspace workspace_tau21ddt_0p50_0p80_topShower --HP 0.50 --LP 0.80 --topShower --doWS &
```


