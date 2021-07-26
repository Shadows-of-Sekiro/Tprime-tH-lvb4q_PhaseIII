
### Producing samples

## Running locally
First you need to produce your input files by skimming nanoAOD samples.

For local skimming tests, the syntax is (remember to change infile!):
```
 python doSkim.py
```

## Running with qsub
To submit batch jobs go to directory ```Skimmer/qsub```

Submit with:
```
python submit_qsub_official.py [ TT | ST | VV | Wjets | QCD | data ] outfolder
```  

The first time, run with option ```-c``` as second argument to create the filelists from DAS

Also remember to perform VOMS login: ```voms-proxy-init --voms cms --valid 48:00```

## Check, resubmit, and merge results

Check that jobs were successful by typing:
```
python checkFiles.py Skimmed_20XX_XX_XX/NameOfTheSample/
```
in order to delete the incomplete files, remember to add the ```-d``` option. The script just provides information on the result of the batch production, and does not take any action.


Once the jobs are finished (the command ```source checkJobs.sh``` indicated the number of jobs running), the output can be checked with the ```resubmit_jobs.py``` script:
```
python resubmit_jobs.py outfolder
```
If there is one or more failed jobs, the directory can be cleaned and the failed jobs resubmitted by adding the option ```-r``` to the previous command.

Once the production is successfully completed and no corrupted files are present, the samples can be merged with the command:
```
source haddall.sh outfolder destinationfolder
```

The weight from the cross section and luminosity is added by running a final script:
```
python addWeight.py -i destinationfolder
```



## Running with crab [obsolete]
To submit with crab go to directory Skimmer/crab and source crab3 if you have not already done so
```
source /cvmfs/cms.cern.ch/crab3/crab.sh
```
Submit with:
```
python submit_all.py -c Pset_nanoSkim.py -d DirectoryName -f listOfDatasets.txt
```  

To make JMAR Skims (Loose skim with >=1 AK8 Jet with Pt > 200 GeV and >=1 Lepton ):(Skim these to create the files we need)
```
cd crab/JMARskim
ln -s $CMSSW_BASE/src/PhysicsTools/NanoAODTools/scripts/haddnano.py .
python  submit_all_uif.py  -c  PSet.py -d June5_nanoskim-JetsAndLepton  -f test94X_DY_madgraph.txt
 
```


## Running outside of CMSSW (only require python2.7 and ROOT) [obsolete]
```
cd PhysicsTools/NanoAODTools/
(JUST ONCE:)
bash standalone/env_standalone.sh build
(EVERY TIME:)
source standalone/env_standalone.sh
```
