while(true); do echo Running jobs: $(qstat | grep -e "zucchett" -e "     r     " | wc -l); sleep 60; done;
