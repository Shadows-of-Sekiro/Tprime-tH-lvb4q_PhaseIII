
### Make the Semileptonic TTbar skims


Remember to source CRAB first!

The text file 94X_TTsemilep.txt is just the hadded file, or list of files before hadding, which are the CRAB output of the JMAR skims which are documented, both the finished samples and the instructions for making your own can be found [[https://twiki.cern.ch/CMS/JetMET/JMARNanoAODskims][here]].

These skims use the module [[https://github.com/BoostedScalefactors/WTopScalefactorProducer/blob/nanoAOD/Skimmer/python/TTSkimmer.py][here]] which selects event that can later be skimmed again to produce either partiallyMerged or fullyMerged TTbar samples for determining W tagging scale factors.

```
cd Skimmer/crab/WtaggingSkim
cmsenv

ln -s $CMSSW_BASE/src/PhysicsTools/NanoAODTools/scripts/haddnano.py .

python   submit_one_uif_responses_unpub.py -c Pset_nanoSkim.py -d 94XJMARSkim-TTbarSkims -f 94X_TTsemilep.txt
```














```