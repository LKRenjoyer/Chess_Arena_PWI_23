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
