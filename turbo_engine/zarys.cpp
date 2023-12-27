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
    char row_enpas = ' ', col_enpas= ' '; // opisuje pole 'za' pionem, ktorego mozna zbic uzywajac en passant, czyli pole docelowe potencjalnego ruchu enpassant
    int halfmoves_amo = 0; // liczba posuniec figurami bez zbicia, liczona do reguly remisu po 50 
    int moves_amo = 0; // liczba zwyklych ruchow
};  

// 
string number_text(int x){ 
    if(x == 0) 
        return "0"; 
    string ans = ""; 
    int dziel = 100000; 
    while(dziel){ 
        if(x/dziel) 
            ans += (char)('0'+x/dziel);  
        else if(sz(ans)) 
            ans +='0'; 
        x= x%dziel; 
        dziel /= 10; 
    }
    return ans; 
}

string fen_from_position(position* pos){ 
    string ans; int buf = 0;
    ans.reserve(30);   
    for(int i = 0; i <8; i++){ 
        for(int j = 0; j <7; j++){ 
            if(pos->board[i][j] != ' '){
                if(buf){ 
                    ans += (char)(buf + '0'); 
                    buf=0; 
                }  
                ans += pos->board[i][j]; 
            }
            else{ 
                buf++; 
            }
        } 
        if(buf){ 
            ans += (char)(buf+'0'); 
            buf = 0; 
        }  
        if(i != 7)
        ans += '/' ; 
    }
    if(pos->mover == 'W') 
        ans += " w "; 
    else 
        ans += " b "; 
    if(!(pos->poss_K || pos->poss_Q || pos->poss_k || pos->poss_q)) 
        ans += "- "; 
    else { 
        if(pos->poss_K) ans += 'K'; 
        if(pos->poss_Q) ans += 'Q'; 
        if(pos->poss_k) ans += 'k'; 
        if(pos->poss_q) ans += 'q'; 
        ans += ' ';  
    } 
    if(!pos->en_passant) 
        ans += "- ";  
    else { 
        ans += (char)('a' + pos->col_enpas); 
        ans += (char)('8' - pos->row_enpas);  
        ans += ' '; 
    }  
    ans += number_text(pos->halfmoves_amo); 
    ans += ' '; 
    ans += number_text(pos->moves_amo); 
    // partia moze miec najdluzej 8848.5 ruchow
    return ans; 
} 

void visualize(position* pos){ 
    for(int i = 0; i < 8; i++){ 
        for(int j = 0; j < 8; j++) 
            cout << pos->board[i][j]; 
        cout << "\n"; 
    }
    cout << "ruch: " << pos->mover << "\n";  
    cout << "roszada K: " << pos->poss_K << " roszada Q: " << pos->poss_Q << "\n"; 
    cout << "roszada k: " << pos->poss_k << " roszada q: " << pos->poss_q << "\n"; 
    cout << "enpassant " << (pos->en_passant)? "TAK ":"NIE "; 
    if(pos->en_passant) cout << pos->row_enpas << " "<< pos->col_enpas << " (" << (char)('a' + pos->col_enpas) << (char)('8' - pos->row_enpas) << ") " << "\n"; 
    else cout << "\n";   
    cout << "nudy-posuniecia: " << pos->halfmoves_amo << "\n"; 
    cout << "pelne ruchy: " << pos->moves_amo << "\n"; 
    cout << "\n"; 
}
position position_from_fen(string fen){ 
    position pos; 
    int ind = 0; char endchar; int wsk; 
    for(int i = 0; i < 8; i++){ 
        wsk = 0; 
        if(i <7) endchar = '/'; 
        else endchar = ' '; 
        while(fen[ind] != endchar){ 
            if(fen[ind] > '9' || fen[ind] < '0') 
                pos.board[i][wsk++] = fen[ind++]; 
            else {
                for(char i = '0'; i < fen[ind]; i++) 
                    pos.board[i][wsk++] = ' '; 
                ind++; 
            } 
        }
    }
    ind++; 
    pos.mover = fen[ind]; 
    if(pos.mover == 'w') 
        pos.mover == 'W'; 
    ind++; ind++;  // spacja
    pos.poss_K=0; pos.poss_Q = 0; pos.poss_k = 0; pos.poss_q =0;
    if(fen[ind] == '-'){
        1+2; // nic nie rob
    } 
    else 
    { 
        while(fen[ind] != ' '){ 
            if(fen[ind] == 'K')pos.poss_K=1; 
            if(fen[ind] == 'Q')pos.poss_Q = 1;
            if(fen[ind] == 'k')pos.poss_k = 1; 
            if(fen[ind++] == 'q')pos.poss_q =1; 
        }
    }
    ind++; 
    if(fen[ind] == '-'){ 
        pos.en_passant =0; 
        pos.row_enpas = -1; 
        pos.col_enpas = -1;
    } 
    else 
    { 
        pos.en_passant = 1; 
        pos.col_enpas = fen[ind] - 'a'; 
        ind++; 
        pos.row_enpas = '8' - fen[ind];  
        ind++; 
    } 
    ind++; 
    pos.halfmoves_amo = 0;  
    while(fen[ind] != ' '){ 
        pos.halfmoves_amo *= 10; 
        pos.halfmoves_amo += fen[ind++]-'0'; 
    } 
    fen += ' '; ind++; 
    pos.moves_amo = 0; 
    while(fen[ind] != ' '){ 
        pos.moves_amo *= 10; 
        pos.moves_amo += fen[ind++]-'0'; 
    } 
    return pos; 
}

ll position_hash(position* pos){ 
    return 0; 
}

void make_move(string move, position* pos){ 

} 

bool position_checked(int a, int b, char color, position *pos){ // czy pole borard[a][b] jest szachowane przez bierki koloru color

} 
