import re
import os

CPUINFO_DIR = "/proc/meminfo"
with open(CPUINFO_DIR, 'r') as f:
	file_contents = f.read()
	mem_total = re.search("MemTotal:(\\s*)(.+) kB", file_contents).group(2)
	mem_free = re.search("MemFree:(\\s*)(.+) kB", file_contents).group(2)
	mem_used = int(mem_total) - int(mem_free)
	print(f"Mem. Total: {mem_total} kB\tMem. Free: {mem_free} kB\tMem. Used: {mem_used} kB")
