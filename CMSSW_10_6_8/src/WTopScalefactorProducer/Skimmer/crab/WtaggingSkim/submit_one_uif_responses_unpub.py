#!/usr/bin/env python                                                                                                                                                                                 
"""                                                                                                                                                                                                   
This is a small script that submits a config over many datasets                                                                                                                                       
"""
import os
from optparse import OptionParser
#from Analysis.QJetMass.helpers.eos_get_rootfiles import eos_get_rootfiles


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

    if options.cfg == None or options.dir == None or options.storageSite == None:
        parser.error(usage)

    return options


def main():

    options = getOptions()

    from WMCore.Configuration import Configuration
    config = Configuration()

    from CRABAPI.RawCommand import crabCommand
    from httplib import HTTPException


    # talk to DBS to get list of files in this dataset                                                                                                                                                     
    #from dbs.apis.dbsClient import DbsApi
    #dbs = DbsApi('https://cmsweb.cern.ch/dbs/prod/phys03/DBSReader')


    # We want to put all the CRAB project directories from the tasks we submit here into one common directory.                                                        =                                
    # That's why we need to set this parameter (here or above in the configuration file, it does not matter, we will not overwrite it).                                                               
    config.section_("General")
    config.General.workArea = options.dir
    config.General.transferLogs = True

    config.section_("JobType")
    config.JobType.pluginName = 'Analysis' #'PrivateMC'#'Analysis'
    config.JobType.psetName = options.cfg

    config.section_("Data")
    #config.Data.inputDataset = None
    #config.Data.splitting = ''
    #config.Data.unitsPerJob = 1
    #config.Data.ignoreLocality = False                                                                                            
    config.Data.publication = False #True
    #config.Data.totalUnits = 100000000000

    config.section_("Site")
    config.Site.storageSite = options.storageSite
    #config.Site.whitelist = ['T2_US_Nebraska','T2_CH_CSCS','T3_US_UMD','T2_US_Caltech','T2_US_MIT']
    config.Site.blacklist = ['T2_US_Florida','T3_TW_*','T2_BR_*','T2_GR_Ioannina','T2_BR_SPRACE','T2_RU_IHEP','T2_PL_Swierk','T3_TW_NTU_HEP','T3_TW_NTU_HEP','T2_ES_CIEMAT','T2_BE_UCL','T3_US_Colorado','T3_US_UCR','T2_PT_NCG_Lisbon','T2_US_Vanderbilt']

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
    adataset = None
    datatier = "USER"
    name = jobsLines[0].split('/')[5][:-11]

    #for ijob, job in enumerate(jobsLines) :

    #    adataset = job.rstrip()                                                                        

    #    #ptbin = job.split('/')[1]
    #    #cond = job.split('/')[2] 
    #    datatier = job.split('/')[3]
    #    #era = job.split('Run2016')[1]
    #    #era = era.split('/')[0]
    #exti = job.split('/')[5]
    #    #exti = exti.split('8')[0]
    #    #config.Data.inputDataset = job
    #    adataset = job 
    #    #if datatier == "USER":
        
        
    requestname = 'WtaggingSkim-'+name
    print requestname
    config.JobType.scriptExe = 'crab_script_SFs.sh' 
    config.JobType.inputFiles = [options.cfg ,'crab_script_SFs.sh', 'crab_script_SFs.py' ,'./haddnano.py' ]
    config.JobType.sendPythonFolder  = True
    '''        
        #lfnList = eos_get_rootfiles( adataset )
        #fileDictList=dbs.listFiles(dataset=adataset)                                                                      

        #print ("dataset %s has %d files" % (adataset, len(lfnList)))

        # DBS client returns a list of dictionaries, but we want a list of Logical File Names                              
        #lfnList = [ dic['logical_file_name'] for dic in fileDictList ]                                                    
        # following 3 lines are the trick to skip DBS data lookup in CRAB Server                                           
        #config.Data.userInputFiles = fileList#lfnList    
    '''       
    datasetsFile = open( options.datasets )                                                                                                                                 
    jobsLines = datasetsFile.readlines()
    filelist = [] 
    for l in jobsLines:
        
        filelist.append(str(l[:-1]))
    print filelist 
    config.Data.userInputFiles = filelist
    
    config.Data.unitsPerJob = 1

    
    config.Data.inputDBS = 'phys03'
    config.Data.splitting = 'FileBased'
    # since the input will have no metadata information, output can not be put in DBS        
    config.Data.publication = False #True
    config.JobType.outputFiles = [ 'WtaggingSkim.root']
    '''
        if datatier == 'MINIAODSIM':
            requestname = 'NANAODrecluster_' + ptbin + '_' + cond
            config.Data.splitting = 'FileBased'
            config.Data.unitsPerJob = 1
            config.Data.publication = True
        elif datatier == 'MINIAOD':
            requestname = 'NANAODrecluster_' + ptbin + '_' + cond
            config.Data.splitting = 'LumiBased'
            config.Data.lumiMask = options.lumiMask
            config.Data.unitsPerJob = 200
            config.Data.publication = True
    '''

    if len(requestname) > 100: requestname = ''.join((requestname[:100-len(requestname)]).split('_')[:-1])
    print 'requestname = ', requestname
    config.General.requestName = requestname
    config.Data.outputDatasetTag = requestname
    print 'Submitting ' + config.General.requestName + ', dataset = ' + name
    print 'Configuration :'
    print config
    print "Not submitting , test complete!!!"
       
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



