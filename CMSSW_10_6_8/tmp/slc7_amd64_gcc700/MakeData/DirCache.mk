ALL_SUBSYSTEMS+=PhysicsTools
subdirs_src_PhysicsTools = src_PhysicsTools_NanoAODTools
ALL_PACKAGES += PhysicsTools/NanoAODTools
subdirs_src_PhysicsTools_NanoAODTools := src_PhysicsTools_NanoAODTools_python src_PhysicsTools_NanoAODTools_scripts src_PhysicsTools_NanoAODTools_src
ifeq ($(strip $(PyPhysicsToolsNanoAODTools)),)
PyPhysicsToolsNanoAODTools := self/src/PhysicsTools/NanoAODTools/python
src_PhysicsTools_NanoAODTools_python_parent := 
ALL_PYTHON_DIRS += $(patsubst src/%,%,src/PhysicsTools/NanoAODTools/python)
PyPhysicsToolsNanoAODTools_files := $(patsubst src/PhysicsTools/NanoAODTools/python/%,%,$(wildcard $(foreach dir,src/PhysicsTools/NanoAODTools/python ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
PyPhysicsToolsNanoAODTools_LOC_USE := self  
PyPhysicsToolsNanoAODTools_PACKAGE := self/src/PhysicsTools/NanoAODTools/python
ALL_PRODS += PyPhysicsToolsNanoAODTools
PyPhysicsToolsNanoAODTools_INIT_FUNC        += $$(eval $$(call PythonProduct,PyPhysicsToolsNanoAODTools,src/PhysicsTools/NanoAODTools/python,src_PhysicsTools_NanoAODTools_python,1,1,$(SCRAMSTORENAME_PYTHON),$(SCRAMSTORENAME_LIB),,))
else
$(eval $(call MultipleWarningMsg,PyPhysicsToolsNanoAODTools,src/PhysicsTools/NanoAODTools/python))
endif
ALL_COMMONRULES += src_PhysicsTools_NanoAODTools_python
src_PhysicsTools_NanoAODTools_python_INIT_FUNC += $$(eval $$(call CommonProductRules,src_PhysicsTools_NanoAODTools_python,src/PhysicsTools/NanoAODTools/python,PYTHON))
src_PhysicsTools_NanoAODTools_scripts_files := $(filter-out \#% %\#,$(notdir $(wildcard $(foreach dir,$(LOCALTOP)/src/PhysicsTools/NanoAODTools/scripts,$(dir)/*))))
$(eval $(call Src2StoreCopy,src_PhysicsTools_NanoAODTools_scripts,src/PhysicsTools/NanoAODTools/scripts,$(SCRAMSTORENAME_BIN),*))
ALL_SUBSYSTEMS+=WTopScalefactorProducer
subdirs_src_WTopScalefactorProducer = src_WTopScalefactorProducer_Fitter src_WTopScalefactorProducer_Skimmer
ALL_PACKAGES += WTopScalefactorProducer/Fitter
subdirs_src_WTopScalefactorProducer_Fitter := src_WTopScalefactorProducer_Fitter_python
ifeq ($(strip $(PyWTopScalefactorProducerFitter)),)
PyWTopScalefactorProducerFitter := self/src/WTopScalefactorProducer/Fitter/python
src_WTopScalefactorProducer_Fitter_python_parent := 
ALL_PYTHON_DIRS += $(patsubst src/%,%,src/WTopScalefactorProducer/Fitter/python)
PyWTopScalefactorProducerFitter_files := $(patsubst src/WTopScalefactorProducer/Fitter/python/%,%,$(wildcard $(foreach dir,src/WTopScalefactorProducer/Fitter/python ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
PyWTopScalefactorProducerFitter_LOC_USE := self  
PyWTopScalefactorProducerFitter_PACKAGE := self/src/WTopScalefactorProducer/Fitter/python
ALL_PRODS += PyWTopScalefactorProducerFitter
PyWTopScalefactorProducerFitter_INIT_FUNC        += $$(eval $$(call PythonProduct,PyWTopScalefactorProducerFitter,src/WTopScalefactorProducer/Fitter/python,src_WTopScalefactorProducer_Fitter_python,1,1,$(SCRAMSTORENAME_PYTHON),$(SCRAMSTORENAME_LIB),,))
else
$(eval $(call MultipleWarningMsg,PyWTopScalefactorProducerFitter,src/WTopScalefactorProducer/Fitter/python))
endif
ALL_COMMONRULES += src_WTopScalefactorProducer_Fitter_python
src_WTopScalefactorProducer_Fitter_python_INIT_FUNC += $$(eval $$(call CommonProductRules,src_WTopScalefactorProducer_Fitter_python,src/WTopScalefactorProducer/Fitter/python,PYTHON))
ALL_PACKAGES += WTopScalefactorProducer/Skimmer
subdirs_src_WTopScalefactorProducer_Skimmer := src_WTopScalefactorProducer_Skimmer_python
ifeq ($(strip $(PyWTopScalefactorProducerSkimmer)),)
PyWTopScalefactorProducerSkimmer := self/src/WTopScalefactorProducer/Skimmer/python
src_WTopScalefactorProducer_Skimmer_python_parent := 
ALL_PYTHON_DIRS += $(patsubst src/%,%,src/WTopScalefactorProducer/Skimmer/python)
PyWTopScalefactorProducerSkimmer_files := $(patsubst src/WTopScalefactorProducer/Skimmer/python/%,%,$(wildcard $(foreach dir,src/WTopScalefactorProducer/Skimmer/python ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
PyWTopScalefactorProducerSkimmer_LOC_USE := self  
PyWTopScalefactorProducerSkimmer_PACKAGE := self/src/WTopScalefactorProducer/Skimmer/python
ALL_PRODS += PyWTopScalefactorProducerSkimmer
PyWTopScalefactorProducerSkimmer_INIT_FUNC        += $$(eval $$(call PythonProduct,PyWTopScalefactorProducerSkimmer,src/WTopScalefactorProducer/Skimmer/python,src_WTopScalefactorProducer_Skimmer_python,1,1,$(SCRAMSTORENAME_PYTHON),$(SCRAMSTORENAME_LIB),,))
else
$(eval $(call MultipleWarningMsg,PyWTopScalefactorProducerSkimmer,src/WTopScalefactorProducer/Skimmer/python))
endif
ALL_COMMONRULES += src_WTopScalefactorProducer_Skimmer_python
src_WTopScalefactorProducer_Skimmer_python_INIT_FUNC += $$(eval $$(call CommonProductRules,src_WTopScalefactorProducer_Skimmer_python,src/WTopScalefactorProducer/Skimmer/python,PYTHON))
ALL_SUBSYSTEMS+=DAS_Root
subdirs_src_DAS_Root = 
ALL_SUBSYSTEMS+=Phase_III_Analysis_with_NanoAOD
subdirs_src_Phase_III_Analysis_with_NanoAOD = src_Phase_III_Analysis_with_NanoAOD_Muon_Efficiency_Run2UL src_Phase_III_Analysis_with_NanoAOD_PileUp_File_Reconstruction src_Phase_III_Analysis_with_NanoAOD_NANO_AOD_Analyzer src_Phase_III_Analysis_with_NanoAOD_Data_Files_Path_NaNoAOD src_Phase_III_Analysis_with_NanoAOD_Analyzed_Files_Nano_AOD src_Phase_III_Analysis_with_NanoAOD_Electron_Efficiency_Run2UL src_Phase_III_Analysis_with_NanoAOD_List_of_NANO_AOD_paths
ALL_PACKAGES += Phase_III_Analysis_with_NanoAOD/Analyzed_Files_Nano_AOD
subdirs_src_Phase_III_Analysis_with_NanoAOD_Analyzed_Files_Nano_AOD := 
ALL_PACKAGES += Phase_III_Analysis_with_NanoAOD/List_of_NANO_AOD_paths
subdirs_src_Phase_III_Analysis_with_NanoAOD_List_of_NANO_AOD_paths := 
ALL_PACKAGES += Phase_III_Analysis_with_NanoAOD/Electron_Efficiency_Run2UL
subdirs_src_Phase_III_Analysis_with_NanoAOD_Electron_Efficiency_Run2UL := 
ALL_PACKAGES += Phase_III_Analysis_with_NanoAOD/Muon_Efficiency_Run2UL
subdirs_src_Phase_III_Analysis_with_NanoAOD_Muon_Efficiency_Run2UL := src_Phase_III_Analysis_with_NanoAOD_Muon_Efficiency_Run2UL_MuonReferenceEfficiencies-master-EfficienciesStudies-UL2017
ALL_PACKAGES += Phase_III_Analysis_with_NanoAOD/PileUp_File_Reconstruction
subdirs_src_Phase_III_Analysis_with_NanoAOD_PileUp_File_Reconstruction := 
ALL_PACKAGES += Phase_III_Analysis_with_NanoAOD/NANO_AOD_Analyzer
subdirs_src_Phase_III_Analysis_with_NanoAOD_NANO_AOD_Analyzer := 
ALL_SUBSYSTEMS+=Large_Data_Files_Listing
subdirs_src_Large_Data_Files_Listing = 
ALL_PACKAGES += Phase_III_Analysis_with_NanoAOD/Data_Files_Path_NaNoAOD
subdirs_src_Phase_III_Analysis_with_NanoAOD_Data_Files_Path_NaNoAOD := 
