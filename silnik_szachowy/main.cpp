#include "funkcje.h"

string pozycja_startowa = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

char kolor_bota;
string najlepszy_ruch;
int glebokoscaktualna;
int glebokoscsrodkowa;
int glebokosckoncowa;

int main(int argc, char ** argv) {
    kolor_bota = argv[1][0];
    najlepszy_ruch = "";
    glebokoscaktualna = 4;
    glebokoscsrodkowa = 5;
    glebokosckoncowa = 6;
    string fen = argv[2];
    pozycja poz;
    fen_to_chessboard(fen, &poz);

    while(1) {
        //wizualizacja(&poz);

        if(poz.czyj_ruch == kolor_bota) {
            alpha_beta(poz, glebokoscaktualna, -10000000, 10000000, 1);
            porusz(najlepszy_ruch, &poz);
            zmiana_glebokosci(&poz);
        }
        else {
            string ruch_przeciwnika;
            cin >> ruch_przeciwnika;
            porusz(ruch_przeciwnika, &poz);
            zmiana_glebokosci(&poz);
        }
        //konczenie programu
        vector <string> ruchy = mozliwe_ruchy(&poz);
        if(ruchy.size() == 0)
            break;
    }

    

    return 0;
}