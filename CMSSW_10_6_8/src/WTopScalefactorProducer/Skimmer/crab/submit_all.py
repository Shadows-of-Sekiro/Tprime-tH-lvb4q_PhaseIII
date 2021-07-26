
#!/usr/bin/env python
"""
This is a small script that submits a config over many datasets
"""
import os
from optparse import OptionParser

def make_list(option, opt, value, parser):
    setattr(parser.values, option.dest, value.split(','))

def getOptions() :
    """
    Parse and return the arguments provided by the user.
    """
    usage = ('usage: python submit_all.py -c CONFIG -d DIR -f DATASETS_FILE')

    parser = OptionParser(usage=usage)    
    parser.add_option("-c", "--config", dest="cfg", default="test94X_NANO.py",
        help=("The crab script you want to submit "),
        metavar="CONFIG")
    parser.add_option("-d", "--dir", dest="dir", default="NANO",
        help=("The crab directory you want to use "),
        metavar="DIR")
    parser.add_option("-f", "--datasets", dest="datasets",
        help=("File listing datasets to run over"),
        metavar="FILE")
    parser.add_option("-s", "--storageSite", dest="storageSite", default="T3_US_FNALLPC",
        help=("Site"),
        metavar="SITE")
    parser.add_option("-l", "--lumiMask", dest="lumiMask",
        help=("Lumi Mask JSON file"),
        metavar="LUMIMASK")

    (options, args) = parser.parse_args()

    if options.cfg == None or options.dir == None or options.datasets == None or options.storageSite == None:
        parser.error(usage)
    
    return options
    

def main():

    options = getOptions()

    from WMCore.Configuration import Configuration
    config = Configuration()

    from CRABAPI.RawCommand import crabCommand
    from httplib import HTTPException

        
    # We want to put all the CRAB project directories from the tasks we submit here into one common directory.
    # That's why we need to set this parameter (here or above in the configuration file, it does not matter, we will not overwrite it).
    config.section_("General")
    config.General.workArea = options.dir 
    config.General.transferLogs = True

    config.section_("JobType")
    config.JobType.pluginName = 'Analysis'
    config.JobType.psetName = options.cfg
    
    config.section_("Data")
    config.Data.inputDataset = None
    config.Data.splitting = ''
    #config.Data.unitsPerJob = 1
    #config.Data.ignoreLocality = True
    # Note on ignoring locality :
    # If running on Sal or Ashley's Nano datasets you can set this to False
    # and comment out the whitelist below

    config.Data.publication = True
        
    config.Data.publishDBS = 'phys03'
   
    config.section_("Site")
    config.Site.storageSite = options.storageSite
    #config.Site.whitelist = ['T2_CH_*']
    print 'Using config ' + options.cfg
    print 'Writing to directory ' + options.dir
    
    def submit(config):
        try:
            crabCommand('submit', config = config)
        except HTTPException, hte:
            print 'Cannot execute command'
            print hte.headers

    #############################################################################################
    ## From now on that's what users should modify: this is the a-la-CRAB2 configuration part. ##
    #############################################################################################

    datasetsFile = open( options.datasets )
    jobsLines = datasetsFile.readlines()
    jobs = []
    for ijob in jobsLines :
        s = ijob.rstrip()
        if (len(s)==0 or s[0][0]=='#'): continue
        s = ijob.rstrip()
        jobs.append( s )
        print '  --> added ' + s
        
    for ijob, job in enumerate(jobs) :

        ptbin = job.split('/')[1]
        cond = job.split('/')[2]
        datatier = job.split('/')[3]
        requestname = 'skim_'+ptbin + '_' + cond
        if len(requestname) > 100: requestname = ''.join((requestname[:100-len(requestname)]).split('_')[:-1])
        print 'requestname = ', requestname
        config.General.requestName = requestname
        config.Data.outputDatasetTag = requestname
        
      
        if datatier == 'USER':

          config.JobType.scriptExe = 'crab_script_SFs.sh' 
          config.JobType.inputFiles = [options.cfg ,'crab_script_SFs.sh', 'crab_script_SFs.py' ,'../haddnano.py', 'keep_and_drop.txt','/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions17/13TeV/PromptReco/Cert_294927-306462_13TeV_PromptReco_Collisions17_JSON.txt'] #hadd nano will not be needed once nano tools are in cmssw                                                                                                                    
          config.JobType.sendPythonFolder  = True
    
          config.Data.inputDataset = job
          config.Data.inputDBS = 'phys03'
          config.Data.splitting = 'FileBased'
          config.Data.unitsPerJob = 1          
          #config.Data.splitting = 'EventAwareLumiBased'# 'FileBased'                                                                                                          
          #config.Data.unitsPerJob = 100 
          #config.Data.totalUnits = 2000
         
          config.Data.publication =  True #False
        
        if 'MINIAOD' in datatier :
          onfig.JobType.psetName = options.cfg
          config.Data.inputDataset = job
          config.Data.publication = True                                                                          
          config.Data.publishDBS = 'phys03'  
        if datatier == 'MINIAODSIM': 
          config.Data.splitting = 'FileBased'
          config.Data.unitsPerJob = 1
        elif datatier == 'MINIAOD': 
          config.Data.splitting = 'LumiBased'
          config.Data.lumiMask = options.lumiMask
          config.Data.unitsPerJob = 200
        print 'Submitting ' + config.General.requestName + ', dataset = ' + job
        print 'Configuration :'
        print config
        try :
            from multiprocessing import Process
            
            p = Process(target=submit, args=(config,))
            p.start()
            p.join()
            #submit(config)
        except :
            print 'Not submitted.'



if __name__ == '__main__':
    main()            
