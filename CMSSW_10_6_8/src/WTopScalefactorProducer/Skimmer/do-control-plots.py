import ROOT,sys
from WTopScalefactorProducer.Fitter.tdrstyle import *
from WTopScalefactorProducer.Fitter.CMS_lumi import *
from WTopScalefactorProducer.Skimmer.getGenEv import getGenEv
setTDRStyle()
from time import sleep
import os

ROOT.gROOT.SetBatch(True)
lumi = 59970. #*0.024

ttbarSF = 1.
wjetsSF = 1.

CMS_lumi.lumi_13TeV = "%.1f fb^{-1} (2018)" % lumi
CMS_lumi.writeExtraText = 1
CMS_lumi.extraText = "Preliminary"
CMS_lumi.lumi_sqrtS = "13 TeV"
iPos = 11
if( iPos==0 ): CMS_lumi.relPosX = 0.12
iPeriod = 4 #iPeriod = 0 for simulation-only plots


#cut = "(SelectedJet_tau21_ddt_retune<0.57)"
#cut = "(abs(dr_LepJet)>1.5708&&abs(dphi_MetJet)>2.&&abs(dphi_WJet)>2&&Wlep_type==0&&SelectedJet_tau21<0.40)"
#cut = "(1==1)"
#cut = "(passedMETfilters&&abs(dr_LepJet)>1.5708&&abs(dphi_MetJet)>1.5708&&Muon_highPtId[0]>=2&&Muon_isPFcand[0]&&Muon_pfIsoId[0]>=6&&W_pt>150.&&maxAK4CSV<0.8484)"
cut = "(maxAK4CSV>0.8484&&Wlep_type==0)" # && SelectedJet_softDrop_mass > 50. && SelectedJet_softDrop_mass < 130. && SelectedJet_pt > 200. && SelectedJet_pt < 10000.)"
vars = ["SelectedJet_softDrop_mass","SelectedJet_tau21", "SelectedJet_tau21_ddt", "SelectedJet_tau21_ddt_retune", "FatJet_pt[0]","FatJet_eta[0]","FatJet_phi[0]","FatJet_tau1[0]","FatJet_tau2[0]","FatJet_tau3[0]","FatJet_mass[0]","FatJet_msoftdrop[0]","SelectedLepton_pt","SelectedLepton_iso","maxAK4CSV","nFatJet", "nJet", "nMuon","PV_npvs","W_pt","MET_pt","fabs(dphi_WJet)","fabs(dphi_MetJet)","fabs(dphi_LepJet)","dr_LepJet"]
#vars = ["SelectedJet_tau21", "FatJet_pt[0]", "W_pt", "SelectedJet_softDrop_mass","SelectedJet_tau21", "SelectedJet_tau21_ddt", "SelectedJet_tau21_ddt_retune"] 
#vars += [ "Muon_pt[0]", "Muon_pfRelIso03_all[0]" ]
#vars += ["Electron_eta[0]", "Electron_phi[0]", "Electron_pt[0]", "Electron_pfRelIso03_all[0]"]


#Data infile
datas   = ["SingleMuon-Run2018A.root", "SingleMuon-Run2018B.root", "SingleMuon-Run2018C.root", "SingleMuon-Run2018D.root", "EGamma-Run2018A.root", "EGamma-Run2018B.root", "EGamma-Run2018C.root", "EGamma-Run2018D.root"]

