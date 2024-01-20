#include "funkcje.h"

string pozycja_startowa = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

char kolor_bota;
string najlepszy_ruch;
int glebokoscaktualna;
int glebokoscsrodkowa;
int glebokosckoncowa;

int main() {
    kolor_bota = 'b';
    najlepszy_ruch = "";
    glebokoscaktualna = 4;
    glebokoscsrodkowa = 5;
    glebokosckoncowa = 6;

    string fen = pozycja_startowa;
    pozycja poz;
    fen_to_chessboard(fen, &poz);
    wizualizacja(&poz);
    while(1) {
        string ruch;
        cin >> ruch;
        porusz(ruch, &poz);
        wizualizacja(&poz);
        zmiana_glebokosci(&poz);
        alpha_beta(poz, glebokoscaktualna, -10000000, 10000000, 1);
        porusz(najlepszy_ruch, &poz);
        wizualizacja(&poz);
        zmiana_glebokosci(&poz);
    }

    return 0;
}