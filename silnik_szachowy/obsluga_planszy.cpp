#include <iostream>

using namespace std;

/* 

format planszy:

 1 2 3 4 5 6 7 8 
a
b
c
d
e
f
g
h

nazewnictwo figur:

mała litera - czarne
duża litera - białe
pion    - P 
skoczek - N
goniec  - B
wieża   - R
hetman  - Q
król    - K

czyj ruch:

białe  - w
czarne - b

możliwe roszady:

czy_Q - biała skrzydło hetmańskie
czy_K - biała skrzydło królewskie
czy_q - czarna skrzydło hetmańskie
czy_k - czarna skrzydło królewskie 

Liczba połówek ruchów - Tutaj się notuje liczbę posunięć (jeden ruch to dwa posunięcia figur) od ostatniego bicia albo posunięcia piona. Służy do implementacji „zasady 50 posunięć”.
Liczba pełnych ruchów -  czyli pełny cykl, posunięcie figury białych oraz posunięcie figury czarnych tworzy jeden ruch.
*/

string pozycja_startowa = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
char plansza[8][8];
char czyj_ruch; 
bool czy_Q, czy_K, czy_q, czy_k;
bool czy_bicie_w_przelocie;
char wiersz_bwp, kolumna_bwp;
int liczba_polowek_ruchow, liczba_ruchow;

void fen_to_chessboard(string fen) {
    for(int i = 0; i <= 7; i++) {
        for(int ii = 0; ii <= 7; ii++) {
            plansza[i][ii] = ' ';
        }
    }
    int x = 0;
    for(int i = 7; i >= 0; i--) {
        for(int ii = 0; ii <= 20; ii++) {
            if(fen[x] == '/' || fen[x] == ' ') {
                x++;
                break;
            }
            else if(fen[x] >= '1' && fen[x] <= '9') {
                ii += (fen[x] - '0') - 1;
                x++;
            }
            else {
                plansza[i][ii] = fen[x];
                x++;
            }
        }
    }
    czyj_ruch = fen[x];
    x += 2;
    while(fen[x] != ' ') {
        if(fen[x] == 'K') {
            czy_K = 1;
        }
        else if(fen[x] == 'Q') {
            czy_Q = 1;
        }
        else if(fen[x] == 'k') {
            czy_k = 1;
        }
        else if(fen[x] == 'q'){
            czy_q = 1;
        }
        x++;
    }
    x++;
    if(fen[x] == '-') {
        x += 2;
    }
    else {
        czy_bicie_w_przelocie = 1;
        wiersz_bwp = fen[x];
        x++;
        kolumna_bwp = fen[x];
        x += 2;
    }
    string pom = "";
    while(fen[x] != ' ') {
        pom += fen[x];
        x++;
    }
    liczba_polowek_ruchow = stoi(pom);
    x++;
    pom = "";
    while(x < (int)fen.size()) {
        pom += fen[x];
        x++;
    }
    liczba_ruchow = stoi(pom);
}

void wizualizacja() {
    cout << '\n';
    cout << '*';
    for(int i = 0; i < 16; i++) {
        cout << '-';
    }
    cout << '*' << '\n';
    for(int i = 7; i >= 0; i--) {
        cout << '|';
        for(int ii = 0; ii < 8; ii++) {
            cout << plansza[i][ii] << ' ';
        }
        cout << '|';
        cout << '\n';
    }
    cout << '*';
    for(int i = 0; i < 16; i++) {
        cout << '-';
    }
    cout << '*' << '\n';
    cout << '\n';
    cout << "czyj ruch: " << czyj_ruch << '\n';
    cout << "możliwe roszady: " << (czy_K ? "K" : "") << (czy_Q ? "Q" : "") << (czy_k ? "k" : "") << (czy_q ? "q" : "") << '\n';
    cout << "czy mozliwe bicie w przelocie: " << (czy_bicie_w_przelocie ? "TAK " : "NIE ") << (czy_bicie_w_przelocie ? wiersz_bwp : ' ') << (czy_bicie_w_przelocie ? kolumna_bwp : ' ') << '\n';
    cout << "liczba_polowek_ruchow: " << liczba_polowek_ruchow << '\n';
    cout << "liczba_ruchow: " << liczba_ruchow << '\n'; 
}

int main() {
    string fen = pozycja_startowa;
    getline(cin, fen);
    fen_to_chessboard(fen);
    wizualizacja();

    return 0;
}