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
        for(int j = 0; j <8; j++){ 
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
    cout << "*--------*\n"; 
    for(int i = 0; i < 8; i++){ 
        cout << '|';  
        for(int j = 0; j < 8; j++){
            if(pos->board[i][j] == ' ') 
                cout << '.'; 
            else
                cout << pos->board[i][j]; 
        }
        cout << "|\n"; 
    } 
    cout << "*--------*\n"; 
    cout << "ruch: " << pos->mover << "\n";  
    cout << "roszada K: " << pos->poss_K << " roszada Q: " << pos->poss_Q << "\n"; 
    cout << "roszada k: " << pos->poss_k << " roszada q: " << pos->poss_q << "\n"; 
    cout << "enpassant " << (pos->en_passant ? "TAK " : "NIE") << " ";
    if(pos->en_passant) cout << (int)pos->row_enpas << " "<< (int)pos->col_enpas << " (" << (char)('a' + pos->col_enpas) << (char)('8' - pos->row_enpas) << ") " << "\n"; 
    else cout << "\n";   
    cout << "nudy-posuniecia: " << pos->halfmoves_amo << "\n"; 
    cout << "pelne ruchy: " << pos->moves_amo << "\n"; 
    cout << "\n"; 
}

void where(int ind){  // funkcja czysto w celu debugu
    for(int i =0; i < ind; i++) 
            cout << ' '; 
    cout << "^\n"; 
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
            else 
            {
                for(char j = '0'; j < fen[ind]; j++) 
                    pos.board[i][wsk++] = ' '; 
                ind++; 
            } 
        } 
        ind++; 
    } 
    //where(ind);   
    pos.mover = fen[ind]; 
    if(pos.mover == 'w') 
        pos.mover = 'W'; 
    ind++; ind++;  // spacja
    pos.poss_K=0; pos.poss_Q = 0; pos.poss_k = 0; pos.poss_q =0;
    if(fen[ind] == '-'){
        1+2; // nic nie rob 
        ind++; 
    } 
    else 
    { 
        while(fen[ind] != ' '){ 
            if(fen[ind] == 'K')pos.poss_K=1; 
            if(fen[ind] == 'Q')pos.poss_Q = 1;
            if(fen[ind] == 'k')pos.poss_k = 1; 
            if(fen[ind++] == 'q')pos.poss_q =1; 
        } 
        //where(ind);  
    }
    ind++; 

    if(fen[ind] == '-'){ 
        pos.en_passant =0; 
        pos.row_enpas = -1; 
        pos.col_enpas = -1; 
        ind++; 
    } 
    else 
    { 
        pos.en_passant = 1; 
        pos.col_enpas = fen[ind] - 'a';  
        //for(int i =0; i < ind; i++) 
        //    cout << ' '; 
        //cout << "^\n"; 
        //cout << "|||||| \n" << (int)fen[ind] << "\n||||||| \n";  
        ind++; 
        pos.row_enpas = '8' - fen[ind];   
        ind++; 
    }  
    //where(ind); 
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

ll position_hash(position* pos) {
    return 0;
}