#MC infiles
bkgs = []
STs   = ["ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-madgraph-pythia8.root", "ST_t-channel_antitop_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8.root", "ST_t-channel_top_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8.root", "ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8.root", "ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8.root"]
VVs   = ["WW_TuneCP5_13TeV-pythia8.root", "WZ_TuneCP5_13TeV-pythia8.root", "ZZ_TuneCP5_13TeV-pythia8.root"]
TTs   = ["TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8.root", "TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8.root"]
#TTs   = ["TT_TuneCH3_13TeV-powheg-herwig7.root"]
#WJs   = ["WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8.root"]
WJs   = ["WJetsToLNu_HT-70To100_TuneCP5_13TeV-madgraphMLM-pythia8.root", "WJetsToLNu_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8.root", "WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8.root", "WJetsToLNu_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8.root", "WJetsToLNu_HT-600To800_TuneCP5_13TeV-madgraphMLM-pythia8.root", "WJetsToLNu_HT-800To1200_TuneCP5_13TeV-madgraphMLM-pythia8.root", "WJetsToLNu_HT-1200To2500_TuneCP5_13TeV-madgraphMLM-pythia8.root", "WJetsToLNu_HT-2500ToInf_TuneCP5_13TeV-madgraphMLM-pythia8.root"]
#QCDs = ["QCD_HT700to1000_TuneCP5_13TeV-madgraphMLM-pythia8.root", "QCD_HT1000to1500_TuneCP5_13TeV-madgraphMLM-pythia8.root", "QCD_HT1500to2000_TuneCP5_13TeV-madgraphMLM-pythia8.root", "QCD_HT2000toInf_TuneCP5_13TeV-madgraphMLM-pythia8.root"]
QCDs = ["QCD_HT100to200_TuneCP5_13TeV-madgraphMLM-pythia8.root", "QCD_HT200to300_TuneCP5_13TeV-madgraphMLM-pythia8.root", "QCD_HT300to500_TuneCP5_13TeV-madgraphMLM-pythia8.root", "QCD_HT500to700_TuneCP5_13TeV-madgraphMLM-pythia8.root", "QCD_HT700to1000_TuneCP5_13TeV-madgraphMLM-pythia8.root", "QCD_HT1000to1500_TuneCP5_13TeV-madgraphMLM-pythia8.root", "QCD_HT1500to2000_TuneCP5_13TeV-madgraphMLM-pythia8.root", "QCD_HT2000toInf_TuneCP5_13TeV-madgraphMLM-pythia8.root"]

bkgs.append(QCDs)
bkgs.append(STs)
bkgs.append(VVs)
bkgs.append(WJs)
bkgs.append(TTs)

dir = "/scratch/zucchett/Ntuple/WSF/" #"/work/mhuwiler/data/WScaleFactors/added/"

plotdir = "plots/"
if "maxAK4CSV<" in cut: plotdir = "plots/WCR/"
if 'herwig' in TTs[0]: plotdir = "plots/Herwig/"
if not os.path.isdir(plotdir) : os.system('mkdir -p '+plotdir)

#For drawing
legs=["QCD", "Single Top","VV","W+jets", "TT" if not 'herwig' in TTs[0] else 'TT Herwig']
fillcolor = [921,432,600,632,417]


def getTreeWeight(filename):
  xSec = getXsec(filename)
  xSF  = getSF(filename)
  genEv = getNev(filename)
  LEQ = float(xSec)*float(xSF)*lumi/float(genEv)
  return LEQ

#def setTreeWeight(filename):
#  print "For = ", filename
#  file = ROOT.TFile(dir+filename, 'UPDATE')
#  treeE = file.Get('Events')
#  event = treeE.GetEntry(0)
#  xSec = treeE.crossection
#  genEv = getGenEv(file.GetName())
#  LEQ = float(xSec*lumi/genEv)
#  print "xs  = " , xSec; print "N   =" ,genEv; print "Rescaling tree by = ", LEQ
#  treeE.SetWeight(LEQ)
#  treeE.AutoSave()
#  print "Tree weight is now: " ,treeE.GetWeight()

def setTreeWeight(filename):
  print "For = ", filename
  file = ROOT.TFile(dir+filename, 'UPDATE')
  treeE = file.Get('Events')
  event = treeE.GetEntry(0)
  weight = getTreeWeight(filename)
  treeE.SetWeight(weight)
  treeE.AutoSave()
  print "Tree weight is now: " ,treeE.GetWeight()
  
