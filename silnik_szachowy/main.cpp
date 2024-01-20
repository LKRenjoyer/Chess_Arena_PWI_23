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
    glebokoscsrodkowa = 4;
    glebokosckoncowa = 5;
    string fen = argv[2];
    pozycja poz;
    fen_to_chessboard(fen, &poz);

    while(1) {
        if(poz.czyj_ruch == kolor_bota) {
            alpha_beta(poz, glebokoscaktualna, -10000000, 10000000, 1);
            porusz(najlepszy_ruch, &poz);
            if(najlepszy_ruch.size() == 5 && najlepszy_ruch[4] >= 'A' && najlepszy_ruch[4] <= 'Z') {
                najlepszy_ruch[4] -= ('A' - 'a');
            }
            cout << najlepszy_ruch << "\n";
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