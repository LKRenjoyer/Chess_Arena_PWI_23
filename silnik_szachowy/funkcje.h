#pragma GCC optimize("O3","unroll-loops")

#include <iostream>
#include <vector>
#include <iomanip>
#include <random>   
#include <unistd.h>
#include <algorithm>
#include <iterator>
#include <unordered_map>
#include <map>

#define pb push_back
#define st first
#define nd second

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_GREEN   "\x1b[32m"

using namespace std;

extern char kolor_bota;
extern string najlepszy_ruch;
extern int glebokoscaktualna;
extern int glebokoscsrodkowa;
extern int glebokosckoncowa;
//Zobrist hashing
extern long long tab1[12][64];
extern long long tab2[13];
extern long long tab3[12][64];
extern long long tab4[13];

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
double ewaluacja_pozycji(pozycja *poz);
bool czy_w_planszy(int i,int j);
string pole(int a,int b,int c,int d);
vector <string> mozliwe_ruchy(pozycja *poz);
void zmiana_glebokosci(pozycja *poz);

vector <int> pole_w_liczby(char bwp1,char bwp2);
long long Zobrist_hash_start(pozycja *poz);
long long Zobrist_hash_start2(pozycja *poz);
long long Zobrist_hash_ruch(string ruch,pozycja *poz,int hash);
bool czy_pat(pozycja *poz,int licznik1,int licznik2,int hash1,int hash2);
bool czy_mat(pozycja *poz);

void czysc();
double alphaBetaMax(pozycja stan, double alpha, double beta, int glebokosc);
double alphaBetaMin(pozycja stan, double alpha, double beta, int glebokosc);
