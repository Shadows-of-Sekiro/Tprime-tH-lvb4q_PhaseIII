
### W-tagging scalefactor producer ###
#########################################

Repository for fitting W-tagging scalefactors in a semi-leptonic ttbar enriched region. Contains code to skim nanoAOD samples using a semi-leptonic ttbar selection (WTopScalefactorProducer/Skimmer). This output is then used to fit data and MC and extract W-tagging scalefactors (WTopScalefactorProducer/Fitter) both from fitting the AK8 W-jet mass at low-pT (around 200 GeV) and fitting the top AK8 W-subjet mass (around 400 GeV). The calculated scalefactors are then statistically combined and fitted, yielding a parametrisation for the W-tagging pT-dependence.

WTopScalefactorProducer/Skimmer : Start here. Produce samples.
WTopScalefactorProducer/Fitter  : Based on output from above, run script mainBLABLA.sh to compute fully- and partially-merged W-tagging scalfactors as well as statistically combining the two

## installation instructions for CMSSW_10_2_X
Setup CMSSW and get nanoAOD packages
```
cmsrel CMSSW_10_2_6
cd CMSSW_10_2_6/src
cmsenv

git clone https://github.com/cms-nanoAOD/nanoAOD-tools.git PhysicsTools/NanoAODTools
scram b

cd $CMSSW_base/src
git clone git@github.com:BoostedScalefactors/WTopScalefactorProducer.git
cd WTopScalefactorProducer
```


## installation instructions for CMSSW_9_4_X [obsolete]
Setup CMSSW and get nanoAOD packages
```
cmsrel CMSSW_9_4_2
cd CMSSW_9_4_2/src
cmsenv

git clone https://github.com/cms-nanoAOD/nanoAOD-tools.git PhysicsTools/NanoAODTools

scram build

cd PhysicsTools/NanoAODTools/

git remote add sal https://github.com/rappoccio/nanoAOD-tools.git
git fetch sal
git checkout -b TTbarResHad remotes/sal/TTbarResHad

cd ../..

git clone https://github.com/cms-jet/NanoAODJMARTools.git PhysicsTools/NanoAODJMARTools

cd PhysicsTools/NanoAODJMARTools/

git remote add ash https://github.com/UBParker/NanoAODJMARTools.git
git fetch ash
git checkout -b amaster remotes/ash/amaster


```

To get the code

```
cd $CMSSW_base/src
git clone -b nanoAOD git@github.com:BoostedScalefactors/WTopScalefactorProducer.git
cd WTopScalefactorProducer


For public version:
git clone https://github.com/${GITUSER}/WTopScalefactorProducer 
cd WTopScalefactorProducer
git remote add originalRemote https://github.com/BoostedScalefactors/WTopScalefactorProducer.git
git fetch originalRemote
git checkout -b nanoOAD originalRemote/nanoAOD
git fetch originalRemote
cd Skimmer/
ln -s $CMSSW_BASE/src/PhysicsTools/NanoAODTools/scripts/haddnano.py .
cd ..
scram b -j18

```

## Working locally (without CMSSW, just python2.7 and ROOT)
```
cd PhysicsTools/NanoAODTools/
(JUST ONCE:)
bash standalone/env_standalone.sh build
(EVERY TIME:)
source standalone/env_standalone.sh
```


## Step 1: Producing samples

First you need to produce your input files by skimming nanoAOD samples. For this, see README in subdirectory Skimmer/.


## Step 2: Running scalefactor code

When you have skimmed your samples you can move to fitting the W-tagging scalefactor. The fitting code is located in Fitter/, see README in that directory. For scalefactors from merged W AK8 jet, use Fitter/partiallyMerged. For scalefactors from merged top AK8 jet, use Fitter/fullyMerged

