#!/bin/zsh
## make sure the right shell will be used
#$ -S /bin/zsh
#######################################################
## Black list nodes
##$ -l h=!bird234.desy.de
#######################################################
## the cpu time for this job
#$ -l h_rt=08:59:00
## the maximum memory usage of this job
#$ -l h_vmem=5900M
## Job Name
#$ -N NANO
## stderr and stdout are merged together to stdout
#$ -j y
## transfer env var from submission host
#$ -V
## set cwd to submission host pwd
#$ -cwd

echo job start at `date`
echo "Running job on machine " `uname -a`

TaskID=$((SGE_TASK_ID))
echo "SGE_TASK_ID: " $TaskID

JobList=$1
TaskCmd=$(cat $JobList | sed ''$TaskID'q;d')

#eval $(scramv1 runtime -sh);

echo "Going to execute" $TaskCmd
eval $TaskCmd

echo "Complete at " `date`