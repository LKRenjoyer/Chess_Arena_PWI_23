#include "funkcje.h"

string pozycja_startowa = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

/*
int licz = 0;
int pom;

void coss(pozycja poz, int gl) {
    if(gl == pom) {
        licz++;
        return;
    }
    vector <string> ruchy = mozliwe_ruchy(&poz);
    for(int i = 0; i < ruchy.size(); i++) {
        pozycja k = poz;
        porusz(ruchy[i], &k);
        coss(k, gl+1);
    }
}
*/

int main() {
    //pom = 5;
    //cin >> pom;
    long long Zobrist1[12][64];
    long long Zobrist2[13];
    string fen; //= pozycja_startowa;
    getline(cin, fen);
    pozycja poz;
    fen_to_chessboard(fen, &poz);
    //coss(poz, 0);
    //cout << licz;
    vector <string> v = mozliwe_ruchy(&poz);
    cout << v.size() <<"\n";
    /*for(int i = 0; i < v.size(); i++) {
        cout << v[i] <<'\n';
    }*/
    //cout << poz.czy_bicie_w_przelocie << ' ' << poz.wiersz_bwp << ' ' << poz.kolumna_bwp << '\n';
    //wizualizacja(&poz);
    
    /*
    while(true) {
        string ruch;
        cin >> ruch;
        porusz(ruch, &poz);
        vector <string> v = mozliwe_ruchy(&poz);
        wizualizacja(&poz);
        cout << "liczba mozliwych ruchow to: " << v.size() << '\n';
        //for(int i = 0; i < v.size(); i++) {
        //    cout << v[i] << '\n';
        //}
    }
    */
    //los1(10000,99999,Zobrist1);
    //los2(10000,99999,Zobrist2);
    //cout<<"\n"<<poz.czy_bicie_w_przelocie;
    return 0;
}
