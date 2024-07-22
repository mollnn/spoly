# Please make sure that timing (ENABLE_TIME_COUNTER) is disabled in chrono_def.h before running this script. Otherwise, the timing results will be slower than expected.
TESTID = "fig08plane"
from labcommon import *

test_name0 = "Newton"
exr_filename0 = "results/%s/%s.exr " % (TESTID, test_name0)
cmd = "..\\mts1\\cbuild\\bin\\mitsuba.exe "
cmd += "../scenes/mbglints/sp_plane/mytestcau_tiny.xml "
cmd += "-o %s " % exr_filename0
cmd += "-Dspp=16 "

my_run_cmd(TESTID, cmd, test_name0, instant=False)

test_name1 = "Ours"
exr_filename1 = "results/%s/%s.exr " % (TESTID, test_name1)
cmd = "..\\mts1\\cbuild\\bin\\mitsuba.exe "
cmd += "../scenes/mbglints/sp_plane/mytestcau_tiny.xml "
cmd += "-DuseResultant=true -DmethodMask=0 "
cmd += "-o %s " % exr_filename1
cmd += "-Dspp=32 "

my_run_cmd(TESTID, cmd, test_name1, instant=False)
