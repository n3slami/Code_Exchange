import re
import os

pid = input("Process PID to fetch: ")
if not pid.isnumeric():
	print("Invalid PID.")
	exit(1)

PROC_DIR = "/proc"
dir_path = os.path.join(PROC_DIR, str(pid))
print(dir_path)
if not os.path.isdir(dir_path):
	print("PID not found.")
	exit(2)

with open(os.path.join(dir_path, "stat"), 'r') as fstat:
	print(f"Name: {fstat.readline().split()[1][1:-1]}", end='\t')
with open(os.path.join(dir_path, "status"), 'r') as fstatus:
	try:
		mem_usage = re.search("VmSize:[\\s]*([0-9]+ kB)", fstatus.read()).group(1)
	except:
		mem_usage = "(Cannot Resolve)"
	print(f"Mem. Usage: {mem_usage}")
with open(os.path.join(dir_path, "cmdline"), 'r') as fcmdline:
	print("Command-line Args.:", fcmdline.read().replace('\x00', ' '))
with open(os.path.join(dir_path, "environ"), 'r') as fenviron:
	print("Env. Vars:", fenviron.read().replace('\x00', ' '))
