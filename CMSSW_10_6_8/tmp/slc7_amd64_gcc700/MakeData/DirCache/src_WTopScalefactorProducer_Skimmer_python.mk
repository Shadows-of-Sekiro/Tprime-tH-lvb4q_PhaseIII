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
