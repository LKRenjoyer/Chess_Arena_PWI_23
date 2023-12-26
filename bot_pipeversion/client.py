import subprocess

bot = subprocess.Popen(['python','main.py',"b"],stdin=subprocess.PIPE,stdout=subprocess.PIPE)

def ruch_clienta():
    return input()

while True:
    wejscie = f"{ruch_clienta()}\n"
    bot.stdin.write(wejscie.encode("utf-8"))
    bot.stdin.flush()
    # print("xd")
    wyjscie = bot.stdout.readline().decode('utf-8')
    print(f"ruch bota {wyjscie}")