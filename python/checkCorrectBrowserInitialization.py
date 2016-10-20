import subprocess
import shlex

PSTREE =   "pstree -p"
XDG_OPEN = "xdg-open"
GREP =     "grep "
PS =       "ps -ax"

def get_subprocess_id(process):
    first_closing_parenthesis = process.find(")")
    second_opening_parenthesis = process.find("(", first_closing_parenthesis)
    second_closing_parenthesis = process.find(")",
        first_closing_parenthesis + 1)
    start = (second_opening_parenthesis + 1)
    end = -(len(process) - second_closing_parenthesis)
    return process[start:end]

def execute_pipe_commands(commands):
    total_commands = len(commands)
    if total_commands > 0:
        args = shlex.split(commands[0])
        execution = subprocess.Popen(args, stdout = subprocess.PIPE)
        commands_range = range(1, total_commands)
        for x in commands_range:
            args = shlex.split(commands[x])
            consecutive_execution = subprocess.Popen(args,
                stdin = execution.stdout, stdout = subprocess.PIPE)
            execution = consecutive_execution
        return [line.rstrip() for line in execution.stdout]
    else:
        return []

def validate_process_parameter(process, parameter):
    subprocess_id = get_subprocess_id(process)
    grep_child_process_id = execute_pipe_commands([PS,
        "{0}{1}".format(GREP, subprocess_id)])
    return any(parameter in result for result in grep_child_process_id)

def validate_web_process_execution(url):
    pstree_results = execute_pipe_commands([PSTREE,
        "{0}{1}".format(GREP, XDG_OPEN)])
    if any(XDG_OPEN in result for result in pstree_results):
        xdg_processes = [xdg_process
            for xdg_process in pstree_results if XDG_OPEN in xdg_process]
        valid_parameters = [validate_process_parameter(process, url)
            for process in xdg_processes]
        return valid_parameters.count(True) >= 1
    else:
        return False

def main():
    url = "http://stackoverflow.com"
    if validate_web_process_execution(url):
        print "OK"
    else:
        print "ERROR"

if __name__ == "__main__":
<<<<<<< HEAD
    main()
=======
    main()
>>>>>>> 3d89851ff08afe750fa5ead0feed5baf0678cdbb
