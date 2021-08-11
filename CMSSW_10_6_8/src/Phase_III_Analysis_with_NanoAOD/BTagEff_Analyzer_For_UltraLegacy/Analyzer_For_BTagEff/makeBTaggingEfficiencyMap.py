#!/usr/bin/env python

import os, sys
from ROOT import gROOT, TFile, TH2D
from array import array

gROOT.SetBatch(1)

#----------------------------------------------------------------------------------
# Configurable parameters

datasets = [
  # Signal
  # [
  #   'Tprime_M1500_UL17_v2', # dataset name
  #   {'b':    [[0., 40., 60., 80., 100., 150., 200., 300., 400., 500., 600., 700., 800., 1000.],[0., 0.6, 1.2, 2.4]],  # jet Pt and |eta| bins for b jets
  #    'c':    [[0., 40., 60., 80., 100., 150., 200., 1000.],[0., 0.6, 1.2, 2.4]],  # jet Pt and |eta| bins for c jets
  #    'udsg': [[0., 40., 60., 80., 100., 150., 200., 1000.],[0., 0.6, 1.2, 2.4]]},  # jet Pt and |eta| bins for udsg jets
  #   'ak4_deepCSV'
  # ], 

  # # Background

  [
    'TT_to_Hadronic_UL17_v2', # dataset name
    {'b':    [[0., 40., 60., 80., 100., 150., 200., 300., 400., 500., 600., 700., 800., 1000.],[0., 0.6, 1.2, 2.4]],  # jet Pt and |eta| bins for b jets
     'c':    [[0., 40., 60., 80., 100., 150., 200., 1000.],[0., 0.6, 1.2, 2.4]],  # jet Pt and |eta| bins for c jets
     'udsg': [[0., 40., 60., 80., 100., 150., 200., 1000.],[0., 0.6, 1.2, 2.4]]},  # jet Pt and |eta| bins for udsg jets
    'ak4_deepCSV'
  ],   

  [
    'TT_to_SemiLeptonic_UL17_v2', # dataset name
    {'b':    [[0., 40., 60., 80., 100., 150., 200., 300., 400., 500., 600., 700., 800., 1000.],[0., 0.6, 1.2, 2.4]],  # jet Pt and |eta| bins for b jets
     'c':    [[0., 40., 60., 80., 100., 150., 200., 1000.],[0., 0.6, 1.2, 2.4]],  # jet Pt and |eta| bins for c jets
     'udsg': [[0., 40., 60., 80., 100., 150., 200., 1000.],[0., 0.6, 1.2, 2.4]]},  # jet Pt and |eta| bins for udsg jets
    'ak4_deepCSV'
  ], 

  [
    'TT_to_2L2Nu_UL17_v2', # dataset name
    {'b':    [[0., 40., 60., 80., 100., 150., 200., 300., 400., 500., 600., 700., 800., 1000.],[0., 0.6, 1.2, 2.4]],  # jet Pt and |eta| bins for b jets
     'c':    [[0., 40., 60., 80., 100., 150., 200., 1000.],[0., 0.6, 1.2, 2.4]],  # jet Pt and |eta| bins for c jets
     'udsg': [[0., 40., 60., 80., 100., 150., 200., 1000.],[0., 0.6, 1.2, 2.4]]},  # jet Pt and |eta| bins for udsg jets
    'ak4_deepCSV'
  ], 

  [
    'ST_s-channel_UL17_v2', # dataset name
    {'b':    [[0., 40., 60., 80., 100., 150., 200., 300., 400., 500., 600., 700., 800., 1000.],[0., 0.6, 1.2, 2.4]],  # jet Pt and |eta| bins for b jets
     'c':    [[0., 40., 60., 80., 100., 150., 200., 1000.],[0., 0.6, 1.2, 2.4]],  # jet Pt and |eta| bins for c jets
     'udsg': [[0., 40., 60., 80., 100., 150., 200., 1000.],[0., 0.6, 1.2, 2.4]]},  # jet Pt and |eta| bins for udsg jets
    'ak4_deepCSV'
  ], 

  [
    'ST_t-channel_antitop_UL17_v2', # dataset name
    {'b':    [[0., 40., 60., 80., 100., 150., 200., 300., 400., 500., 600., 700., 800., 1000.],[0., 0.6, 1.2, 2.4]],  # jet Pt and |eta| bins for b jets
     'c':    [[0., 40., 60., 80., 100., 150., 200., 1000.],[0., 0.6, 1.2, 2.4]],  # jet Pt and |eta| bins for c jets
     'udsg': [[0., 40., 60., 80., 100., 150., 200., 1000.],[0., 0.6, 1.2, 2.4]]},  # jet Pt and |eta| bins for udsg jets
    'ak4_deepCSV'
  ], 

  [
    'ST_t-channel_top_UL17_v2', # dataset name
    {'b':    [[0., 40., 60., 80., 100., 150., 200., 300., 400., 500., 600., 700., 800., 1000.],[0., 0.6, 1.2, 2.4]],  # jet Pt and |eta| bins for b jets
     'c':    [[0., 40., 60., 80., 100., 150., 200., 1000.],[0., 0.6, 1.2, 2.4]],  # jet Pt and |eta| bins for c jets
     'udsg': [[0., 40., 60., 80., 100., 150., 200., 1000.],[0., 0.6, 1.2, 2.4]]},  # jet Pt and |eta| bins for udsg jets
    'ak4_deepCSV'
  ],  

  [
    'ST_tW_top_UL17_v2', # dataset name
    {'b':    [[0., 40., 60., 80., 100., 150., 200., 300., 400., 500., 600., 700., 800., 1000.],[0., 0.6, 1.2, 2.4]],  # jet Pt and |eta| bins for b jets
     'c':    [[0., 40., 60., 80., 100., 150., 200., 1000.],[0., 0.6, 1.2, 2.4]],  # jet Pt and |eta| bins for c jets
     'udsg': [[0., 40., 60., 80., 100., 150., 200., 1000.],[0., 0.6, 1.2, 2.4]]},  # jet Pt and |eta| bins for udsg jets
    'ak4_deepCSV'
  ],       

  [
    'ST_tW_antitop_UL17_v2', # dataset name
    {'b':    [[0., 40., 60., 80., 100., 150., 200., 300., 400., 500., 600., 700., 800., 1000.],[0., 0.6, 1.2, 2.4]],  # jet Pt and |eta| bins for b jets
     'c':    [[0., 40., 60., 80., 100., 150., 200., 1000.],[0., 0.6, 1.2, 2.4]],  # jet Pt and |eta| bins for c jets
     'udsg': [[0., 40., 60., 80., 100., 150., 200., 1000.],[0., 0.6, 1.2, 2.4]]},  # jet Pt and |eta| bins for udsg jets
    'ak4_deepCSV'
  ],  


  [
    'QCD_Pt-80_MuEnr_UL17_v2',
    {'b':    [[0., 40., 60., 80., 100.,  1000.],[0., 0.6, 1.2, 2.4]],
     'c':    [[0., 40., 60., 80., 100.,  1000.],[0., 0.6, 1.2, 2.4]],
     'udsg': [[0., 40., 60., 80., 100.,  1000.],[0., 0.6, 1.2, 2.4]]},
    'ak4_deepCSV'
  ],
  [
    'QCD_Pt-120_MuEnr_UL17_v2',
    {'b':    [[0., 40., 60., 80., 100., 150., 200.,  1000.],[0., 0.6, 1.2, 2.4]],
     'c':    [[0., 40., 60., 80., 100., 150., 200.,  1000.],[0., 0.6, 1.2, 2.4]],
     'udsg': [[0., 40., 60., 80., 100., 150., 200.,  1000.],[0., 0.6, 1.2, 2.4]]},
    'ak4_deepCSV'
  ],
  [
    'QCD_Pt-170_MuEnr_UL17_v2',
    {'b':    [[0., 40., 60., 80., 100., 150., 200., 250., 300., 1000.],[0., 0.6, 1.2, 2.4]],
     'c':    [[0., 40., 60., 80., 100., 150., 200., 250., 300., 1000.],[0., 0.6, 1.2, 2.4]],
     'udsg': [[0., 40., 60., 80., 100., 150., 200., 250., 300., 1000.],[0., 0.6, 1.2, 2.4]]},
    'ak4_deepCSV'
  ],
  [
    'QCD_Pt-300_MuEnr_UL17_v2',
    {'b':    [[0., 40., 60., 80., 100., 150., 200., 250., 300., 350., 400., 450., 550., 1000.],[0., 0.6, 1.2, 2.4]],
     'c':    [[0., 40., 60., 80., 100., 150., 200., 250., 300., 350., 400., 450., 550., 1000.],[0., 0.6, 1.2, 2.4]],
     'udsg': [[0., 40., 60., 80., 100., 150., 200., 250., 300., 350., 400., 450., 550., 1000.],[0., 0.6, 1.2, 2.4]]},
    'ak4_deepCSV'
  ],
  [
    'QCD_Pt-470_MuEnr_UL17_v2',
    {'b':    [[0., 40., 60., 80., 100., 150., 200., 250., 300., 350., 400., 450., 500., 600., 700., 1000.],[0., 0.6, 1.2, 2.4]],
     'c':    [[0., 40., 60., 80., 100., 150., 200., 250., 300., 350., 400., 450., 500., 600., 700., 1000.],[0., 0.6, 1.2, 2.4]],
     'udsg': [[0., 40., 60., 80., 100., 150., 200., 250., 300., 350., 400., 450., 500., 600., 700., 1000.],[0., 0.6, 1.2, 2.4]]},
    'ak4_deepCSV'
  ],
  [
    'QCD_Pt-600_MuEnr_UL17_v2',
    {'b':    [[0., 40., 60., 80., 100., 150., 200., 300., 400., 500., 600., 700., 800., 1000.],[0., 0.6, 1.2, 2.4]],
     'c':    [[0., 40., 60., 80., 100., 150., 200., 300., 400., 500., 600., 700., 800., 1000.],[0., 0.6, 1.2, 2.4]],
     'udsg': [[0., 40., 60., 80., 100., 150., 200., 300., 400., 500., 600., 700., 800., 1000.],[0., 0.6, 1.2, 2.4]]},
    'ak4_deepCSV'
  ],
  [
    'QCD_Pt-800_MuEnr_UL17_v2',
    {'b':    [[0., 40., 60., 80., 100., 150., 200., 300., 400., 500., 600., 700., 800., 950., 1000.],[0., 0.6, 1.2, 2.4]],
     'c':    [[0., 40., 60., 80., 100., 150., 200., 300., 400., 500., 600., 700., 800., 950., 1000.],[0., 0.6, 1.2, 2.4]],
     'udsg': [[0., 40., 60., 80., 100., 150., 200., 300., 400., 500., 600., 700., 800., 950., 1000.],[0., 0.6, 1.2, 2.4]]},
    'ak4_deepCSV'
  ],
  [
    'QCD_Pt-1000_MuEnr_UL17_v2',
    {'b':    [[0., 40., 60., 80., 100., 150., 200., 300., 400., 500., 600., 700., 800., 950., 1000.],[0., 0.6, 1.2, 2.4]],
     'c':    [[0., 40., 60., 80., 100., 150., 200., 300., 400., 500., 600., 700., 800., 950., 1000.],[0., 0.6, 1.2, 2.4]],
     'udsg': [[0., 40., 60., 80., 100., 150., 200., 300., 400., 500., 600., 700., 800., 950., 1000.],[0., 0.6, 1.2, 2.4]]},
    'ak4_deepCSV'
  ],  


  [
    'QCD_Pt-50_EMEnr_UL17_v2',
    {'b':    [[0., 40., 60., 80., 100., 120., 1000.],[0., 0.6, 1.2, 2.4]],
     'c':    [[0., 40., 60., 80., 100., 120., 1000.],[0., 0.6, 1.2, 2.4]],
     'udsg': [[0., 40., 60., 80., 100., 120., 1000.],[0., 0.6, 1.2, 2.4]]},
    'ak4_deepCSV'
  ],
  [
    'QCD_Pt-80_EMEnr_UL17_v2',
    {'b':    [[0., 40., 60., 80., 100.,  1000.],[0., 0.6, 1.2, 2.4]],
     'c':    [[0., 40., 60., 80., 100.,  1000.],[0., 0.6, 1.2, 2.4]],
     'udsg': [[0., 40., 60., 80., 100.,  1000.],[0., 0.6, 1.2, 2.4]]},
    'ak4_deepCSV'
  ],
  [
    'QCD_Pt-120_EMEnr_UL17_v2',
    {'b':    [[0., 40., 60., 80., 100., 150., 200., 1000.],[0., 0.6, 1.2, 2.4]],
     'c':    [[0., 40., 60., 80., 100., 150., 200., 1000.],[0., 0.6, 1.2, 2.4]],
     'udsg': [[0., 40., 60., 80., 100., 150., 200., 1000.],[0., 0.6, 1.2, 2.4]]},
    'ak4_deepCSV'
  ],
  [
    'QCD_Pt-170_EMEnr_UL17_v2',
    {'b':    [[0., 40., 60., 80., 100., 150., 200., 250., 300.,  1000.],[0., 0.6, 1.2, 2.4]],
     'c':    [[0., 40., 60., 80., 100., 150., 200., 250., 300.,  1000.],[0., 0.6, 1.2, 2.4]],
     'udsg': [[0., 40., 60., 80., 100., 150., 200., 250., 300.,  1000.],[0., 0.6, 1.2, 2.4]]},
    'ak4_deepCSV'
  ],
  [
    'QCD_Pt-300_EMEnr_UL17_v2',
    {'b':    [[0., 40., 60., 80., 100., 150., 200., 300., 400., 500., 600.,  1000.],[0., 0.6, 1.2, 2.4]],
     'c':    [[0., 40., 60., 80., 100., 150., 200., 300., 400., 500., 600.,  1000.],[0., 0.6, 1.2, 2.4]],
     'udsg': [[0., 40., 60., 80., 100., 150., 200., 300., 400., 500., 600.,  1000.],[0., 0.6, 1.2, 2.4]]},
    'ak4_deepCSV'
  ],
  [
    'DYJetsToLL_M-50_HT-70To100_UL17_v2',
    {'b':    [[0., 40., 60., 80., 100.,  1000.],[0., 0.6, 1.2, 2.4]],
     'c':    [[0., 40., 60., 80., 100.,  1000.],[0., 0.6, 1.2, 2.4]],
     'udsg': [[0., 40., 60., 80., 100.,  1000.],[0., 0.6, 1.2, 2.4]]},
    'ak4_deepCSV'
  ],
  [
    'DYJetsToLL_M-50_HT-100To200_UL17_v2',
    {'b':    [[0., 40., 60., 80., 100., 150., 200., 1000.],[0., 0.6, 1.2, 2.4]],
     'c':    [[0., 40., 60., 80., 100., 150., 200., 1000.],[0., 0.6, 1.2, 2.4]],
     'udsg': [[0., 40., 60., 80., 100., 150., 200., 1000.],[0., 0.6, 1.2, 2.4]]},
    'ak4_deepCSV'
  ],
  [
    'DYJetsToLL_M-50_HT-200To400_UL17_v2',
    {'b':    [[0., 40., 60., 80., 100., 150., 200., 250., 300., 350., 400.,  1000.],[0., 0.6, 1.2, 2.4]],
     'c':    [[0., 40., 60., 80., 100., 150., 200., 250., 300., 350., 400.,  1000.],[0., 0.6, 1.2, 2.4]],
     'udsg': [[0., 40., 60., 80., 100., 150., 200., 250., 300., 350., 400.,  1000.],[0., 0.6, 1.2, 2.4]]},
    'ak4_deepCSV'
  ],
  [
    'DYJetsToLL_M-50_HT-400To600_UL17_v2',
    {'b':    [[0., 40., 60., 80., 100., 150., 200., 250., 300., 350., 400., 450., 500., 600., 1000.],[0., 0.6, 1.2, 2.4]],
     'c':    [[0., 40., 60., 80., 100., 150., 200., 250., 300., 350., 400., 450., 500., 600., 1000.],[0., 0.6, 1.2, 2.4]],
     'udsg': [[0., 40., 60., 80., 100., 150., 200., 250., 300., 350., 400., 450., 500., 600., 1000.],[0., 0.6, 1.2, 2.4]]},
    'ak4_deepCSV'
  ],
  [
    'DYJetsToLL_M-50_HT-600To800_UL17_v2',
    {'b':    [[0., 40., 60., 80., 100., 150., 200., 300., 400., 500., 600., 700., 800., 1000.],[0., 0.6, 1.2, 2.4]],
     'c':    [[0., 40., 60., 80., 100., 150., 200., 300., 400., 500., 600., 700., 800., 1000.],[0., 0.6, 1.2, 2.4]],
     'udsg': [[0., 40., 60., 80., 100., 150., 200., 300., 400., 500., 600., 700., 800., 1000.],[0., 0.6, 1.2, 2.4]]},
    'ak4_deepCSV'
  ],
  [
    'DYJetsToLL_M-50_HT-800To1200_UL17_v2',
    {'b':    [[0., 40., 60., 80., 100., 150., 200., 300., 400., 500., 600., 700., 800., 950., 1000.],[0., 0.6, 1.2, 2.4]],
     'c':    [[0., 40., 60., 80., 100., 150., 200., 300., 400., 500., 600., 700., 800., 950., 1000.],[0., 0.6, 1.2, 2.4]],
     'udsg': [[0., 40., 60., 80., 100., 150., 200., 300., 400., 500., 600., 700., 800., 950., 1000.],[0., 0.6, 1.2, 2.4]]},
    'ak4_deepCSV'
  ],
  [
    'DYJetsToLL_M-50_HT-1200To2500_UL17_v2',
    {'b':    [[0., 40., 60., 80., 100., 150., 200., 300., 400., 500., 600., 700., 800., 950., 1000.],[0., 0.6, 1.2, 2.4]],
     'c':    [[0., 40., 60., 80., 100., 150., 200., 300., 400., 500., 600., 700., 800., 950., 1000.],[0., 0.6, 1.2, 2.4]],
     'udsg': [[0., 40., 60., 80., 100., 150., 200., 300., 400., 500., 600., 700., 800., 950., 1000.],[0., 0.6, 1.2, 2.4]]},
    'ak4_deepCSV'
  ],  
  [
    'DYJetsToLL_M-50_HT-2500ToInf_UL17_v2',
    {'b':    [[0., 40., 60., 80., 100., 150., 200., 300., 400., 500., 600., 700., 800., 950., 1000.],[0., 0.6, 1.2, 2.4]],
     'c':    [[0., 40., 60., 80., 100., 150., 200., 300., 400., 500., 600., 700., 800., 950., 1000.],[0., 0.6, 1.2, 2.4]],
     'udsg': [[0., 40., 60., 80., 100., 150., 200., 300., 400., 500., 600., 700., 800., 950., 1000.],[0., 0.6, 1.2, 2.4]]},
    'ak4_deepCSV'
  ],   
  # [
  #   'WJets_LNu_HT-70To100_UL17_v2',
  #   {'b':    [[0., 40., 60., 80., 100., 150., 200., 1000.],[0., 0.6, 1.2, 2.4]],
  #    'c':    [[0., 40., 60., 80., 100., 150., 200., 1000.],[0., 0.6, 1.2, 2.4]],
  #    'udsg': [[0., 40., 60., 80., 100., 150., 200., 1000.],[0., 0.6, 1.2, 2.4]]},
  #   'ak4_deepCSV'
  # ],
  [
    'WJets_LNu_HT-100To200_UL17_v2',
    {'b':    [[0., 40., 60., 80., 100., 150., 200., 1000.],[0., 0.6, 1.2, 2.4]],
     'c':    [[0., 40., 60., 80., 100., 150., 200., 1000.],[0., 0.6, 1.2, 2.4]],
     'udsg': [[0., 40., 60., 80., 100., 150., 200., 1000.],[0., 0.6, 1.2, 2.4]]},
    'ak4_deepCSV'
  ],
  [
    'WJets_LNu_HT-200To400_UL17_v2',
    {'b':    [[0., 40., 60., 80., 100., 150., 200., 250., 300., 350., 400., 1000.],[0., 0.6, 1.2, 2.4]],
     'c':    [[0., 40., 60., 80., 100., 150., 200., 250., 300., 350., 400., 1000.],[0., 0.6, 1.2, 2.4]],
     'udsg': [[0., 40., 60., 80., 100., 150., 200., 250., 300., 350., 400., 1000.],[0., 0.6, 1.2, 2.4]]},
    'ak4_deepCSV'
  ],
  [
    'WJets_LNu_HT-400To600_UL17_v2',
    {'b':    [[0., 40., 60., 80., 100., 150., 200., 250., 300., 350., 400., 450., 500., 600.,  1000.],[0., 0.6, 1.2, 2.4]],
     'c':    [[0., 40., 60., 80., 100., 150., 200., 250., 300., 350., 400., 450., 500., 600.,  1000.],[0., 0.6, 1.2, 2.4]],
     'udsg': [[0., 40., 60., 80., 100., 150., 200., 250., 300., 350., 400., 450., 500., 600.,  1000.],[0., 0.6, 1.2, 2.4]]},
    'ak4_deepCSV'
  ],
  [
    'WJets_LNu_HT-600To800_UL17_v2',
    {'b':    [[0., 40., 60., 80., 100., 150., 200., 300., 400., 500., 600., 700., 800., 1000.],[0., 0.6, 1.2, 2.4]],
     'c':    [[0., 40., 60., 80., 100., 150., 200., 300., 400., 500., 600., 700., 800., 1000.],[0., 0.6, 1.2, 2.4]],
     'udsg': [[0., 40., 60., 80., 100., 150., 200., 300., 400., 500., 600., 700., 800., 1000.],[0., 0.6, 1.2, 2.4]]},
    'ak4_deepCSV'
  ],
  [
    'WJets_LNu_HT-800To1200_UL17_v2',
    {'b':    [[0., 40., 60., 80., 100., 150., 200., 300., 400., 500., 600., 700., 800., 950., 1000.],[0., 0.6, 1.2, 2.4]],
     'c':    [[0., 40., 60., 80., 100., 150., 200., 300., 400., 500., 600., 700., 800., 950., 1000.],[0., 0.6, 1.2, 2.4]],
     'udsg': [[0., 40., 60., 80., 100., 150., 200., 300., 400., 500., 600., 700., 800., 950., 1000.],[0., 0.6, 1.2, 2.4]]},
    'ak4_deepCSV'
  ],
  [
    'WJets_LNu_HT-1200To2500_UL17_v2',
    {'b':    [[0., 40., 60., 80., 100., 150., 200., 300., 400., 500., 600., 700., 800., 950., 1000.],[0., 0.6, 1.2, 2.4]],
     'c':    [[0., 40., 60., 80., 100., 150., 200., 300., 400., 500., 600., 700., 800., 950., 1000.],[0., 0.6, 1.2, 2.4]],
     'udsg': [[0., 40., 60., 80., 100., 150., 200., 300., 400., 500., 600., 700., 800., 950., 1000.],[0., 0.6, 1.2, 2.4]]},
    'ak4_deepCSV'
  ],  
  # [
  #   'WJets_LNu_HT-2500ToInf_UL17_v2',
  #   {'b':    [[0., 40., 60., 80., 100., 150., 200., 300., 400., 500., 600., 700., 800., 950., 1000.],[0., 0.6, 1.2, 2.4]],
  #    'c':    [[0., 40., 60., 80., 100., 150., 200., 300., 400., 500., 600., 700., 800., 950., 1000.],[0., 0.6, 1.2, 2.4]],
  #    'udsg': [[0., 40., 60., 80., 100., 150., 200., 300., 400., 500., 600., 700., 800., 950., 1000.],[0., 0.6, 1.2, 2.4]]},
  #   'ak4_deepCSV'
  # ],    
]

