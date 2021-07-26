import os,sys
import ROOT as rt
rt.gROOT.SetBatch(True)
from WTopScalefactorProducer.Fitter.tdrstyle import *
setTDRStyle()
from WTopScalefactorProducer.Fitter.CMS_lumi import *

from WTopScalefactorProducer.Fitter.makepdf import MakeExtendedModel,change_dataset_to_histpdf,fixParameters,makeTTbarModel

CMS_lumi.lumi_13TeV = "36.5 fb^{-1}(2016)"
CMS_lumi.writeExtraText = 1
CMS_lumi.extraText = ""
CMS_lumi.lumi_sqrtS = "13 TeV" # used with iPeriod = 0, e.g. for simulation-only plots (default is an empty string)
iPos = 11
if( iPos==0 ): CMS_lumi.relPosX = 0.12
iPeriod = 4
# iPeriod = 40 #2016

def getCanvas():
    H_ref = 600
    W_ref = 800
    W = W_ref
    H  = H_ref
    T = 0.08*H_ref
    B = 0.12*H_ref 
    L = 0.12*W_ref
    R = 0.04*W_ref
    canvas = rt.TCanvas("c1","c1",50,50,W,H)
    canvas.SetFillColor(0)
    canvas.SetBorderMode(0)
    canvas.SetFrameFillStyle(0)
    canvas.SetFrameBorderMode(0)
    canvas.SetLeftMargin( (L/W)*1.5 )
    canvas.SetRightMargin( R/W )
    canvas.SetTopMargin( T/H )
    canvas.SetBottomMargin( B/H )
    canvas.SetTickx(0)
    canvas.SetTicky(0)
    rt.gStyle.SetOptStat(0)
    rt.gStyle.SetOptTitle(0)
    return canvas
         
def getPavetext():
  addInfo = rt.TPaveText(0.73010112,0.2566292,0.8202143,0.5523546,"NDC")
  addInfo.SetFillColor(0)
  addInfo.SetLineColor(0)
  addInfo.SetFillStyle(0)
  addInfo.SetBorderSize(0)
  addInfo.SetTextFont(42)
  addInfo.SetTextSize(0.040)
  addInfo.SetTextAlign(12)
  return addInfo
  
def getLegend(mplot,channel,x1=0.62,x2=0.7,y1=0.92,y2=0.9):
    theLeg = rt.TLegend(x1,x2,y1,y2,"","brNDC")
    theLeg.SetName("theLegend");
    theLeg.SetNColumns(2)
    theLeg.SetFillColor(0)
    theLeg.SetFillStyle(0)
    theLeg.SetBorderSize(0)
    theLeg.SetLineColor(0)
    theLeg.SetLineWidth(0)
    theLeg.SetLineStyle(0)
    theLeg.SetTextSize(0.039)
    theLeg.SetTextFont(42)

    return theLeg       


def pdfDSCBtoGAUS(ws, sample):
    rrv_alpha1 = ws.var("rrv_alpha1_ttbar_"+sample+"_em_mj")
    rrv_alpha2 = ws.var("rrv_alpha2_ttbar_"+sample+"_em_mj")
#    rrv_sign1 = ws.var("rrv_sign1_ttbar_"+sample+"_em_mj")
#    rrv_sign2 = ws.var("rrv_sign2_ttbar_"+sample+"_em_mj")
    
    if not rrv_alpha1==None:
        rrv_alpha1.setVal(4.5); rrv_alpha1.setMin(4.); rrv_alpha1.setMax(5.)
    if not rrv_alpha2==None:
        rrv_alpha2.setVal(4.5); rrv_alpha2.setMin(4.); rrv_alpha2.setMax(5.)

def pdfGAUStoDSCB(ws, sample):
    rrv_alpha1 = ws.var("rrv_alpha1_ttbar_"+sample+"_em_mj")
    rrv_alpha2 = ws.var("rrv_alpha2_ttbar_"+sample+"_em_mj")
#    rrv_sign1 = ws.var("rrv_sign1_ttbar_"+sample+"_em_mj")
#    rrv_sign2 = ws.var("rrv_sign2_ttbar_"+sample+"_em_mj")
    
    if not rrv_alpha1==None:
        rrv_alpha1.setVal(1.); rrv_alpha1.setMin(0.1); rrv_alpha1.setMax(5.)
    if not rrv_alpha2==None:
        rrv_alpha2.setVal(1.); rrv_alpha2.setMin(0.1); rrv_alpha2.setMax(5.)

    
def doTTscalefactor(workspace,channel):

    data      = workspace.data(("rdataset_data_"  +channel+"_mj")).sumEntries()
    tt        = workspace.data(("rdataset_TTbar_" +channel+"_mj")).sumEntries()
    minorBKG  = workspace.data(("rdataset_WJets_" +channel+"_mj")).sumEntries()
    minorBKG += workspace.data(("rdataset_VV_"    +channel+"_mj")).sumEntries()
    minorBKG += workspace.data(("rdataset_STop_"  +channel+"_mj")).sumEntries()
    # minorBKG += workspace.data(("rdataset_QCD_"  +channel+"_mj")).sumEntries()*0.697187387981
    ttScalefactor = (data-minorBKG)/tt
    
    scalefactor = rt.RooRealVar("tt_scalefactor","tt_scalefactor",ttScalefactor)
    getattr(workspace,'import')(scalefactor)
    
    
    data      = workspace.data(("rdataset_data_failtau2tau1cut_"  +channel+"_mj")).sumEntries()
    tt        = workspace.data(("rdataset_TTbar_failtau2tau1cut_" +channel+"_mj")).sumEntries()
    minorBKG  = workspace.data(("rdataset_WJets_failtau2tau1cut_" +channel+"_mj")).sumEntries()
    minorBKG += workspace.data(("rdataset_VV_failtau2tau1cut_"    +channel+"_mj")).sumEntries()
    minorBKG += workspace.data(("rdataset_STop_failtau2tau1cut_"  +channel+"_mj")).sumEntries()
    # minorBKG += workspace.data(("rdataset_QCD_failtau2tau1cut_"  +channel+"_mj")).sumEntries()*0.697187387981
    LPttScalefactor = (data-minorBKG)/tt
    
    LPscalefactor = rt.RooRealVar("LP_tt_scalefactor","LP_tt_scalefactor",LPttScalefactor)
    getattr(workspace,'import')(LPscalefactor)
    
    return scalefactor.getVal()
    

def fit_mj_single_MC(workspace,fileName,label, model,channel, wtagger_label,wsname = ""):

    rrv_mass_j  = workspace.var("rrv_mass_j")
    rdataset_mj = workspace.data("rdataset4fit"+label+"_"+channel+"_mj")

    constraint_list = []
    
    model_pdf = MakeExtendedModel(workspace,label,model,"_mj",channel,wtagger_label,constraint_list,"W",wsname)
    rfresult = model_pdf.fitTo(rdataset_mj,rt.RooFit.Save(1),rt.RooFit.SumW2Error(rt.kTRUE),rt.RooFit.Extended(rt.kTRUE), rt.RooFit.Minimizer("Minuit2"),rt.RooFit.Verbose(rt.kFALSE))
    rfresult = model_pdf.fitTo(rdataset_mj,rt.RooFit.Save(1),rt.RooFit.SumW2Error(rt.kTRUE),rt.RooFit.Extended(rt.kTRUE), rt.RooFit.Minimizer("Minuit2"),rt.RooFit.Verbose(rt.kFALSE))
    rfresult = model_pdf.fitTo(rdataset_mj,rt.RooFit.Save(1),rt.RooFit.SumW2Error(rt.kTRUE),rt.RooFit.Extended(rt.kTRUE), rt.RooFit.Minimizer("Minuit2"),rt.RooFit.Verbose(rt.kFALSE))
    print "";rfresult.Print();print "";
    getattr(workspace,'import')(rfresult)
    
    
    
    pars = rfresult.floatParsFinal()
    if label.find("TTbar")!=-1:
        params = model_pdf.getParameters(rdataset_mj)
        params.printLatex(rt.RooFit.Columns(1), rt.RooFit.OutputFile("fitres"+label+wsname+".txt"))
        with open("ttfit_parameters%s.txt"%wsname,"a") as f:
            for i in range(0,pars.getSize()):
                p = pars.at(i)
                f.write("%s %f %f \n" %(p.getTitle(),p.getVal(),p.getError())) 

    mplot = rrv_mass_j.frame(rt.RooFit.Title((label+" fitted by "+model)), rt.RooFit.Bins(int(rrv_mass_j.getBins())))
    mplot.GetYaxis().SetRangeUser(0,mplot.GetMaximum()*1.2)
    rdataset_mj.plotOn(mplot,rt.RooFit.MarkerSize(1.5),rt.RooFit.DataError(rt.RooAbsData.SumW2),rt.RooFit.XErrorSize(0),rt.RooFit.Invisible())
  
    model_pdf.plotOn(mplot,rt.RooFit.Name( "Gaussian comp."   ),rt.RooFit.Components("gaus*"),rt.RooFit.LineStyle(rt.kDashed),rt.RooFit.LineColor(rt.kRed+3))
    model_pdf.plotOn(mplot,rt.RooFit.Name( "Gaussian comp. 1" ),rt.RooFit.Components("gaus1*"),rt.RooFit.LineStyle(rt.kDashed),rt.RooFit.LineColor(rt.kRed+3))
    model_pdf.plotOn(mplot,rt.RooFit.Name( "Gaussian comp. 2" ),rt.RooFit.Components("gaus2*"),rt.RooFit.LineStyle(rt.kDashed),rt.RooFit.LineColor(rt.kRed+4))
    model_pdf.plotOn(mplot,rt.RooFit.Name( "ErfExp comp." ),rt.RooFit.Components("erfExp*"),rt.RooFit.LineStyle(rt.kDashed),rt.RooFit.LineColor(rt.kRed+3))
    model_pdf.plotOn(mplot,rt.RooFit.Name( "Exp. comp." ),rt.RooFit.Components("exp*"),rt.RooFit.LineStyle(rt.kDashed),rt.RooFit.LineColor(rt.kRed+2))
    model_pdf.plotOn(mplot,rt.RooFit.Name( "Chebychev comp." ),rt.RooFit.Components("cheb*"),rt.RooFit.LineStyle(rt.kDashed),rt.RooFit.LineColor(rt.kRed+3))
    model_pdf.plotOn(mplot,rt.RooFit.Name((model) )) 

    rdataset_mj.plotOn(mplot,rt.RooFit.MarkerSize(1.),rt.RooFit.Name( (label) ), rt.RooFit.DataError(rt.RooAbsData.SumW2), rt.RooFit.XErrorSize(1))
    leg1 = getLegend(mplot,channel)
    mplot.addObject(leg1)

    #TODO RooPlot* mplot_pull = get_ratio(rrv_mass_j,rdataset_mj,model_pdf,rfresult,0,1)
    mplot.GetYaxis().SetRangeUser(0,mplot.GetMaximum()*1.2)
    mplot.GetYaxis().SetTitle("MC events / 5 GeV")
  
    
    datahist = rdataset_mj.binnedClone(rdataset_mj.GetName()+"_binnedClone", rdataset_mj.GetName()+"_binnedClone")
    Nbin = int(rrv_mass_j.getBins())
    rresult_param = rfresult.floatParsFinal()
    nparameters =  rresult_param.getSize()
    ChiSquare = model_pdf.createChi2(datahist,rt.RooFit.Extended(rt.kTRUE),rt.RooFit.DataError(rt.RooAbsData.Poisson))
    chi_over_ndf= ChiSquare.getVal()/(Nbin - nparameters)

    
    Name  = "#chi^{2}/ndf = %0.2f " %float(chi_over_ndf)
    cs = getPavetext()
    cs.AppendPad("same")
    mplot.addObject(cs)
    c1 = getCanvas()
    mplot.Draw()
    # leg1.Draw("same")
    # from time import sleep
    # sleep(100)
    dirname = "plots/"+wsname.replace('workspace_', '')
    if not os.path.exists(dirname): os.makedirs(dirname)
    if not os.path.exists(dirname+"/MCfits"): os.makedirs(dirname+"/MCfits")
    c1.SaveAs(dirname+"/MCfits/"+label.replace('_', '', 1)+".png")
    c1.SaveAs(dirname+"/MCfits/"+label.replace('_', '', 1)+".pdf")

    # TODO # draw_canvas_with_pull(mplot,mplot_pull,rt.RooArgList(*parameters_list),"plots/MCfits/",label+fileName,model,channel,0,0,GetLumi())
    workspace.var("rrv_number"+label+"_"+channel+"_mj").setVal(workspace.var("rrv_number"+label+"_"+channel+"_mj").getVal()*workspace.var("rrv_scale_to_lumi"+label+"_"+channel).getVal())
    workspace.var("rrv_number"+label+"_"+channel+"_mj").setError(workspace.var("rrv_number"+label+"_"+channel+"_mj").getError()*workspace.var("rrv_scale_to_lumi"+label+"_"+channel).getVal())
                                                                                                          
