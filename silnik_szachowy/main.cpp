#include "funkcje.h"

string pozycja_startowa = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

int main() {
    string fen = pozycja_startowa;
    //getline(cin, fen);
    pozycja poz;
    fen_to_chessboard(fen, &poz);
    wizualizacja(&poz);
    while(true) {
        string ruch;
        cin >> ruch;
        if(ruch.size() == 1) {
            break;
        }
        porusz(ruch, &poz);
        wizualizacja(&poz);
    }

    return 0;
}