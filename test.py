import shlex
import subprocess

for i in range(20):
    out = subprocess.run(shlex.split("python run_duel.py fast_q_bot fast_q_bot -eve -nv"))
    print(i)