def ScaleFactorTTbarControlSampleFit(workspace, mj_shape, color_palet, constraintlist_data, constraintlist_MC, channel,wtagger,peak,wsname=""):
  
  LPttScalefactor = workspace.var("LP_tt_scalefactor").getVal()
  ttScalefactor   = workspace.var("tt_scalefactor").getVal()
  print ""
  print "Using tt scalefactor HP of " , ttScalefactor 
  print "Using tt scalefactor LP of " , LPttScalefactor 
  print ""

  label = ""
  rrv_mass_j                 = workspace.var("rrv_mass_j")
  rdataset_data_mj           = workspace.data(("rdataset_data"+ label+"_"+channel+"_mj"))
  rdataset_TTbar_mj          = workspace.data(("rdataset_TTbar"+ label+"_"+channel+"_mj"))
  rdataset_STop_mj           = workspace.data(("rdataset_STop"+  label+"_"+channel+"_mj"))
  rdataset_VV_mj             = workspace.data(("rdataset_VV"+    label+"_"+channel+"_mj"))
  # rdataset_QCD_mj            = workspace.data(("rdataset_QCD"+    label+"_"+channel+"_mj"))
  rdataset_WJets_mj          = workspace.data(("rdataset_WJets"+label+"_"+channel+"_mj"))
  rdataset_TTbar_mj_merged   = workspace.data(("rdataset_TTbar_realW"+ label+"_"+channel+"_mj"))
  rdataset_TTbar_mj_unmerged = workspace.data(("rdataset_TTbar_fakeW"+ label+"_"+channel+"_mj"))
  
  change_dataset_to_histpdf(workspace,rrv_mass_j,rdataset_TTbar_mj)
  change_dataset_to_histpdf(workspace,rrv_mass_j,rdataset_STop_mj)
  change_dataset_to_histpdf(workspace,rrv_mass_j,rdataset_VV_mj)
  # change_dataset_to_histpdf(workspace,rrv_mass_j,rdataset_QCD_mj)
  change_dataset_to_histpdf(workspace,rrv_mass_j,rdataset_WJets_mj)
  change_dataset_to_histpdf(workspace,rrv_mass_j,rdataset_TTbar_mj_merged)
  change_dataset_to_histpdf(workspace,rrv_mass_j,rdataset_TTbar_mj_unmerged)
  
  model_histpdf_TTbar          = workspace.pdf(((rdataset_TTbar_mj.GetName())+"_histpdf"))
  model_histpdf_STop           = workspace.pdf(((rdataset_STop_mj.GetName())+"_histpdf"))
  model_histpdf_VV             = workspace.pdf(((rdataset_VV_mj.GetName())+"_histpdf"))
  # model_histpdf_QCD            = workspace.pdf(((rdataset_QCD_mj.GetName())+"_histpdf"))
  model_histpdf_WJets          = workspace.pdf(((rdataset_WJets_mj.GetName())+"_histpdf"))
  model_histpdf_TTbar_merged   = workspace.pdf(((rdataset_TTbar_mj_merged.GetName())+"_histpdf"))
  model_histpdf_TTbar_unmerged = workspace.pdf(((rdataset_TTbar_mj_unmerged.GetName())+"_histpdf"))

  number_TTbar                 = rt.RooRealVar(("rrv_number_TTbar"+label+"_"+channel),("rrv_number_TTbar"+label+"_"+channel),rdataset_TTbar_mj.sumEntries()*ttScalefactor)
  number_STop                  = rt.RooRealVar(("rrv_number_STop"+label+"_"+channel),("rrv_number_STop"+label+"_"+channel),rdataset_STop_mj.sumEntries())
  number_VV                    = rt.RooRealVar(("rrv_number_VV"+label+"_"+channel),("rrv_number_VV"+label+"_"+channel),rdataset_VV_mj.sumEntries())
  # number_QCD                   = rt.RooRealVar(("rrv_number_QCD"+label+"_"+channel),("rrv_number_QCD"+label+"_"+channel),rdataset_QCD_mj.sumEntries())
  number_WJets                 = rt.RooRealVar(("rrv_number_WJets"+label+"_"+channel),("rrv_number_WJets"+label+"_"+channel),rdataset_WJets_mj.sumEntries())                            
  number_TTbar_merged          = rt.RooRealVar(("rrv_number_TTbar_realW"+label+"_"+channel),("rrv_number_TTbar_realW"+label+"_"+channel),rdataset_TTbar_mj_merged.sumEntries()*ttScalefactor)
  number_TTbar_unmerged        = rt.RooRealVar(("rrv_number_TTbar_fakeW"+label+"_"+channel),("rrv_number_TTbar_fakeW"+label+"_"+channel),rdataset_TTbar_mj_unmerged.sumEntries()*ttScalefactor)
  
  # model_TTbar_STop_VV_WJets    = rt.RooAddPdf(("model_TTbar_STop_VV_WJets"+label+"_"+channel),("model_TTbar_STop_VV_WJets"+label+"_"+channel),rt.RooArgList(model_histpdf_TTbar_merged,model_histpdf_TTbar_unmerged,model_histpdf_STop,model_histpdf_VV,model_histpdf_QCD,model_histpdf_WJets),rt.RooArgList(number_TTbar_merged,number_TTbar_unmerged,number_STop,number_VV,number_QCD,number_WJets))
  model_TTbar_STop_VV_WJets    = rt.RooAddPdf(("model_TTbar_STop_VV_WJets"+label+"_"+channel),("model_TTbar_STop_VV_WJets"+label+"_"+channel),rt.RooArgList(model_histpdf_TTbar_merged,model_histpdf_TTbar_unmerged,model_histpdf_STop,model_histpdf_VV,model_histpdf_WJets),rt.RooArgList(number_TTbar_merged,number_TTbar_unmerged,number_STop,number_VV,number_WJets))
  
  getattr(workspace,'import')(model_TTbar_STop_VV_WJets)

  rdataset_data_mj_fail           =  workspace.data(("rdataset_data"+label+"_"+"failtau2tau1cut_"+channel+"_mj"))
  rdataset_TTbar_mj_fail          =  workspace.data(("rdataset_TTbar"+label+"_"+"failtau2tau1cut_"+channel+"_mj"))
  rdataset_STop_mj_fail           =  workspace.data(("rdataset_STop"+label+"_"+"failtau2tau1cut_"+channel+"_mj"))
  rdataset_VV_mj_fail             =  workspace.data(("rdataset_VV"+label+"_"+"failtau2tau1cut_"+channel+"_mj"))
  # rdataset_QCD_mj_fail            =  workspace.data(("rdataset_QCD"+label+"_"+"failtau2tau1cut_"+channel+"_mj"))
  rdataset_WJets_mj_fail          =  workspace.data(("rdataset_WJets"+label+"_"+"failtau2tau1cut_"+channel+"_mj"))
  rdataset_TTbar_mj_fail_merged   =  workspace.data(("rdataset_TTbar_realW"+label+"_"+"failtau2tau1cut_"+channel+"_mj"))
  rdataset_TTbar_mj_fail_unmerged =  workspace.data(("rdataset_TTbar_fakeW"+label+"_"+"failtau2tau1cut_"+channel+"_mj"))

  change_dataset_to_histpdf(workspace,rrv_mass_j,rdataset_TTbar_mj_fail)
  change_dataset_to_histpdf(workspace,rrv_mass_j,rdataset_STop_mj_fail)
  change_dataset_to_histpdf(workspace,rrv_mass_j,rdataset_VV_mj_fail)
  # change_dataset_to_histpdf(workspace,rrv_mass_j,rdataset_QCD_mj_fail)
  change_dataset_to_histpdf(workspace,rrv_mass_j,rdataset_WJets_mj_fail)
  change_dataset_to_histpdf(workspace,rrv_mass_j,rdataset_TTbar_mj_fail_merged)
  change_dataset_to_histpdf(workspace,rrv_mass_j,rdataset_TTbar_mj_fail_unmerged)

  model_histpdf_TTbar_fail          = workspace.pdf(((rdataset_TTbar_mj_fail.GetName())+"_histpdf"))
  model_histpdf_STop_fail           = workspace.pdf(((rdataset_STop_mj_fail.GetName())+"_histpdf"))
  model_histpdf_VV_fail             = workspace.pdf(((rdataset_VV_mj_fail.GetName())+"_histpdf"))
  # model_histpdf_QCD_fail             = workspace.pdf(((rdataset_QCD_mj_fail.GetName())+"_histpdf"))
  model_histpdf_WJets_fail          = workspace.pdf(((rdataset_WJets_mj_fail.GetName())+"_histpdf"))
  model_histpdf_TTbar_fail_merged   = workspace.pdf(((rdataset_TTbar_mj_fail_merged.GetName())+"_histpdf"))
  model_histpdf_TTbar_fail_unmerged = workspace.pdf(((rdataset_TTbar_mj_fail_unmerged.GetName())+"_histpdf"))

  number_TTbar_fail  = rt.RooRealVar(("rrv_number_TTbar_fail"+label+"_"+channel),("rrv_number_TTbar_fail"+label+"_"+channel),rdataset_TTbar_mj_fail.sumEntries()*LPttScalefactor)
  number_STop_fail   = rt.RooRealVar(("rrv_number_STop_fail"+label +"_"+channel),("rrv_number_STop_fail"+label+"_"+channel),rdataset_STop_mj_fail.sumEntries())
  number_VV_fail     = rt.RooRealVar(("rrv_number_VV_fail"+label   +"_"+channel),("rrv_number_VV_fail"+label+"_"+channel),rdataset_VV_mj_fail.sumEntries())
  # number_QCD_fail    = rt.RooRealVar(("rrv_number_QCD_fail"+label   +"_"+channel),("rrv_number_QCD_fail"+label+"_"+channel),rdataset_QCD_mj_fail.sumEntries())
  number_WJets_fail  = rt.RooRealVar(("rrv_number_WJets_fail"+label+"_"+channel),("rrv_number_WJets_fail"+label+"_"+channel),rdataset_WJets_mj_fail.sumEntries())

  number_TTbar_fail_merged    = rt.RooRealVar(("rrv_number_TTbar_fail_realW"+label+"_"+channel),("rrv_number_TTbar_fail_realW"+label+"_"+channel),rdataset_TTbar_mj_fail_merged.sumEntries()*LPttScalefactor)
  number_TTbar_fail_unmerged  = rt.RooRealVar(("rrv_number_TTbar_fail_fakeW"+label+"_"+channel),("rrv_number_TTbar_fail_fakeW"+label+"_"+channel),rdataset_TTbar_mj_fail_unmerged.sumEntries()*LPttScalefactor)
  
  # model_TTbar_STop_VV_WJets_fail = rt.RooAddPdf(("model_TTbar_STop_VV_WJets_fail"+label+"_"+channel),("model_TTbar_STop_VV_WJets_fail"+label+"_"+channel),rt.RooArgList(model_histpdf_TTbar_fail_merged,model_histpdf_TTbar_fail_unmerged,model_histpdf_STop_fail,model_histpdf_VV_fail,model_histpdf_QCD_fail,model_histpdf_WJets_fail), rt.RooArgList(number_TTbar_fail_merged,number_TTbar_fail_unmerged,number_STop_fail,number_VV_fail,number_QCD_fail,number_WJets_fail))
  model_TTbar_STop_VV_WJets_fail = rt.RooAddPdf(("model_TTbar_STop_VV_WJets_fail"+label+"_"+channel),("model_TTbar_STop_VV_WJets_fail"+label+"_"+channel),rt.RooArgList(model_histpdf_TTbar_fail_merged,model_histpdf_TTbar_fail_unmerged,model_histpdf_STop_fail,model_histpdf_VV_fail,model_histpdf_WJets_fail), rt.RooArgList(number_TTbar_fail_merged,number_TTbar_fail_unmerged,number_STop_fail,number_VV_fail,number_WJets_fail))
  getattr(workspace,'import')(model_TTbar_STop_VV_WJets_fail)
  
  
  # scale_number_TTbar_STop_VV_WJets      = (rdataset_TTbar_mj_merged.sumEntries()*ttScalefactor+rdataset_TTbar_mj_unmerged.sumEntries()*ttScalefactor+rdataset_STop_mj.sumEntries()+rdataset_VV_mj.sumEntries()+rdataset_QCD_mj.sumEntries()+rdataset_WJets_mj.sumEntries())/(rdataset_data_mj.sumEntries()+rdataset_data_mj_fail.sumEntries())
  # scale_number_TTbar_STop_VV_WJets_fail = (rdataset_TTbar_mj_fail_merged.sumEntries()*LPttScalefactor+rdataset_TTbar_mj_fail_unmerged.sumEntries()*LPttScalefactor+rdataset_STop_mj_fail.sumEntries()+rdataset_VV_mj_fail.sumEntries()+rdataset_QCD_mj_fail.sumEntries()+rdataset_WJets_mj_fail.sumEntries())/( rdataset_data_mj.sumEntries()+rdataset_data_mj_fail.sumEntries())
  scale_number_TTbar_STop_VV_WJets      = (rdataset_TTbar_mj_merged.sumEntries()*ttScalefactor+rdataset_TTbar_mj_unmerged.sumEntries()*ttScalefactor+rdataset_STop_mj.sumEntries()+rdataset_VV_mj.sumEntries()+rdataset_WJets_mj.sumEntries())/(rdataset_data_mj.sumEntries()+rdataset_data_mj_fail.sumEntries())
  scale_number_TTbar_STop_VV_WJets_fail = (rdataset_TTbar_mj_fail_merged.sumEntries()*LPttScalefactor+rdataset_TTbar_mj_fail_unmerged.sumEntries()*LPttScalefactor+rdataset_STop_mj_fail.sumEntries()+rdataset_VV_mj_fail.sumEntries()+rdataset_WJets_mj_fail.sumEntries())/( rdataset_data_mj.sumEntries()+rdataset_data_mj_fail.sumEntries())
  rrv_scale_number_TTbar_STop_VV_WJets      = rt.RooRealVar(("rrv_scale_number_TTbar_STop_VV_WJets"+label),("rrv_scale_number_TTbar_STop_VV_WJets"+label),scale_number_TTbar_STop_VV_WJets)
  rrv_scale_number_TTbar_STop_VV_WJets_fail = rt.RooRealVar(("rrv_scale_number_TTbar_STop_VV_WJets_fail"+label),("rrv_scale_number_TTbar_STop_VV_WJets_fail"+label),scale_number_TTbar_STop_VV_WJets_fail)
  getattr(workspace,'import')(rrv_scale_number_TTbar_STop_VV_WJets)
  getattr(workspace,'import')(rrv_scale_number_TTbar_STop_VV_WJets_fail)
  
  #Fix all shape parameters and normalization                                                                  
  model_STop       = fixParameters(workspace,"_STop"+label                    ,channel)
  model_VV         = fixParameters(workspace,"_VV"+label                      ,channel)
  # model_QCD        = fixParameters(workspace,"_QCD"+label                     ,channel)
  model_WJets      = fixParameters(workspace,"_WJets"+label                   ,channel)
  model_STop_fail  = fixParameters(workspace,"_STop"+label+"_failtau2tau1cut" ,channel)
  model_VV_fail    = fixParameters(workspace,"_VV"+label+"_failtau2tau1cut"   ,channel)
  model_WJets_fail = fixParameters(workspace,"_WJets"+label+"_failtau2tau1cut",channel)
  
  model_bkg_TotalMC        = MakeExtendedModel(workspace,"_bkg_TotalMC"+label,mj_shape["bkg_mc"],"_mj",channel,wtagger,constraintlist_MC,peak,wsname)
  model_bkg_TotalMC_fail   = MakeExtendedModel(workspace,"_bkg_TotalMC"+label+"_failtau2tau1cut",mj_shape["bkg_mc_fail"],"_mj",channel,wtagger,constraintlist_MC,peak,wsname)
  model_ttbar_TotalMC      = makeTTbarModel(workspace,"_ttbar_TotalMC"+label                   ,mj_shape["signal_mc"]     ,channel,wtagger,constraintlist_MC,peak,wsname ) 
  model_ttbar_TotalMC_fail = makeTTbarModel(workspace,"_ttbar_TotalMC"+label+"_failtau2tau1cut",mj_shape["signal_mc_fail"],channel,wtagger,constraintlist_MC,peak,wsname)                                                                                                                      
  model_TotalMC            = rt.RooAddPdf(("model_TotalMC"+label+"_"+channel),("model_TotalMC"+label+"_"+channel),rt.RooArgList(model_ttbar_TotalMC,model_bkg_TotalMC,model_STop,model_VV,model_WJets))
  model_TotalMC_fail       = rt.RooAddPdf(("model_TotalMC"+label+"_"+"failtau2tau1cut"+"_"+channel),("model_TotalMC"+label+"_"+"failtau2tau1cut"+"_"+channel),rt.RooArgList(model_ttbar_TotalMC_fail,model_bkg_TotalMC_fail,model_STop_fail,model_VV_fail,model_WJets_fail))
 
  getattr(workspace,'import')(model_TotalMC_fail)
  getattr(workspace,'import')(model_TotalMC)
  

  model_bkg_data         =  MakeExtendedModel(workspace,"_bkg_data"  +label                    ,mj_shape["bkg_data"],"_mj",channel,wtagger,constraintlist_data,peak,wsname)                 
  model_bkg_data_fail    =  MakeExtendedModel(workspace,"_bkg_data"  +label+"_failtau2tau1cut" ,mj_shape["bkg_data_fail"],"_mj",channel,wtagger,constraintlist_data,peak,wsname)     
  model_ttbar_data       =  makeTTbarModel   (workspace,"_ttbar_data"+label                    ,mj_shape["signal_data"]     ,channel,wtagger,constraintlist_data,peak,wsname)   
  model_ttbar_data_fail  =  makeTTbarModel   (workspace,"_ttbar_data"+label+"_failtau2tau1cut" ,mj_shape["signal_data_fail"],channel,wtagger,constraintlist_data,peak,wsname)
  model_data      = rt.RooAddPdf("model_data"+label+"_"+channel,"model_data"+label+"_"+channel                                , rt.RooArgList(model_ttbar_data ,model_bkg_data ,model_STop ,model_VV ,model_WJets ) )
  model_data_fail = rt.RooAddPdf("model_data"+label+"_failtau2tau1cut_"+channel,"model_data"+label+"_failtau2tau1cut_"+channel, rt.RooArgList(model_ttbar_data_fail,model_bkg_data_fail,model_STop_fail,model_VV_fail,model_WJets_fail) )
  
 
  print "Importing models: "
  getattr(workspace,'import')(model_data)
  getattr(workspace,'import')(model_data_fail)

