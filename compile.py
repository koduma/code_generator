import subprocess
import os
import time
r=1-subprocess.run([r"/usr/bin/g++", "-Wall", "-o", "gene", 'gene.cpp'], stdout=subprocess.PIPE, stderr=subprocess.PIPE).returncode
f = open('log.txt', 'w')#1は成功、0は失敗
f.write(str(r))
f.close()