def getCanvas():
  H_ref = 600
  W_ref = 800
  W = W_ref
  H  = H_ref
  T = 0.08*H_ref
  B = 0.12*H_ref 
  L = 0.12*W_ref
  R = 0.04*W_ref
  canvas = ROOT.TCanvas("c1","c1",50,50,W,H)
  canvas.SetFillColor(0)
  canvas.SetBorderMode(0)
  canvas.SetFrameFillStyle(0)
  canvas.SetFrameBorderMode(0)
  canvas.SetLeftMargin( L/W )
  canvas.SetRightMargin( R/W )
  canvas.SetTopMargin( T/H )
  canvas.SetBottomMargin( B/H )
  canvas.SetTickx(0)
  canvas.SetTicky(0)
  ROOT.gStyle.SetOptStat(0)
  ROOT.gStyle.SetOptTitle(0)
  legend = ROOT.TLegend(0.62,0.7,0.92,0.9,"","brNDC")
  legend.SetBorderSize(0)
  legend.SetLineColor(1)
  legend.SetLineStyle(1)
  legend.SetLineWidth(1)
  legend.SetFillColor(0)
  legend.SetFillStyle(0)
  legend.SetTextFont(42)
  addInfo = ROOT.TPaveText(0.73010112,0.2566292,0.8202143,0.5523546,"NDC")
  addInfo.SetFillColor(0)
  addInfo.SetLineColor(0)
  addInfo.SetFillStyle(0)
  addInfo.SetBorderSize(0)
  addInfo.SetTextFont(42)
  addInfo.SetTextSize(0.040)
  addInfo.SetTextAlign(12)
  return canvas, legend, addInfo
  	
def drawTH1(id,tree,var,cuts,bins,min,max,fillcolor,titlex = "",units = "",drawStyle = "HIST",lumi="%s"%lumi):
  h = ROOT.TH1D("tmpTH1_%s" % id,"",bins,min,max)
  h.Sumw2()
  h.SetFillColor(fillcolor)
  if units=="": h.GetXaxis().SetTitle(titlex)
  else: h.GetXaxis().SetTitle(titlex+ " ["+units+"]")
  tree.Draw(var+">>tmpTH1_%s" % id,"("+cuts+")*eventweightlumi","goff")
  
  if not "data" in id:
      if "W+jets" in legs[int(id)]: h.Scale(wjetsSF)
      if "TT" in legs[int(id)]: h.Scale(ttbarSF)
#  corrString='1'
#  if id.find("data")==-1:
#    corrString = corrString+"*(genWeight)"
#  else:
#    lumi = "1"
#  tree.Draw(var+">>tmpTH1","("+cuts+")*"+lumi+"*("+corrString+")","goff")
#  if id.find("data")==-1:
#      tree.Draw(var+">>tmpTH1","("+cuts+")","goff")
#  else:
#      tree.Draw(var+">>tmpTH1","("+cuts+")*"+lumi+"*(genWeight)","goff")
  return h

def doCP(cutL,postfix=""):
  for var in vars:
    name = var
    canvas,legend,pave = getCanvas()
    minx = 200.
    maxx = 2000.
    bins = 36
    unit = "GeV"
    if var.find("MET")!=-1: minx=40.; maxx=3000.; bins=60; 
    if var.find("softdrop")!=-1 or var.find("mass")!=-1: minx=0.; maxx=130.; bins=16; 
    if var.find("eta")!=-1: minx=-3; maxx=3; bins=25; unit = "";
    if var.find("phi")!=-1: minx=-3.15; maxx=3.15; bins=50; unit = "";
    if var.find("tau")!=-1: minx=0.; maxx=1.0; bins=20; unit = "";
    if var.find("ddt")!=-1: minx=-0.2; maxx=1.2; bins=20; unit = "";
    if var.find("Muon_pt")!=-1: minx=50.; maxx=1000.0; bins=100; unit = "GeV";
    if var.find("RelIso")!=-1: minx=0.; maxx=0.15; bins=100; unit = "";
    if var.find("CSV")!=-1: minx=0.; maxx=1.; bins=100; unit = "";
    if var.find("nJet")!=-1: minx=-0.5; maxx=19.5; bins=20; unit = "";
    if var.find("nFatJet")!=-1: minx=-0.5; maxx=9.5; bins=10; unit = "";
    if var.find("nMuon")!=-1: minx=-0.5; maxx=4.5; bins=5; unit = "";
    if var.find("W_pt")!=-1: minx=0.; maxx=2000.; bins=100; unit = "";
    if var.find("W_mass")!=-1: minx=0.; maxx=200.; bins=200; unit = "";
    if var.find("dphi_")!=-1: minx=0; maxx=3.15; bins=30; unit = "";
    if var.find("dr_")!=-1: minx=0; maxx=5; bins=25; unit = "";
    if var.find("npvs")!=-1: minx=0; maxx=80; bins=80; unit = "";
    if var.find("MET_pt")!=-1: minx=0; maxx=500; bins=25; unit = "";
    if var.find("Electron_pt")!=-1: minx=0; maxx=600; bins=25; unit = "";
    if var.find("Electron_pfRelIso")!=-1: minx=0.; maxx=0.06; bins=100; unit = "";
    treeD = ROOT.TChain("Events")
    for file in datas:
      print "Using file: ", ROOT.TString(dir+file)
      fileIn_name = ROOT.TString(dir+file)  
      treeD.Add(fileIn_name.Data())
    cutT = cutL if not var in cutL else ()
    
    cutsData ='*'.join([cutL]) #,"(passedMETfilters==1)"])
    cutsData ='*'.join([cutL])
    datahist = drawTH1("data",treeD,var,cutsData,bins,minx,maxx,1,var.replace("_", " ").replace("[0]", "").replace("FatJet", "AK8 jet").replace("pt", "p_{T}"),unit,"HIST","1")
    datahist.SetName("data")
    legend.AddEntry(datahist,"Data (2018)","LEP")
    tmpfile={}
    tmphist={}
    hists=[]
    stack = ROOT.THStack("stack","")
    dataint		= datahist.Integral(0, datahist.GetNbinsX()+1)
    backint 	= [None]*len(bkgs)
    for i,bg in enumerate(bkgs):
      tree = ROOT.TChain("Events")
      name = bg[0]
      hist = None
      print "Name is: ", name
      for j, file in enumerate(bg):
        print "Using file: ", ROOT.TString(dir+file)
        #setTreeWeight(file)
        fileIn_name = ROOT.TString(dir+file)  
        tree.Add(fileIn_name.Data())
