import ROOT
from ROOT import RooHistPdf,RooRealVar,RooExponential,RooGaussian,RooCBShape,RooExtendPdf,RooAddPdf,RooArgList,RooArgSet,RooFormulaVar
import sys

ROOT.gSystem.Load("PDFs/HWWLVJRooPdfs_cxx.so")
def addConstraint(workspace,rrv_x, x_mean, x_sigma, ConstraintsList):
    rrv_x_mean = RooRealVar(rrv_x.GetName()+"_mean",rrv_x.GetName()+"_mean",x_mean )
    rrv_x_sigma = RooRealVar(rrv_x.GetName()+"_sigma",rrv_x.GetName()+"_sigma",x_sigma )
    constrainpdf_x = RooGaussian("constrainpdf_"+rrv_x.GetName(),"constrainpdf_"+rrv_x.GetName(),rrv_x, rrv_x_mean, rrv_x_sigma)
    ConstraintsList.append(constrainpdf_x.GetName())
    getattr(workspace,"import")(constrainpdf_x)
    print "Added constrain to parameter", rrv_x.GetName(), "with mean",  x_mean, "and sigma", x_sigma
    return constrainpdf_x
            
def change_dataset_to_histpdf(workspace,x,dataset):
  datahist = dataset.binnedClone(dataset.GetName()+"_binnedClone",dataset.GetName()+"_binnedClone")
  histpdf  = RooHistPdf(dataset.GetName()+"_histpdf",dataset.GetName()+"_histpdf",RooArgSet(x),datahist)
  getattr(workspace,'import')(histpdf)

def MakeGeneralPdf(workspace,label,model,spectrum,wtagger_label, channel,constraint,peak="W",wsname = ""):
    
    print "Making general PDF for ","model_pdf"+label+"_"+channel+spectrum 
    rrv_x = workspace.var("rrv_mass_j")
    gaus_means  = 8.2653e+01
    gaussigmas   = 7
    if peak == "t":
        gaus_means  = 180
        gaussigmas   = 18
    
    
    if model == "Gaus2ErfExp":
        mean1_tmp = 8.2653e+01;
        sigma1_tmp = 7.5932e+00;
        rangeMean = 8. ;
        rangeWidth = 5. ;
        c0_tmp     = -2.7180e-02 ; c0_tmp_err     = 6.83e-03;
        offset_tmp =  8.6888e+01 ; offset_tmp_err = 19.35e+00;
        width_tmp  =  3.6383e+01 ; width_tmp_err  = 1.34e+00;

        rrv_offset_ErfExp = RooRealVar("rrv_offset_ErfExp"+label+"_"+channel+spectrum ,"rrv_offset_ErfExp"+label+"_"+channel+spectrum ,offset_tmp,0,300)
        rrv_width_ErfExp  = RooRealVar("rrv_width_ErfExp" +label+"_"+channel+spectrum ,"rrv_width_ErfExp" +label+"_"+channel+spectrum ,width_tmp, 0., 300.)
        rrv_c_ErfExp      = RooRealVar("rrv_c_ErfExp"     +label+"_"+channel+spectrum ,"rrv_c_ErfExp"     +label+"_"+channel+spectrum ,c0_tmp,-1, +1 )
        rrv_mean1_gaus  = RooRealVar("rrv_mean1_gaus"+label+"_"+channel+spectrum ,"rrv_mean1_gaus"+label+"_"+channel+spectrum   ,80.,75.,87.)
        rrv_sigma1_gaus = RooRealVar("rrv_sigma1_gaus"+label+"_"+channel+spectrum ,"rrv_sigma1_gaus"+label+"_"+channel+spectrum ,7.6,5.,16. )
        rrv_mean2_gaus  = RooRealVar("rrv_mean2_gaus"+label+"_"+channel+spectrum ,"rrv_mean2_gaus"+label+"_"+channel+spectrum   ,170,150,180)
        rrv_sigma2_gaus = RooRealVar("rrv_sigma2_gaus"+label+"_"+channel+spectrum ,"rrv_sigma2_gaus"+label+"_"+channel+spectrum ,13,10.,20. )
        gaus1 = RooGaussian("gaus1"+label+"_"+channel+spectrum ,"gaus1"+label+"_"+channel+spectrum ,rrv_x,rrv_mean1_gaus,rrv_sigma1_gaus)     
        gaus2 = RooGaussian("gaus2"+label+"_"+channel+spectrum ,"gaus2"+label+"_"+channel+spectrum ,rrv_x,rrv_mean2_gaus,rrv_sigma2_gaus)
        rrv_frac = RooRealVar("rrv_frac"+label+"_"+channel+spectrum ,"rrv_frac"+label+"_"+channel+spectrum ,0.95,0.70,1.)

        erfExp    = ROOT.RooErfExpPdf("erfExp"+label+"_"+channel+spectrum,"model_pdf"+label+"_"+channel+spectrum,rrv_x,rrv_c_ErfExp,rrv_offset_ErfExp,rrv_width_ErfExp)
        model_pdf = RooAddPdf("model_pdf"+label+"_"+channel+spectrum,"model_pdf"+label+"_"+channel+spectrum,RooArgList(gaus1,erfExp),RooArgList(rrv_frac),1)
        
    if model == "ErfExp":
        rrv_c_ErfExp      = RooRealVar("rrv_c_ErfExp"+label+"_"+channel+spectrum,"rrv_c_ErfExp"+label+"_"+channel+spectrum,-0.026,-0.05, 0.05)
        rrv_offset_ErfExp = RooRealVar("rrv_offset_ErfExp"+label+"_"+channel+spectrum,"rrv_offset_ErfExp"+label+"_"+channel+spectrum,41.,0.,100)
        rrv_width_ErfExp  = RooRealVar("rrv_width_ErfExp"+label+"_"+channel+spectrum,"rrv_width_ErfExp"+label+"_"+channel+spectrum,30.,1.,100.)
        model_pdf         = ROOT.RooErfExpPdf("model_pdf"+label+"_"+channel+spectrum,"model_pdf"+label+"_"+channel+spectrum,rrv_x,rrv_c_ErfExp,rrv_offset_ErfExp,rrv_width_ErfExp)

    if model == "ExpGaus":
        
        if label.find("_STop_failtau2tau1cut")!=-1:
            rrv_c_Exp       = RooRealVar("rrv_c_Exp"+label+"_"+channel+spectrum,"rrv_c_Exp"+label+"_"+channel+spectrum,-0.03,-0.5,0.5)
            rrv_mean1_gaus  = RooRealVar("rrv_mean1_gaus"+label+"_"+channel+spectrum,"rrv_mean1_gaus"+label+"_"+channel+spectrum,gaus_means,gaus_means*.8,gaus_means*1.2) #Too narrow limits here often lead to error!! eg max 80
            rrv_sigma1_gaus = RooRealVar("rrv_sigma1_gaus"+label+"_"+channel+spectrum,"rrv_sigma1_gaus"+label+"_"+channel+spectrum,gaussigmas,gaussigmas*.5,gaussigmas*1.5)
        
        
        elif label.find("fail")!=-1:
            rrv_c_Exp       = RooRealVar("rrv_c_Exp"+label+"_"+channel+spectrum,"rrv_c_Exp"+label+"_"+channel+spectrum,-0.05,-0.5,0.5)
            rrv_mean1_gaus  = RooRealVar("rrv_mean1_gaus"+label+"_"+channel+spectrum,"rrv_mean1_gaus"+label+"_"+channel+spectrum,gaus_means,gaus_means*.8,gaus_means*1.2)
            rrv_sigma1_gaus = RooRealVar("rrv_sigma1_gaus"+label+"_"+channel+spectrum,"rrv_sigma1_gaus"+label+"_"+channel+spectrum,gaussigmas,gaussigmas*.5,gaussigmas*1.5)
            rrv_high        = RooRealVar("rrv_high"+label+"_"+channel+spectrum,"rrv_high"+label+"_"+channel+spectrum,0.3,0.3,1.)
        
        else:
            rrv_c_Exp       = RooRealVar("rrv_c_Exp"+label+"_"+channel+spectrum,"rrv_c_Exp"+label+"_"+channel+spectrum,-0.01,-1.,0.)
            rrv_mean1_gaus  = RooRealVar("rrv_mean1_gaus"+label+"_"+channel+spectrum,"rrv_mean1_gaus"+label+"_"+channel+spectrum,gaus_means,gaus_means*.8,gaus_means*1.2) 
            rrv_sigma1_gaus = RooRealVar("rrv_sigma1_gaus"+label+"_"+channel+spectrum,"rrv_sigma1_gaus"+label+"_"+channel+spectrum,gaussigmas,gaussigmas*.5,gaussigmas*1.5)
            rrv_high        = RooRealVar("rrv_high"+label+"_"+channel+spectrum,"rrv_high"+label+"_"+channel+spectrum,0.7,0.,1.)
          
        exp     = RooExponential("exp"+label+"_"+channel+spectrum,"exp"+label+"_"+channel+spectrum,rrv_x,rrv_c_Exp)
        gaus        = RooGaussian("gaus"+label+"_"+channel+spectrum,"gaus"+label+"_"+channel+spectrum, rrv_x,rrv_mean1_gaus,rrv_sigma1_gaus)
        model_pdf   = RooAddPdf("model_pdf"+label+"_"+channel+spectrum,"model_pdf"+label+"_"+channel+spectrum,RooArgList(exp,gaus),RooArgList(rrv_high))
     
    if model == "ErfExp_ttbar" or model == "ErfExp_ttbar_ddt" or model == "ErfExp_ttbar_failtau2tau1cut" or model == "ErfExp_ttbar_failtau2tau1cut_fitMC" or model == "ErfExp_ttbar_failtau2tau1cut_ddt" or model == "ErfExp_ttbar_fitMC":
        
        if model.find("fitMC")!=-1:
            c0_tmp     =  -3.5239e-02 ; c0_tmp_err     = 4.52e-03;
            offset_tmp =  9.3695e+01  ; offset_tmp_err = 3.53e+00;
            width_tmp  =  3.2006e+01  ; width_tmp_err  = 1.84e+00;
            rrv_offset_ErfExp = RooRealVar("rrv_offset_ErfExp"+label+"_"+channel+spectrum ,"rrv_offset_ErfExp"+label+"_"+channel+spectrum ,8.5861e+01, 0,300) 
            rrv_width_ErfExp  = RooRealVar("rrv_width_ErfExp" +label+"_"+channel+spectrum ,"rrv_width_ErfExp" +label+"_"+channel+spectrum ,3.7079e+01,0,200)#,width_tmp-10, width_tmp+10)
            rrv_c_ErfExp  = RooRealVar("rrv_c_ErfExp"  +label+"_"+channel+spectrum ,"rrv_c_ErfExp"     +label+"_"+channel+spectrum ,-2.2697e-02    , -5, 5 )
            if peak == "Wt":
                rrv_offset_ErfExp = RooRealVar("rrv_offset_ErfExp"+label+"_"+channel+spectrum ,"rrv_offset_ErfExp"+label+"_"+channel+spectrum ,105.531277, 0,300)
                rrv_width_ErfExp  = RooRealVar("rrv_width_ErfExp" +label+"_"+channel+spectrum ,"rrv_width_ErfExp" +label+"_"+channel+spectrum ,35.684694,0,200)#,width_tmp-10, width_tmp+10)
                rrv_c_ErfExp  = RooRealVar("rrv_c_ErfExp"  +label+"_"+channel+spectrum ,"rrv_c_ErfExp"     +label+"_"+channel+spectrum ,-0.050428    , -5, 5 )

        else:
            with open("ttfit_parameters%s.txt"%wsname) as f: 
                for line in f:
                    name  = line.split(" ")[0]
                    value = float(line.split(" ")[1])
                    err   = abs(float(line.split(" ")[2]))
                    # err = abs(0.10*value)
                    if label.find('fail')!=-1:              
                        print "FAIL FIT: Importing variable - ", line
                        if line.find('rrv_c_ErfExp_TTbar_fakeW_failtau2tau1cut_em_mj'     )!=-1: rrv_c_ErfExp      = RooRealVar('rrv_c_ErfExp'     + label+"_"+channel+spectrum ,'rrv_c_ErfExp'     + label+"_"+channel+spectrum  ,value)#, value-err, value+err )
                        if line.find('rrv_offset_ErfExp_TTbar_fakeW_failtau2tau1cut_em_mj')!=-1: rrv_offset_ErfExp = RooRealVar('rrv_offset_ErfExp'+ label+"_"+channel+spectrum ,'rrv_offset_ErfExp'+ label+"_"+channel+spectrum  ,value)#, value-err, value+err )
                        if line.find('rrv_width_ErfExp_TTbar_fakeW_failtau2tau1cut_em_mj' )!=-1: rrv_width_ErfExp  = RooRealVar('rrv_width_ErfExp' + label+"_"+channel+spectrum ,'rrv_width_ErfExp' + label+"_"+channel+spectrum  ,value)#, value-err, value+err )
                    else:
                        if line.find('rrv_c_ErfExp_TTbar_fakeW_em_mj'     )!=-1: rrv_c_ErfExp      = RooRealVar('rrv_c_ErfExp'     + label+"_"+channel+spectrum ,'rrv_c_ErfExp'     + label+"_"+channel+spectrum  ,value)# , value-err, value+err )
                        if line.find('rrv_offset_ErfExp_TTbar_fakeW_em_mj')!=-1: rrv_offset_ErfExp = RooRealVar('rrv_offset_ErfExp'+ label+"_"+channel+spectrum ,'rrv_offset_ErfExp'+ label+"_"+channel+spectrum  ,value)# , value-err, value+err )
                        if line.find('rrv_width_ErfExp_TTbar_fakeW_em_mj' )!=-1: rrv_width_ErfExp  = RooRealVar('rrv_width_ErfExp' + label+"_"+channel+spectrum ,'rrv_width_ErfExp' + label+"_"+channel+spectrum  ,value)# , value-err, value+err )
                        if wsname.find("2017")!=-1:
                           if line.find('rrv_c_ErfExp_TTbar_fakeW_em_mj'     )!=-1: rrv_c_ErfExp      = RooRealVar('rrv_c_ErfExp'     + label+"_"+channel+spectrum ,'rrv_c_ErfExp'     + label+"_"+channel+spectrum  ,value)# , value-err, value+err )
                           if line.find('rrv_offset_ErfExp_TTbar_fakeW_em_mj')!=-1: rrv_offset_ErfExp = RooRealVar('rrv_offset_ErfExp'+ label+"_"+channel+spectrum ,'rrv_offset_ErfExp'+ label+"_"+channel+spectrum  ,value)# , value-err, value+err )
                           if line.find('rrv_width_ErfExp_TTbar_fakeW_em_mj' )!=-1: rrv_width_ErfExp  = RooRealVar('rrv_width_ErfExp' + label+"_"+channel+spectrum ,'rrv_width_ErfExp' + label+"_"+channel+spectrum  ,value)# , value-err, value+err )
        
        model_pdf     = ROOT.RooErfExpPdf("model_pdf"+label+"_"+channel+spectrum,"model_pdf"+label+"_"+channel+spectrum ,rrv_x,rrv_c_ErfExp,rrv_offset_ErfExp,rrv_width_ErfExp)
        
