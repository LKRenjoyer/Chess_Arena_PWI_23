import subprocess

with open('komunikacja.txt','w') as file:
    file.write('start game')

bot1 = subprocess.Popen(['python','main.py'],stdin=subprocess.PIPE,stdout=subprocess.PIPE)
bot2 = subprocess.Popen(['python','client.py'],stdin=subprocess.PIPE,stdout=subprocess.PIPE)

# print(1)