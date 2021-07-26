import sys
import math
import json
import array as array
from optparse import OptionParser
import ROOT
from plotter import *




parser = OptionParser()

parser.add_option('--MC',dest="MC", default=True, action="store_true", help="Only plot the MC")

(options, args) = parser.parse_args()


if not options.MC :
    lumi = 4008.37 

    dataFile = ROOT.TFile("./")

    dataFile.cd()

    #right now only muons present

    #get histos to plot
    dhists = {}

    dirList = ROOT.gDirectory.GetListOfKeys()
    print dirList
    for k1 in dirList: 
      d1 = k1.ReadObj()
      d1.cd()
      hList = ROOT.gDirectory.GetListOfKeys()
      for h in hList:
        print "hist name is "
        print h.ReadObj().GetName()
        dhists[h.GetName()] = h


mcFile = ROOT.TFile("./fullyMerged_hists_TTToSemiLeptonic.root")
#get histos to plot
mhists = {}

titles = [

['h_lep0pt' , 'P_{T} Lepton (GeV) '],
['h_lep0eta' , '\eta  Lepton'],
['h_lep0phi' , '\phi Lepton'],
['h_hadToppt' , 'AK8 Jet P_{T} (GeV)'],
['h_hadTopeta' , 'AK8 Jet \eta'],
['h_hadTopphi' , 'AK8 Jet \phi'],
['h_hadTopmass' , 'AK8 Jet Ungroomed mass (GeV)'],
['h_WcandSubjetpt' , 'AK8 Soft Drop Subjet 0 P_{T} (GeV)'],
['h_WcandSubjeteta' , 'AK8 Soft Drop Subjet 0 \eta'],
['h_WcandSubjetphi' , 'AK8 Soft Drop Subjet 0 \phi '],
['h_WcandSubjetmass' , 'AK8 Soft Drop Subjet 0 mass (GeV)'],
['h_WcandSubjettau21' , 'AK8 Soft Drop Subjet 0 #tau_{#frac{2}{1}}'],
['h_WcandSubjetpt_ptbin0' , ' Jet Soft Drop Mass (GeV)'],
['h_WcandSubjetpt' , 'AK8 Soft Drop Subjet 0 P_{T} (GeV)'],
['h_WcandSubjeteta_ptbin0' , 'AK8 Soft Drop Subjet 0 \eta'],
['h_WcandSubjetphi_ptbin0' , 'AK8 Soft Drop Subjet 0 \phi '],
['h_WcandSubjetmass_ptbin0' , 'AK8 Soft Drop Subjet 0 Mass (GeV)'],
['h_WcandSubjettau21_ptbin0' , 'AK8 Soft Drop Subjet 0 #tau_{#frac{2}{1}}'],
['h_WcandSubjetpt_ptbin1' , 'AK8 Soft Drop Subjet 0 P_{T} (GeV)'],
['h_WcandSubjeteta_ptbin1' , 'AK8 Soft Drop Subjet 0 \eta'],
['h_WcandSubjetphi_ptbin1' , 'AK8 Soft Drop Subjet 0 \phi '],
['h_WcandSubjetmass_ptbin1' , 'AK8 Soft Drop Subjet 0 Mass (GeV)'],
['h_WcandSubjettau21_ptbin1' , 'AK8 Soft Drop Subjet 0 #tau_{#frac{2}{1}}'],
['h_WcandSubjetpt_ptbin2' , 'AK8 Soft Drop Subjet 0 P_{T} (GeV)'],
['h_WcandSubjeteta_ptbin2' , 'AK8 Soft Drop Subjet 0 \eta'],
['h_WcandSubjetphi_ptbin2' , 'AK8 Soft Drop Subjet 0 \phi '],
['h_WcandSubjetmass_ptbin2' , 'AK8 Soft Drop Subjet 0 Mass (GeV)'],
['h_WcandSubjettau21_ptbin2' , 'AK8 Soft Drop Subjet 0 #tau_{#frac{2}{1}}'],
['h_Wleppt' , 'Leptonic W P_{T} (GeV)'],
['h_Wlepeta' , 'Leptonic W \eta'],
['h_Wlepphi' , 'Leptonic W \phi '],
['h_Wlepmass' , 'Leptonic W Mass ( GeV)'],
['h_matchedAK8Subjetpt' , 'Gen Matched AK8 Soft Drop Subjet 0 P_{T} (GeV)'],
['h_matchedAK8Subjeteta' , 'Gen Matched AK8 Soft Drop Subjet 0 \eta'],
['h_matchedAK8Subjetphi' , 'Gen Matched AK8 Soft Drop Subjet 0 \phi'],
['h_matchedAK8Subjetmass' , 'Gen Matched AK8 Soft Drop Subjet 0 Mass (GeV)'],
['h_unmatchedAK8Subjetpt' , 'UnMatched AK8 Soft Drop Subjet 0 P_{T} (GeV) '],
['h_unmatchedAK8Subjeteta' , 'UnMatched AK8 Soft Drop Subjet 0 \eta '],
['h_unmatchedAK8Subjetphi' , 'UnMatched AK8 Soft Drop Subjet 0 \phi'],
['h_unmatchedAK8Subjetmass' , 'UnMatched AK8 Soft Drop Subjet 0 Mass (GeV) '],


]

