#this is not mean to be run locally
#
echo Check if TTY
if [ "`tty`" != "not a tty" ]; then
  echo "YOU SHOULD NOT RUN THIS IN INTERACTIVE, IT DELETES YOUR LOCAL FILES"
else

ls -lR .
echo "ENV..................................."
env 
echo "VOMS"
voms-proxy-info -all
echo "CMSSW BASE, python path, pwd"
echo $CMSSW_BASE 
echo $PYTHON_PATH
echo $PWD 
rm -rf $CMSSW_BASE/lib/
rm -rf $CMSSW_BASE/src/
rm -rf $CMSSW_BASE/module/
rm -rf $CMSSW_BASE/python/
mv lib $CMSSW_BASE/lib
mv src $CMSSW_BASE/src
mv python $CMSSW_BASE/python

source /cvmfs/cms.cern.ch/slc6_amd64_gcc630/external/fastjet-contrib/1.033-omkpbe/etc/profile.d/dependencies-setup.sh

source /cvmfs/cms.cern.ch/slc6_amd64_gcc630/external/fastjet-contrib/1.033-omkpbe/etc/profile.d/init.sh


echo Found Proxy in: $X509_USER_PROXY
python crab_script.py $1
fi