
#!/Usr/bin/env python                                                                                                                                                                                 
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


    # talk to DBS to get list of files in this dataset                                                                                                                                                     
    from dbs.apis.dbsClient import DbsApi
    dbs = DbsApi('https://cmsweb.cern.ch/dbs/prod/phys03/DBSReader')


    # We want to put all the CRAB project directories from the tasks we submit here into one common directory.                                                        =                                
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
    config.Data.unitsPerJob = 1
    #config.Data.ignoreLocality = False                                                                                            
    #config.Data.publication = True
    #config.Data.publishDBS = 'phys03'

    config.section_("Site")
    config.Site.storageSite = options.storageSite
    #config.Site.whitelist = ['T2_US_Nebraska','T2_CH_CSCS','T3_US_UMD','T2_US_Caltech','T2_US_MIT']
    config.Site.blacklist = ['T2_US_Florida','T3_TW_*','T2_BR_*','T2_GR_Ioannina','T2_BR_SPRACE','T2_RU_IHEP','T2_PL_Swierk','T3_TW_NTU_HEP']

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
    adataset = None
    for ijob, job in enumerate(jobs) :

        ptbin = job.split('/')[1]
        cond = job.split('/')[2] 
        datatier = 'USER' #job.split('/')[3]

        ### Get the name of the input file and decide if it is 80XMC , 94X MC , data 2016 or 2017                                               
        nameTag = None 
        is80XMC = False
        is94XMC = False
        is2016Data = False
        is2017Data = False
        print "Analyzing dataset name for keywords....."
        nameis = str(cond)
        print nameis
        if ('SingleMuon' in nameis) or ('SingleElectron' in nameis) :
            nameis = cond[9:32]
            nameTag = '-Data-'
            if 'Run2016' in nameis : 
                is2016Data = True
                nameis = job.split('Run')[1] 
                nameis = nameis.split('/')[0][0:7]  
            if 'Run2017' in nameis : 
                is2017Data = True
                nameis = job.split('Run')[1]
                nameis = nameis.split('/')[0][0:7]    
          
            nameis = ptbin +'_'+ nameis
        else :
            
            nameis = cond.split('asparker-')[1]#('srappocc-')[1]
            if '16MiniAOD' in str(cond) : 
                is80XMC = True
                nameTag = '-80XMC-'
                nameis = nameis.split('Mini')[0]        
            elif '17MiniAOD' in str(cond) : 
                is94XMC = True
                nameTag= '-94XMC-'
                nameis = nameis.split('Mini')[0]
            elif 'pythia' in str(cond):
                is80XMC = True
                nameTag = '-80XMC-'
                nameis = nameis.split('8-')[0]



        print "NAMEISSSSS"
        print  nameis
        # ???  
        #era = job.split('Run2016')[1]
        #era = era.split('/')[0]
        #exti = job.split('srappocc-')[1]
        #exti = exti.split('a8-')[0]
        #config.Data.inputDataset = job
         
        adataset = job 
        if datatier == "USER":
            
            
            requestname = 'nanoskim-JetsAndLepton'+nameTag + nameis
            
            
            config.JobType.scriptExe = 'crab_script.sh' 
            config.JobType.inputFiles = [options.cfg ,'crab_script.sh', 'crab_script.py' ,'./haddnano.py', 'keep_and_drop.txt'  ]
            config.JobType.sendPythonFolder  = True
           
            fileDictList=dbs.listFiles(dataset=adataset)

            print ("dataset %s has %d files" % (adataset, len(fileDictList)))

            # DBS client returns a list of dictionaries, but we want a list of Logical File Names
            lfnList = [ dic['logical_file_name'] for dic in fileDictList ]
            # following 3 lines are the trick to skip DBS data lookup in CRAB Server
            config.Data.userInputFiles = lfnList
            config.Data.splitting = 'FileBased'
            config.Data.unitsPerJob = 1
            #config.Data.splitting = 'Automatic'
            #config.Data.inputDataset = job
            #config.Data.inputDBS = 'phys03'
            #config.Data.splitting = 'FileBased'
            #config.Data.unitsPerJob = 1
            #config.Data.splitting = 'Automatic'#'EventAwareLumiBased'
            #config.Data.unitsPerJob = 100
            #config.Data.totalUnits = 2000  
            # since the input will have no metadata information, output can not be put in DBS        
            config.Data.publication = False #True
            config.JobType.outputFiles = ['nanoskim-histos.root','nanoskim-trees.root' ]
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
        if len(requestname) > 100: requestname = (requestname[:95-len(requestname)])
        print 'requestname = ', requestname
        config.General.requestName = requestname
        config.Data.outputDatasetTag = requestname
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



