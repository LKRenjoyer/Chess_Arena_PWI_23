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
struct position{ 
    char board[8][8] = {}; 
    char mover = ' '; 
    bool poss_Q = 0, poss_K = 0, poss_q = 0, poss_k = 0;
    bool en_passant = 0; 
    char row_enpas = ' ', col_enpas= ' '; 
    int halfmoves_amo = 0, moves_amo = 0; 
};  

//
string fen_from_position(position* pos){ 
    return " "; 
} 

position position_from_fen(string fen){ 
    position pos; 
    return pos; 
}

ll position_hash(position* pos){ 
    return 0; 
}

void make_move(string move, position* pos){ 

} 

bool position_checked(int a, int b, char color, position *pos){ // czy pole borard[a][b] jest szachowane przez bierki koloru color

} 