void make_move(string move, position* pos) {
    /*pii st_kord, en_kord, bicie_kord = {-1,-1};
    char przemiana = ' ';
    char typ_figury=' ';
    char kon = move[move.size() - 1];
    if ('a' <= kon && kon <= 'z')przemiana = kon;
    if ('A' <= kon && kon <= 'Z')przemiana = kon;
    pos->row_enpas = ' ';
    pos->col_enpas = ' ';
    if (move=="O-O"){
        if (pos->mover == 'W') {
            pos->board[7][4] = ' '; 
            pos->board[7][5] = 'R';
            pos->board[7][6] = 'K';
            pos->board[7][7] = ' ';
            pos->poss_Q = 1; pos->poss_K = 1;
        }
        else {
            pos->board[0][4] = ' ';
            pos->board[0][5] = 'r';
            pos->board[0][6] = 'k';
            pos->board[0][7] = ' ';
            pos->poss_q = 1; pos->poss_k = 1;
        }
        pos->halfmoves_amo++;
        if (pos->mover == 'W')pos->mover = 'b';
        else { pos->mover = 'W'; pos->moves_amo++; }
        return;
    }
    //roszady kr�tkie
    if (move == "O-O-O") {
        if (pos->mover == 'W') {
            pos->board[7][0] = ' ';
            pos->board[7][1] = ' ';
            pos->board[7][2] = 'K';
            pos->board[7][3] = 'R';
            pos->board[7][4] = ' ';
            pos->poss_Q = 1; pos->poss_K = 1;
        }
        else {
            pos->board[0][0] = ' ';
            pos->board[0][1] = ' ';
            pos->board[0][2] = 'k';
            pos->board[0][3] = 'r';
            pos->board[0][4] = ' ';
            pos->poss_q = 1; pos->poss_k = 1;
        }
        pos->halfmoves_amo++;
        if (pos->mover == 'W')pos->mover = 'b';
        else { pos->mover = 'W'; pos->moves_amo++; }
        return;
    }
    //roszady d�ugie
    st_kord = {s[0]-'0',s[1]-'0'};
    en_kord = {s[2]-'0',s[3]-'0'};
    if (move.size() > 5)bicie_kord = {s[4]-'0',s[5] - '0'};
    typ_figury = pos->board[st_kord.st][st_kord.nd];
    if (bicie_kord.st >= 0 || typ_figury == 'p' || typ_figury == 'P')pos->halfmoves_amo = -1; 
    pos->halfmoves_amo++;
    //rozwa�enie p�ruch�w (czy ruch pionkiem lub czy bicie)
    if (st_kord == {0, 0} || en_kord == { 0,0 })pos->poss_q = 1; 
    if (st_kord == {7, 0} || en_kord == { 7,0 })pos->poss_k = 1;
    if (st_kord == {7, 7} || en_kord == { 7,7 })pos->poss_K = 1;
    if (st_kord == {0, 7} || en_kord == { 0,7 })pos->poss_Q = 1;
    if (typ_figury == 'K') { pos->poss_K = 1; pos->poss_Q = 1; }
    if (typ_figury == 'k') { pos->poss_k = 1; pos->poss_q = 1; }
    //sprawdzenie roszad
    if (abs(st_kord.nd - en_kord.nd) == 2 && (typ_figury == 'p' || typ_figury == 'P')) {
        char sasiad = ' ';
        if (w_planszy(en_kord.st - 1, en_kord.nd))sasiad = pos->board[en_kord.st - 1][en_kord.nd];
        if ((sasiad == 'p' || sasiad == 'P') && sasiad != typ_figury) { pos->col_enpas = st_kord.st; pos->row_enpas = (st_kord.nd + en_kord.nd) / 2; }
        if (w_planszy(en_kord.st + 1, en_kord.nd))sasiad = pos->board[en_kord.st + 1][en_kord.nd];
        if ((sasiad == 'p' || sasiad == 'P') && sasiad != typ_figury) { pos->col_enpas = st_kord.st; pos->row_enpas = (st_kord.nd + en_kord.nd) / 2; }
    }
    //sprawdzenie en-passant
    if (przemiana != ' ')typ_figury = przemiana; 
    // jesli jest promocja to zmien typ figury
    pos->board[st_kord.st][st_kord.nd] = ' ';
    if (bicie_kord.st >= 0)pos->board[bicie_kord.st][bicie_kord.nd] = ' ';
    pos->board[en_kord.st][en_kord.nd] = przemiana;
    //wykonanie ruchu + zrobienie bicia
    if (pos->mover == 'W')pos->mover = 'b';
    else { pos->mover = 'W'; pos->moves_amo++; }
    //zmiana strony dodanie cyklu 
    */
}

