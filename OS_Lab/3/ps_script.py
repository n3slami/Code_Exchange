import os

PROC_DIR = "/proc"
for dir_name in os.listdir(PROC_DIR):
	dir_path = os.path.join(PROC_DIR, dir_name)
	if os.path.isdir(dir_path) and dir_name.isnumeric():
		with open(os.path.join(dir_path, "stat")) as fstat:
			details = fstat.readline().split()[:3]
			if details[2] not in "xXZ":
				print(f"PID: {details[0]}\t\tName:{details[1][1:-1]}")
