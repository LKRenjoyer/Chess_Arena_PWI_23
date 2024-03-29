#include "funkcje.h"

string pozycja_startowa = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

char kolor_bota;
string najlepszy_ruch;
int glebokoscaktualna;
int glebokoscsrodkowa;
int glebokosckoncowa;
//rzeczy do hashowania
long long tab1[12][64];
long long tab2[13];
long long tab3[12][64];
long long tab4[13];
//koniec rzeczy do hashowania

int main(int argc, char ** argv) {
    kolor_bota = argv[1][0];
    najlepszy_ruch = "";
    glebokoscaktualna = 4;
    glebokoscsrodkowa = 4;
    glebokosckoncowa = 6;
    string fen = argv[2];
    pozycja poz;
    fen_to_chessboard(fen, &poz);
    //tabelki hashy
    mt19937_64 gen(getpid());
    long long a = 100000000000000LL;
    long long b = 999999999999999LL;
    for (int i = 0; i < 12; i++) 
        for (int j = 0; j < 64; j++)
            tab1[i][j] = gen();
    for (int i = 0; i < 13; i++)
        tab2[i] = gen();
    for (int i = 0; i < 12; i++) 
        for (int j = 0; j < 64; j++)
            tab3[i][j] = gen();
    for (int i = 0; i < 13; i++)
        tab4[i] = gen();
    //koniec tabelek hashy

    while(1) {
        if(poz.czyj_ruch == kolor_bota) {
            czysc();
            alphaBetaMax(poz, (double)-100000000, (double)100000000, glebokoscaktualna);
            porusz(najlepszy_ruch, &poz);
            if(najlepszy_ruch.size() == 5 && najlepszy_ruch[4] >= 'A' && najlepszy_ruch[4] <= 'Z') {
                najlepszy_ruch[4] -= ('A' - 'a');
            }
            if(najlepszy_ruch.size() < 3) {
                fprintf(stderr, "blad");
            }
            fprintf(stderr, "%c%c%c%c\n", najlepszy_ruch[0], najlepszy_ruch[1], najlepszy_ruch[2], najlepszy_ruch[3]);
            cout << najlepszy_ruch << endl;
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
