#include "funkcje.h"

string pozycja_startowa = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

bool czy_jestesmy_bialymi;
string najlepszy_ruch;
int glebokoscstartowa;

int main() {
    czy_jestesmy_bialymi = 1;
    najlepszy_ruch = "";
    glebokoscstartowa = 4;

    string fen = pozycja_startowa;
    pozycja poz;
    fen_to_chessboard(fen, &poz);
    wizualizacja(&poz);
    while(true) {
        string ruch;
        cin >> ruch;
        porusz(ruch, &poz);
        alpha_beta(poz, glebokoscstartowa, -10000, 10000, 1);
        porusz(najlepszy_ruch, &poz);
        wizualizacja(&poz);
    }

    return 0;
}