#! /bin/usr/env python
# Author: Izaak Neutelings (November 2018)
from ROOT import TFile
#from ScaleFactorTool import ensureTFile

path = '$CMSSW_BASE/src/WTopScalefactorProducer/Skimmer/python/pileup/'

class PileupWeightTool:
    
    def __init__( self, yearData = 2018, yearMC = 2017, sigma='central' ):
        """Load data and MC pilup profiles."""
        
        assert( yearMC in [2016,2017,2018] ), "You must choose a year from: 2016, 2017, or 2018."
        assert( yearData in [2016,2017,2018] ), "You must choose a year from: 2016, 2017, or 2018."
        assert( sigma in ['central','up','down'] ), "You must choose a s.d. variation from: 'central', 'up', or 'down'."
        
        minbias = '69p2'
        if sigma=='down':
          minbias = '66p0168' # -4.6%
        elif sigma=='up':
          minbias = '72p3832' # +4.6%
        
        if yearData==2016:
          self.datafile = TFile( path+'Data_PileUp_2016_%s.root'%(minbias), 'READ')
        elif yearData==2017:
          self.datafile = TFile( path+'Data_PileUp_2017_%s.root'%(minbias), 'READ')
        elif yearData==2018:
          self.datafile = TFile( path+'Data_PileUp_2018_%s.root'%(minbias), 'READ')
        if yearMC==2016:
          self.mcfile   = TFile( path+'MC_PileUp_2016_Moriond17.root', 'READ')
        elif yearMC==2017:
          self.mcfile   = TFile( path+'MC_PileUp_2017_Winter17_V2.root', 'READ')
        elif yearMC==2018:
          self.mcfile   = TFile( path+'MC_PileUp_2018_Autumn18.root', 'READ')
        self.datahist = self.datafile.Get('pileup')
        self.mchist   = self.mcfile.Get('pileup')
        self.datahist.SetDirectory(0)
        self.mchist.SetDirectory(0)
        self.datahist.Scale(1./self.datahist.Integral())
        self.mchist.Scale(1./self.mchist.Integral())
        self.datafile.Close()
        self.mcfile.Close()
        
    
    def getWeight(self,npu):
        """Get pileup weight for a given number of pileup interactions."""
        data = self.datahist.GetBinContent(self.datahist.GetXaxis().FindBin(npu))
        mc   = self.mchist.GetBinContent(self.mchist.GetXaxis().FindBin(npu))
        if mc>0.:
          return data/mc
        print ">>> Warning! PileupWeightTools.getWeight: Could not make pileup weight for npu=%s data=%s, mc=%s"%(npu,data,mc)  
        return 1.
    

