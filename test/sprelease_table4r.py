# Uncomment the macro ENABLE_TIME_COUNTER in chrono_def.h to enable timing!
TESTID = "table4r"
from labcommon import *
for group in range(2):
    scene_path = "../scenes/mbglints/sp_tinfoil/tinfoil.xml"
    test_name = "mbglints_%d" % group
    exr_filename = "results/%s/%s.exr " % (TESTID, test_name)
    cmd = "..\\mts1\\cbuild\\bin\\mtsutil.exe mbglints "
    cmd += "-o %s " % exr_filename
    # In this performance test, we use the original max iteration (5 (+1)) from Path Cuts's code release, though we found increasing it could yield more glints. For visual comparison, we use 32 instead.
    cmd += "-b 1 -e 0.000001 -i 6 -I 1 -S 1 -T 1e-9 -c 4 -C 8 -P 1 " 
    if group == 1:
        cmd += "-r -m 0 "
    cmd += "%s " % scene_path
    my_run_cmd(TESTID, cmd, test_name, instant=True)
# Some timings are not stable. Please run this script multiple times.