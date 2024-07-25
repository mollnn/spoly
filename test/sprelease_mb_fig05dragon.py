# Use serial CPU version currently, which is fairly slow
TESTID = "fig05dragon"
from labcommon import *

group_name = ["Newton", "Ours"]

for group in range(2):
    scene_path = "../scenes/mbglints/bunnym.xml"
    test_name = "mbglints_%d" % group
    exr_filename = "results/%s/%s.exr " % (TESTID, test_name)
    cmd = "..\\mts1\\cbuild\\bin\\mtsutil.exe mbglints "
    cmd += "-o %s " % exr_filename
    cmd += "-b 2 -e 0.001 -i 32 -I 1 -S 1 -T 1e-999 -c 15 -C 100 -d 10 -P 1 " # please use MULTI_BOUNCE in resultant.h
    if group == 1:
        cmd += "-r -m 16 "
    cmd += "%s " % scene_path
    my_run_cmd(TESTID, cmd, test_name, instant=True)