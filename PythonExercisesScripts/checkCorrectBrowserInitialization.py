import subprocess
import shlex
import time
import os

PROC_SEARCH = "/proc/{0}/cmdline"
PSTREE_SEARCH = "pstree -p | grep "
XDG_OPEN = "xdg-open"
URL_CHECK = ("http://google.com")
DELIMITER = "\x00"

def get_xdg_subprocess_id(process):
    #process e.g: `-xdg-open(63141)---<browser>(<pid>)+-{<browser>}(63251)
    xdg_pos = process.find(XDG_OPEN)
    xdg_closing_parenthesis = process.find(")", xdg_pos)
    subprocess_opening_parenthesis = process.find("(", xdg_closing_parenthesis)
    if subprocess_opening_parenthesis == -1:
        return None
    subprocess_closing_parenthesis = process.find(")",
        subprocess_opening_parenthesis)
    start = (subprocess_opening_parenthesis + 1)
    end = -(len(process) - subprocess_closing_parenthesis)
    return process[start:end]

def execute_command(command):
    execution = subprocess.Popen(command, stdout=subprocess.PIPE, shell=True)
    return [line.strip() for line in execution.stdout]

def validate_process_parameter(process, parameter):
    subprocess_id = get_xdg_subprocess_id(process)
    if subprocess_id is None:
        return False
    subprocess_cmdline_path = PROC_SEARCH.format(subprocess_id)
    if not os.path.exists(subprocess_cmdline_path):
        return False
    calling_cmd = open(subprocess_cmdline_path).read().split(DELIMITER)
    return calling_cmd[1] == parameter

def validate_web_process_execution(url):
    pstree_results = execute_command("{0}{1}".format(PSTREE_SEARCH, XDG_OPEN))
    if any(XDG_OPEN in result for result in pstree_results):
        valid_parameters = [validate_process_parameter(process, url)
            for process in pstree_results]
        return valid_parameters.count(True) >= 1
    else:
        test.log("Any xdg-open process was found")
        return False

def main():
    if validate_web_process_execution(URL_CHECK):
        print "Ok"
    else:
        print "ERROR"

if __name__ == "__main__":
    main()