pathToInputFiles = '../Input_RootFiles_For_BtagEff/'
inputFileExtension = 'BtagEff_2DPtEta_02-Aug-21'
outputFileSuffix = 'bTaggingEfficiencyMap'
pathForOutputFiles = '../Output_RootFiles_For_BtagEff/'

#----------------------------------------------------------------------------------

def produceEfficiencyMaps(dataset, inputPath, extension, suffix, outputPath):

  inputFilename = os.path.join(inputPath, dataset[0] + '_' + extension +'.root')
  inputFile = TFile(inputFilename, 'READ')

  outputFilename = outputPath  + dataset[0] + '_' + dataset[2] + '_' + suffix + '.root'
  outputFile = TFile(outputFilename, 'RECREATE')

  for partonFlavor in ['b', 'c', 'udsg']:

    denominatorHisto =  'Hist_2D_BtagEff_Denom_' + partonFlavor
    numeratorHisto   =  'Hist_2D_BtagEff_Num_' + partonFlavor

    denominatorIn = inputFile.Get(denominatorHisto)
    numeratorIn = inputFile.Get(numeratorHisto)

    xShift = denominatorIn.GetXaxis().GetBinWidth(1)/2.
    yShift = denominatorIn.GetYaxis().GetBinWidth(1)/2.

    binsX = array('d', dataset[1][partonFlavor][0])
    binsY = array('d', dataset[1][partonFlavor][1])

    denominatorOut = TH2D('denominator_' + partonFlavor, '', (len(binsX)-1), binsX, (len(binsY)-1), binsY)
    numeratorOut   = TH2D('numerator_' + partonFlavor, '', (len(binsX)-1), binsX, (len(binsY)-1), binsY)
    efficiencyOut  = TH2D('efficiency_' + partonFlavor, '', (len(binsX)-1), binsX, (len(binsY)-1), binsY)

    # loop over all bins
    for i in range(1,denominatorOut.GetXaxis().GetNbins()+1):
      for j in range(1,denominatorOut.GetYaxis().GetNbins()+1):

        binXMin = denominatorIn.GetXaxis().FindBin(denominatorOut.GetXaxis().GetBinLowEdge(i)+xShift)
        binXMax = denominatorIn.GetXaxis().FindBin(denominatorOut.GetXaxis().GetBinUpEdge(i)-xShift)
        binYMinPos = denominatorIn.GetYaxis().FindBin(denominatorOut.GetYaxis().GetBinLowEdge(j)+yShift)
        binYMaxPos = denominatorIn.GetYaxis().FindBin(denominatorOut.GetYaxis().GetBinUpEdge(j)-yShift)
        binYMinNeg = denominatorIn.GetYaxis().FindBin(-denominatorOut.GetYaxis().GetBinUpEdge(j)+yShift)
        binYMaxNeg = denominatorIn.GetYaxis().FindBin(-denominatorOut.GetYaxis().GetBinLowEdge(j)-yShift)

        denominator = denominatorIn.Integral(binXMin,binXMax,binYMinPos,binYMaxPos)
        denominator = denominator + denominatorIn.Integral(binXMin,binXMax,binYMinNeg,binYMaxNeg)
        numerator = numeratorIn.Integral(binXMin,binXMax,binYMinPos,binYMaxPos)
        numerator = numerator + numeratorIn.Integral(binXMin,binXMax,binYMinNeg,binYMaxNeg)

        if(i==denominatorOut.GetXaxis().GetNbins()): # also add overflow to the last bin in jet pT
          denominator = denominator + denominatorIn.Integral(binXMax+1,denominatorIn.GetXaxis().GetNbins()+1,binYMinPos,binYMaxPos)
          denominator = denominator + denominatorIn.Integral(binXMax+1,denominatorIn.GetXaxis().GetNbins()+1,binYMinNeg,binYMaxNeg)
          numerator = numerator + numeratorIn.Integral(binXMax+1,numeratorIn.GetXaxis().GetNbins()+1,binYMinPos,binYMaxPos)
          numerator = numerator + numeratorIn.Integral(binXMax+1,numeratorIn.GetXaxis().GetNbins()+1,binYMinNeg,binYMaxNeg)

        denominatorOut.SetBinContent(i,j,denominator)
        numeratorOut.SetBinContent(i,j,numerator)
        if(denominator>0.): efficiencyOut.SetBinContent(i,j,numerator/denominator)

    # check if there are any bins with 0 or 100% efficiency
    for i in range(1,denominatorOut.GetXaxis().GetNbins()+1):
      for j in range(1,denominatorOut.GetYaxis().GetNbins()+1):

        efficiency = efficiencyOut.GetBinContent(i,j)
        if(efficiency==0. or efficiency==1.):
          print 'Warning! Bin(%i,%i) for %s jets has a b-tagging efficiency of %.3f'%(i,j,partonFlavor,efficiency)

    # set efficiencies in overflow bins
    for i in range(1,denominatorOut.GetXaxis().GetNbins()+1):
      efficiencyOut.SetBinContent(i, denominatorOut.GetYaxis().GetNbins()+1, efficiencyOut.GetBinContent(i, denominatorOut.GetYaxis().GetNbins()))

    for j in range(1,denominatorOut.GetYaxis().GetNbins()+2):
      efficiencyOut.SetBinContent(denominatorOut.GetXaxis().GetNbins()+1, j, efficiencyOut.GetBinContent(denominatorOut.GetXaxis().GetNbins(), j))

    outputFile.cd()

    denominatorOut.Write()
    numeratorOut.Write()
    efficiencyOut.Write()

  outputFile.Close()

  print '-------------------------------------------------------------------------------------------'
  print 'b-tagging efficiency map for'
  print dataset[0]
  print 'successfully created and stored in %s'%outputFilename
  print ''


def main():

  for dataset in datasets:
    produceEfficiencyMaps(dataset, pathToInputFiles, inputFileExtension, outputFileSuffix, pathForOutputFiles)

if __name__ == "__main__":
  main()
