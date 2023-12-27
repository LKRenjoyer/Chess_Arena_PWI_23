#include<bits/stdc++.h>

#define st first
#define nd second
#define pb(x) push_back(x)
#define pp(x) pop_back(x)
#define mp(a, b) make_pair(a, b)
#define all(x) (x).begin(), (x).end()
#define rev(x) reverse(all(x))
#define sor(x) sort(all(x))
#define sz(x) (int)(x).size()
#define rsz(x) resize(x)

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<pii > vii;
typedef vector<ll> vl;
typedef vector<pll> vll;
typedef string str;
#define BOOST ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL); 

// 
struct position {
    char board[8][8] = {};
    char mover = ' ';
    bool poss_Q = 0, poss_K = 0, poss_q = 0, poss_k = 0;
    bool en_passant = 0;
    char row_enpas = ' ', col_enpas = ' ';
    int halfmoves_amo = 0, moves_amo = 0;
};

//
string fen_from_position(position* pos) {
    return " ";
}

position position_from_fen(string fen) {
    position pos;
    return pos;
}

ll position_hash(position* pos) {
    return 0;
}

void make_move(string move, position* pos) {
    pii st_kord, en_kord, bicie_kord = {-1,-1};
    char przemiana = '';
    char typ_figury='';
    char kon = move[move.size() - 1];
    if ('a' <= kon && kon <= 'z')przemiana = kon;
    if ('A' <= kon && kon <= 'Z')przemiana = kon;
    pos->row_enpas = '';
    pos->col_enpas = '';
    if (move=='O-O'){
        if (pos->mover == 'W') {
            pos->board[7][4] = ' '; 
            pos->board[7][5] = 'R';
            pos->board[7][6] = 'K';
            pos->board[7][7] = ' ';
            poss_Q = 1; poss_K = 1;
        }
        else {
            pos->board[0][4] = ' ';
            pos->board[0][5] = 'r';
            pos->board[0][6] = 'k';
            pos->board[0][7] = ' ';
            poss_q = 1; poss_k = 1;
        }
        pos->halfmoves_amo++;
        if (pos->mover == 'W')pos->mover = 'b';
        else { pos->mover = 'W'; pos->moves_amo++; }
        return;
    }
    //roszady krótkie
    if (move == 'O-O-O') {
        if (pos->mover == 'W') {
            pos->board[7][0] = ' ';
            pos->board[7][1] = ' ';
            pos->board[7][2] = 'K';
            pos->board[7][3] = 'R';
            pos->board[7][4] = ' ';
            poss_Q = 1; poss_K = 1;
        }
        else {
            pos->board[0][0] = ' ';
            pos->board[0][1] = ' ';
            pos->board[0][2] = 'k';
            pos->board[0][3] = 'r';
            pos->board[0][4] = ' ';
            poss_q = 1; poss_k = 1;
        }
        pos->halfmoves_amo++;
        if (pos->mover == 'W')pos->mover = 'b';
        else { pos->mover = 'W'; pos->moves_amo++; }
        return;
    }
    //roszady d³ugie
    st_kord = {s[0]-'0',s[1]-'0'};
    en_kord = {s[2]-'0',s[3]-'0'};
    if (move.size() > 5)bicie_kord = {s[4]-'0',s[5] - '0'};
    typ_figury = pos->board[st_kord.st][st_kord.nd];
    if (bicie_kord.st >= 0 || typ_figury == 'p' || typ_figury == 'P')pos->halfmoves_amo = -1; 
    pos->halfmoves_amo++;
    //rozwa¿enie pó³ruchów (czy ruch pionkiem lub czy bicie)
    if (st_kord == {0, 0} || en_kord = { 0,0 })poss_q = 1; 
    if (st_kord == {7, 0} || en_kord = { 7,0 })poss_k = 1;
    if (st_kord == {7, 7} || en_kord = { 7,7 })poss_K = 1;
    if (st_kord == {0, 7} || en_kord = { 0,7 })poss_Q = 1;
    if (typ_figury == 'K') { poss_K = 1; poss_Q = 1; }
    if (typ_figury == 'k') { poss_k = 1; poss_q = 1; }
    //sprawdzenie roszad
    if (abs(st_kord.nd - en_kord.nd) == 2 && (typ_figury == 'p' || typ_figury == 'P')) {
        char sasiad = '';
        if (w_planszy(en_kord.st - 1, en_kord.nd))sasiad = pos->board[en_kord.st - 1][en_kord.nd];
        if ((sasiad == 'p' || sasiad == 'P') && sasiad != typ_figury) { col_enpas = st_kord.st; row_enpas = (st_kord.nd + en_kord.nd) / 2; }
        if (w_planszy(en_kord.st + 1, en_kord.nd))sasiad = pos->board[en_kord.st + 1][en_kord.nd];
        if ((sasiad == 'p' || sasiad == 'P') && sasiad != typ_figury) { col_enpas = st_kord.st; row_enpas = (st_kord.nd + en_kord.nd) / 2; }
    }
    //sprawdzenie en-passant
    if (przemiana != '')typ_figury = przemiana; 
    // jesli jest promocja to zmien typ figury
    pos->board[st_kord.st][st_kord.nd] = ' ';
    if (bicie_kord.st >= 0)pos->board[bicie_kord.st][bicie_kord.nd] = ' ';
    pos->board[en_kord.st][en_kord.nd] = przemiana;
    //wykonanie ruchu + zrobienie bicia
    if (pos->mover == 'W')pos->mover = 'b';
    else { pos->mover = 'W'; pos->moves_amo++; }
    //zmiana strony dodanie cyklu
}