#        tmpfile[file] = ROOT.TFile(fileIn_name.Data(), 'READ')
#        tmptree = tmpfile[file].Get("Events")
#        tmphist[file] = drawTH1(str(i),tmptree,var,cutL,bins,minx,maxx,fillcolor[i],var.replace("_", " ").replace("[0]", "").replace("FatJet", "AK8 jet"),unit,"HIST")
#        tmphist[file].Scale(getTreeWeight(fileIn_name.Data()))
#        if hist==None: hist = tmphist[file]
#        else: hist.Add(tmphist[file])
        
        
      hist = drawTH1(str(i),tree,var,cutL,bins,minx,maxx,fillcolor[i],var.replace("_", " ").replace("[0]", "").replace("FatJet", "AK8 jet").replace("pt", "p_{T}"),unit,"HIST")
      legend.AddEntry(hist,legs[i],"F")
      hist.SetFillColor(fillcolor[i])
      backint[i] = hist.Integral(0, hist.GetNbinsX()+1)
#      if name.find("TT")!=-1:
#        ttint = hist.Integral()
#        scale = (datahist.Integral()-totalMinoInt)/ttint
#        hist.Scale(scale)
#      else: totalMinoInt += hist.Integral()
      stack.Add(hist)
      hists.append(hist)
    
    
#    print "DATA/MC" ,scale
    canvas.cd()
    datahist.GetYaxis().SetRangeUser(0, datahist.GetMaximum()*1.6);
    if var in ["FatJet_pt[0]","Muon_pt[0]","W_pt","Muon_pfRelIso03_chg[0]","Muon_pfRelIso03_all[0]"]:
    	datahist.GetYaxis().SetRangeUser(0.1, datahist.GetMaximum()*1000);
    	canvas.SetLogy()
    datahist.Draw("ME")
    stack.Draw("HIST SAME")
    datahist.Draw("ME same")
    legend.Draw("SAME")
    CMS_lumi(canvas, iPeriod, iPos)
    canvas.Update()
    canvas.SaveAs(plotdir+var.replace("[0]","").replace("abs(","").replace("(","").replace(")","")+postfix+".png")
    canvas.SaveAs(plotdir+var.replace("[0]","").replace("abs(","").replace("(","").replace(")","")+postfix+".pdf")
    
    print "--- Summary ----"
    print "Data (2018)", "\t", dataint
    print "-"*20
    for i,bg in enumerate(bkgs):
      print legs[i], "\t", backint[i]
    print "-"*20
    print "Ratio data/bkg", "\t", dataint/sum(backint)
    print "\n"
    b = 4
    print "Scale factor for", legs[b], (dataint - sum([x for i, x in enumerate(backint) if not i==b] )) / backint[b]
    
    sleep(10)

if __name__ == "__main__":
	doCP(cut)
