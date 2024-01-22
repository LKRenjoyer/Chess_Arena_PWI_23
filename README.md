# Chess_Arena_PWI_23
Projekt grupowy na zajęcia PWI 2023 polegający na stworzeniu interfejsu szachowego wraz z botami.


# Jak uruchomić projekt
Uruchomienie projektu wymaga wersji pythona 3.11. Potencjalnie może działać w dowolnej wersji nowszej niż 3.7, ale nie było to testowane.

Zainstaluj wymagane moduły pythonowe poleceniem `pip install -r requirements.txt`.

Aby uruchomić walkę między botami, użyj polecenia `python run_duel.py -eve nazwa_bota1 nazwa_bota2`.

Aby zawalczyć z botem, użyj polecenia `python run_duel.py -pve nazwa_bota`.

Aby uruchomić walkę między graczami ludzkimi użyj polecenia `python run_duel.py -pvp`.

Program `run_duel.py` obsługuje dodatkowo następujące argumenty

`-fen` - startowy fen

`-time` - czas gracza w sekundach

Przykład: `python run_duel.py -pve 1000101bot -time=600 -fen="r1bqkb1r/pppp1ppp/2n2n2/4p3/4P3/2N2N2/PPPP1PPP/R1BQKB1R w KQkq - 0 1"` - zawalcz z botem o nazwie 1000101 gdzie każdy gracz ma 10 minut, a startowy fen jest podany.

# Dostępne boty

# bot_jana_2

# bot_jana_1_lepszy

# snakeOrginal
Bot napisany w Pythonie przez Cypriana Ziółkowskiego z własną biblioteczką szachową. Używa alpha-beta pruning i spamiętywania ewaluacji pozycji za pomocą Zobrist hashing. Okazął się za wolny by obsługiwać na początku gry głębokość 4, zatem działa na głębokości 2 i jest dość słaby. W końcówce radzi sobie z głębokośćią 4 i jest w stanie matować królem i wieżą, bądź królową.
# snakeGood
Bot napisany w Pythonie przez Cypriana Ziółkowskiego. Jest to wersja snakeOriginal używająca biblioteki pythonowej chess. Używa alpha-beta pruning i spamiętywania ewaluacji pozycji za pomocą Zobrist hashing. Obsługuje przez całą grę głębokość 4 i jest całkiem solidny. W końcówce jest w stanie matować królem i wieżą, bądź królową.
# heurabot

# 1000101bot - jako, że jest on napisany w C++, to należy go skompilować