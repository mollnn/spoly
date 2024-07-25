TESTID = "fig08pool"
import os
from labcommon import *

test_name0 = "Newton"
exr_filename0 = "results/%s/%s.exr " % (TESTID, test_name0)
cmd = "..\\mts1\\cbuild\\bin\\mitsuba.exe "
cmd += "../scenes/mbglints/sp_pool/mytestcau_pool_ours.xml "
cmd += "-o %s " % exr_filename0 

my_run_cmd(TESTID, cmd, test_name0, instant=False)

test_name1 = "Ours"
exr_filename1 = "results/%s/%s.exr " % (TESTID, test_name1)
cmd = "..\\mts1\\cbuild\\bin\\mitsuba.exe "
cmd += "../scenes/mbglints/sp_pool/mytestcau_pool_ours.xml "
cmd += "-DuseResultant=true -DmethodMask=0 "
cmd += "-o %s " % exr_filename1 

my_run_cmd(TESTID, cmd, test_name1, instant=False)