def DrawScaleFactorTTbarControlSample(xtitle,workspace, color_palet, label, channel, wtagger, ptmin, ptmax, sample,outname):
        if outname.find("2016")!=-1: iPeriod = 40 #2016
        else: iPeriod = 4
        ttScalefactor = workspace.var("tt_scalefactor").getVal()
        LPttScalefactor = workspace.var("LP_tt_scalefactor").getVal()
        print ""
        print "Using tt scalefactor HP of " , ttScalefactor 
        print "Using tt scalefactor LP of " , LPttScalefactor 
        print ""
        
        rrv_mass_j = workspace.var("rrv_mass_j")
        model_histpdf_TTbar          = workspace.pdf("rdataset_TTbar"+label+"_"+channel+"_mj_histpdf")
        model_histpdf_STop           = workspace.pdf("rdataset_STop"+label+"_"+channel+"_mj_histpdf")
        model_histpdf_VV             = workspace.pdf("rdataset_VV"+label+"_"+channel+"_mj_histpdf")
        # model_histpdf_QCD            = workspace.pdf("rdataset_QCD"+label+"_"+channel+"_mj_histpdf")
        model_histpdf_WJets          = workspace.pdf("rdataset_WJets"+label+"_"+channel+"_mj_histpdf")
        model_histpdf_TTbar_merged   = workspace.pdf("rdataset_TTbar_realW"+label+"_"+channel+"_mj_histpdf")
        model_histpdf_TTbar_unmerged = workspace.pdf("rdataset_TTbar_fakeW"+label+"_"+channel+"_mj_histpdf")
        model_TTbar_STop_VV_WJets    = workspace.pdf("model_TTbar_STop_VV_WJets"+label+"_"+channel)
        
        model_histpdf_TTbar_fail          = workspace.pdf("rdataset_TTbar"+label+"_"+"failtau2tau1cut_"+channel+"_mj_histpdf")
        model_histpdf_STop_fail           = workspace.pdf("rdataset_STop"+label+"_"+"failtau2tau1cut_"+channel+"_mj_histpdf")
        model_histpdf_VV_fail             = workspace.pdf("rdataset_VV"+label+"_"+"failtau2tau1cut_"+channel+"_mj_histpdf")
        # model_histpdf_QCD_fail            = workspace.pdf("rdataset_QCD"+label+"_"+"failtau2tau1cut_"+channel+"_mj_histpdf")
        model_histpdf_WJets_fail          = workspace.pdf("rdataset_WJets"+label+"_"+"failtau2tau1cut_"+channel+"_mj_histpdf")
        model_histpdf_TTbar_fail_merged   = workspace.pdf("rdataset_TTbar_realW"+label+"_"+"failtau2tau1cut_"+channel+"_mj_histpdf")
        model_histpdf_TTbar_fail_unmerged = workspace.pdf("rdataset_TTbar_fakeW"+label+"_"+"failtau2tau1cut_"+channel+"_mj_histpdf") 
        model_TTbar_STop_VV_WJets_fail    = workspace.pdf("model_TTbar_STop_VV_WJets_fail"+label+"_"+channel);
        
        ## rescale factor for plots
        scale_number_TTbar_STop_VV_WJets      =  workspace.var("rrv_scale_number_TTbar_STop_VV_WJets").getValV();
        scale_number_TTbar_STop_VV_WJets_fail =  workspace.var("rrv_scale_number_TTbar_STop_VV_WJets_fail").getValV();

        simPdf_TotalMC = workspace.pdf("simPdf_TotalMC_em")
        simPdf_data    = workspace.pdf("simPdf_data_em")
        combData_p_f_TotalMC = workspace.data("combData_TotalMC_plot")
        combData_p_f_data = workspace.data("combData_data_plot")
        sample_type=workspace.cat("sample_type")

        xframe_data      = rrv_mass_j.frame( rt.RooFit.Bins(int(rrv_mass_j.getBins())));
        xframe_data_fail = rrv_mass_j.frame( rt.RooFit.Bins(int(rrv_mass_j.getBins())));
        xframe_data     .GetYaxis().SetTitle(" Events / (5 GeV)");
        xframe_data_fail.GetYaxis().SetTitle(" Events / (5 GeV)");
        xframe_data     .GetXaxis().SetTitle(xtitle);
        xframe_data_fail.GetXaxis().SetTitle(xtitle);
        
        ## plot data and mc on the frame
        
        #pass plot
        combData_p_f_data.plotOn(xframe_data,rt.RooFit.Name("data_invisible"), rt.RooFit.Cut("sample_type==sample_type::em_pass"), rt.RooFit.MarkerSize(1.5), rt.RooFit.DataError(rt.RooAbsData.SumW2), rt.RooFit.XErrorSize(0) );
        
        # model_TTbar_STop_VV_WJets.plotOn(xframe_data,rt.RooFit.Normalization(scale_number_TTbar_STop_VV_WJets),rt.RooFit.Name("TTbar")      ,rt.RooFit.DrawOption("F"), rt.RooFit.FillColor(color_palet["TTbar"+label]), rt.RooFit.LineColor(rt.kBlack), rt.RooFit.VLines())
 #        model_TTbar_STop_VV_WJets.plotOn(xframe_data,rt.RooFit.Normalization(scale_number_TTbar_STop_VV_WJets),rt.RooFit.Name("TTbar_realW"),rt.RooFit.Components("%s,%s,%s,%s,%s,%s"%(model_histpdf_TTbar_merged.GetName(),model_histpdf_TTbar_unmerged.GetName(),model_histpdf_STop.GetName(), model_histpdf_VV.GetName(), model_histpdf_WJets.GetName(),model_histpdf_QCD.GetName())),rt.RooFit.DrawOption("F"), rt.RooFit.FillColor(color_palet["TTbar_realW"+label]), rt.RooFit.LineColor(rt.kBlack), rt.RooFit.VLines())
 #        model_TTbar_STop_VV_WJets.plotOn(xframe_data,rt.RooFit.Normalization(scale_number_TTbar_STop_VV_WJets),rt.RooFit.Name("TTbar_fakeW"),rt.RooFit.Components("%s,%s,%s,%s,%s"   %(model_histpdf_TTbar_unmerged.GetName(),model_histpdf_STop.GetName(), model_histpdf_VV.GetName(), model_histpdf_WJets.GetName(),model_histpdf_QCD.GetName())),rt.RooFit.DrawOption("F"), rt.RooFit.FillColor(color_palet["TTbar_fakeW"+label]), rt.RooFit.LineColor(rt.kBlack), rt.RooFit.VLines())
 #        model_TTbar_STop_VV_WJets.plotOn(xframe_data,rt.RooFit.Normalization(scale_number_TTbar_STop_VV_WJets),rt.RooFit.Name("STop")       ,rt.RooFit.Components("%s,%s,%s,%s"      %(model_histpdf_STop.GetName(), model_histpdf_VV.GetName(), model_histpdf_WJets.GetName(),model_histpdf_QCD.GetName())), rt.RooFit.DrawOption("F"), rt.RooFit.FillColor(color_palet["STop"]), rt.RooFit.LineColor(rt.kBlack), rt.RooFit.VLines())
 #        model_TTbar_STop_VV_WJets.plotOn(xframe_data,rt.RooFit.Normalization(scale_number_TTbar_STop_VV_WJets),rt.RooFit.Name("VV")         ,rt.RooFit.Components("%s,%s,%s"         %(model_histpdf_VV.GetName(), model_histpdf_WJets.GetName(),model_histpdf_QCD.GetName()) ), rt.RooFit.DrawOption("F"), rt.RooFit.FillColor(color_palet["VV"]), rt.RooFit.LineColor(rt.kBlack), rt.RooFit.VLines())
 #        model_TTbar_STop_VV_WJets.plotOn(xframe_data,rt.RooFit.Normalization(scale_number_TTbar_STop_VV_WJets),rt.RooFit.Name("WJets")      ,rt.RooFit.Components("%s,%s"            %(model_histpdf_WJets.GetName(),model_histpdf_QCD.GetName()) ), rt.RooFit.DrawOption("F"), rt.RooFit.FillColor(color_palet["WJets"]), rt.RooFit.LineColor(rt.kBlack), rt.RooFit.VLines())
 #        # model_TTbar_STop_VV_WJets.plotOn(xframe_data,rt.RooFit.Normalization(scale_number_TTbar_STop_VV_WJets),rt.RooFit.Name("QCD")        ,rt.RooFit.Components("%s"               %(model_histpdf_QCD.GetName()) ), rt.RooFit.DrawOption("F"), rt.RooFit.FillColor(color_palet["QCD"]), rt.RooFit.LineColor(rt.kBlack), rt.RooFit.VLines())
        model_TTbar_STop_VV_WJets.plotOn(xframe_data,rt.RooFit.Normalization(scale_number_TTbar_STop_VV_WJets),rt.RooFit.Name("TTbar")      ,rt.RooFit.DrawOption("F"), rt.RooFit.FillColor(color_palet["TTbar"+label]), rt.RooFit.LineColor(rt.kBlack), rt.RooFit.VLines())    
        model_TTbar_STop_VV_WJets.plotOn(xframe_data,rt.RooFit.Normalization(scale_number_TTbar_STop_VV_WJets),rt.RooFit.Name("TTbar_realW"),rt.RooFit.Components("%s,%s,%s,%s,%s"%(model_histpdf_TTbar_merged.GetName(),model_histpdf_TTbar_unmerged.GetName(),model_histpdf_STop.GetName(), model_histpdf_VV.GetName(), model_histpdf_WJets.GetName())),rt.RooFit.DrawOption("F"), rt.RooFit.FillColor(color_palet["TTbar_realW"+label]), rt.RooFit.LineColor(rt.kBlack), rt.RooFit.VLines())    
        model_TTbar_STop_VV_WJets.plotOn(xframe_data,rt.RooFit.Normalization(scale_number_TTbar_STop_VV_WJets),rt.RooFit.Name("TTbar_fakeW"),rt.RooFit.Components("%s,%s,%s,%s"   %(model_histpdf_TTbar_unmerged.GetName(),model_histpdf_STop.GetName(), model_histpdf_VV.GetName(), model_histpdf_WJets.GetName())),rt.RooFit.DrawOption("F"), rt.RooFit.FillColor(color_palet["TTbar_fakeW"+label]), rt.RooFit.LineColor(rt.kBlack), rt.RooFit.VLines())    
        model_TTbar_STop_VV_WJets.plotOn(xframe_data,rt.RooFit.Normalization(scale_number_TTbar_STop_VV_WJets),rt.RooFit.Name("STop")       ,rt.RooFit.Components("%s,%s,%s"      %(model_histpdf_STop.GetName(), model_histpdf_VV.GetName(), model_histpdf_WJets.GetName())), rt.RooFit.DrawOption("F"), rt.RooFit.FillColor(color_palet["STop"]), rt.RooFit.LineColor(rt.kBlack), rt.RooFit.VLines())        
        model_TTbar_STop_VV_WJets.plotOn(xframe_data,rt.RooFit.Normalization(scale_number_TTbar_STop_VV_WJets),rt.RooFit.Name("VV")         ,rt.RooFit.Components("%s,%s"         %(model_histpdf_VV.GetName(), model_histpdf_WJets.GetName()) ), rt.RooFit.DrawOption("F"), rt.RooFit.FillColor(color_palet["VV"]), rt.RooFit.LineColor(rt.kBlack), rt.RooFit.VLines())
        model_TTbar_STop_VV_WJets.plotOn(xframe_data,rt.RooFit.Normalization(scale_number_TTbar_STop_VV_WJets),rt.RooFit.Name("WJets")      ,rt.RooFit.Components("%s"            %(model_histpdf_WJets.GetName()) ), rt.RooFit.DrawOption("F"), rt.RooFit.FillColor(color_palet["WJets"]), rt.RooFit.LineColor(rt.kBlack), rt.RooFit.VLines())
        # model_TTbar_STop_VV_WJets.plotOn(xframe_data,rt.RooFit.Normalization(scale_number_TTbar_STop_VV_WJets),rt.RooFit.Name("QCD")        ,rt.RooFit.Components("%s"               %(model_histpdf_QCD.GetName()) ), rt.RooFit.DrawOption("F"), rt.RooFit.FillColor(color_palet["QCD"]), rt.RooFit.LineColor(rt.kBlack), rt.RooFit.VLines())
        
        # model_TTbar_STop_VV_WJets.plotOn(xframe_data,rt.RooFit.Normalization(scale_number_TTbar_STop_VV_WJets),rt.RooFit.Name("TTline_invisible"), rt.RooFit.LineColor(rt.kBlack), rt.RooFit.LineWidth(2), rt.RooFit.VLines())
