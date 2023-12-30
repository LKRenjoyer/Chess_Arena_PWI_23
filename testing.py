import subprocess
import sys

for x in range(15):
    xd = subprocess.run([sys.executable,'run_duel.py','bot_jana_1_lepszy','bot_jana_2','-eve'],stdout=subprocess.PIPE)