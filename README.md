# Chess_Arena_PWI_23
Projekt grupowy na zajęcia PWI 2023 polegający na stworzeniu interfejsu szachowego wraz z botami.


# Jak uruchomić projekt
Uruchomienie projektu wymaga wersji pythona 3.11. Potencjalnie może działać w dowolnej wersji nowszej niż 3.7, ale nie było to testowane.

Zainstaluj wymagane moduły pythonowe poleceniem `pip install -r requirements.txt`.

Aby uruchomić walkę między botami, użyj polecenia `python run_duel.py -pvp nazwa_bota1 nazwa_bota2`.

Aby zawalczyć z botem, użyj polecenia `python run_duel.py -pve nazwa_bota`.

Program `run_duel.py` obsługuje dodatkowo następujące argumenty

`-fen` - startowy fen

`-time` - czas gracza w sekundach

Przykład: `python run_duel.py -pve 1000101bot -time=600 -fen="r1bqkb1r/pppp1ppp/2n2n2/4p3/4P3/2N2N2/PPPP1PPP/R1BQKB1R w KQkq - 0 1"` - zawalcz z botem o nazwie 1000101 gdzie każdy gracz ma 10 minut, a startowy fen jest podany.

# Dostępne boty
bot_jana_2

bot_jana_1_lepszy

snakeGood

heurabot

1000101bot - jako, że jest on napisany w C++, to należy go skompilować