bool position_checked(int a, int b, char color, position* pos) {
    int x_kon[8] = { 1,2,2,1,-1,-2,-2,-1 };
    int y_kon[8] = { -2,-1,1,2,2,1,-1,-2 };
    if (color == 'W') {
        for (int i = 0; i < 8; i++) {            //szach czarnym koniem
            int akt_x = a + x_kon[i], akt_y = b + y_kon[i];
            if (!w_planszy[akt_x][akt_y])continue;
            if (pos->board[akt_x][akt_y] == 'n')return 1;
        }
        if ((w_planszy(a - 1, b - 1) && pos->board[a - 1][b - 1] == 'p') || (w_planszy(a - 1, b + 1) && pos->board[a - 1][b + 1] == 'p'))return 1; //szach czarnym pionem
        //lewo
        for (int i = a; i >= 0; i--) {
            if (pos->board[i][b] == ' ')continue;
            if (pos->board[i][b] == 'r' || pos->board[i][b] == 'q')return 1;
            break;
        }
        //prawo
        for (int i = a; i < 8; i++) {
            if (pos->board[i][b] == ' ')continue;
            if (pos->board[i][b] == 'r' || pos->board[i][b] == 'q')return 1;
            break;
        }
        //góra
        for (int i = b; i >= 0; i--) {
            if (pos->board[a][i] == ' ')continue;
            if (pos->board[a][i] == 'r' || pos->board[a][i] == 'q')return 1;
            break;
        }
        //dó³
        for (int i = b; i < 8; i++) {
            if (pos->board[a][i] == ' ')continue;
            if (pos->board[a][i] == 'r' || pos->board[a][i] == 'q')return 1;
            break;
        }
        //lewo-góra
        for (int i = 1; a - i >= 0 && b - i >= 0; i++) {
            if (pos->board[a - i][b - i] == ' ')continue;
            if (pos->board[a - i][b - i] == 'q' || pos->board[a - i][b - i] == 'b')return 1;
        }
        //prawo-góra
        for (int i = 1; a - i >= 0 && b + i < 8; i++) {
            if (pos->board[a - i][b + i] == ' ')continue;
            if (pos->board[a - i][b + i] == 'q' || pos->board[a - i][b + i] == 'b')return 1;
        }
        //lewo-dó³
        for (int i = 1; a + i < 8 && b - i >= 0; i++) {
            if (pos->board[a + i][b - i] == ' ')continue;
            if (pos->board[a + i][b - i] == 'q' || pos->board[a + i][b - i] == 'b')return 1;
        }
        //prawo-dó³
        for (int i = i; a + i < 8 && b + i < 8; i++) {
            if (pos->board[a + i][b + i] == ' ')continue;
            if (pos->board[a + i][b + i] == 'q' || pos->board[a + i][b + i] == 'b')return 1;
        }
    }
    if (color == 'b') {
        for (int i = 0; i < 8; i++) {            //szach bia³ym koniem
            int akt_x = a + x_kon[i], akt_y = b + y_kon[i];
            if (!w_planszy[akt_x][akt_y])continue;
            if (pos->board[akt_x][akt_y] == 'N')return 1;
        }
        if ((w_planszy(a + 1, b - 1) && pos->board[a + 1][b - 1] == 'P') || (w_planszy(a + 1, b + 1) && pos->board[a + 1][b + 1] == 'P'))return 1; //szach bia³ym pionem
        //lewo
        for (int i = a; i >= 0; i--) {
            if (pos->board[i][b] == ' ')continue;
            if (pos->board[i][b] == 'R' || pos->board[i][b] == 'Q')return 1;
            break;
        }
        //prawo
        for (int i = a; i < 8; i++) {
            if (pos->board[i][b] == ' ')continue;
            if (pos->board[i][b] == 'R' || pos->board[i][b] == 'Q')return 1;
            break;
        }
        //góra
        for (int i = b; i >= 0; i--) {
            if (pos->board[a][i] == ' ')continue;
            if (pos->board[a][i] == 'R' || pos->board[a][i] == 'Q')return 1;
            break;
        }
        //dó³
        for (int i = b; i < 8; i++) {
            if (pos->board[a][i] == ' ')continue;
            if (pos->board[a][i] == 'R' || pos->board[a][i] == 'Q')return 1;
            break;
        }
        //lewo-góra
        for (int i = 1; a - i >= 0 && b - i >= 0; i++) {
            if (pos->board[a - i][b - i] == ' ')continue;
            if (pos->board[a - i][b - i] == 'Q' || pos->board[a - i][b - i] == 'B')return 1;
        }
        //prawo-góra
        for (int i = 1; a - i >= 0 && b + i < 8; i++) {
            if (pos->board[a - i][b + i] == ' ')continue;
            if (pos->board[a - i][b + i] == 'Q' || pos->board[a - i][b + i] == 'B')return 1;
        }
        //lewo-dó³
        for (int i = 1; a + i < 8 && b - i >= 0; i++) {
            if (pos->board[a + i][b - i] == ' ')continue;
            if (pos->board[a + i][b - i] == 'Q' || pos->board[a + i][b - i] == 'B')return 1;
        }
        //prawo-dó³
        for (int i = i; a + i < 8 && b + i < 8; i++) {
            if (pos->board[a + i][b + i] == ' ')continue;
            if (pos->board[a + i][b + i] == 'Q' || pos->board[a + i][b + i] == 'B')return 1;
        }
    }
    return 0;
}
