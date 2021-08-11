#ifndef makeBTaggingEfficiencyMap
#define makeBTaggingEfficiencyMap


#include "TCanvas.h"
#include "TDirectory.h"
#include "TF1.h"
#include "TFile.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TH1D.h"
#include "TH2D.h"
#include "THStack.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TMath.h"
#include "Math/ProbFunc.h"
#include "TProfile.h"
#include "TPaveStats.h"
#include "TPaveText.h"
#include "TROOT.h"
#include "TString.h"
#include "TStyle.h"
#include "TEfficiency.h"
#include "TArrow.h"
#include "TLine.h"
#include "TPad.h"
#include "TVirtualFitter.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <map>
#include <array>

void makeBTaggingEfficiency(TString InputFileName ) ;



struct Person{
    
    TString name;
    TString surname;
    int age;

};


struct Tprime_M1000{

       TString Sample_Name = "Tprime_M1000" ;


       const int eta_Bins = 3;
       double eta_Edges[eta_Bins + 1] = [0.0, 0.6, 1.2, 2.4] ;

       const int pT_b_Bins = 11;
       double pT_b_Edges[pT_b_Bins + 1] = [0., 40., 60., 80., 100., 150., 200., 300., 400., 550., 700., 1000.] ;       

       TH2D* h2_BTaggingEff_Denom_b = new TH2D("h2_BTaggingEff_Denom_b", "h2_BTaggingEff_Denom_b Distribution", pT_b_Bins, pT_b_Edges, eta_Bins, eta_Edges);
       h2_BTaggingEff_Denom_b    ->GetXaxis()->SetTitle("P_{T}(jet)(GeV)");  
       h2_BTaggingEff_Denom_b    ->GetYaxis()->SetTitle("#eta(jet)"); 

       TH2D* h2_BTaggingEff_Num_b = new TH2D("h2_BTaggingEff_Num_b", "h2_BTaggingEff_Num_b Distribution", pT_b_Bins, pT_b_Edges, eta_Bins, eta_Edges);
       h2_BTaggingEff_Num_b       ->GetXaxis()->SetTitle("P_{T}(jet)(GeV)");  
       h2_BTaggingEff_Num_b       ->GetYaxis()->SetTitle("#eta(jet)"); 

       TH2D* h2_BTaggingEff_beff = new TH2D("h2_BTaggingEff_beff", "h2_BTaggingEff_beff Distribution", pT_b_Bins, pT_b_Edges, eta_Bins, eta_Edges);
       h2_BTaggingEff_beff       ->GetXaxis()->SetTitle("P_{T}(jet)(GeV)");  
       h2_BTaggingEff_beff       ->GetYaxis()->SetTitle("#eta(jet)");        




}     

struct Tprime_M1500{

       TString Sample_Name = "Tprime_M1500" ;


       const int eta_Bins = 3;
       double eta_Edges[eta_Bins + 1] = [0.0, 0.6, 1.2, 2.4] ;

       const int pT_b_Bins = 13;
       double pT_b_Edges[pT_b_Bins + 1] = [0., 40., 60., 80., 100., 150., 200., 300., 400., 500., 600., 700., 800., 1000.] ;       

       TH2D* h2_BTaggingEff_Denom_b = new TH2D("h2_BTaggingEff_Denom_b", "h2_BTaggingEff_Denom_b Distribution", pT_b_Bins, pT_b_Edges, eta_Bins, eta_Edges);
       h2_BTaggingEff_Denom_b    ->GetXaxis()->SetTitle("P_{T}(jet)(GeV)");  
       h2_BTaggingEff_Denom_b    ->GetYaxis()->SetTitle("#eta(jet)"); 

       TH2D* h2_BTaggingEff_Num_b = new TH2D("h2_BTaggingEff_Num_b", "h2_BTaggingEff_Num_b Distribution", pT_b_Bins, pT_b_Edges, eta_Bins, eta_Edges);
       h2_BTaggingEff_Num_b       ->GetXaxis()->SetTitle("P_{T}(jet)(GeV)");  
       h2_BTaggingEff_Num_b       ->GetYaxis()->SetTitle("#eta(jet)"); 

       TH2D* h2_BTaggingEff_beff = new TH2D("h2_BTaggingEff_beff", "h2_BTaggingEff_beff Distribution", pT_b_Bins, pT_b_Edges, eta_Bins, eta_Edges);
       h2_BTaggingEff_beff       ->GetXaxis()->SetTitle("P_{T}(jet)(GeV)");  
       h2_BTaggingEff_beff       ->GetYaxis()->SetTitle("#eta(jet)");        

       


} 


struct Tprime_M1800{

       TString Sample_Name = "Tprime_M1800" ;


       const int eta_Bins = 3;
       double eta_Edges[eta_Bins + 1] = [0.0, 0.6, 1.2, 2.4] ;

       const int pT_b_Bins = 13;
       double pT_b_Edges[pT_b_Bins + 1] = [0., 40., 60., 80., 100., 150., 200., 300., 400., 500., 600., 700., 800., 1000.] ;      

       TH2D* h2_BTaggingEff_Denom_b = new TH2D("h2_BTaggingEff_Denom_b", "h2_BTaggingEff_Denom_b Distribution", pT_b_Bins, pT_b_Edges, eta_Bins, eta_Edges);
       h2_BTaggingEff_Denom_b    ->GetXaxis()->SetTitle("P_{T}(jet)(GeV)");  
       h2_BTaggingEff_Denom_b    ->GetYaxis()->SetTitle("#eta(jet)"); 

       TH2D* h2_BTaggingEff_Num_b = new TH2D("h2_BTaggingEff_Num_b", "h2_BTaggingEff_Num_b Distribution", pT_b_Bins, pT_b_Edges, eta_Bins, eta_Edges);
       h2_BTaggingEff_Num_b       ->GetXaxis()->SetTitle("P_{T}(jet)(GeV)");  
       h2_BTaggingEff_Num_b       ->GetYaxis()->SetTitle("#eta(jet)"); 

       TH2D* h2_BTaggingEff_beff = new TH2D("h2_BTaggingEff_beff", "h2_BTaggingEff_beff Distribution", pT_b_Bins, pT_b_Edges, eta_Bins, eta_Edges);
       h2_BTaggingEff_beff       ->GetXaxis()->SetTitle("P_{T}(jet)(GeV)");  
       h2_BTaggingEff_beff       ->GetYaxis()->SetTitle("#eta(jet)");        

       


}  



            // int sz = InputString_outputvec[Dataset].size() ;      

            // std::array<float,3> check ;
            // // float check[] =  { InputString_outputarray[Dataset][0], InputString_outputarray[Dataset][1], InputString_outputarray[Dataset][2] }       ;

            // check = InputString_outputarray[Dataset] ;

            // std::vector<float> vec_check ;            

            // vec_check = InputString_outputvec[Dataset];

            // TH1D* h =  new TH1D( "h", "h", check.size(),check) ;

            // cout <<" \n\n Yo man I did it   Ist =" << check[0] <<" && Last = " << InputString_outputarray[Dataset][2] <<endl;

#endif