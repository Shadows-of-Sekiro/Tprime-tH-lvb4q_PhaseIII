### Producing JMAR skims of expanded NanoAOD datasets

To make JMAR Skims (Loose skim with >=1 AK8 Jet with Pt > 200 GeV and >=1 Lepton ):
```
cd crab/JMARskim
ln -s $CMSSW_BASE/src/PhysicsTools/NanoAODTools/scripts/haddnano.py .
python  submit_all_uif.py  -c  PSet.py -d June5_nanoskim-JetsAndLepton  -f test94X_DY_madgraph.txt
 
```
