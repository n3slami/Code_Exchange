import re
import os

CPUINFO_DIR = "/proc/cpuinfo"
with open(CPUINFO_DIR, 'r') as f:
	file_contents = f.read()
	model_name = re.search("model name(\\s*): (.+)", file_contents).group(2)
	print("Model Name:", model_name)
	freq = re.search("cpu MHz(\\s*): (.+)", file_contents).group(2)
	cache_size = re.search("cache size(\\s*): (.+) KB", file_contents).group(2)
	print(f"CPU Frequency: {freq} MHz\t\t\tCache Size: {cache_size} KB")
