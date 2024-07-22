TESTID = "fig06plane"
from labcommon import *

test_name1 = "Ours"
exr_filename1 = "results/%s/%s.exr " % (TESTID, test_name1)
cmd = "..\\mts1\\cbuild\\bin\\mitsuba.exe "
cmd += "../scenes/mbglints/sp_plane/mytestcau.xml "
cmd += "-DuseResultant=true -DmethodMask=0 "
cmd += "-o %s " % exr_filename1

my_run_cmd(TESTID, cmd, test_name1, instant=False) 

test_name2 = "SMS"
exr_filename2 = "results/%s/%s.exr " % (TESTID, test_name2)
cmd = "..\\mts\\build\\dist\\mitsuba.exe -m scalar_rgb "
cmd += "../scenes/mbglints/sp_plane/mytestcau_sms.xml "
cmd += "-o %s " % exr_filename2

# my_run_cmd(TESTID, cmd, test_name2, instant=False)

test_name3 = "MPG"
exr_filename3 = "results/%s/%s.exr " % (TESTID, test_name3)
cmd = "..\\mts\\build\\dist\\mitsuba.exe -m scalar_rgb "
cmd += "../scenes/mbglints/sp_plane/mytestcau_mpg.xml "
cmd += "-o %s " % exr_filename3

# my_run_cmd(TESTID, cmd, test_name3, instant=False)

test_name4 = "PT"
exr_filename4 = "results/%s/%s.exr " % (TESTID, test_name4)
cmd = "..\\mts1\\cbuild\\bin\\mitsuba.exe "
cmd += "../scenes/mbglints/sp_plane/mytestcau_pt.xml "
cmd += "-o %s " % exr_filename4

my_run_cmd(TESTID, cmd, test_name4, instant=False)

test_name5 = "PPG"
exr_filename5 = "results/%s/%s.exr " % (TESTID, test_name5)
cmd = "..\\mts1\\cbuild\\bin\\mitsuba.exe "
cmd += "../scenes/mbglints/sp_plane/mytestcau_ppg.xml "
cmd += "-o %s " % exr_filename5

# my_run_cmd(TESTID, cmd, test_name5, instant=False)

test_name6 = "Ref"
exr_filename6 = "results/%s/%s.exr " % (TESTID, test_name6)
cmd = "..\\mts\\build\\dist\\mitsuba.exe -m scalar_rgb "
cmd += "../scenes/mbglints/sp_plane/mytestcau_ref.xml "
cmd += "-o %s " % exr_filename6

# my_run_cmd(TESTID, cmd, test_name6, instant=False)