bool position_checked(int a, int b, char color, position* pos) {
   /* int x_kon[8] = { 1,2,2,1,-1,-2,-2,-1 };
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
        //g�ra
        for (int i = b; i >= 0; i--) {
            if (pos->board[a][i] == ' ')continue;
            if (pos->board[a][i] == 'r' || pos->board[a][i] == 'q')return 1;
            break;
        }
        //d�
        for (int i = b; i < 8; i++) {
            if (pos->board[a][i] == ' ')continue;
            if (pos->board[a][i] == 'r' || pos->board[a][i] == 'q')return 1;
            break;
        }
        //lewo-g�ra
        for (int i = 1; a - i >= 0 && b - i >= 0; i++) {
            if (pos->board[a - i][b - i] == ' ')continue;
            if (pos->board[a - i][b - i] == 'q' || pos->board[a - i][b - i] == 'b')return 1;
        }
        //prawo-g�ra
        for (int i = 1; a - i >= 0 && b + i < 8; i++) {
            if (pos->board[a - i][b + i] == ' ')continue;
            if (pos->board[a - i][b + i] == 'q' || pos->board[a - i][b + i] == 'b')return 1;
        }
        //lewo-d�
        for (int i = 1; a + i < 8 && b - i >= 0; i++) {
            if (pos->board[a + i][b - i] == ' ')continue;
            if (pos->board[a + i][b - i] == 'q' || pos->board[a + i][b - i] == 'b')return 1;
        }
        //prawo-d�
        for (int i = i; a + i < 8 && b + i < 8; i++) {
            if (pos->board[a + i][b + i] == ' ')continue;
            if (pos->board[a + i][b + i] == 'q' || pos->board[a + i][b + i] == 'b')return 1;
        }
    }
    if (color == 'b') {
        for (int i = 0; i < 8; i++) {            //szach bia�ym koniem
            int akt_x = a + x_kon[i], akt_y = b + y_kon[i];
            if (!w_planszy[akt_x][akt_y])continue;
            if (pos->board[akt_x][akt_y] == 'N')return 1;
        }
        if ((w_planszy(a + 1, b - 1) && pos->board[a + 1][b - 1] == 'P') || (w_planszy(a + 1, b + 1) && pos->board[a + 1][b + 1] == 'P'))return 1; //szach bia�ym pionem
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
        //g�ra
        for (int i = b; i >= 0; i--) {
            if (pos->board[a][i] == ' ')continue;
            if (pos->board[a][i] == 'R' || pos->board[a][i] == 'Q')return 1;
            break;
        }
        //d�
        for (int i = b; i < 8; i++) {
            if (pos->board[a][i] == ' ')continue;
            if (pos->board[a][i] == 'R' || pos->board[a][i] == 'Q')return 1;
            break;
        }
        //lewo-g�ra
        for (int i = 1; a - i >= 0 && b - i >= 0; i++) {
            if (pos->board[a - i][b - i] == ' ')continue;
            if (pos->board[a - i][b - i] == 'Q' || pos->board[a - i][b - i] == 'B')return 1;
        }
        //prawo-g�ra
        for (int i = 1; a - i >= 0 && b + i < 8; i++) {
            if (pos->board[a - i][b + i] == ' ')continue;
            if (pos->board[a - i][b + i] == 'Q' || pos->board[a - i][b + i] == 'B')return 1;
        }
        //lewo-d�
        for (int i = 1; a + i < 8 && b - i >= 0; i++) {
            if (pos->board[a + i][b - i] == ' ')continue;
            if (pos->board[a + i][b - i] == 'Q' || pos->board[a + i][b - i] == 'B')return 1;
        }
        //prawo-d�
        for (int i = i; a + i < 8 && b + i < 8; i++) {
            if (pos->board[a + i][b + i] == ' ')continue;
            if (pos->board[a + i][b + i] == 'Q' || pos->board[a + i][b + i] == 'B')return 1;
        }
    }
    return 0; */  
    return 0;
} 
string beginnig_fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"; 
int main(){  
    string fen = 
    //"rnbqkbnr/pp1ppppp/8/2p5/1P2P3/8/P1PP1PPP/RNBQKBNR b KQkq b3 0 2";  
    "rnbq1rk1/pp1ppp2/5n1b/2p3p1/1PB1PPPp/B4N2/P1PPQ2P/RN2K2R b KQ g3 0 8"; 
    cout << fen << "\n"; 
    position pos; 
    pos = position_from_fen(fen); 
    //visualize(&pos); 
    string rekr = fen_from_position(&pos);  
    cout << rekr << "\n"; 
}