Min = []
rangeMax = []

dirList = ROOT.gDirectory.GetListOfKeys()
print dirList
for k1 in dirList: 
  d1 = k1.ReadObj()
  d1.cd()
  hList = ROOT.gDirectory.GetListOfKeys()
  for h in hList:
    #print "hist name is "
    hname =  h.ReadObj().GetName()
    if 'response' in hname : continue 
    for t in titles :
        if t[0] in hname :
            title = t[1]
    mhists[h.GetName()] = [h.ReadObj() , title]


w = 1.
if not options.MC :
    xsec = 243.856 #3. * 2008.4
    nevents =  (2253756.) #(32553254. + 11623646.)
    w = xsec * lumi / nevents


y_max_scale = 1.3

rangexs = []

cans = []
if not options.MC :
    for name, hist in dhists.iteritems() :
        # get MC hist
        mc = mhists[name]
        #Apply scaling calculated above
        mc.Scale(w)
        #mc.SetFillColor(3)#ROOT.kGreen +1)
         
        # create the MC stack for the plot
        Stack = ROOT.THStack("mcStack"+ name, "mcStack"+ name )
        Stack.Add(mc)
        
        # rebin thse hists which need it
        rbnum = -1

        #if rbnum > 0. :
        #    print "rebinning!!! {}".format(int(rbnum))
        #    mc.Rebin(int(rbnum))
        #    data.Rebin(int(rbnum))
      
        therange = None #rangexs[i] 
        #print "Now plotting histo {} name is {} rangex[i] is {}".format(i, name, therange)
        newcan = printPlot("default", "plots", name ,therange, data , mc, Stack ) 
        cans.append(newcan)

if options.MC :
    for name, hist in mhists.iteritems() :
        data = None

        #print hist
        #Apply scaling calculated above
        hist[0].Scale(w)
        ROOT.gStyle.SetOptStat(000000)

        # create the MC stack for the plot
        Stack = ROOT.THStack("mcStack"+ name, "mcStack"+ name )
        hist[0].SetFillColor(ROOT.kGreen+1)
        Stack.Add(hist[0])
        
        # rebin thse hists which need it
        rbnum = -1

        #if rbnum > 0. :
        #    print "rebinning!!! {}".format(int(rbnum))
        #    hist[0].Rebin(int(rbnum))

        rangexs = None   
        xtitle =  hist[1]
        #if 'eta' in name :
        #    rangexs = [-3,3]
        #if 'phi' in name :
        #    rangexs = [-5,5]

        #print "Now plotting histogram {} with x range {}".format(name, rangexs)
        newcan = printPlot("NANO07feb", "fullymerged_plots", xtitle, name ,rangexs, y_max_scale, data , hist[0], Stack ) 
        cans.append(newcan)