#        if "fail" in model:
#            gaus1 = addConstraint(workspace,rrv_c_ErfExp,rrv_c_ErfExp.getVal(),rrv_c_ErfExp.getError(),constraint)
#            gaus2 = addConstraint(workspace,rrv_offset_ErfExp,rrv_offset_ErfExp.getVal(),rrv_offset_ErfExp.getError(),constraint)
#            gaus3 = addConstraint(workspace,rrv_width_ErfExp,rrv_width_ErfExp.getVal(),rrv_width_ErfExp.getError(),constraint)
        
    # if model.find("GausErfExp_ttbar")!=-1:
   #
   #      frac_tmp = 1.; #Use only Gaussian component to model real W-jets, ErfExp set to zero by setting fraction to 1!
   #
   #      if model.find("MC")!=-1:
   #          mean1_tmp = 8.2653e+01;
   #          sigma1_tmp = 7.5932e+00;
   #          rangeMean = 8. ;
   #          rangeWidth = 5. ;
   #          c0_tmp     = -2.7180e-02 ; c0_tmp_err     = 6.83e-03;
   #          offset_tmp =  8.6888e+01 ; offset_tmp_err = 19.35e+00;
   #          width_tmp  =  3.6383e+01 ; width_tmp_err  = 1.34e+00;
   #
   #          rrv_mean1_gaus  = RooRealVar("rrv_mean2_gaus"+label+"_"+channel+spectrum ,"rrv_mean2_gaus"+label+"_"+channel+spectrum   ,gaus_means,gaus_means*.2,gaus_means*2.2)
   #          rrv_sigma1_gaus = RooRealVar("rrv_sigma2_gaus"+label+"_"+channel+spectrum ,"rrv_sigma2_gaus"+label+"_"+channel+spectrum ,gaussigmas,gaussigmas*.2,gaussigmas*2.5 )
   #          gaus1 = RooGaussian("gaus2"+label+"_"+channel+spectrum ,"gaus2"+label+"_"+channel+spectrum ,rrv_x,rrv_mean1_gaus,rrv_sigma1_gaus)
   #          rrv_offset_ErfExp = RooRealVar("rrv_offset_ErfExp"+label+"_"+channel+spectrum ,"rrv_offset_ErfExp"+label+"_"+channel+spectrum ,offset_tmp,60,100)
   #          rrv_width_ErfExp  = RooRealVar("rrv_width_ErfExp" +label+"_"+channel+spectrum ,"rrv_width_ErfExp" +label+"_"+channel+spectrum ,36., 30., 170.)
   #          rrv_c_ErfExp      = RooRealVar("rrv_c_ErfExp"     +label+"_"+channel+spectrum ,"rrv_c_ErfExp"     +label+"_"+channel+spectrum ,c0_tmp,-1, +1 )
   #          rrv_frac = RooRealVar("rrv_frac"+label+"_"+channel+spectrum ,"rrv_frac"+label+"_"+channel+spectrum ,0.95,0.70,1.)
   #          if model.find("fail")!=-1: rrv_frac = RooRealVar("rrv_frac"+label+"_"+channel+spectrum ,"rrv_frac"+label+"_"+channel+spectrum ,0.67,0.6,1.)
   #
   #      else:
   #          with open("ttfit_parameters%s.txt"%wsname) as f:
   #              for line in f:
   #                 name  = line.split(" ")[0]
   #                 value = float(line.split(" ")[1])
   #                 err   = abs(float(line.split(" ")[2]))
   #                 # err = abs(0.20*value)
   #                 if label.find('fail')!=-1:
   #                     if line.find('rrv_c_ErfExp_TTbar_realW_failtau2tau1cut_em_mj'     )!=-1: rrv_c_ErfExp      = RooRealVar('rrv_c_ErfExp'     + label+"_"+channel+spectrum ,'rrv_c_ErfExp'     + label+"_"+channel+spectrum  ,value   , value*0.8, value*1.2 )
   #                     if line.find('rrv_offset_ErfExp_TTbar_realW_failtau2tau1cut_em_mj')!=-1: rrv_offset_ErfExp = RooRealVar('rrv_offset_ErfExp'+ label+"_"+channel+spectrum ,'rrv_offset_ErfExp'+ label+"_"+channel+spectrum  ,value   , value*0.8, value*1.2 )
   #                     if line.find('rrv_width_ErfExp_TTbar_realW_failtau2tau1cut_em_mj' )!=-1: rrv_width_ErfExp  = RooRealVar('rrv_width_ErfExp' + label+"_"+channel+spectrum ,'rrv_width_ErfExp' + label+"_"+channel+spectrum  ,value   , value*0.8, value*1.2 )
   #                     if line.find('rrv_mean2_gaus_TTbar_realW_failtau2tau1cut_em_mj'   )!=-1: rrv_mean1_gaus    = RooRealVar("rrv_mean2_gaus"   + label +"_"+channel+spectrum ,"rrv_mean2_gaus"   + label +"_"+channel+spectrum,value   , value*0.8, value*1.2 )
   #                     if line.find('rrv_sigma2_gaus_TTbar_realW_failtau2tau1cut_em_mj'  )!=-1: rrv_sigma1_gaus   = RooRealVar("rrv_sigma2_gaus"  + label +"_"+channel+spectrum ,"rrv_sigma2_gaus"  + label +"_"+channel+spectrum,value   , value*0.8, value*1.2 )
   #                     if line.find('rrv_frac_TTbar_realW_failtau2tau1cut_em_mj'         )!=-1: rrv_frac          = RooRealVar("rrv_frac"         + label +"_"+channel+spectrum ,"rrv_frac"         + label +"_"+channel+spectrum,value   , value*0.8, value*1.2 )
   #                 else:
   #                     if line.find('rrv_c_ErfExp_TTbar_realW_em_mj'     )!=-1: rrv_c_ErfExp      = RooRealVar('rrv_c_ErfExp'     + label +"_"+channel+spectrum ,'rrv_c_ErfExp'     + label +"_"+channel+spectrum  ,value   , value*0.8, value*1.2 )
   #                     if line.find('rrv_offset_ErfExp_TTbar_realW_em_mj')!=-1: rrv_offset_ErfExp = RooRealVar('rrv_offset_ErfExp'+ label +"_"+channel+spectrum ,'rrv_offset_ErfExp'+ label +"_"+channel+spectrum  ,value   , value*0.8, value*1.2 )
   #                     if line.find('rrv_width_ErfExp_TTbar_realW_em_mj' )!=-1: rrv_width_ErfExp  = RooRealVar('rrv_width_ErfExp' + label +"_"+channel+spectrum ,'rrv_width_ErfExp' + label +"_"+channel+spectrum  ,value   , value*0.8, value*1.2 )
   #                     if line.find('rrv_mean2_gaus_TTbar_realW_em_mj'   )!=-1: rrv_mean1_gaus    = RooRealVar("rrv_mean2_gaus"   + label +"_"+channel+spectrum ,"rrv_mean2_gaus"   + label +"_"+channel+spectrum  ,value   , value*0.8, value*1.2 )
   #                     if line.find('rrv_sigma2_gaus_TTbar_realW_em_mj'  )!=-1: rrv_sigma1_gaus   = RooRealVar("rrv_sigma2_gaus"  + label +"_"+channel+spectrum ,"rrv_sigma2_gaus"  + label +"_"+channel+spectrum  ,value   , value*0.8, value*1.2 )
   #                     if line.find('rrv_frac_TTbar_realW_em_mj'         )!=-1: rrv_frac          = RooRealVar("rrv_frac"         + label +"_"+channel+spectrum ,"rrv_frac"         + label +"_"+channel+spectrum  ,value   , value*0.8, value*1.2 )
   #
   #          gaus1 = RooGaussian("gaus2"+label+"_"+channel+spectrum ,"gaus2"+label+"_"+channel+spectrum ,rrv_x,rrv_mean1_gaus,rrv_sigma1_gaus)
   #          rrv_frac.setConstant(ROOT.kTRUE)
   #
   #      erfExp    = ROOT.RooErfExpPdf("erfExp"+label+"_"+channel+spectrum,"model_pdf"+label+"_"+channel+spectrum,rrv_x,rrv_c_ErfExp,rrv_offset_ErfExp,rrv_width_ErfExp)
   #      model_pdf = RooAddPdf("model_pdf"+label+"_"+channel+spectrum,"model_pdf"+label+"_"+channel+spectrum,RooArgList(gaus1,erfExp),RooArgList(rrv_frac),1)

    if model == "Gaus2ErfExp" or model == "Gaus2ErfExp_ttbar" or model == "Gaus2ErfExp_ttbar_fitMC" or model =="Gaus2ErfExp_ttbar_failtau2tau1cut" or model =="Gaus2ErfExp_ttbar_failtau2tau1cut_fitMC":
        
        frac_tmp = 1.0; #Use only Gaussian component to model real W-jets, ErfExp set to zero by setting fraction to 1!
        
        # if model.find("fitMC")!=-1:
        mean1_tmp = 8.2653e+01;
        sigma1_tmp = 7.5932e+00;
        rangeMean = 8. ;
        rangeWidth = 5. ;
        c0_tmp     = -2.7180e-02 ; c0_tmp_err     = 6.83e-03;
        offset_tmp =  8.6888e+01 ; offset_tmp_err = 19.35e+00;
        width_tmp  =  3.6383e+01 ; width_tmp_err  = 1.34e+00;

        rrv_offset_ErfExp = RooRealVar("rrv_offset_ErfExp"+label+"_"+channel+spectrum ,"rrv_offset_ErfExp"+label+"_"+channel+spectrum ,130.,0,300)
        rrv_width_ErfExp  = RooRealVar("rrv_width_ErfExp" +label+"_"+channel+spectrum ,"rrv_width_ErfExp" +label+"_"+channel+spectrum ,45, 0., 300.)
        rrv_c_ErfExp      = RooRealVar("rrv_c_ErfExp"     +label+"_"+channel+spectrum ,"rrv_c_ErfExp"     +label+"_"+channel+spectrum ,-0.03,-1, +1 )
        rrv_mean1_gaus  = RooRealVar("rrv_mean1_gaus"+label+"_"+channel+spectrum ,"rrv_mean1_gaus"+label+"_"+channel+spectrum   ,80.,70.,90.)
        rrv_sigma1_gaus = RooRealVar("rrv_sigma1_gaus"+label+"_"+channel+spectrum ,"rrv_sigma1_gaus"+label+"_"+channel+spectrum ,7.6,3.,16. )
        rrv_mean2_gaus  = RooRealVar("rrv_mean2_gaus"+label+"_"+channel+spectrum ,"rrv_mean2_gaus"+label+"_"+channel+spectrum   ,170,150,180)
        rrv_sigma2_gaus = RooRealVar("rrv_sigma2_gaus"+label+"_"+channel+spectrum ,"rrv_sigma2_gaus"+label+"_"+channel+spectrum ,13,10.,20. )
        gaus1 = RooGaussian("gaus1"+label+"_"+channel+spectrum ,"gaus1"+label+"_"+channel+spectrum ,rrv_x,rrv_mean1_gaus,rrv_sigma1_gaus)     
        gaus2 = RooGaussian("gaus2"+label+"_"+channel+spectrum ,"gaus2"+label+"_"+channel+spectrum ,rrv_x,rrv_mean2_gaus,rrv_sigma2_gaus)
        
        rrv_frac1 = RooRealVar("rrv_frac1"+label+"_"+channel+spectrum ,"rrv_frac1"+label+"_"+channel+spectrum ,0.64,0.0,1.)
        rrv_frac2 = RooRealVar("rrv_frac2"+label+"_"+channel+spectrum ,"rrv_frac2"+label+"_"+channel+spectrum ,0.05,0.0,1.)
            
        # else:
        #   with open("ttfit_parameters%s.txt"%wsname) as f:
        #       for line in f:
        #          name  = line.split(" ")[0]
        #          value = float(line.split(" ")[1])
        #          err   = abs(float(line.split(" ")[2]))
        #          # err = abs(0.20*value)
        #          if label.find('fail')!=-1:
        #              if line.find('rrv_c_ErfExp_TTbar_realW_failtau2tau1cut_em_mj'     )!=-1: rrv_c_ErfExp      = RooRealVar('rrv_c_ErfExp'     + label+"_"+channel+spectrum ,'rrv_c_ErfExp'     + label+"_"+channel+spectrum  ,value   , value-err, value+err )
        #              if line.find('rrv_offset_ErfExp_TTbar_realW_failtau2tau1cut_em_mj')!=-1: rrv_offset_ErfExp = RooRealVar('rrv_offset_ErfExp'+ label+"_"+channel+spectrum ,'rrv_offset_ErfExp'+ label+"_"+channel+spectrum  ,value   , value-err, value+err )
        #              if line.find('rrv_width_ErfExp_TTbar_realW_failtau2tau1cut_em_mj' )!=-1: rrv_width_ErfExp  = RooRealVar('rrv_width_ErfExp' + label+"_"+channel+spectrum ,'rrv_width_ErfExp' + label+"_"+channel+spectrum  ,value   , value-err, value+err )
        #              if line.find('rrv_mean1_gaus_TTbar_realW_failtau2tau1cut_em_mj'   )!=-1: rrv_mean1_gaus    = RooRealVar("rrv_mean1_gaus"   + label +"_"+channel+spectrum ,"rrv_mean1_gaus"   + label +"_"+channel+spectrum  ,value   , value*0.8, value*1.2 )
        #              if line.find('rrv_sigma1_gaus_TTbar_realW_failtau2tau1cut_em_mj'  )!=-1: rrv_sigma1_gaus   = RooRealVar("rrv_sigma1_gaus"  + label +"_"+channel+spectrum ,"rrv_sigma1_gaus"  + label +"_"+channel+spectrum  ,value   , value*0.8, value*1.2 )
        #              if line.find('rrv_mean2_gaus_TTbar_realW_failtau2tau1cut_em_mj'   )!=-1: rrv_mean2_gaus    = RooRealVar("rrv_mean2_gaus"   + label +"_"+channel+spectrum ,"rrv_mean2_gaus"   + label +"_"+channel+spectrum  ,value   , value*0.8, value*1.2 )
        #              if line.find('rrv_sigma2_gaus_TTbar_realW_failtau2tau1cut_em_mj'  )!=-1: rrv_sigma2_gaus   = RooRealVar("rrv_sigma2_gaus"  + label +"_"+channel+spectrum ,"rrv_sigma2_gaus"  + label +"_"+channel+spectrum  ,value   , value*0.8, value*1.2 )
        #              if line.find('rrv_frac_TTbar_realW_failtau2tau1cut_em_mj'         )!=-1: rrv_frac          = RooRealVar("rrv_frac"         + label +"_"+channel+spectrum ,"rrv_frac"         + label +"_"+channel+spectrum  ,value   , value-err, value+err )
        #          else:
        #              if line.find('rrv_c_ErfExp_TTbar_realW_em_mj'     )!=-1: rrv_c_ErfExp      = RooRealVar('rrv_c_ErfExp'     + label +"_"+channel+spectrum ,'rrv_c_ErfExp'     + label +"_"+channel+spectrum  ,value   , value-err, value+err )
        #              if line.find('rrv_offset_ErfExp_TTbar_realW_em_mj')!=-1: rrv_offset_ErfExp = RooRealVar('rrv_offset_ErfExp'+ label +"_"+channel+spectrum ,'rrv_offset_ErfExp'+ label +"_"+channel+spectrum  ,value   , value-err, value+err )
        #              if line.find('rrv_width_ErfExp_TTbar_realW_em_mj' )!=-1: rrv_width_ErfExp  = RooRealVar('rrv_width_ErfExp' + label +"_"+channel+spectrum ,'rrv_width_ErfExp' + label +"_"+channel+spectrum  ,value   , value-err, value+err )
        #              if line.find('rrv_mean1_gaus_TTbar_realW_em_mj'   )!=-1: rrv_mean1_gaus    = RooRealVar("rrv_mean1_gaus"   + label +"_"+channel+spectrum ,"rrv_mean1_gaus"   + label +"_"+channel+spectrum  ,value   , value*0.8, value*1.2 )
        #              if line.find('rrv_sigma1_gaus_TTbar_realW_em_mj'  )!=-1: rrv_sigma1_gaus   = RooRealVar("rrv_sigma1_gaus"  + label +"_"+channel+spectrum ,"rrv_sigma1_gaus"  + label +"_"+channel+spectrum  ,value   , value*0.8, value*1.2 )
        #              if line.find('rrv_mean2_gaus_TTbar_realW_em_mj'   )!=-1: rrv_mean2_gaus    = RooRealVar("rrv_mean2_gaus"   + label +"_"+channel+spectrum ,"rrv_mean2_gaus"   + label +"_"+channel+spectrum  ,value   , value*0.8, value*1.2 )
        #              if line.find('rrv_sigma2_gaus_TTbar_realW_em_mj'  )!=-1: rrv_sigma2_gaus   = RooRealVar("rrv_sigma2_gaus"  + label +"_"+channel+spectrum ,"rrv_sigma2_gaus"  + label +"_"+channel+spectrum  ,value   , value*0.8, value*1.2 )
        #              if line.find('rrv_frac_TTbar_realW_em_mj'         )!=-1: rrv_frac          = RooRealVar("rrv_frac"         + label +"_"+channel+spectrum ,"rrv_frac"         + label +"_"+channel+spectrum  ,value   , value-err, value+err )
        #   gaus1 = RooGaussian("gaus1"+label+"_"+channel+spectrum ,"gaus1"+label+"_"+channel+spectrum ,rrv_x,rrv_mean1_gaus,rrv_sigma1_gaus)
        #   gaus2 = RooGaussian("gaus2"+label+"_"+channel+spectrum ,"gaus2"+label+"_"+channel+spectrum ,rrv_x,rrv_mean2_gaus,rrv_sigma2_gaus)
            
             
        erfExp    = ROOT.RooErfExpPdf("erfExp"+label+"_"+channel+spectrum,"model_pdf"+label+"_"+channel+spectrum,rrv_x,rrv_c_ErfExp,rrv_offset_ErfExp,rrv_width_ErfExp)
        model_pdf = RooAddPdf("model_pdf"+label+"_"+channel+spectrum,"model_pdf"+label+"_"+channel+spectrum,RooArgList(gaus1,gaus2,erfExp),RooArgList(rrv_frac1,rrv_frac2),1)

    if model == "Exp" :
        rrv_c_Exp = RooRealVar("rrv_c_Exp"+label+"_"+channel+spectrum,"rrv_c_Exp"+label+"_"+channel+spectrum,-0.030, -2., 0.05)
        model_pdf = RooExponential("model_pdf"+label+"_"+channel+spectrum,"model_pdf"+label+"_"+channel+spectrum,rrv_x,rrv_c_Exp)       
    
    if model == "Gaus":
        rrv_mean1_gaus   = RooRealVar("rrv_mean1_gaus" +label+"_"+channel+spectrum ,"rrv_mean1_gaus" +label+"_"+channel+spectrum,gaus_means,gaus_means*.8,gaus_means*1.2)
        rrv_sigma1_gaus  = RooRealVar("rrv_sigma1_gaus"+label+"_"+channel+spectrum ,"rrv_sigma1_gaus"+label+"_"+channel+spectrum,gaussigmas,gaussigmas*.5,gaussigmas*1.5)  
        model_pdf        = RooGaussian("gaus"+label+"_"+channel+spectrum,"gaus"+label+"_"+channel+spectrum, rrv_x,rrv_mean1_gaus,rrv_sigma1_gaus)
    
    if model == "ErfExpGaus_sp":
        
        rrv_c_ErfExp     = RooRealVar("rrv_c_ErfExp"+label+"_"    +channel+spectrum,"rrv_c_ErfExp"    +label+"_"+channel+spectrum,-0.04,-1.,1.)
        rrv_width_ErfExp = RooRealVar("rrv_width_ErfExp"+label+"_"+channel+spectrum,"rrv_width_ErfExp"+label+"_"+channel+spectrum,30.,0.,400.)
        rrv_offset_ErfExp = RooRealVar("rrv_offset_ErfExp"+label+"_"+channel+spectrum,"rrv_offset_ErfExp"+label+"_"+channel+spectrum, 60.,50.,100.)
        rrv_mean1_gaus   = RooRealVar("rrv_mean1_gaus"+label+"_"  +channel+spectrum,"rrv_mean1_gaus"  +label+"_"+channel+spectrum,gaus_means,gaus_means*.8,gaus_means*1.2)
        rrv_sigma1_gaus  = RooRealVar("rrv_sigma1_gaus"+label+"_" +channel+spectrum,"rrv_sigma1_gaus" +label+"_"+channel+spectrum,gaussigmas,gaussigmas*.5,gaussigmas*1.5)
        erfExp           = ROOT.RooErfExpPdf("erfExp"+label+"_"+channel+spectrum,"erfExp"+label+"_"+channel+spectrum,rrv_x,rrv_c_ErfExp,rrv_offset_ErfExp,rrv_width_ErfExp)
        gaus             = RooGaussian ("gaus"+label+"_"+channel+spectrum  ,"gaus"+label+"_"+channel+spectrum  , rrv_x,rrv_mean1_gaus,rrv_sigma1_gaus)
        rrv_high   = RooRealVar("rrv_high"+label+"_"+channel+spectrum,"rrv_high"+label+"_"+channel+spectrum,0.3,0.0,0.99)
        model_pdf  = RooAddPdf("model_pdf"+label+"_"+channel+spectrum,"model_pdf"+label+"_"+channel+spectrum,erfExp,gaus,rrv_high)

    if model.find("DoubleCB")!=-1 and model.find("Gauss")==-1  :
        if model.find("fitMC")!=-1:
           
            rrv_mean1_gaus   = RooRealVar("rrv_mean1_gaus"+label+"_"+channel+spectrum,"rrv_mean1_gaus"+label+"_"+channel+spectrum,8.1955e+01,gaus_means*.8,gaus_means*1.2)
            rrv_sigma1_gaus  = RooRealVar("rrv_sigma1_gaus"+label+"_"+channel+spectrum,"rrv_sigma1_gaus"+label+"_"+channel+spectrum,6.8141e+00,gaussigmas*.95,gaussigmas*1.8)
            rrv_alpha1        = RooRealVar("rrv_alpha1"+label+"_"  +channel+spectrum, "rrv_alpha1"+label+"_"  +channel+spectrum, 9.2102e-01, -10., 10.)
            rrv_sign1         = RooRealVar("rrv_sign1" +label+"_"  +channel+spectrum, "rrv_sign1" +label+"_"  +channel+spectrum, 3.6660e+01, 0., 46.)
            rrv_alpha2        = RooRealVar("rrv_alpha2"+label+"_"  +channel+spectrum, "rrv_alpha2"+label+"_"  +channel+spectrum, 1.0758e+00, -10., 10.)
            rrv_sign2         = RooRealVar("rrv_sign2" +label+"_"  +channel+spectrum, "rrv_sign2" +label+"_"  +channel+spectrum, 1.4910e+01, 0., 46.)
            if wsname.find("ddt")!=-1:
                rrv_mean1_gaus   = RooRealVar("rrv_mean1_gaus"+label+"_"+channel+spectrum,"rrv_mean1_gaus"+label+"_"+channel+spectrum,8.1955e+01,73,86)
                rrv_sigma1_gaus  = RooRealVar("rrv_sigma1_gaus"+label+"_"+channel+spectrum,"rrv_sigma1_gaus"+label+"_"+channel+spectrum,9.,5.,12.)
                rrv_alpha1        = RooRealVar("rrv_alpha1"+label+"_"  +channel+spectrum, "rrv_alpha1"+label+"_"  +channel+spectrum, 1.4, 0., 6.)
                rrv_sign1         = RooRealVar("rrv_sign1" +label+"_"  +channel+spectrum, "rrv_sign1" +label+"_"  +channel+spectrum, 36.1, -100., 146.)
                rrv_alpha2        = RooRealVar("rrv_alpha2"+label+"_"  +channel+spectrum, "rrv_alpha2"+label+"_"  +channel+spectrum, 1.9, 0., 10.)
                rrv_sign2         = RooRealVar("rrv_sign2" +label+"_"  +channel+spectrum, "rrv_sign2" +label+"_"  +channel+spectrum, 5, 0., 40.)
                if label.find('fail')!=-1:
                    rrv_mean1_gaus   = RooRealVar("rrv_mean1_gaus"+label+"_"+channel+spectrum,"rrv_mean1_gaus"+label+"_"+channel+spectrum,83.,78,86)
                    rrv_sigma1_gaus  = RooRealVar("rrv_sigma1_gaus"+label+"_"+channel+spectrum,"rrv_sigma1_gaus"+label+"_"+channel+spectrum,9.,5.,13.)
                    rrv_alpha1        = RooRealVar("rrv_alpha1"+label+"_"  +channel+spectrum, "rrv_alpha1"+label+"_"  +channel+spectrum, 0.93, -10., 10.)
                    rrv_sign1         = RooRealVar("rrv_sign1" +label+"_"  +channel+spectrum, "rrv_sign1" +label+"_"  +channel+spectrum, 47, 30., 90.)
                    rrv_alpha2        = RooRealVar("rrv_alpha2"+label+"_"  +channel+spectrum, "rrv_alpha2"+label+"_"  +channel+spectrum, 0.57, 0., 40.)
                    rrv_sign2         = RooRealVar("rrv_sign2" +label+"_"  +channel+spectrum, "rrv_sign2" +label+"_"  +channel+spectrum, 7., -10, 16.)

        
        else:
            with open("ttfit_parameters%s.txt"%wsname) as f: 
                for line in f:
                   name  = line.split(" ")[0]
                   value = float(line.split(" ")[1])
                   err   = abs(float(line.split(" ")[2]))
                   if err == 0: err = abs(value*.10)
                   err = abs(0.20*value)
                   if label.find('fail')!=-1:            
                       if line.find('rrv_mean1_gaus_TTbar_realW_failtau2tau1cut_em_mj'  )!=-1: rrv_mean1_gaus   = RooRealVar("rrv_mean1_gaus"  + label +"_"+channel+spectrum ,"rrv_mean1_gaus"  + label +"_"+channel+spectrum ,value , value-2, value+2 )
                       if line.find('rrv_sigma1_gaus_TTbar_realW_failtau2tau1cut_em_mj' )!=-1: rrv_sigma1_gaus  = RooRealVar("rrv_sigma1_gaus" + label +"_"+channel+spectrum ,"rrv_sigma1_gaus" + label +"_"+channel+spectrum ,value , value-1, value+1 )
                       if line.find('rrv_alpha1_TTbar_realW_failtau2tau1cut_em_mj'      )!=-1: rrv_alpha1       = RooRealVar("rrv_alpha1"      + label +"_"+channel+spectrum ,"rrv_alpha1"      + label +"_"+channel+spectrum ,value , value*0.8, value*1.2 )
                       if line.find('rrv_sign1_TTbar_realW_failtau2tau1cut_em_mj'       )!=-1: rrv_sign1        = RooRealVar("rrv_sign1"       + label +"_"+channel+spectrum ,"rrv_sign1"       + label +"_"+channel+spectrum ,value , value*0.8, value*1.2 )
                       if line.find('rrv_alpha2_TTbar_realW_failtau2tau1cut_em_mj'      )!=-1: rrv_alpha2       = RooRealVar("rrv_alpha2"      + label +"_"+channel+spectrum ,"rrv_alpha2"      + label +"_"+channel+spectrum ,value , value*0.8, value*1.2 )
                       if line.find('rrv_sign2_TTbar_realW_failtau2tau1cut_em_mj'       )!=-1: rrv_sign2        = RooRealVar("rrv_sign2"       + label +"_"+channel+spectrum ,"rrv_sign2"       + label +"_"+channel+spectrum ,value , value*0.8, value*1.2 )
                       if wsname.find("ddt")!=-1:
                           if line.find('rrv_mean1_gaus_TTbar_realW_failtau2tau1cut_em_mj'  )!=-1: rrv_mean1_gaus   = RooRealVar("rrv_mean1_gaus"  + label +"_"+channel+spectrum ,"rrv_mean1_gaus"  + label +"_"+channel+spectrum ,value, value-4, value+4)
                           if line.find('rrv_sigma1_gaus_TTbar_realW_failtau2tau1cut_em_mj' )!=-1: rrv_sigma1_gaus  = RooRealVar("rrv_sigma1_gaus" + label +"_"+channel+spectrum ,"rrv_sigma1_gaus" + label +"_"+channel+spectrum ,value, value-2, value+2)
                           if line.find('rrv_alpha1_TTbar_realW_failtau2tau1cut_em_mj'      )!=-1: rrv_alpha1       = RooRealVar("rrv_alpha1"      + label +"_"+channel+spectrum ,"rrv_alpha1"      + label +"_"+channel+spectrum ,value, value-err, value+err )
                           if line.find('rrv_sign1_TTbar_realW_failtau2tau1cut_em_mj'       )!=-1: rrv_sign1        = RooRealVar("rrv_sign1"       + label +"_"+channel+spectrum ,"rrv_sign1"       + label +"_"+channel+spectrum ,value, value-err, value+err )
                           if line.find('rrv_alpha2_TTbar_realW_failtau2tau1cut_em_mj'      )!=-1: rrv_alpha2       = RooRealVar("rrv_alpha2"      + label +"_"+channel+spectrum ,"rrv_alpha2"      + label +"_"+channel+spectrum ,value, value-err, value+err )
                           if line.find('rrv_sign2_TTbar_realW_failtau2tau1cut_em_mj'       )!=-1: rrv_sign2        = RooRealVar("rrv_sign2"       + label +"_"+channel+spectrum ,"rrv_sign2"       + label +"_"+channel+spectrum ,value, value-err, value+err )
                       
                   else:
                       if line.find('rrv_mean1_gaus_TTbar_realW_em_mj'  )!=-1: rrv_mean1_gaus   = RooRealVar("rrv_mean1_gaus"  + label +"_"+channel+spectrum ,"rrv_mean1_gaus"  + label +"_"+channel+spectrum ,value , value-2, value+2 )
                       if line.find('rrv_sigma1_gaus_TTbar_realW_em_mj' )!=-1: rrv_sigma1_gaus  = RooRealVar("rrv_sigma1_gaus" + label +"_"+channel+spectrum ,"rrv_sigma1_gaus" + label +"_"+channel+spectrum ,value , value-1, value+1 )
                       if line.find('rrv_alpha1_TTbar_realW_em_mj'      )!=-1: rrv_alpha1       = RooRealVar("rrv_alpha1"      + label +"_"+channel+spectrum ,"rrv_alpha1"      + label +"_"+channel+spectrum ,value , value*0.8, value*1.2 )
                       if line.find('rrv_sign1_TTbar_realW_em_mj'       )!=-1: rrv_sign1        = RooRealVar("rrv_sign1"       + label +"_"+channel+spectrum ,"rrv_sign1"       + label +"_"+channel+spectrum ,value , value*0.8, value*1.2 )
                       if line.find('rrv_alpha2_TTbar_realW_em_mj'      )!=-1: rrv_alpha2       = RooRealVar("rrv_alpha2"      + label +"_"+channel+spectrum ,"rrv_alpha2"      + label +"_"+channel+spectrum ,value , value*0.8, value*1.2 )
                       if line.find('rrv_sign2_TTbar_realW_em_mj'       )!=-1: rrv_sign2        = RooRealVar("rrv_sign2"       + label +"_"+channel+spectrum ,"rrv_sign2"       + label +"_"+channel+spectrum ,value , value*0.8, value*1.2 )
                       if wsname.find("ddt")!=-1:
                           if line.find('rrv_mean1_gaus_TTbar_realW_em_mj'  )!=-1: rrv_mean1_gaus   = RooRealVar("rrv_mean1_gaus"  + label +"_"+channel+spectrum ,"rrv_mean1_gaus"  + label +"_"+channel+spectrum ,value , value-10 , value+10)
                           if line.find('rrv_sigma1_gaus_TTbar_realW_em_mj' )!=-1: rrv_sigma1_gaus  = RooRealVar("rrv_sigma1_gaus" + label +"_"+channel+spectrum ,"rrv_sigma1_gaus" + label +"_"+channel+spectrum ,value , value-15 , value+15 )
                           if line.find('rrv_alpha1_TTbar_realW_em_mj'      )!=-1: rrv_alpha1       = RooRealVar("rrv_alpha1"      + label +"_"+channel+spectrum ,"rrv_alpha1"      + label +"_"+channel+spectrum ,value , value*0.5, value*1.5 )
                           if line.find('rrv_sign1_TTbar_realW_em_mj'       )!=-1: rrv_sign1        = RooRealVar("rrv_sign1"       + label +"_"+channel+spectrum ,"rrv_sign1"       + label +"_"+channel+spectrum ,value , value*0.5, value*1.5 )
                           if line.find('rrv_alpha2_TTbar_realW_em_mj'      )!=-1: rrv_alpha2       = RooRealVar("rrv_alpha2"      + label +"_"+channel+spectrum ,"rrv_alpha2"      + label +"_"+channel+spectrum ,value , value*0.5, value*1.5 )
                           if line.find('rrv_sign2_TTbar_realW_em_mj'       )!=-1: rrv_sign2        = RooRealVar("rrv_sign2"       + label +"_"+channel+spectrum ,"rrv_sign2"       + label +"_"+channel+spectrum ,value , value*0.5, value*1.5 )
                           if wsname.find("2017")!=-1:
                              if line.find('rrv_mean1_gaus_TTbar_realW_em_mj'  )!=-1: rrv_mean1_gaus   = RooRealVar("rrv_mean1_gaus"  + label +"_"+channel+spectrum ,"rrv_mean1_gaus"  + label +"_"+channel+spectrum ,value , value-3 , value+3)
                              if line.find('rrv_sigma1_gaus_TTbar_realW_em_mj' )!=-1: rrv_sigma1_gaus  = RooRealVar("rrv_sigma1_gaus" + label +"_"+channel+spectrum ,"rrv_sigma1_gaus" + label +"_"+channel+spectrum ,value , value-2 , value+2 )
                              # if line.find('rrv_alpha1_TTbar_realW_em_mj'      )!=-1: rrv_alpha1       = RooRealVar("rrv_alpha1"      + label +"_"+channel+spectrum ,"rrv_alpha1"      + label +"_"+channel+spectrum ,value , value*0.5, value*1.5 )
                              # if line.find('rrv_sign1_TTbar_realW_em_mj'       )!=-1: rrv_sign1        = RooRealVar("rrv_sign1"       + label +"_"+channel+spectrum ,"rrv_sign1"       + label +"_"+channel+spectrum ,value , value*0.5, value*1.5 )
                              # if line.find('rrv_alpha2_TTbar_realW_em_mj'      )!=-1: rrv_alpha2       = RooRealVar("rrv_alpha2"      + label +"_"+channel+spectrum ,"rrv_alpha2"      + label +"_"+channel+spectrum ,value , value*0.5, value*1.5 )
                              # if line.find('rrv_sign2_TTbar_realW_em_mj'       )!=-1: rrv_sign2        = RooRealVar("rrv_sign2"       + label +"_"+channel+spectrum ,"rrv_sign2"       + label +"_"+channel+spectrum ,value , value*0.5, value*1.5 )

        model_pdf       = ROOT.RooDoubleCrystalBall("model_pdf"+label+"_"+channel+spectrum,"model_pdf"+label+"_"+channel+spectrum, rrv_x, rrv_mean1_gaus, rrv_sigma1_gaus, rrv_alpha1, rrv_sign1, rrv_alpha2, rrv_sign2)

    if model.find("SingleSideCB")!=-1  :
        if model.find("MC")!=-1:
            rrv_mean1_gaus   = RooRealVar("rrv_mean1_gaus"+label+"_"+channel+spectrum,"rrv_mean1_gaus"+label+"_"+channel+spectrum,8.1955e+01,50,100)
            rrv_sigma1_gaus  = RooRealVar("rrv_sigma1_gaus"+label+"_"+channel+spectrum,"rrv_sigma1_gaus"+label+"_"+channel+spectrum,6.8141e+00,0,15)
            rrv_alpha1        = RooRealVar("rrv_alpha1"+label+"_"  +channel+spectrum, "rrv_alpha1"+label+"_"  +channel+spectrum, -9.2102e-01, -20., 20.)#For a tail on the right side, use a negative alpha.
            rrv_sign1         = RooRealVar("rrv_sign1" +label+"_"  +channel+spectrum, "rrv_sign1" +label+"_"  +channel+spectrum, 3.6660e+01, -40., 46.)
        
        else:
            with open("ttfit_parameters%s.txt"%wsname) as f: 
                for line in f:
                   name  = line.split(" ")[0]
                   value = float(line.split(" ")[1])
                   err   = abs(float(line.split(" ")[2]))
                   # err = abs(0.20*value)
                   if label.find('fail')!=-1:            
                       if line.find('rrv_mean1_gaus_TTbar_realW_failtau2tau1cut_em_mj'  )!=-1: rrv_mean1_gaus   = RooRealVar("rrv_mean1_gaus"  + label +"_"+channel+spectrum ,"rrv_mean1_gaus"  + label +"_"+channel+spectrum ,value , value-5, value+5 )
                       if line.find('rrv_sigma1_gaus_TTbar_realW_failtau2tau1cut_em_mj' )!=-1: rrv_sigma1_gaus  = RooRealVar("rrv_sigma1_gaus" + label +"_"+channel+spectrum ,"rrv_sigma1_gaus" + label +"_"+channel+spectrum ,value , value-3, value+3 )
                       if line.find('rrv_alpha1_TTbar_realW_failtau2tau1cut_em_mj'      )!=-1: rrv_alpha1       = RooRealVar("rrv_alpha1"      + label +"_"+channel+spectrum ,"rrv_alpha1"      + label +"_"+channel+spectrum ,value , value*0.9, value*1.1 )
                       if line.find('rrv_sign1_TTbar_realW_failtau2tau1cut_em_mj'       )!=-1: rrv_sign1        = RooRealVar("rrv_sign1"       + label +"_"+channel+spectrum ,"rrv_sign1"       + label +"_"+channel+spectrum ,value , value*0.9, value*1.1 )
                   else:
                       if line.find('rrv_mean1_gaus_TTbar_realW_em_mj'  )!=-1: rrv_mean1_gaus   = RooRealVar("rrv_mean1_gaus"  + label +"_"+channel+spectrum ,"rrv_mean1_gaus"  + label +"_"+channel+spectrum ,value , value-5, value+5 )
                       if line.find('rrv_sigma1_gaus_TTbar_realW_em_mj' )!=-1: rrv_sigma1_gaus  = RooRealVar("rrv_sigma1_gaus" + label +"_"+channel+spectrum ,"rrv_sigma1_gaus" + label +"_"+channel+spectrum ,value , value-3, value+3 )
                       if line.find('rrv_alpha1_TTbar_realW_em_mj'      )!=-1: rrv_alpha1       = RooRealVar("rrv_alpha1"      + label +"_"+channel+spectrum ,"rrv_alpha1"      + label +"_"+channel+spectrum ,value , value*0.9, value*1.1 )
                       if line.find('rrv_sign1_TTbar_realW_em_mj'       )!=-1: rrv_sign1        = RooRealVar("rrv_sign1"       + label +"_"+channel+spectrum ,"rrv_sign1"       + label +"_"+channel+spectrum ,value , value*0.9, value*1.1 )

        model_pdf       = RooCBShape("model_pdf"+label+"_"+channel+spectrum,"model_pdf"+label+"_"+channel+spectrum, rrv_x, rrv_mean1_gaus, rrv_sigma1_gaus, rrv_alpha1, rrv_sign1)
        
    if model.find("DoubleCBGauss")!=-1:
        if model.find("MC")!=-1:
            rrv_mean1_gaus   = RooRealVar("rrv_mean1_gaus"+label+"_"+channel+spectrum,"rrv_mean1_gaus"+label+"_"+channel+spectrum,8.1955e+01,gaus_means*.8,gaus_means*1.2)
            rrv_sigma1_gaus  = RooRealVar("rrv_sigma1_gaus"+label+"_"+channel+spectrum,"rrv_sigma1_gaus"+label+"_"+channel+spectrum,6.8141e+00,gaussigmas*.95,gaussigmas*1.8)
            rrv_alpha1        = RooRealVar("rrv_alpha1"+label+"_"  +channel+spectrum, "rrv_alpha1"+label+"_"  +channel+spectrum, 9.2102e-01, -10., 10.)
            rrv_sign1         = RooRealVar("rrv_sign1" +label+"_"  +channel+spectrum, "rrv_sign1" +label+"_"  +channel+spectrum, 3.6660e+01, -10., 46.)
            rrv_alpha2        = RooRealVar("rrv_alpha2"+label+"_"  +channel+spectrum, "rrv_alpha2"+label+"_"  +channel+spectrum, 1.0758e+00, -10., 10.)
            rrv_sign2         = RooRealVar("rrv_sign2" +label+"_"  +channel+spectrum, "rrv_sign2" +label+"_"  +channel+spectrum, 1.4910e+01, -100., 46.)
            
            rrv_mean2_gaus  = RooRealVar("rrv_mean2_gaus"+label+"_"+channel+spectrum ,"rrv_mean2_gaus"+label+"_"+channel+spectrum   ,170,150,180)
            rrv_sigma2_gaus = RooRealVar("rrv_sigma2_gaus"+label+"_"+channel+spectrum ,"rrv_sigma2_gaus"+label+"_"+channel+spectrum ,13,10.,20. ) 
            rrv_frac = RooRealVar("rrv_frac"+label+"_"+channel+spectrum ,"rrv_frac"+label+"_"+channel+spectrum ,0.95,0.0,1.)
            
        
        else:
            with open("ttfit_parameters%s.txt"%wsname) as f: 
                for line in f:
                   name  = line.split(" ")[0]
                   value = float(line.split(" ")[1])
                   err   = abs(float(line.split(" ")[2]))
                   err = abs(0.50*value)
                   if line.find('rrv_frac_TTbar_realW_failtau2tau1cut_em_mj'        )!=-1: rrv_frac         = RooRealVar("rrv_frac"         + label +"_"+channel+spectrum ,"rrv_frac"         + label +"_"+channel+spectrum  ,value   , value-err, value+err )
                   if line.find('rrv_mean2_gaus_TTbar_realW_failtau2tau1cut_em_mj'  )!=-1: rrv_mean2_gaus   = RooRealVar("rrv_mean2_gaus"  + label +"_"+channel+spectrum ,"rrv_mean2_gaus"  + label +"_"+channel+spectrum ,value , value*0.8, value*1.2 )
                   if line.find('rrv_sigma2_gaus_TTbar_realW_failtau2tau1cut_em_mj' )!=-1: rrv_sigma2_gaus  = RooRealVar("rrv_sigma2_gaus" + label +"_"+channel+spectrum ,"rrv_sigma2_gaus" + label +"_"+channel+spectrum ,value , value*0.8, value*1.2 )
                   if label.find('fail')!=-1:            
                       if line.find('rrv_mean1_gaus_TTbar_realW_failtau2tau1cut_em_mj'  )!=-1: rrv_mean1_gaus   = RooRealVar("rrv_mean1_gaus"  + label +"_"+channel+spectrum ,"rrv_mean1_gaus"  + label +"_"+channel+spectrum ,value , value*0.8, value*1.2 )
                       if line.find('rrv_sigma1_gaus_TTbar_realW_failtau2tau1cut_em_mj' )!=-1: rrv_sigma1_gaus  = RooRealVar("rrv_sigma1_gaus" + label +"_"+channel+spectrum ,"rrv_sigma1_gaus" + label +"_"+channel+spectrum ,value , value*0.8, value*1.2 )
                       if line.find('rrv_alpha1_TTbar_realW_failtau2tau1cut_em_mj'      )!=-1: rrv_alpha1       = RooRealVar("rrv_alpha1"      + label +"_"+channel+spectrum ,"rrv_alpha1"      + label +"_"+channel+spectrum ,value , value-err, value+err )
                       if line.find('rrv_sign1_TTbar_realW_failtau2tau1cut_em_mj'       )!=-1: rrv_sign1        = RooRealVar("rrv_sign1"       + label +"_"+channel+spectrum ,"rrv_sign1"       + label +"_"+channel+spectrum ,value , value-err, value+err )
                       if line.find('rrv_alpha2_TTbar_realW_failtau2tau1cut_em_mj'      )!=-1: rrv_alpha2       = RooRealVar("rrv_alpha2"      + label +"_"+channel+spectrum ,"rrv_alpha2"      + label +"_"+channel+spectrum ,value , value-err, value+err )
                       if line.find('rrv_sign2_TTbar_realW_failtau2tau1cut_em_mj'       )!=-1: rrv_sign2        = RooRealVar("rrv_sign2"       + label +"_"+channel+spectrum ,"rrv_sign2"       + label +"_"+channel+spectrum ,value , value-err, value+err )
                   else:
                       if line.find('rrv_mean1_gaus_TTbar_realW_em_mj'  )!=-1: rrv_mean1_gaus   = RooRealVar("rrv_mean1_gaus"  + label +"_"+channel+spectrum ,"rrv_mean1_gaus"  + label +"_"+channel+spectrum ,value , value*0.9, value*1.1 )
                       if line.find('rrv_sigma1_gaus_TTbar_realW_em_mj' )!=-1: rrv_sigma1_gaus  = RooRealVar("rrv_sigma1_gaus" + label +"_"+channel+spectrum ,"rrv_sigma1_gaus" + label +"_"+channel+spectrum ,value , value*0.5, value*1.5 )
                       if line.find('rrv_alpha1_TTbar_realW_em_mj'      )!=-1: rrv_alpha1       = RooRealVar("rrv_alpha1"      + label +"_"+channel+spectrum ,"rrv_alpha1"      + label +"_"+channel+spectrum ,value , value-err, value+err )
                       if line.find('rrv_sign1_TTbar_realW_em_mj'       )!=-1: rrv_sign1        = RooRealVar("rrv_sign1"       + label +"_"+channel+spectrum ,"rrv_sign1"       + label +"_"+channel+spectrum ,value , value-err, value+err )
                       if line.find('rrv_alpha2_TTbar_realW_em_mj'      )!=-1: rrv_alpha2       = RooRealVar("rrv_alpha2"      + label +"_"+channel+spectrum ,"rrv_alpha2"      + label +"_"+channel+spectrum ,value , value-err, value+err )
                       if line.find('rrv_sign2_TTbar_realW_em_mj'       )!=-1: rrv_sign2        = RooRealVar("rrv_sign2"       + label +"_"+channel+spectrum ,"rrv_sign2"       + label +"_"+channel+spectrum ,value , value-err, value+err )
        
            
                      
        if model.find("fail")==-1:
            rrv_frac = RooRealVar("rrv_frac"+label+"_"+channel+spectrum ,"rrv_frac"+label+"_"+channel+spectrum ,1.)
            rrv_frac.setConstant(ROOT.kTRUE)
            rrv_mean2_gaus.setConstant(ROOT.kTRUE)
            rrv_sigma2_gaus.setConstant(ROOT.kTRUE)
            
        gaus2 = RooGaussian("gaus2"+label+"_"+channel+spectrum ,"gaus2"+label+"_"+channel+spectrum ,rrv_x,rrv_mean2_gaus,rrv_sigma2_gaus)     
        dcb       = ROOT.RooDoubleCrystalBall("dcb"+label+"_"+channel+spectrum,"dcb"+label+"_"+channel+spectrum, rrv_x, rrv_mean1_gaus, rrv_sigma1_gaus, rrv_alpha1, rrv_sign1, rrv_alpha2, rrv_sign2)
        model_pdf       = RooAddPdf("model_pdf"+label+"_"+channel+spectrum,"model_pdf"+label+"_"+channel+spectrum,RooArgList(dcb,gaus2),RooArgList(rrv_frac),1)              
       
    if model.find("ErfExpGauss_ttbar")!=-1:
        frac_tmp = 1.; #Use only Gaussian component to model real W-jets, ErfExp set to zero by setting fraction to 1!
        
        if model.find("MC")!=-1:
            mean1_tmp = 8.2653e+01;
            sigma1_tmp = 7.5932e+00;
            rangeMean = 8. ;
            rangeWidth = 5. ;
            c0_tmp     = -2.7180e-02 ; c0_tmp_err     = 6.83e-03;
            offset_tmp =  8.6888e+01 ; offset_tmp_err = 19.35e+00;
            width_tmp  =  3.6383e+01 ; width_tmp_err  = 1.34e+00;
                
            rrv_mean1_gaus  = RooRealVar("rrv_mean1_gaus"+label+"_"+channel+spectrum ,"rrv_mean1_gaus"+label+"_"+channel+spectrum   ,1.6504e+02,150,180)
            rrv_sigma1_gaus = RooRealVar("rrv_sigma1_gaus"+label+"_"+channel+spectrum ,"rrv_sigma1_gaus"+label+"_"+channel+spectrum ,1.8855e+01,10.,50. )
            gaus1 = RooGaussian("gaus1"+label+"_"+channel+spectrum ,"gaus1"+label+"_"+channel+spectrum ,rrv_x,rrv_mean1_gaus,rrv_sigma1_gaus)     
            rrv_offset_ErfExp = RooRealVar("rrv_offset_ErfExp"+label+"_"+channel+spectrum ,"rrv_offset_ErfExp"+label+"_"+channel+spectrum ,8.3954e+01,0,300)
            rrv_width_ErfExp  = RooRealVar("rrv_width_ErfExp" +label+"_"+channel+spectrum ,"rrv_width_ErfExp" +label+"_"+channel+spectrum ,4.1175e+01, 0., 170.)
            rrv_c_ErfExp      = RooRealVar("rrv_c_ErfExp"     +label+"_"+channel+spectrum ,"rrv_c_ErfExp"     +label+"_"+channel+spectrum ,-3.2231e-02,-10, +10 )
            rrv_frac = RooRealVar("rrv_frac"+label+"_"+channel+spectrum ,"rrv_frac"+label+"_"+channel+spectrum ,0.70,0.,1.)
            if model.find("fail")!=-1: rrv_frac = RooRealVar("rrv_frac"+label+"_"+channel+spectrum ,"rrv_frac"+label+"_"+channel+spectrum ,0.30,0.,1.)

        else:
            with open("ttfit_parameters%s.txt"%wsname) as f: 
                for line in f:
                   name  = line.split(" ")[0]
                   value = float(line.split(" ")[1])
                   err   = abs(float(line.split(" ")[2]))
                   err = abs(0.20*value)
                   if label.find('fail')!=-1:            
                       if line.find('rrv_c_ErfExp_TTbar_fakeW_failtau2tau1cut_em_mj'     )!=-1: rrv_c_ErfExp      = RooRealVar('rrv_c_ErfExp'     + label+"_"+channel+spectrum ,'rrv_c_ErfExp'     + label+"_"+channel+spectrum  ,value     , value-err, value+err )
                       if line.find('rrv_offset_ErfExp_TTbar_fakeW_failtau2tau1cut_em_mj')!=-1: rrv_offset_ErfExp = RooRealVar('rrv_offset_ErfExp'+ label+"_"+channel+spectrum ,'rrv_offset_ErfExp'+ label+"_"+channel+spectrum  ,value     , value-err, value+err )
                       if line.find('rrv_width_ErfExp_TTbar_fakeW_failtau2tau1cut_em_mj' )!=-1: rrv_width_ErfExp  = RooRealVar('rrv_width_ErfExp' + label+"_"+channel+spectrum ,'rrv_width_ErfExp' + label+"_"+channel+spectrum  ,value     , value-err, value+err )                      
                       if line.find('rrv_mean1_gaus_TTbar_fakeW_failtau2tau1cut_em_mj'   )!=-1: rrv_mean1_gaus    = RooRealVar("rrv_mean1_gaus"   + label +"_"+channel+spectrum ,"rrv_mean1_gaus"   + label +"_"+channel+spectrum  ,value   , value*0.5, value*1.5 )
                       if line.find('rrv_sigma1_gaus_TTbar_fakeW_failtau2tau1cut_em_mj'  )!=-1: rrv_sigma1_gaus   = RooRealVar("rrv_sigma1_gaus"  + label +"_"+channel+spectrum ,"rrv_sigma1_gaus"  + label +"_"+channel+spectrum  ,value   , value*0.5, value*1.5 )
                       if line.find('rrv_frac_TTbar_fakeW_failtau2tau1cut_em_mj'         )!=-1: rrv_frac          = RooRealVar("rrv_frac"         + label +"_"+channel+spectrum ,"rrv_frac"         + label +"_"+channel+spectrum  ,value   , value*0.5, value*1.5 )
                   else:
                       if line.find('rrv_c_ErfExp_TTbar_fakeW_em_mj'     )!=-1: rrv_c_ErfExp      = RooRealVar('rrv_c_ErfExp'     + label +"_"+channel+spectrum ,'rrv_c_ErfExp'     + label +"_"+channel+spectrum  ,value   , value-err, value+err )
                       if line.find('rrv_offset_ErfExp_TTbar_fakeW_em_mj')!=-1: rrv_offset_ErfExp = RooRealVar('rrv_offset_ErfExp'+ label +"_"+channel+spectrum ,'rrv_offset_ErfExp'+ label +"_"+channel+spectrum  ,value   , value-err, value+err )
                       if line.find('rrv_width_ErfExp_TTbar_fakeW_em_mj' )!=-1: rrv_width_ErfExp  = RooRealVar('rrv_width_ErfExp' + label +"_"+channel+spectrum ,'rrv_width_ErfExp' + label +"_"+channel+spectrum  ,value   , value-err, value+err )
                       if line.find('rrv_mean1_gaus_TTbar_fakeW_em_mj'   )!=-1: rrv_mean1_gaus    = RooRealVar("rrv_mean1_gaus"   + label +"_"+channel+spectrum ,"rrv_mean1_gaus"   + label +"_"+channel+spectrum  ,value   , value*0.8, value*1.2 )
                       if line.find('rrv_sigma1_gaus_TTbar_fakeW_em_mj'  )!=-1: rrv_sigma1_gaus   = RooRealVar("rrv_sigma1_gaus"  + label +"_"+channel+spectrum ,"rrv_sigma1_gaus"  + label +"_"+channel+spectrum  ,value   , value*0.8, value*1.2 )
                       if line.find('rrv_frac_TTbar_fakeW_em_mj'         )!=-1: rrv_frac          = RooRealVar("rrv_frac"         + label +"_"+channel+spectrum ,"rrv_frac"         + label +"_"+channel+spectrum  ,value   , value*0.8, value*1.2 )
                       
            gaus1 = RooGaussian("gaus1"+label+"_"+channel+spectrum ,"gaus1"+label+"_"+channel+spectrum ,rrv_x,rrv_mean1_gaus,rrv_sigma1_gaus)
            rrv_frac.setConstant(ROOT.kTRUE)
        
        erfExp    = ROOT.RooErfExpPdf("erfExp"+label+"_"+channel+spectrum,"model_pdf"+label+"_"+channel+spectrum,rrv_x,rrv_c_ErfExp,rrv_offset_ErfExp,rrv_width_ErfExp)
        model_pdf = RooAddPdf("model_pdf"+label+"_"+channel+spectrum,"model_pdf"+label+"_"+channel+spectrum,RooArgList(gaus1,erfExp),RooArgList(rrv_frac),1)
    
    
    if model.find("DoubleSidedCB")!=-1:
        isfinal = ("_TotalMC" in label or "_data" in label)
        freelabel, corrlabel = label, label.replace("_failtau2tau1cut", "")
        rrv_mean1_gaus   = RooRealVar("rrv_mean1_gaus"+freelabel+"_"+channel+spectrum,"rrv_mean1_gaus"+label+"_"+channel+spectrum, 89., 80., 100.) # 89., 75., 100.
        rrv_sigma1_gaus  = RooRealVar("rrv_sigma1_gaus"+freelabel+"_"+channel+spectrum,"rrv_sigma1_gaus"+label+"_"+channel+spectrum, 8., 5., 20.) # 9., 1., 20.
        rrv_alpha1  = RooRealVar("rrv_alpha1"+corrlabel+"_"  +channel+spectrum, "rrv_alpha1"+label+"_"  +channel+spectrum, 0.5, 0.1, 10.) # 0.5, 0.1, 10.
        rrv_alpha2  = RooRealVar("rrv_alpha2"+corrlabel+"_"  +channel+spectrum, "rrv_alpha2"+label+"_"  +channel+spectrum, 1.0, 0.1, 10.) # 1., 0.1, 10.
        rrv_sign1   = RooRealVar("rrv_sign1" +corrlabel+"_"  +channel+spectrum, "rrv_sign1" +label+"_"  +channel+spectrum, 0.2, 0.01, 5.) # 2, 1, 5.
        rrv_sign2   = RooRealVar("rrv_sign2" +corrlabel+"_"  +channel+spectrum, "rrv_sign2" +label+"_"  +channel+spectrum, 0.2, 0.01, 10.) # 2, 1, 10.
        
        # small sign values mean high tails. 1 is left, 2 is right.
        if isfinal:
            if not 'ddt' in wsname:
                rrv_mean1_gaus.SetName("rrv_mean1_gaus"+corrlabel+"_"+channel+spectrum)
                rrv_sigma1_gaus.SetName("rrv_sigma1_gaus"+corrlabel+"_"+channel+spectrum)
                if 'topShower' in wsname:
                    rrv_alpha1.setMax(1.); rrv_alpha2.setMax(1.);
                    rrv_mean1_gaus.SetName("rrv_mean1_gaus"+freelabel+"_"+channel+spectrum)
                    rrv_sigma1_gaus.SetName("rrv_sigma1_gaus"+freelabel+"_"+channel+spectrum)
            if 'ddt_0p50_0p80' in wsname:
                rrv_mean1_gaus.SetName("rrv_mean1_gaus"+corrlabel+"_"+channel+spectrum)
                rrv_sigma1_gaus.SetName("rrv_sigma1_gaus"+corrlabel+"_"+channel+spectrum)
            if 'ddt_0p43_0p79' in wsname and 'topGen' in wsname:
                rrv_alpha1.setVal(5.); rrv_alpha2.setVal(5.); rrv_alpha1.setMin(4.5); rrv_alpha2.setMin(4.5); rrv_sign1.setMin(0.2); rrv_sign2.setMin(0.2);
            if 'ddt_0p50_0p80' in wsname and 'topShower' in wsname:
                rrv_alpha1.setVal(5.); rrv_alpha2.setVal(5.); rrv_alpha1.setMin(4.5); rrv_alpha2.setMin(4.5);
        model_pdf   = ROOT.RooDoubleCrystalBall("model_pdf"+label+"_"+channel+spectrum,"model_pdf"+label+"_"+channel+spectrum, rrv_x, rrv_mean1_gaus, rrv_sigma1_gaus, rrv_alpha1, rrv_sign1, rrv_alpha2, rrv_sign2)
        if 'bias' in wsname:
            model_pdf   = RooGaussian("model_pdf"+label+"_"+channel+spectrum,"model_pdf"+label+"_"+channel+spectrum, rrv_x, rrv_mean1_gaus, rrv_sigma1_gaus)
    
    if model == "ErfExp_ttbar" or model == "ErfExp_ttbar_ddt" or model == "ErfExp_ttbar_failtau2tau1cut" or model == "ErfExp_ttbar_failtau2tau1cut_fitMC" or model == "ErfExp_ttbar_failtau2tau1cut_ddt" or model == "ErfExp_ttbar_fitMC":
        rrv_offset_ErfExp = RooRealVar("rrv_offset_ErfExp"+label+"_"+channel+spectrum ,"rrv_offset_ErfExp"+label+"_"+channel+spectrum, 90, 10, 200) # 90, 10, 200
        rrv_width_ErfExp  = RooRealVar("rrv_width_ErfExp" +label+"_"+channel+spectrum ,"rrv_width_ErfExp" +label+"_"+channel+spectrum, 40, 25, 300) # 40, 25, 100
        rrv_c_ErfExp  = RooRealVar("rrv_c_ErfExp"  +label+"_"+channel+spectrum ,"rrv_c_ErfExp"     +label+"_"+channel+spectrum, -0.03, -1., 0.) # -0.04, -1, 0.
        model_pdf     = ROOT.RooErfExpPdf("model_pdf"+label+"_"+channel+spectrum,"model_pdf"+label+"_"+channel+spectrum ,rrv_x,rrv_c_ErfExp,rrv_offset_ErfExp,rrv_width_ErfExp)
    
    
    getattr(workspace,'import')(model_pdf)
    return workspace.pdf("model_pdf"+label+"_"+channel+spectrum)
            
