import os

from numpy import append
import config
import time
from subprocess import PIPE, run



def init(TESTID):
    try:
        os.mkdir('results')
    except:
        pass

    try:
        os.mkdir('results' + '/' + TESTID)
    except:
        pass


def run_cmd(TESTID, command, name):
    # print("Render {} ..".format(name))
    t0 = time.time()
    # mem.monitor_start()
    result = run(command, stdout=PIPE, stderr=PIPE,
                 universal_newlines=True, shell=True)
    # mem_used = mem.monitor_stop()
    log_str = result.stdout
    err_str = result.stderr
    t1 = time.time()
    with open('results/{}_log.txt'.format(TESTID + "/" + name), 'w') as file:
        file.write(log_str)
        print("@timeused", t1-t0, file=file)
        # print("@memused", mem_used, file=file)
        file.close()
    with open('results/{}_err.txt'.format(TESTID + "/" + name), 'w') as file:
        file.write(err_str)
        file.close()


def my_run_cmd(TESTID, command, name, instant = False):
    init(TESTID)
    # Manually switch here to choose whether to display log on screen or write to file
    t = time.time()
    if instant:
        os.system(command)
    else:
        run_cmd(TESTID, command, name)
    delta_t = time.time() - t
    print(delta_t)
    return delta_t

def run_test(TESTID, name, scene_file, mts_version, params, appendix, overwrite = True):
    t0 = time.time()
    cmd = config.MITSUBA2_EXE + " -m scalar_rgb " if mts_version == 2 else config.MITSUBA1_EXE if mts_version == 1 else config.MITSUBA1_EXE_STD
    cmd += scene_file + " "
    filename = "results/{}.exr".format(TESTID + "/" + name)
    if os.path.exists(filename) and overwrite == False:
        print("Already exist", filename, ", skip")
        return
    cmd += "-o results/{}.exr ".format(TESTID + "/" + name)
    for [k, v] in params.items():
        cmd += "-D" + k + "=" + str(v) + " "
    cmd += appendix
    print("\033[32m","[LabLog] Running on test", name,"\033[0m")
    # print("\033[32m","[LabLog] current cmd =", cmd,"\033[0m")
    print(cmd)
    my_run_cmd(TESTID, cmd, name, instant=False)
    t1 = time.time()
    print("\033[33m","[LabLog] finish test", name, "Time usage:", "%.3f" % (t1 - t0), "secs", "\033[0m")
    print()


def compose_exr_name(TESTID, testname):
    return "results/" + TESTID + "/" + testname + ".exr"