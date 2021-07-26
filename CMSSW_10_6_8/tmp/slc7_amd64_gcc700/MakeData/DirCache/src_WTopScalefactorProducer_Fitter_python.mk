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