#         model_TTbar_STop_VV_WJets.plotOn(xframe_data,rt.RooFit.Normalization(scale_number_TTbar_STop_VV_WJets),rt.RooFit.Name("TTrealW_line_invisible"), rt.RooFit.LineColor(rt.kBlack), rt.RooFit.LineWidth(2), rt.RooFit.VLines())
#         model_TTbar_STop_VV_WJets.plotOn(xframe_data,rt.RooFit.Normalization(scale_number_TTbar_STop_VV_WJets),rt.RooFit.Name("TTfakeW_line_invisible"), rt.RooFit.LineColor(rt.kBlack), rt.RooFit.LineWidth(2), rt.RooFit.VLines())
#         model_TTbar_STop_VV_WJets.plotOn(xframe_data,rt.RooFit.Normalization(scale_number_TTbar_STop_VV_WJets),rt.RooFit.Name("STline_invisible") ,rt.RooFit.Components("%s,%s,%s,%s"%(model_histpdf_STop.GetName(), model_histpdf_VV.GetName(), model_histpdf_WJets.GetName(),model_histpdf_QCD.GetName()) ), rt.RooFit.LineColor(rt.kBlack), rt.RooFit.LineWidth(2), rt.RooFit.VLines())
#         model_TTbar_STop_VV_WJets.plotOn(xframe_data,rt.RooFit.Normalization(scale_number_TTbar_STop_VV_WJets),rt.RooFit.Name("VVline_invisible") ,rt.RooFit.Components("%s,%s,%s"%(model_histpdf_VV.GetName(), model_histpdf_WJets.GetName(),model_histpdf_QCD.GetName()) ), rt.RooFit.LineColor(rt.kBlack), rt.RooFit.LineWidth(2), rt.RooFit.VLines())
#         model_TTbar_STop_VV_WJets.plotOn(xframe_data,rt.RooFit.Normalization(scale_number_TTbar_STop_VV_WJets),rt.RooFit.Name("WJ_line_invisible"),rt.RooFit.Components("%s,%s"%(model_histpdf_WJets.GetName(),model_histpdf_QCD.GetName()) ), rt.RooFit.LineColor(rt.kBlack), rt.RooFit.LineWidth(2), rt.RooFit.VLines())
#         # model_TTbar_STop_VV_WJets.plotOn(xframe_data,rt.RooFit.Normalization(scale_number_TTbar_STop_VV_WJets),rt.RooFit.Name("QC_line_invisible"),rt.RooFit.Components("%s"%(model_histpdf_QCD.GetName()) ), rt.RooFit.LineColor(rt.kBlack), rt.RooFit.LineWidth(2), rt.RooFit.VLines())
#       model_TTbar_STop_VV_WJets.plotOn(xframe_data,rt.RooFit.Normalization(scale_number_TTbar_STop_VV_WJets),rt.RooFit.Name("TTline_invisible"), rt.RooFit.LineColor(rt.kBlack), rt.RooFit.LineWidth(2), rt.RooFit.VLines())        
        model_TTbar_STop_VV_WJets.plotOn(xframe_data,rt.RooFit.Normalization(scale_number_TTbar_STop_VV_WJets),rt.RooFit.Name("TTrealW_line_invisible"), rt.RooFit.LineColor(rt.kBlack), rt.RooFit.LineWidth(2), rt.RooFit.VLines())
        model_TTbar_STop_VV_WJets.plotOn(xframe_data,rt.RooFit.Normalization(scale_number_TTbar_STop_VV_WJets),rt.RooFit.Name("TTfakeW_line_invisible"), rt.RooFit.LineColor(rt.kBlack), rt.RooFit.LineWidth(2), rt.RooFit.VLines())
        model_TTbar_STop_VV_WJets.plotOn(xframe_data,rt.RooFit.Normalization(scale_number_TTbar_STop_VV_WJets),rt.RooFit.Name("STline_invisible") ,rt.RooFit.Components("%s,%s,%s"%(model_histpdf_STop.GetName(), model_histpdf_VV.GetName(), model_histpdf_WJets.GetName()) ), rt.RooFit.LineColor(rt.kBlack), rt.RooFit.LineWidth(2), rt.RooFit.VLines())
        model_TTbar_STop_VV_WJets.plotOn(xframe_data,rt.RooFit.Normalization(scale_number_TTbar_STop_VV_WJets),rt.RooFit.Name("VVline_invisible") ,rt.RooFit.Components("%s,%s"%(model_histpdf_VV.GetName(), model_histpdf_WJets.GetName()) ), rt.RooFit.LineColor(rt.kBlack), rt.RooFit.LineWidth(2), rt.RooFit.VLines())
        model_TTbar_STop_VV_WJets.plotOn(xframe_data,rt.RooFit.Normalization(scale_number_TTbar_STop_VV_WJets),rt.RooFit.Name("WJ_line_invisible"),rt.RooFit.Components("%s"%(model_histpdf_WJets.GetName()) ), rt.RooFit.LineColor(rt.kBlack), rt.RooFit.LineWidth(2), rt.RooFit.VLines())
        # model_TTbar_STop_VV_WJets.plotOn(xframe_data,rt.RooFit.Normalization(scale_number_TTbar_STop_VV_WJets),rt.RooFit.Name("QC_line_invisible"),rt.RooFit.Components("%s"%(model_histpdf_QCD.GetName()) ), rt.RooFit.LineColor(rt.kBlack), rt.RooFit.LineWidth(2), rt.RooFit.VLines())
        
        #redraw data
        combData_p_f_data.plotOn(xframe_data,rt.RooFit.Name("data"), rt.RooFit.Cut("sample_type==sample_type::em_pass"), rt.RooFit.MarkerSize(1.5), rt.RooFit.DataError(rt.RooAbsData.SumW2), rt.RooFit.XErrorSize(0) );
        
        #plot MC fit function 
        simPdf_TotalMC.plotOn(xframe_data,rt.RooFit.Name("MC fit"),rt.RooFit.Slice(sample_type,"em_pass"), rt.RooFit.ProjWData(rt.RooArgSet(sample_type),combData_p_f_data),rt.RooFit.NormRange("controlsample_fitting_range"), rt.RooFit.LineStyle(rt.kSolid), rt.RooFit.LineColor(rt.kRed))
        cut ="model_bkg_TotalMC_%s_mj,model_STop_%s_mj,model_VV_%s_mj,model_WJets_%s_mj"%(channel,channel,channel,channel);
        simPdf_TotalMC.plotOn(xframe_data,rt.RooFit.Name("mcfit bkg_invisible"),rt.RooFit.Slice(sample_type,"em_pass"),rt.RooFit.ProjWData(rt.RooArgSet(sample_type),combData_p_f_data),rt.RooFit.NormRange("controlsample_fitting_range"), rt.RooFit.Components(cut), rt.RooFit.LineColor(rt.kRed), rt.RooFit.LineStyle(rt.kDashed))
        
        ## plot data fit function
        combData_p_f_data.plotOn(xframe_data,rt.RooFit.Name("dinvisible"), rt.RooFit.Cut("sample_type==sample_type::em_pass"), rt.RooFit.MarkerSize(1.5), rt.RooFit.DataError(rt.RooAbsData.SumW2), rt.RooFit.XErrorSize(0) );
        simPdf_data.plotOn(xframe_data,rt.RooFit.Name("Data fit"),rt.RooFit.Slice(sample_type,"em_pass"),rt.RooFit.ProjWData(rt.RooArgSet(sample_type),combData_p_f_data),rt.RooFit.NormRange("controlsample_fitting_range"), rt.RooFit.LineStyle(rt.kSolid), rt.RooFit.LineColor(rt.kBlue))
        cut = "model_bkg_data_%s_mj,model_STop_%s_mj,model_VV_%s_mj,model_WJets0_%s_mj"%(channel,channel,channel,channel)
        simPdf_data.plotOn(xframe_data,rt.RooFit.Name("dat fit bkg_invisible"),rt.RooFit.Slice(sample_type,"em_pass"),rt.RooFit.ProjWData(rt.RooArgSet(sample_type),combData_p_f_data),rt.RooFit.NormRange("controlsample_fitting_range"), rt.RooFit.Components(cut), rt.RooFit.LineStyle(rt.kDashed), rt.RooFit.LineColor(rt.kBlue))
        
        #fail plot
        combData_p_f_data.plotOn(xframe_data_fail,rt.RooFit.Name("dinvisible"), rt.RooFit.Cut("sample_type==sample_type::em_fail"), rt.RooFit.MarkerSize(1.5), rt.RooFit.DataError(rt.RooAbsData.SumW2), rt.RooFit.XErrorSize(0) );
        
        # model_TTbar_STop_VV_WJets_fail.plotOn(xframe_data_fail,rt.RooFit.Normalization(scale_number_TTbar_STop_VV_WJets_fail),rt.RooFit.Name("TTbar"), rt.RooFit.DrawOption("F"), rt.RooFit.FillColor(color_palet["TTbar"+label]), rt.RooFit.LineColor(rt.kBlack), rt.RooFit.VLines())