def MakeExtendedModel(workspace, label, model,spectrum, channel, wtagger_label,constraint,peak="W",wsname=""):
    
    print "Making extended model with name: " , "model"+label+"_"+channel+spectrum
    rrv_number = RooRealVar("rrv_number"+label+"_"+channel+spectrum,"rrv_number"+label+"_"+channel+spectrum,500.,0.,1e5)
    model_pdf = MakeGeneralPdf(workspace,label,model,spectrum,wtagger_label,channel,constraint,peak,wsname)

    model_extended = RooExtendPdf("model"+label+"_"+channel+spectrum,"model"+label+"_"+channel+spectrum,model_pdf, rrv_number)
    
    getattr(workspace,'import')(rrv_number)
    getattr(workspace,'import')(model_extended)
    return workspace.pdf("model"+label+"_"+channel+spectrum)

def fixParameters(workspace,label,channel,fix=1):
    name = "rdataset%s_%s_mj"%(label,channel)
    rdataset_General_mj = workspace.data(name)
    model_General = workspace.pdf("model"+label+"_"+channel+"_mj")
    rdataset_General_mj.Print()
    model_General.Print()
    
    parameters_General = model_General.getParameters(rdataset_General_mj)
    par=parameters_General.createIterator()
    par.Reset()
    param=par.Next()
    while (param):
        param.setConstant(ROOT.kTRUE)
        param=par.Next()
    print "Failing for " ,"model"+label+"_"+channel+"_mj"
    return workspace.pdf("model"+label+"_"+channel+"_mj")
            
