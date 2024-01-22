# Chess_Arena_PWI_23
Projekt grupowy na zajęcia PWI 2023 polegający na stworzeniu interfejsu szachowego wraz z botami.


# Jak uruchomić projekt
Uruchomienie projektu wymaga wersji pythona 3.11. Projekt został napisany z myślą o systemie operacyjnym Windows i na systemach Linux ma wiele problemów (zdaje się, że jak się postara to można go uruchomić, ale niektóre komendy nie zawsze działają).Potencjalnie może działać w dowolnej wersji nowszej niż 3.7, ale nie było to testowane.

Zainstaluj wymagane moduły pythonowe poleceniem `pip install -r requirements.txt`.

Aby uruchomić walkę między botami, użyj polecenia `python run_duel.py -eve nazwa_bota1 nazwa_bota2`.

Aby zawalczyć z botem, użyj polecenia `python run_duel.py -pve nazwa_bota`.

Aby uruchomić walkę między graczami ludzkimi użyj polecenia `python run_duel.py -pvp`.

Program `run_duel.py` obsługuje dodatkowo następujące argumenty

`-fen` - startowy fen

`-time` - czas gracza w sekundach (domyślny czas to 10 min i boty zostały w większości napisane z myślą o tym czasie)

`-randomfen` - wystartuj grę z w miarę równej pozycji, ale nie początkowej. Służy do wielokrotnej gry między botami, które są deterministyczne

`-nv` - włącz walkę botów bez wizualizacji

Przykład: `python run_duel.py -pve 1000101bot -time=600 -fen="r1bqkb1r/pppp1ppp/2n2n2/4p3/4P3/2N2N2/PPPP1PPP/R1BQKB1R w KQkq - 0 1"` - zawalcz z botem o nazwie 1000101bot gdzie każdy gracz ma 10 minut, a startowy fen jest podany.

Framework posiada opcję gry online należy wtedy wywołać program run_duel z:
"-online" - potrzebna flaga kiedy chce się tworzyć grę online lub do niej dołączać
"-host" - jeżeli jesteś graczem który hostuje serwer
"-player" - jeżeli chcesz grać samemu (a nie bot)
"-ngrok" - flaga do której można wpisać w formacie: "adres_ip:port" i łączy wtedy clienta z odpowiednim serwerem

Przykład użycia:
1. osoba: python run_duel.py -host -player -online
2. osoba: python run_duel.py -player -online -ngrok="0.0.0.0:12345"

Spowoduje to utworzenie gry online, gdzie obaj gracze robią sami ruchy. Client łączy się z ip: 0.0.0.0 i portem: 12345

Plik run_duel.py służy do menage'owania frameworkiem i wczytująć się w kod można rozwiać swoje niektóre wątpliwości.
Po więcej informacji można wpisać: python run_duel.py --help

# Dostępne boty

## bot_jana_2
Bot napisany przez Jana Zbrockiego wykonujcy losowe ruchy.
## bot_jana_1_lepszy
Bot napisany przez Jana Zbrockiego i Kubę Walęgę. Wykonuje losowe ruchy, ALE: unika pata, jeśli może to bije, pcha piony. Regularnie wygrywa z losowym. 
## snakeOrginal
Bot napisany w Pythonie przez Cypriana Ziółkowskiego z własną biblioteczką szachową (obsługującą wykonywanie, cofanie i generaję ruchów). Używa alpha-beta pruning i spamiętywania ewaluacji pozycji za pomocą Zobrist hashing. Okazął się za wolny by obsługiwać na początku gry głębokość 4, zatem działa na głębokości 2 i jest dość słaby. W końcówce radzi sobie z głębokością 4 i jest w stanie matować królem i wieżą, bądź królową.
## snakeGood
Bot napisany w Pythonie przez Cypriana Ziółkowskiego. Jest to wersja snakeOriginal używająca biblioteki pythonowej chess. Używa alpha-beta pruning i spamiętywania ewaluacji pozycji za pomocą Zobrist hashing. Obsługuje przez całą grę głębokość 4 i jest całkiem solidny. W końcówce jest w stanie matować królem i wieżą, bądź królową.
## heurabot
Bot napisany przez Kubę Walęgę używający biblioteki pythonowej chess. Obsługuje głębokość 2 (na 4 jest nieco za wolny). Jest dość słaby ale regularnie wygrywa z losowym.
## 1000101bot - jako, że jest on napisany w C++, to należy go skompilować
Kod źródłowy znajduje się w folderze "silnik_szachowy".
Aby skompilować program, należy wpisać polecenie: "g++ -O3 main.cpp funkcje.cpp -o main.exe" (nie należy zmieniać nazwy main.exe na inną).
Następnie plik "main.exe" należy przenieść do folderu 1000101bot znajdującego się w folderze boty.
W pliku main.cpp można modyfikować parametry silnika szachowego.
Zalecane wartości dla partii 10-minutowej:
glebokoscaktualna = 4;
glebokoscsrodkowa = 4;
glebokosckoncowa  = 6;
Zalecane wartości dla partii krótszych, ale nie krótszych niż minuta:
glebokoscaktualna = 4;
glebokoscsrodkowa = 4;
glebokosckoncowa = 4;
Program posiada:
- przesuwanie figur
- własną generację ruchów
- konwersję fen na szachownicę
- własną wizualizację przydatną do debugowania
- heurystyczną ewaluację pozycji
- hasze (Zobrist)
- przeszukiwanie alfa-beta