#         model_TTbar_STop_VV_WJets_fail.plotOn(xframe_data_fail,rt.RooFit.Normalization(scale_number_TTbar_STop_VV_WJets_fail),rt.RooFit.Name("TTbar_realW"),rt.RooFit.Components("%s,%s,%s,%s,%s,%s"%(model_histpdf_TTbar_fail_merged.GetName(),model_histpdf_TTbar_fail_unmerged.GetName(),model_histpdf_STop_fail.GetName(), model_histpdf_VV_fail.GetName(), model_histpdf_WJets_fail.GetName(),model_histpdf_QCD_fail.GetName()) ), rt.RooFit.DrawOption("F"), rt.RooFit.FillColor(color_palet["TTbar_realW"+label]), rt.RooFit.LineColor(rt.kBlack), rt.RooFit.VLines())
#         model_TTbar_STop_VV_WJets_fail.plotOn(xframe_data_fail,rt.RooFit.Normalization(scale_number_TTbar_STop_VV_WJets_fail),rt.RooFit.Name("TTbar_fakeW"),rt.RooFit.Components("%s,%s,%s,%s,%s"%(model_histpdf_TTbar_fail_unmerged.GetName(),model_histpdf_STop_fail.GetName(), model_histpdf_VV_fail.GetName(), model_histpdf_WJets_fail.GetName(),model_histpdf_QCD_fail.GetName()) ), rt.RooFit.DrawOption("F"), rt.RooFit.FillColor(color_palet["TTbar_fakeW"+label]), rt.RooFit.LineColor(rt.kBlack), rt.RooFit.VLines())
#         model_TTbar_STop_VV_WJets_fail.plotOn(xframe_data_fail,rt.RooFit.Normalization(scale_number_TTbar_STop_VV_WJets_fail),rt.RooFit.Name("STop")       ,rt.RooFit.Components("%s,%s,%s,%s"%(model_histpdf_STop_fail.GetName(), model_histpdf_VV_fail.GetName(), model_histpdf_WJets_fail.GetName(),model_histpdf_QCD_fail.GetName()) ), rt.RooFit.DrawOption("F"), rt.RooFit.FillColor(color_palet["STop"]), rt.RooFit.LineColor(rt.kBlack), rt.RooFit.VLines())
#         model_TTbar_STop_VV_WJets_fail.plotOn(xframe_data_fail,rt.RooFit.Normalization(scale_number_TTbar_STop_VV_WJets_fail),rt.RooFit.Name("VV")         ,rt.RooFit.Components("%s,%s,%s"%(model_histpdf_VV_fail.GetName(), model_histpdf_WJets_fail.GetName(),model_histpdf_QCD_fail.GetName()) ), rt.RooFit.DrawOption("F"), rt.RooFit.FillColor(color_palet["VV"]), rt.RooFit.LineColor(rt.kBlack), rt.RooFit.VLines())
#         model_TTbar_STop_VV_WJets_fail.plotOn(xframe_data_fail,rt.RooFit.Normalization(scale_number_TTbar_STop_VV_WJets_fail),rt.RooFit.Name("WJets")      ,rt.RooFit.Components("%s,%s"%( model_histpdf_WJets_fail.GetName(),model_histpdf_QCD_fail.GetName()) ), rt.RooFit.DrawOption("F"), rt.RooFit.FillColor(color_palet["WJets"]), rt.RooFit.LineColor(rt.kBlack), rt.RooFit.VLines())
#         # model_TTbar_STop_VV_WJets_fail.plotOn(xframe_data_fail,rt.RooFit.Normalization(scale_number_TTbar_STop_VV_WJets_fail),rt.RooFit.Name("QCD")        ,rt.RooFit.Components("%s"%( model_histpdf_QCD_fail.GetName()) ), rt.RooFit.DrawOption("F"), rt.RooFit.FillColor(color_palet["QCD"]), rt.RooFit.LineColor(rt.kBlack), rt.RooFit.VLines())
#
#         #solid line
#         model_TTbar_STop_VV_WJets_fail.plotOn(xframe_data_fail,rt.RooFit.Normalization(scale_number_TTbar_STop_VV_WJets_fail),rt.RooFit.Name("TT_line_invisible"), rt.RooFit.LineColor(rt.kBlack), rt.RooFit.LineWidth(2), rt.RooFit.VLines())
#         model_TTbar_STop_VV_WJets_fail.plotOn(xframe_data_fail,rt.RooFit.Normalization(scale_number_TTbar_STop_VV_WJets_fail),rt.RooFit.Name("TTrealW_line_invisible"), rt.RooFit.LineColor(rt.kBlack), rt.RooFit.LineWidth(2), rt.RooFit.VLines())
#         model_TTbar_STop_VV_WJets_fail.plotOn(xframe_data_fail,rt.RooFit.Normalization(scale_number_TTbar_STop_VV_WJets_fail),rt.RooFit.Name("TTfakeW_line_invisible"), rt.RooFit.LineColor(rt.kBlack), rt.RooFit.LineWidth(2), rt.RooFit.VLines())
#         model_TTbar_STop_VV_WJets_fail.plotOn(xframe_data_fail,rt.RooFit.Normalization(scale_number_TTbar_STop_VV_WJets_fail),rt.RooFit.Name("STline_invisible") ,rt.RooFit.Components("%s,%s,%s,%s"%(model_histpdf_STop_fail.GetName(), model_histpdf_VV_fail.GetName(), model_histpdf_WJets_fail.GetName(),model_histpdf_QCD_fail.GetName()) ), rt.RooFit.LineColor(rt.kBlack), rt.RooFit.LineWidth(2), rt.RooFit.VLines())
#         model_TTbar_STop_VV_WJets_fail.plotOn(xframe_data_fail,rt.RooFit.Normalization(scale_number_TTbar_STop_VV_WJets_fail),rt.RooFit.Name("VVline_invisible") ,rt.RooFit.Components("%s,%s,%s"%(model_histpdf_VV_fail.GetName(), model_histpdf_WJets_fail.GetName(),model_histpdf_QCD_fail.GetName()) ), rt.RooFit.LineColor(rt.kBlack), rt.RooFit.LineWidth(2), rt.RooFit.VLines())
#         model_TTbar_STop_VV_WJets_fail.plotOn(xframe_data_fail,rt.RooFit.Normalization(scale_number_TTbar_STop_VV_WJets_fail),rt.RooFit.Name("WJ_line_invisible"),rt.RooFit.Components("%s,%s"%( model_histpdf_WJets_fail.GetName(),model_histpdf_QCD_fail.GetName()) ), rt.RooFit.LineColor(rt.kBlack), rt.RooFit.LineWidth(2), rt.RooFit.VLines())
#         # model_TTbar_STop_VV_WJets_fail.plotOn(xframe_data_fail,rt.RooFit.Normalization(scale_number_TTbar_STop_VV_WJets_fail),rt.RooFit.Name("QCD_line_invisible"),rt.RooFit.Components("%s"%( model_histpdf_QCD_fail.GetName()) ), rt.RooFit.LineColor(rt.kBlack), rt.RooFit.LineWidth(2), rt.RooFit.VLines())

        model_TTbar_STop_VV_WJets_fail.plotOn(xframe_data_fail,rt.RooFit.Normalization(scale_number_TTbar_STop_VV_WJets_fail),rt.RooFit.Name("TTbar"), rt.RooFit.DrawOption("F"), rt.RooFit.FillColor(color_palet["TTbar"+label]), rt.RooFit.LineColor(rt.kBlack), rt.RooFit.VLines())        
        model_TTbar_STop_VV_WJets_fail.plotOn(xframe_data_fail,rt.RooFit.Normalization(scale_number_TTbar_STop_VV_WJets_fail),rt.RooFit.Name("TTbar_realW"),rt.RooFit.Components("%s,%s,%s,%s,%s"%(model_histpdf_TTbar_fail_merged.GetName(),model_histpdf_TTbar_fail_unmerged.GetName(),model_histpdf_STop_fail.GetName(), model_histpdf_VV_fail.GetName(), model_histpdf_WJets_fail.GetName()) ), rt.RooFit.DrawOption("F"), rt.RooFit.FillColor(color_palet["TTbar_realW"+label]), rt.RooFit.LineColor(rt.kBlack), rt.RooFit.VLines())        
        model_TTbar_STop_VV_WJets_fail.plotOn(xframe_data_fail,rt.RooFit.Normalization(scale_number_TTbar_STop_VV_WJets_fail),rt.RooFit.Name("TTbar_fakeW"),rt.RooFit.Components("%s,%s,%s,%s"%(model_histpdf_TTbar_fail_unmerged.GetName(),model_histpdf_STop_fail.GetName(), model_histpdf_VV_fail.GetName(), model_histpdf_WJets_fail.GetName()) ), rt.RooFit.DrawOption("F"), rt.RooFit.FillColor(color_palet["TTbar_fakeW"+label]), rt.RooFit.LineColor(rt.kBlack), rt.RooFit.VLines())        
        model_TTbar_STop_VV_WJets_fail.plotOn(xframe_data_fail,rt.RooFit.Normalization(scale_number_TTbar_STop_VV_WJets_fail),rt.RooFit.Name("STop")       ,rt.RooFit.Components("%s,%s,%s"%(model_histpdf_STop_fail.GetName(), model_histpdf_VV_fail.GetName(), model_histpdf_WJets_fail.GetName()) ), rt.RooFit.DrawOption("F"), rt.RooFit.FillColor(color_palet["STop"]), rt.RooFit.LineColor(rt.kBlack), rt.RooFit.VLines())        
        model_TTbar_STop_VV_WJets_fail.plotOn(xframe_data_fail,rt.RooFit.Normalization(scale_number_TTbar_STop_VV_WJets_fail),rt.RooFit.Name("VV")         ,rt.RooFit.Components("%s,%s"%(model_histpdf_VV_fail.GetName(), model_histpdf_WJets_fail.GetName()) ), rt.RooFit.DrawOption("F"), rt.RooFit.FillColor(color_palet["VV"]), rt.RooFit.LineColor(rt.kBlack), rt.RooFit.VLines())        
        model_TTbar_STop_VV_WJets_fail.plotOn(xframe_data_fail,rt.RooFit.Normalization(scale_number_TTbar_STop_VV_WJets_fail),rt.RooFit.Name("WJets")      ,rt.RooFit.Components("%s"%( model_histpdf_WJets_fail.GetName()) ), rt.RooFit.DrawOption("F"), rt.RooFit.FillColor(color_palet["WJets"]), rt.RooFit.LineColor(rt.kBlack), rt.RooFit.VLines())
        # model_TTbar_STop_VV_WJets_fail.plotOn(xframe_data_fail,rt.RooFit.Normalization(scale_number_TTbar_STop_VV_WJets_fail),rt.RooFit.Name("QCD")        ,rt.RooFit.Components("%s"%( model_histpdf_QCD_fail.GetName()) ), rt.RooFit.DrawOption("F"), rt.RooFit.FillColor(color_palet["QCD"]), rt.RooFit.LineColor(rt.kBlack), rt.RooFit.VLines())
        
        #solid line
        model_TTbar_STop_VV_WJets_fail.plotOn(xframe_data_fail,rt.RooFit.Normalization(scale_number_TTbar_STop_VV_WJets_fail),rt.RooFit.Name("TT_line_invisible"), rt.RooFit.LineColor(rt.kBlack), rt.RooFit.LineWidth(2), rt.RooFit.VLines())      
        model_TTbar_STop_VV_WJets_fail.plotOn(xframe_data_fail,rt.RooFit.Normalization(scale_number_TTbar_STop_VV_WJets_fail),rt.RooFit.Name("TTrealW_line_invisible"), rt.RooFit.LineColor(rt.kBlack), rt.RooFit.LineWidth(2), rt.RooFit.VLines())
        model_TTbar_STop_VV_WJets_fail.plotOn(xframe_data_fail,rt.RooFit.Normalization(scale_number_TTbar_STop_VV_WJets_fail),rt.RooFit.Name("TTfakeW_line_invisible"), rt.RooFit.LineColor(rt.kBlack), rt.RooFit.LineWidth(2), rt.RooFit.VLines())
        model_TTbar_STop_VV_WJets_fail.plotOn(xframe_data_fail,rt.RooFit.Normalization(scale_number_TTbar_STop_VV_WJets_fail),rt.RooFit.Name("STline_invisible") ,rt.RooFit.Components("%s,%s,%s"%(model_histpdf_STop_fail.GetName(), model_histpdf_VV_fail.GetName(), model_histpdf_WJets_fail.GetName()) ), rt.RooFit.LineColor(rt.kBlack), rt.RooFit.LineWidth(2), rt.RooFit.VLines())
        model_TTbar_STop_VV_WJets_fail.plotOn(xframe_data_fail,rt.RooFit.Normalization(scale_number_TTbar_STop_VV_WJets_fail),rt.RooFit.Name("VVline_invisible") ,rt.RooFit.Components("%s,%s"%(model_histpdf_VV_fail.GetName(), model_histpdf_WJets_fail.GetName()) ), rt.RooFit.LineColor(rt.kBlack), rt.RooFit.LineWidth(2), rt.RooFit.VLines())
        model_TTbar_STop_VV_WJets_fail.plotOn(xframe_data_fail,rt.RooFit.Normalization(scale_number_TTbar_STop_VV_WJets_fail),rt.RooFit.Name("WJ_line_invisible"),rt.RooFit.Components("%s"%( model_histpdf_WJets_fail.GetName()) ), rt.RooFit.LineColor(rt.kBlack), rt.RooFit.LineWidth(2), rt.RooFit.VLines())
        # model_TTbar_STop_VV_WJets_fail.plotOn(xframe_data_fail,rt.RooFit.Normalization(scale_number_TTbar_STop_VV_WJets_fail),rt.RooFit.Name("QCD_line_invisible"),rt.RooFit.Components("%s"%( model_histpdf_QCD_fail.GetName()) ), rt.RooFit.LineColor(rt.kBlack), rt.RooFit.LineWidth(2), rt.RooFit.VLines())
        
        #redraw data
        combData_p_f_data.plotOn(xframe_data_fail,rt.RooFit.Name("data"), rt.RooFit.Cut("sample_type==sample_type::em_fail"), rt.RooFit.MarkerSize(1.5), rt.RooFit.DataError(rt.RooAbsData.SumW2), rt.RooFit.XErrorSize(0) );
        
        #plot MC fit function 
        simPdf_TotalMC.plotOn(xframe_data_fail,rt.RooFit.Name("MC fit"),rt.RooFit.Slice(sample_type,"em_fail"), rt.RooFit.ProjWData(rt.RooArgSet(sample_type),combData_p_f_data),rt.RooFit.NormRange("controlsample_fitting_range"), rt.RooFit.LineStyle(rt.kSolid), rt.RooFit.LineColor(rt.kRed))
        cut = "model_bkg_TotalMC_failtau2tau1cut_%s_mj,model_STop_failtau2tau1cut_%s_mj,model_VV_failtau2tau1cut_%s_mj,model_WJets0_failtau2tau1cut_%s_mj"%(channel,channel,channel,channel)
        simPdf_TotalMC.plotOn(xframe_data_fail,rt.RooFit.Name("mcfit bkg_invisible"),rt.RooFit.Slice(sample_type,"em_fail"),rt.RooFit.ProjWData(rt.RooArgSet(sample_type),combData_p_f_data),rt.RooFit.NormRange("controlsample_fitting_range"), rt.RooFit.Components(cut), rt.RooFit.LineColor(rt.kRed), rt.RooFit.LineStyle(rt.kDashed))
        
        ## plot data fit function
        combData_p_f_data.plotOn(xframe_data_fail,rt.RooFit.Name("dinvisible"), rt.RooFit.Cut("sample_type==sample_type::em_fail"), rt.RooFit.MarkerSize(1.5), rt.RooFit.DataError(rt.RooAbsData.SumW2), rt.RooFit.XErrorSize(0) );
        simPdf_data.plotOn(xframe_data_fail,rt.RooFit.Name("Data fit"),rt.RooFit.Slice(sample_type,"em_fail"),rt.RooFit.ProjWData(rt.RooArgSet(sample_type),combData_p_f_data),rt.RooFit.NormRange("controlsample_fitting_range"), rt.RooFit.LineStyle(rt.kSolid), rt.RooFit.LineColor(rt.kBlue))
        cut = "model_bkg_data_failtau2tau1cut_%s_mj,model_STop_failtau2tau1cut_%s_mj,model_VV_failtau2tau1cut_%s_mj,model_WJets0_failtau2tau1cut_%s_mj"%(channel,channel,channel,channel)
        simPdf_data.plotOn(xframe_data_fail,rt.RooFit.Name("dat fit bkg_invisible"),rt.RooFit.Slice(sample_type,"em_fail"),rt.RooFit.ProjWData(rt.RooArgSet(sample_type),combData_p_f_data),rt.RooFit.NormRange("controlsample_fitting_range"), rt.RooFit.Components(cut), rt.RooFit.LineStyle(rt.kDashed), rt.RooFit.LineColor(rt.kBlue))
        
        
        #add mean and width
        rrv_mean_gaus_data    =workspace.var("rrv_mean1_gaus_ttbar_data_em_mj")
        rrv_sigma_gaus_data   =workspace.var("rrv_sigma1_gaus_ttbar_data_em_mj")
        rrv_mean_gaus_TotalMC =workspace.var("rrv_mean1_gaus_ttbar_TotalMC_em_mj")
        rrv_sigma_gaus_TotalMC=workspace.var("rrv_sigma1_gaus_ttbar_TotalMC_em_mj")
        
        tl_bin  = rt.TLatex(0.70,0.40, ("%i GeV < p_{T} < %i GeV")%(ptmin,ptmax) )
        tl_bin.SetNDC()
        tl_bin.SetTextSize(0.03)
        xframe_data.addObject(tl_bin)

        if rrv_mean_gaus_TotalMC:
            tl_MC_mean  = rt.TLatex(0.75,0.62, ("#mu_{MC } = %3.2f #pm %2.2f")%(rrv_mean_gaus_TotalMC.getVal(), rrv_mean_gaus_TotalMC.getError()) );
            tl_MC_sigma = rt.TLatex(0.75,0.57, ("#sigma_{MC }= %2.2f #pm %2.2f")%(rrv_sigma_gaus_TotalMC.getVal(), rrv_sigma_gaus_TotalMC.getError()) );
            tl_MC_mean.SetNDC(); tl_MC_sigma.SetNDC();
            tl_MC_mean.SetTextSize(0.03)
            tl_MC_sigma.SetTextSize(0.03)
            xframe_data.addObject(tl_MC_mean);
            xframe_data.addObject(tl_MC_sigma);

        if rrv_mean_gaus_data:
            tl_data_mean =rt.TLatex(0.75,0.52, ("#mu_{data} = %3.2f #pm %2.2f")%(rrv_mean_gaus_data.getVal(), rrv_mean_gaus_data.getError()) );
            tl_data_sigma=rt.TLatex(0.75,0.47, ("#sigma_{data}= %2.2f #pm %2.2f")%(rrv_sigma_gaus_data.getVal(), rrv_sigma_gaus_data.getError()) );
            tl_data_mean.SetNDC(); tl_data_sigma.SetNDC();
            tl_data_mean.SetTextSize(0.03)
            tl_data_sigma.SetTextSize(0.03)
            xframe_data.addObject(tl_data_mean); xframe_data.addObject(tl_data_sigma);

        # rrv_mean_gaus_data_fail    =workspace.var("rrv_mean1_gaus_ttbar_data_failtau2tau1cut_em_mj")
 #        rrv_sigma_gaus_data_fail   =workspace.var("rrv_sigma1_gaus_ttbar_data_failtau2tau1cut_em_mj")
 #        rrv_mean_gaus_TotalMC_fail =workspace.var("rrv_mean1_gaus_ttbar_TotalMC_failtau2tau1cut_em_mj")
 #        rrv_sigma_gaus_TotalMC_fail=workspace.var("rrv_sigma1_gaus_ttbar_TotalMC_failtau2tau1cut_em_mj")
 #
 #        tl_bin_fail  = rt.TLatex(0.70,0.40, ("%i GeV < p_{T} < %i GeV")%(ptmin,ptmax) )
 #        tl_bin_fail.SetNDC()
 #        tl_bin_fail.SetTextSize(0.03)
 #        xframe_data_fail.addObject(tl_bin_fail)
 #
 #        if rrv_mean_gaus_TotalMC_fail:
 #            tl_MC_mean_fail  = rt.TLatex(0.75,0.62, ("#mu_{MC } = %3.2f #pm %2.2f")%(rrv_mean_gaus_TotalMC_fail.getVal(), rrv_mean_gaus_TotalMC_fail.getError()) );
 #            tl_MC_sigma_fail = rt.TLatex(0.75,0.57, ("#sigma_{MC }= %2.2f #pm %2.2f")%(rrv_sigma_gaus_TotalMC_fail.getVal(), rrv_sigma_gaus_TotalMC_fail.getError()) );
 #            tl_MC_mean_fail.SetNDC(); tl_MC_sigma_fail.SetNDC();
 #            tl_MC_mean_fail.SetTextSize(0.03)
 #            tl_MC_sigma_fail.SetTextSize(0.03)
 #            xframe_data_fail.addObject(tl_MC_mean_fail);
 #            xframe_data_fail.addObject(tl_MC_sigma_fail);
 #
 #        if rrv_mean_gaus_data_fail:
 #            tl_data_mean_fail =rt.TLatex(0.75,0.52, ("#mu_{data} = %3.2f #pm %2.2f")%(rrv_mean_gaus_data_fail.getVal(), rrv_mean_gaus_data_fail.getError()) );
 #            tl_data_sigma_fail=rt.TLatex(0.75,0.47, ("#sigma_{data}= %2.2f #pm %2.2f")%(rrv_sigma_gaus_data_fail.getVal(), rrv_sigma_gaus_data_fail.getError()) );
 #            tl_data_mean_fail.SetNDC(); tl_data_sigma_fail.SetNDC();
 #            tl_data_mean_fail.SetTextSize(0.03)
 #            tl_data_sigma_fail.SetTextSize(0.03)
 #            xframe_data_fail.addObject(tl_data_mean_fail); xframe_data_fail.addObject(tl_data_sigma_fail);

         
        xframe_data.GetYaxis().SetRangeUser(1e-2,xframe_data.GetMaximum()*1.5);
        xframe_data_fail.GetYaxis().SetRangeUser(1e-2,xframe_data_fail.GetMaximum()*1.5);
        
        legend = getLegend(xframe_data,"em",0.3885213,0.6640827,0.9774937,0.8992248)
        legend.AddEntry(xframe_data.findObject("data")       ,"Data"                ,"PLE"); 
        legend.AddEntry(xframe_data.findObject("TTbar_fakeW"),"t#bar{t} (unmerged)" ,"F");
        legend.AddEntry(xframe_data.findObject("Data fit")   ,"Data fit"            ,"L");
        legend.AddEntry(xframe_data.findObject("STop")       ,"Single top"          ,"F");
        legend.AddEntry(xframe_data.findObject("MC fit")     ,"MC fit"              ,"L");
        legend.AddEntry(xframe_data.findObject("WJets")      ,"W+jets"              ,"F");
        legend.AddEntry(xframe_data.findObject("TTbar_realW"),"t#bar{t} (merged)"   ,"F"); 
        legend.AddEntry(xframe_data.findObject("VV")         ,"WW/WZ/ZZ"            ,"F");
        # legend.AddEntry(xframe_data.findObject("QCD")        ,"QCD"                 ,"F");
        
        xframe_data.addObject(legend);
        xframe_data_fail.addObject(legend);
        
        c1 = getCanvas()
        c1.cd()
        xframe_data.Draw()
        CMS_lumi(c1, iPeriod, iPos)
        c1.Update()
        dirname = "plots/"+outname.replace('workspace_', '')
        c1.SaveAs(dirname+"/pass.png")
        c1.SaveAs(dirname+"/pass.pdf")
        c1.SaveAs(dirname+"/pass.C")
        c1.SaveAs(dirname+"/pass.root")
        c1.cd()
        xframe_data_fail.Draw()
        CMS_lumi(c1, iPeriod, iPos)
        c1.Update()
        c1.SaveAs(dirname+"/fail.png")
        c1.SaveAs(dirname+"/fail.pdf")
        c1.SaveAs(dirname+"/fail.C")
        c1.SaveAs(dirname+"/fail.root")
        
        
                # # #signal window
        #           lowerLine = rt.TLine(mj_signal_min,0.,mj_signal_min,xframe_data.GetMaximum()); lowerLine.SetLineWidth(2); lowerLine.SetLineColor(kGray+2); lowerLine.SetLineStyle(9);
        #           upperLine = rt.TLine(mj_signal_max,0.,mj_signal_max,xframe_data.GetMaximum()); upperLine.SetLineWidth(2); upperLine.SetLineColor(kGray+2); upperLine.SetLineStyle(9);
        #           xframe_data.addObject(lowerLine); xframe_data.addObject(upperLine);
        #           lowerLine = rt.TLine(mj_signal_min,0.,mj_signal_min,xframe_data_fail.GetMaximum()); lowerLine.SetLineWidth(2); lowerLine.SetLineColor(kGray+2); lowerLine.SetLineStyle(9);
        #           upperLine = rt.TLine(mj_signal_max,0.,mj_signal_max,xframe_data_fail.GetMaximum()); upperLine.SetLineWidth(2); upperLine.SetLineColor(kGray+2); upperLine.SetLineStyle(9);
        #           xframe_data_fail.addObject(lowerLine); xframe_data_fail.addObject(upperLine);
        
                # # #legend
                #   leg_data=legend4Plot(xframe_data,0,1, 0.15)
                #   xframe_data.addObject(leg_data)
                #   leg_data_fail=legend4Plot(xframe_data_fail,0,1,0.18)
                #   xframe_data_fail.addObject(leg_data_fail)
                