def makeTTbarModel(workspace,label, model,channel, wtagger, constraint=[],peak="W", wsname="", spectrum="_mj"):

     with open("ttfit_parameters%s.txt"%wsname) as f: 
        for line in f:
           name  = line.split(" ")[0]
           value = float(line.split(" ")[1])
           if line.find('rrv_number_TTbar_realW_em_mj'                 )!=-1: realW_pass = value
           if line.find('rrv_number_TTbar_fakeW_em_mj'                 )!=-1: fakeW_pass = value
           if line.find('rrv_number_TTbar_realW_failtau2tau1cut_em_mj' )!=-1: realW_fail = value
           if line.find('rrv_number_TTbar_fakeW_failtau2tau1cut_em_mj' )!=-1: fakeW_fail = value
     effS      = realW_pass/(realW_pass+fakeW_pass+realW_fail+fakeW_fail)
     effS      = realW_pass/(realW_pass+realW_fail)
     print ""; print "Real MC signal efficiency = " ,effS; print ""; 
     info =""
     if label.find("_ttbar_data")!=-1 and label.find("fail")==-1:
         rrv_number_total = RooRealVar("rrv_number_total_ttbar_data"+info+"_"+channel,"rrv_number_total_ttbar_data"+info+"_"+channel,500,0.,1e10)
         #eff_ttbar = RooRealVar("eff_ttbar_data"+info+"_"+channel,"eff_ttbar_data"+info+"_"+channel,effS,effS*0.7,effS*1.3)
         eff_ttbar = RooRealVar("eff_ttbar_data"+info+"_"+channel,"eff_ttbar_data"+info+"_"+channel,effS,0.,1.)
         if wsname.find("2017")!=-1: eff_ttbar = RooRealVar("eff_ttbar_data"+info+"_"+channel,"eff_ttbar_data"+info+"_"+channel,effS,effS*0.8,effS*1.2)
         
         rrv_number = RooFormulaVar("rrv_number"+label+"_"+channel+spectrum, "@0*@1", RooArgList(eff_ttbar,rrv_number_total))

     elif label.find("_ttbar_data")!=-1 and label.find("fail")!=-1:
         rrv_number_total = workspace.var("rrv_number_total_ttbar_data"+info+"_"+channel)
         eff_ttbar        = workspace.var("eff_ttbar_data"+info+"_"+channel)
         rrv_number       = RooFormulaVar("rrv_number"+label+"_"+channel+spectrum, "(1-@0)*@1", RooArgList(eff_ttbar,rrv_number_total))
         
     elif label.find("_ttbar_TotalMC")!=-1 and label.find("fail")==-1:
         rrv_number_total = RooRealVar("rrv_number_total_ttbar_TotalMC"+info+"_"+channel,"rrv_number_total_ttbar_TotalMC"+info+"_"+channel,500,0.,1e10)
         #eff_ttbar = RooRealVar("eff_ttbar_TotalMC"+info+"_"+channel,"eff_ttbar_TotalMC"+info+"_"+channel,effS,effS*0.7,effS*1.3)
         eff_ttbar = RooRealVar("eff_ttbar_TotalMC"+info+"_"+channel,"eff_ttbar_TotalMC"+info+"_"+channel,effS,0.,1.)
         if wsname.find("2017")!=-1: eff_ttbar = RooRealVar("eff_ttbar_TotalMC"+info+"_"+channel,"eff_ttbar_TotalMC"+info+"_"+channel,effS,effS*0.8,effS*1.2)
         
         rrv_number = RooFormulaVar("rrv_number"+label+"_"+channel+spectrum, "@0*@1", RooArgList(eff_ttbar,rrv_number_total))
         
     elif label.find("_ttbar_TotalMC")!=-1 and label.find("fail")!=-1:
         rrv_number_total = workspace.var("rrv_number_total_ttbar_TotalMC"+info+"_"+channel)
         eff_ttbar = workspace.var("eff_ttbar_TotalMC"+info+"_"+channel)
         rrv_number = RooFormulaVar("rrv_number"+label+"_"+channel+spectrum, "(1-@0)*@1", RooArgList(eff_ttbar,rrv_number_total)) 
         
     model_pdf = MakeGeneralPdf(workspace,label,model,spectrum,wtagger,channel,constraint,peak,wsname)

     model = RooExtendPdf("model"+label+"_"+channel+spectrum,"model"+label+"_"+channel+spectrum, model_pdf, rrv_number)
     getattr(workspace,"import")(model)
     return workspace.pdf("model"+label+"_"+channel+spectrum)
    
