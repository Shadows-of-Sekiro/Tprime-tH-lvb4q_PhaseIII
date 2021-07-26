
import ROOT



def printPlot(nameSelection , plotdir, title, CanvasName, XYrange, Ymax, histofAlldata ,histofAllMC, mcStack ):
        theCanvas = ROOT.TCanvas("c" + CanvasName, "c" + CanvasName,1,1,745,701)
        
        
        
        theCanvas.SetHighLightColor(2)
        theCanvas.Range(0,0,1,1)
        theCanvas.SetFillColor(0)
        theCanvas.SetBorderMode(0)
        theCanvas.SetBorderSize(2)
        theCanvas.SetTickx(1)
        theCanvas.SetTicky(1)
        theCanvas.SetLeftMargin(0.14)
        theCanvas.SetRightMargin(0.04)
        theCanvas.SetTopMargin(0.08)
        theCanvas.SetBottomMargin(0.15)
        theCanvas.SetFrameFillStyle(0)
        theCanvas.SetFrameBorderMode(0)
        
        if histofAlldata != None :      
            pad1 = ROOT.TPad("pad" +CanvasName, "pad" + CanvasName,0,0.3333333,1,1)
        else :      
            pad1 = ROOT.TPad("pad" +CanvasName, "pad" + CanvasName,0,0.111,1,1)        

        pad1.Draw()
        pad1.cd()

        
        
        if XYrange != None :
            rangeMin = XYrange[0]
            rangeMax = XYrange[1]
            print("X axis range is {} to {} for {}".format(rangeMin, rangeMax, CanvasName))

        if histofAlldata != None :
            histofAlldata.GetXaxis().SetRangeUser( rangeMin, rangeMax )

            histofAlldata.SetMinimum(0.0001 )
            histofAlldata.GetYaxis().SetTitle("Events")
            

            histofAlldata.GetYaxis().SetTitleSize(0.065)
            histofAlldata.GetYaxis().SetTitleOffset(0.9) ## 0.7)
            histofAlldata.GetYaxis().SetLabelSize(0.04)
            histofAlldata.SetLineColor(1)
            histofAlldata.SetFillColor(1)
            histofAlldata.SetFillStyle(0)
            histofAlldata.SetLineWidth(2)
            
            

            histofAlldata.SetMarkerStyle(20)
            histofAlldata.SetMarkerSize(0.8)
            histofAlldata.SetMarkerColor(1)
            histofAlldata.SetTitle("")
                

            histofAlldata.GetXaxis().SetNdivisions(506)
            histofAlldata.GetXaxis().SetLabelFont(42)
            histofAlldata.GetXaxis().SetLabelSize(0.05)
            histofAlldata.GetXaxis().SetTitleSize(0.0475)
            histofAlldata.GetXaxis().SetTickLength(0.045)
            histofAlldata.GetXaxis().SetTitleOffset(1.15)
            histofAlldata.GetXaxis().SetTitleFont(42)
            histofAlldata.GetXaxis().SetTitle(title)

            
            histofAlldata.GetYaxis().SetNdivisions(506)
            histofAlldata.GetYaxis().SetLabelFont(42)
            histofAlldata.GetYaxis().SetLabelSize(0.06375)
            histofAlldata.GetYaxis().SetTitleSize(0.06225)
            histofAlldata.GetYaxis().SetTitleOffset(0.7)
            histofAlldata.GetYaxis().SetTitleFont(42)
            histofAlldata.GetYaxis().SetTitle("Events")           
            histofAlldata.GetYaxis().SetRangeUser(0.0001,Ymax * histofAllMC.GetMaximum())
            histofAlldata.Draw("e")
            histofAllMC.Draw("E2 same")
            if XYrange != None :
                histofAlldata.GetXaxis().SetRangeUser( rangeMin, rangeMax ) 
        else :

            #histofAllMC.SetLineColor(1)
            #histofAllMC.SetFillColor(ROOT.kGreen+1)
            #histofAllMC.SetFillStyle(0)
            #histofAllMC.SetLineWidth(2)
            #histofAllMC.SetMarkerStyle(20)
            #histofAllMC.SetMarkerSize(0.8)
            #histofAllMC.SetMarkerColor(1)
            histofAllMC.SetTitle("")
                

            histofAllMC.GetXaxis().SetNdivisions(506)
            histofAllMC.GetXaxis().SetLabelFont(42)
            histofAllMC.GetXaxis().SetLabelSize(0.035)
            histofAllMC.GetXaxis().SetTitleSize(0.037)
            histofAllMC.GetXaxis().SetTickLength(0.045)
            histofAllMC.GetXaxis().SetTitleOffset(1.01)
            histofAllMC.GetXaxis().SetTitleFont(42)
            histofAllMC.GetXaxis().SetTitle(title)

            
            histofAllMC.GetYaxis().SetNdivisions(506)
            histofAllMC.GetYaxis().SetLabelFont(42)
            histofAllMC.GetYaxis().SetLabelSize(0.03)
            histofAllMC.GetYaxis().SetTitleSize(0.045)
            histofAllMC.GetYaxis().SetTitleOffset(1.165)
            histofAllMC.GetYaxis().SetTitleFont(42)
            histofAllMC.GetYaxis().SetTitle("Events")

            histofAllMC.GetYaxis().SetRangeUser(0.0001,Ymax* histofAllMC.GetMaximum())    
            #print histofAllMC.GetOption()
            if XYrange != None :
                histofAllMC.GetXaxis().SetRangeUser( rangeMin, rangeMax )               
            
            histofAllMC.Draw('hist')

            #histofAllMC.Draw('e4 same')

        mcStack.Draw("e same")
        
        if CanvasName == 'h_zpt' :
            histofAllMC.GetYaxis().SetRangeUser(0.0001,Ymax* 1.2 *histofAllMC.GetMaximum())
            pad1.cd()
            ROOT.gPad.SetLogy() 
        #if 'rho' in mhistNames[i]:
        #    pad1.cd()
        #    ROOT.gPad.SetLogx() 

        leg = ROOT.TLegend(0.74,0.84,0.84,0.89)#(0.8,0.64,0.89,0.84)
        leg.SetFillColor(0)
        leg.SetBorderSize(0)
        leg.SetTextSize(0.026)     

        leg.SetTextSize(0.036)   

        if histofAlldata != None :    

            histofAlldata.Draw("e same")

            words = ROOT.TLatex(0.14,0.916,"#font[62]{CMS} #font[52]{Preliminary}")
            words.SetNDC()
            words.SetTextFont(42)
            words.SetTextSize(0.0725)
            words.SetLineWidth(2)
            words.Draw()    

            words1 = ROOT.TLatex(0.9,0.916,"%2.2f fb^{-1} (13 TeV)"%(lumi/1000.))
            words1.SetNDC()
            words1.SetTextAlign(31)
            words1.SetTextFont(42)
            words1.SetTextSize(0.0725)
            words1.SetLineWidth(2)
            words1.Draw()

            leg.AddEntry( histofAlldata, 'Data', 'p')

        else : 
            #histofAllMC.Draw("same")

            words = ROOT.TLatex(0.13,0.916,"#font[62]{CMS}")
            words.SetNDC()
            #words.SetTextFont(42)
            words.SetTextSize(0.065)
            words.SetLineWidth(2)
            words.Draw()

            words1 = ROOT.TLatex(0.475,0.86,"#font[52]{ Simulation Preliminary}")
            words1.SetNDC()
            words1.SetTextAlign(31)
            #words1.SetTextFont(42)
            words1.SetTextSize(0.0425)
            words1.SetLineWidth(2)
            words1.Draw()

        '''
        words1b = ROOT.TLatex(0.72,0.816," dPhi(reco&gen),Z) > 2. , dR(gen,reco) < 0.1, dR(l,AK8) > 1.0")
        words1b.SetNDC()
        words1b.SetTextAlign(31)
        words1b.SetTextFont(42)
        words1b.SetTextSize(0.037)
        words1b.SetLineWidth(2)
        words1b.Draw()

        words2b = ROOT.TLatex(0.69,0.716,"AK8 Pt > 125 GeV")
        words2b.SetNDC()
        words2b.SetTextAlign(31)
        words2b.SetTextFont(42)
        words2b.SetTextSize(0.037)
        words2b.SetLineWidth(2)
        words2b.Draw()

        words3b = ROOT.TLatex(0.69,0.616,"Tight Leps 0(1)(0+1) Pt > 40(30)(120) GeV,  Zmass 80-102 GeV")
        words3b.SetNDC()
        words3b.SetTextAlign(31)
        words3b.SetTextFont(42)
        words3b.SetTextSize(0.037)
        words3b.SetLineWidth(2)
        words3b.Draw()
        '''

                
        leg.AddEntry( histofAllMC, 'TT(2017)', 'f')


        leg.Draw('same')
        '''
        histofAllMC.SetLineWidth(2)
        histofAllMC.SetFillColor(ROOT.kGreen+1)
        histofAllMC.SetFillStyle(2)
        histofAllMC.SetMarkerStyle(22)
        histofAllMC.SetMarkerSize(0.8)
        histofAllMC.SetMarkerColor(1)
        '''
        #histofAllMC.Draw('e2 same')
        
        pad1.Modified()
        theCanvas.cd()

        
        if histofAlldata != None :      
            print("Making pad2")

            pad2 = ROOT.TPad("pad2" + CanvasName , "pad2" + CanvasName,0,0, 1, 0.33333)
            pad2.Draw()
            pad2.cd()
            
            pad2.SetFillColor(0)
            pad2.SetBorderMode(0)
            pad2.SetBorderSize(2)
            pad2.SetTickx(1)
            pad2.SetTicky(1)
            pad2.SetLeftMargin(0.14)
            pad2.SetRightMargin(0.04)
            pad2.SetTopMargin(0)
            pad2.SetBottomMargin(0.45)
            pad2.SetFrameFillStyle(0)
            pad2.SetFrameBorderMode(0)
            pad2.SetFrameFillStyle(0)
            pad2.SetFrameBorderMode(0)
            
            hRatio = histofAlldata.Clone('hRatio')
            hData = histofAlldata.Clone('hData')
            hMC = histofAllMC.Clone('hMC')
                    
            hRatioBinWidth = histofAlldata.GetBinWidth(0)
            hRationBins =  histofAlldata.GetSize()
            #hRatio.SetStats(0)

            hmcBinWidth = histofAllMC.GetBinWidth(0)
            hmcnBins =  histofAllMC.GetSize()
            hRatio.Divide(histofAllMC)            
            #hRatio.Sumw2()
            #hRatio.SetStats(0)
            
            hRatio.GetYaxis().SetRangeUser(0.5001,1.5)   #(-1.01, 2.99)#
            hRatio.GetXaxis().SetRangeUser( rangeMin, rangeMax  )
            hRatio.GetXaxis().SetTitle( CanvasName   )

            
            hRatio.SetFillColor(1)
            hRatio.SetFillStyle(0)
            hRatio.SetLineWidth(2)
            hRatio.SetLineColor(1)
            hRatio.SetMarkerStyle(20)
            hRatio.SetMarkerSize(0.8)
            hRatio.GetXaxis().SetNdivisions(506)
            hRatio.GetXaxis().SetLabelFont(42)
            hRatio.GetXaxis().SetLabelOffset(0.015)
            hRatio.GetXaxis().SetLabelSize(0.1275)
            hRatio.GetXaxis().SetTitleSize(0.12)
            hRatio.GetXaxis().SetTickLength(0.09)
            hRatio.GetXaxis().SetTitleOffset(1.35)
            hRatio.GetXaxis().SetTitleFont(42)
          
            hRatio.GetYaxis().SetTitle("#frac{Data}{MC}")
            #hRatio.GetYaxis().CenterTitle(true)
            hRatio.GetYaxis().SetNdivisions(304)
            hRatio.GetYaxis().SetLabelFont(42)
            hRatio.GetYaxis().SetLabelSize(0.1275)
            hRatio.GetYaxis().SetTitleSize(0.121)
            hRatio.GetYaxis().SetTickLength(0.045)
            hRatio.GetYaxis().SetTitleOffset(0.415)
            hRatio.GetYaxis().SetTitleFont(42)

            hRatio.Draw("same") #lepe0")

            lineup = ROOT.TF1("lineup", "1.25", -7000, 7000)
            lineup.SetLineColor(1)
            lineup.SetLineStyle(2)
            lineup.SetLineWidth(2)
            lineup.Draw("same")
            hRatio.Draw("e same x0")

            line = ROOT.TF1("line", "1", -7000, 7000)
            line.SetLineColor(1)
            line.SetLineStyle(1)
            line.SetLineWidth(3)
            line.Draw("same")
            hRatio.Draw("e same x0")

            lined = ROOT.TF1("lined", "0.75", -7000, 7000)
            lined.SetLineColor(1)
            lined.SetLineStyle(2)
            lined.SetLineWidth(2)
            lined.Draw("same")
            hRatio.Draw("e same x0")
            ROOT.gPad.RedrawAxis()
             
            pad2.Modified()

        theCanvas.Modified()
        
        theCanvas.Print("./"+plotdir+"/"+nameSelection+"_plotstack_"+ CanvasName + ".pdf", "pdf")

        return theCanvas
