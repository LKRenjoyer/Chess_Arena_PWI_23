import shlex
import subprocess

for i in range(20):
    out = subprocess.run(shlex.split("python run_duel.py test_101bot bot_jana_1_lepszy -eve -nv"))
    print(i)


