#include <iostream>
#include <vector>

#define pb push_back
#define st first
#define nd second

using namespace std;

struct pozycja {
    char plansza[8][8] = {};
    char czyj_ruch = ' '; 
    bool czy_Q = 0, czy_K = 0, czy_q = 0, czy_k = 0;
    bool czy_bicie_w_przelocie = 0;
    char wiersz_bwp = ' ', kolumna_bwp = ' ';
    int liczba_polowek_ruchow = 0, liczba_ruchow = 0;
};

void porusz(string ruch, pozycja *poz);
bool czy_pole_jest_szachowane(int y, int x, char kolor, pozycja *poz);
void fen_to_chessboard(string fen, pozycja *poz);
void wizualizacja(pozycja *poz);
long double ewaluacja_pozycji(pozycja *poz);
bool czy_w_planszy(int i,int j);
string pole(int a,int b,int c,int d);
vector <string> mozliwe_ruchy(pozycja *poz);
