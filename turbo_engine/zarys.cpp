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
    char row_enpas = ' ', col_enpas = ' '; // opisuje pole 'za' pionem, ktorego mozna zbic uzywajac en passant, czyli pole docelowe potencjalnego ruchu enpassant
    int halfmoves_amo = 0; // liczba posuniec figurami bez zbicia, liczona do reguly remisu po 50 
    int moves_amo = 0; // liczba zwyklych ruchow
};

//
bool pair_comp(pii para, int f, int s) {
    return para.st == f && para.nd == s;
}
bool w_planszy(int a, int b) {
    return a >= 0 && a < 8 && b >= 0 && b < 8;
}

string number_text(int x) {
    if (x == 0)
        return "0";
    string ans = "";
    int dziel = 100000;
    while (dziel) {
        if (x / dziel)
            ans += (char)('0' + x / dziel);
        else if (sz(ans))
            ans += '0';
        x = x % dziel;
        dziel /= 10;
    }
    return ans;
}
string fen_from_position(position* pos) {
    string ans; int buf = 0;
    ans.reserve(30);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (pos->board[i][j] != ' ') {
                if (buf) {
                    ans += (char)(buf + '0');
                    buf = 0;
                }
                ans += pos->board[i][j];
            }
            else {
                buf++;
            }
        }
        if (buf) {
            ans += (char)(buf + '0');
            buf = 0;
        }
        if (i != 7)
            ans += '/';
    }
    if (pos->mover == 'W')
        ans += " w ";
    else
        ans += " b ";
    if (!(pos->poss_K || pos->poss_Q || pos->poss_k || pos->poss_q))
        ans += "- ";
    else {
        if (pos->poss_K) ans += 'K';
        if (pos->poss_Q) ans += 'Q';
        if (pos->poss_k) ans += 'k';
        if (pos->poss_q) ans += 'q';
        ans += ' ';
    }
    if (!pos->en_passant)
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

void visualize(position* pos) {
    cout << "*--------*\n";
    for (int i = 0; i < 8; i++) {
        cout << '|';
        for (int j = 0; j < 8; j++) {
            if (pos->board[i][j] == ' ')
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
    if (pos->en_passant) cout << (int)pos->row_enpas << " " << (int)pos->col_enpas << " (" << (char)('a' + pos->col_enpas) << (char)('8' - pos->row_enpas) << ") " << "\n";
    else cout << "\n";
    cout << "nudy-posuniecia: " << pos->halfmoves_amo << "\n";
    cout << "pelne ruchy: " << pos->moves_amo << "\n";
    cout << "\n";
}

void where(int ind) {
    for (int i = 0; i < ind; i++)
        cout << ' ';
    cout << "^\n";
}
position position_from_fen(string fen) {
    position pos;
    int ind = 0; char endchar; int wsk;
    for (int i = 0; i < 8; i++) {
        wsk = 0;
        if (i < 7) endchar = '/';
        else endchar = ' ';
        while (fen[ind] != endchar) {
            if (fen[ind] > '9' || fen[ind] < '0')
                pos.board[i][wsk++] = fen[ind++];
            else
            {
                for (char j = '0'; j < fen[ind]; j++)
                    pos.board[i][wsk++] = ' ';
                ind++;
            }
        }
        ind++;
    }
    //where(ind);   
    pos.mover = fen[ind];
    if (pos.mover == 'w')
        pos.mover = 'W';
    ind++; ind++;  // spacja
    pos.poss_K = 0; pos.poss_Q = 0; pos.poss_k = 0; pos.poss_q = 0;
    if (fen[ind] == '-') {
        1 + 2; // nic nie rob 
        ind++;
    }
    else
    {
        while (fen[ind] != ' ') {
            if (fen[ind] == 'K')pos.poss_K = 1;
            if (fen[ind] == 'Q')pos.poss_Q = 1;
            if (fen[ind] == 'k')pos.poss_k = 1;
            if (fen[ind++] == 'q')pos.poss_q = 1;
        }
        //where(ind);  
    }
    ind++;

    if (fen[ind] == '-') {
        pos.en_passant = 0;
        pos.row_enpas = -1;
        pos.col_enpas = -1;
        ind++;
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
    //where(ind); 
    pos.halfmoves_amo = 0;
    while (fen[ind] >= '0' && fen[ind] <= '9') {
        pos.halfmoves_amo *= 10;
        pos.halfmoves_amo += fen[ind++] - '0';
    }
    //where(ind); 
    fen += " "; ind++;
    pos.moves_amo = 0; 
    //where(ind); 
    while (fen[ind] >= '0' && fen[ind] <= '9') {
        pos.moves_amo *= 10;
        pos.moves_amo += fen[ind++] - '0';
    }
    //where(ind); 
    return pos;
}

ll position_hash(position* pos) {
    return 0;
}



void make_move(string move, position* pos) {
    pii st_kord = { 0,0 }, en_kord = { 0,0 }, bicie_kord = { -1,-1 };
    char przemiana = ' ';
    char typ_figury = ' ';
    char kon = move[move.size() - 1];
    if ('a' <= kon && kon <= 'z')przemiana = kon;
    if ('A' <= kon && kon <= 'Z')przemiana = kon;
    pos->row_enpas = ' ';
    pos->col_enpas = ' ';
    if (move == "O-O") {
        if (pos->mover == 'W') {
            pos->board[7][4] = ' ';
            pos->board[7][5] = 'R';
            pos->board[7][6] = 'K';
            pos->board[7][7] = ' ';
            pos->poss_Q = 0; pos->poss_K = 0;
        }
        else {
            pos->board[0][4] = ' ';
            pos->board[0][5] = 'r';
            pos->board[0][6] = 'k';
            pos->board[0][7] = ' ';
            pos->poss_q = 0; pos->poss_k = 0;
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
            pos->poss_Q = 0; pos->poss_K = 0;
        }
        else {
            pos->board[0][0] = ' ';
            pos->board[0][1] = ' ';
            pos->board[0][2] = 'k';
            pos->board[0][3] = 'r';
            pos->board[0][4] = ' ';
            pos->poss_q = 0; pos->poss_k = 0;
        }
        pos->halfmoves_amo++;
        if (pos->mover == 'W')pos->mover = 'b';
        else { pos->mover = 'W'; pos->moves_amo++; }
        return;
    }
    //roszady d�ugie
    st_kord = { move[0] - '0',move[1] - '0' };
    en_kord = { move[2] - '0',move[3] - '0' };
    if (move.size() > 5)bicie_kord = { move[4] - '0',move[5] - '0' };
    typ_figury = pos->board[st_kord.st][st_kord.nd];
    if (bicie_kord.st >= 0 || typ_figury == 'p' || typ_figury == 'P')pos->halfmoves_amo = -1;
    pos->halfmoves_amo++;
    //rozwa�enie p�ruch�w (czy ruch pionkiem lub czy bicie)
    if (pair_comp(st_kord, 0, 0) || pair_comp(en_kord, 0, 0))pos->poss_q = 0;
    if (pair_comp(st_kord, 7, 0) || pair_comp(en_kord, 7, 0))pos->poss_Q = 0;
    if (pair_comp(st_kord, 7, 7) || pair_comp(en_kord, 7, 7))pos->poss_K = 0;
    if (pair_comp(st_kord, 0, 7) || pair_comp(en_kord, 0, 7))pos->poss_k = 0;
    if (typ_figury == 'K') { pos->poss_K = 0; pos->poss_Q = 0; }
    if (typ_figury == 'k') { pos->poss_k = 0; pos->poss_q = 0; }
    //sprawdzenie roszad
    pos->en_passant=0;
    if (abs(st_kord.st - en_kord.st) == 2 && (typ_figury == 'p' || typ_figury == 'P')) {
        char sasiad = ' ';
        if (w_planszy(en_kord.nd - 1, en_kord.st))sasiad = pos->board[en_kord.st][en_kord.nd-1];
        if ((sasiad == 'p' || sasiad == 'P') && sasiad != typ_figury) { pos->en_passant = 1;  pos->col_enpas = st_kord.nd; pos->row_enpas = (st_kord.st + en_kord.st) / 2; }
        if (w_planszy(en_kord.nd + 1, en_kord.st))sasiad = pos->board[en_kord.st][en_kord.nd+1];
        if ((sasiad == 'p' || sasiad == 'P') && sasiad != typ_figury) { pos->en_passant = 1; pos->col_enpas = st_kord.nd; pos->row_enpas = (st_kord.st + en_kord.st) / 2; }
    }
    //sprawdzenie en-passant
    if (przemiana != ' ')typ_figury = przemiana;
    // jesli jest promocja to zmien typ figury
    pos->board[st_kord.st][st_kord.nd] = ' ';
    if (bicie_kord.st >= 0)pos->board[bicie_kord.st][bicie_kord.nd] = ' ';
    pos->board[en_kord.st][en_kord.nd] = typ_figury;
    //wykonanie ruchu + zrobienie bicia
    if (pos->mover == 'W')pos->mover = 'b';
    else { pos->mover = 'W'; pos->moves_amo++; }
    //zmiana strony dodanie cyklu 

}

bool position_checked(int a, int b, char color, position* pos) {
     int x_kon[8] = { 1,2,2,1,-1,-2,-2,-1 };
     int y_kon[8] = { -2,-1,1,2,2,1,-1,-2 };
     int x_krol[8] = {-1,-1,-1,0,0,1,1,1};
     int y_krol[8] = {-1,0,1,-1,1,-1,0,1};
     if (color == 'W') {
         for (int i = 0; i < 8; i++) {            //szach czarnym koniem
             int akt_x = a + x_kon[i], akt_y = b + y_kon[i];
             if (!w_planszy(akt_x,akt_y))continue;
             if (pos->board[akt_x][akt_y] == 'n')return 1;
         }
         if ((w_planszy(a - 1, b - 1) && pos->board[a - 1][b - 1] == 'p') || (w_planszy(a - 1, b + 1) && pos->board[a - 1][b + 1] == 'p'))return 1; //szach czarnym pionem
         //lewo
         for (int i = a-1; i >= 0; i--) {
             if (pos->board[i][b] == ' ')continue;
             if (pos->board[i][b] == 'r' || pos->board[i][b] == 'q')return 1;
             break;
         }
         //prawo
         for (int i = a+1; i < 8; i++) {
             if (pos->board[i][b] == ' ')continue;
             if (pos->board[i][b] == 'r' || pos->board[i][b] == 'q')return 1;
             break;
         }
         //g�ra
         for (int i = b-1; i >= 0; i--) {
             if (pos->board[a][i] == ' ')continue;
             if (pos->board[a][i] == 'r' || pos->board[a][i] == 'q')return 1;
             break;
         }
         //d�
         for (int i = b+1; i < 8; i++) {
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
         //szach krol
         for (int i = 0; i < 8; i++) {
             int akt_x = a + x_krol[i],akt_y=b+y_krol[i];
             if (pos->board[akt_x][akt_y] == 'k')return 1;
         }
     }
     if (color == 'b') {
         for (int i = 0; i < 8; i++) {            //szach bia�ym koniem
             int akt_x = a + x_kon[i], akt_y = b + y_kon[i];
             if (!w_planszy(akt_x,akt_y))continue;
             if (pos->board[akt_x][akt_y] == 'N')return 1;
         }
         if ((w_planszy(a + 1, b - 1) && pos->board[a + 1][b - 1] == 'P') || (w_planszy(a + 1, b + 1) && pos->board[a + 1][b + 1] == 'P'))return 1; //szach bia�ym pionem
         //lewo
         for (int i = a-1; i >= 0; i--) {
             if (pos->board[i][b] == ' ')continue;
             if (pos->board[i][b] == 'R' || pos->board[i][b] == 'Q')return 1;
             break;
         }
         //prawo
         for (int i = a+1; i < 8; i++) {
             if (pos->board[i][b] == ' ')continue;
             if (pos->board[i][b] == 'R' || pos->board[i][b] == 'Q')return 1;
             break;
         }
         //g�ra
         for (int i = b-1; i >= 0; i--) {
             if (pos->board[a][i] == ' ')continue;
             if (pos->board[a][i] == 'R' || pos->board[a][i] == 'Q')return 1;
             break;
         }
         //d�
         for (int i = b+1; i < 8; i++) {
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
         //szach krol    
             for (int i = 0; i < 8; i++) {
                 int akt_x = a + x_krol[i], akt_y = b + y_krol[i];
                 if (pos->board[akt_x][akt_y] == 'K')return 1;
             }
         }
    return 0;
} 
string beginnig_fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"; 

// [wiersz, kolumna][wiersz, kolumna]
string uci_from_our_fromat(string move, position* pos){  
    string ans = ""; 
    if(move == "O-O-O"){ 
        if(pos->mover == 'W') return "e1c1"; 
        if(pos->mover == 'b') return "e8c8";  
        return "---"; 
    } 
    if(move == "O-O"){ 
        if(pos->mover == 'W') return "e1g1"; 
        if(pos->mover == 'b') return "e8g8"; 
    } 
    char row, col; 
    col = 'a' + (move[1] - '0'); 
    row = '0' + ('8' - move[0]);
    ans += col; ans += row;   
    col = 'a' + (move[3] - '0'); 
    row = '0' + ('8' - move[2]);
    ans += col; ans += row;  
    char pom = move.back(); 
    if(!(pom>='0' && pom <= '9')){ 
        if((pom >= 'A' && pom <'Z'))
            pom = pom + 'a' -'A';
        ans += pom;  
    } 
    return ans; 
} 

char number_sign(int val){ return (char)(val + '0');}

string our_format_from_uci(string uci_move, position* pos){  
    pii from; pii to; string ans; 
    char col = uci_move[0]; char row = uci_move[1]; 
    from.st = ('8' - row); from.nd = col-'a'; 
    col = uci_move[2]; row = uci_move[3]; 
    to.st = ('8' - row); to.nd =  col-'a'; 

    if( pos->en_passant != 0 && (pos->board[from.st][from.nd] == 'p' || pos->board[from.st][from.nd] == 'P') 
        && pos->col_enpas == to.nd && pos->row_enpas == to.st && pos->board[to.st][to.nd] == ' ' 
        && abs(from.st-to.st) == 1 && abs(from.nd-to.nd) == 1){ 
            pii capture = {pos->row_enpas,pos->col_enpas};
            if(pos->mover == 'W')  
                capture.st++; 
            if(pos->mover == 'b') 
                capture.st--; 
            assert((pos->board[capture.st][capture.nd] == 'p' || pos->board[capture.st][capture.nd]=='P') && pos->board[capture.st][capture.nd]!=pos->board[from.st][from.nd] ); 
            ans+=number_sign(from.st);ans+=number_sign(from.nd); 
            ans+=number_sign(to.st);ans+=number_sign(to.nd); ans+=number_sign(capture.st); ans+=number_sign(capture.nd); 
            return ans;  
    } 
    // if na promocje  
    if(sz(uci_move) == 5){ // wtedy i tylko wtedy jest promocja
        char type = uci_move.back(); 
        if(pos->mover == 'W') 
            type = type + 'A' - 'a'; 
         ans+=number_sign(from.st);ans+=number_sign(from.nd); 
         ans+=number_sign(to.st);ans+=number_sign(to.nd); 
        if(pos->board[from.st][from.nd] != ' '){
            ans+=number_sign(to.st);ans+=number_sign(to.nd);
        }       
        ans += type;
        return ans;  
    } 
    // if na roszady
    if( (pos->board[from.st][from.nd] == 'k' || pos->board[from.st][from.nd] == 'K')
    && abs(from.nd - to.nd) == 2){ 
        if(to.nd == 6) 
            return "O-O";  
        if(to.nd == 2) 
            return "O-O-O";  
        cout << from.st << " " << from.nd << " " << from.st << " " << to.nd << "\n"; 
        assert(1 == 0); 
        // roszada error
    } 
    ans+=number_sign(from.st);ans+=number_sign(from.nd); 
    ans+=number_sign(to.st);ans+=number_sign(to.nd);  
    if(pos->board[to.st][to.nd] !=' '){ 
        ans+=number_sign(to.st);ans+=number_sign(to.nd);
    }  
    return ans; 
}
string daj_ruch(int st_x, int st_y, int en_x, int en_y, int bicie_x, int bicie_y, char promocja) {
    string ruch = "";
    ruch.pb(st_x + '0');
    ruch.pb(st_y + '0');
    ruch.pb(en_x + '0');
    ruch.pb(en_y + '0');
    if (bicie_x >= 0) {
        ruch.pb(bicie_x + '0');
        ruch.pb(bicie_y + '0');
    }
    if (promocja != 'X')ruch.pb(promocja);
    return ruch;
}
bool czy_szach(char color, position* pos, string move) {
    position* klon = pos;
    make_move(move, klon);
    if (color == 'W') {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++)
                if (klon->board[i][j] == 'K') { if (position_checked(i, j, 'W', klon))return 1; return 0; }
        }
    }
    else {
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                if (klon->board[i][j] == 'k') { if (position_checked(i, j, 'b', klon))return 1; return 0; }
    }
    return 0;
}
vector<string> possible_moves(position* pos, char color) {
    vector<string> moves = {};
    int x_kon[8] = { 1,2,2,1,-1,-2,-2,-1 };
    int y_kon[8] = { -2,-1,1,2,2,1,-1,-2 };
    int x_krol[8] = { -1,-1,-1,0,0,1,1,1 };
    int y_krol[8] = { -1,0,1,-1,1,-1,0,1 };
    if (color == 'W') {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (pos->board[i][j] == 'K') {
                    for (int z = 0; z < 8; z++) {
                        int akt_x = i + x_krol[z], akt_y = j + y_krol[z];
                        if (!w_planszy(akt_x, akt_y))continue;
                        char attacked = pos->board[akt_x][akt_y];
                        if (attacked == ' ')moves.pb(daj_ruch(i, j, akt_x, akt_y, -1, -1, 'X'));
                        if ('a' <= attacked && attacked <= 'z')moves.pb(daj_ruch(i, j, akt_x, akt_y, akt_x, akt_y, 'X'));
                    }
                    if (pos->poss_K && pos->board[7][5] == ' ' && pos->board[7][6] == ' ') { 
                        if(position_checked(7, 4, 'W', pos) == 0 && position_checked(7, 5, 'W', pos) == 0 && position_checked(7, 6, 'W', pos) == 0 )
                        moves.pb("O-O"); 
                    }
                    if (pos->poss_Q && pos->board[7][1] == ' ' && pos->board[7][2] == ' ' && pos->board[7][3] == ' ') { 
                        if(position_checked(7,4,'W',pos)==0&&position_checked(7,3,'W',pos)==0&&position_checked(7,2,'W',pos)==0)
                        moves.pb("O-O-O"); }
                }
                if (pos->board[i][j] == 'Q') {
                    //gora
                    for (int z = i - 1; z >= 0; z--) {
                        if ('A' <= pos->board[z][j] && pos->board[z][j] <= 'Z')break;
                        if ('a' <= pos->board[z][j] && pos->board[z][j] <= 'z') { moves.pb(daj_ruch(i, j, z, j, z, j, 'X')); break; }
                        moves.pb(daj_ruch(i, j, z, j, -1, -1, 'X'));
                    }
                    //dol
                    for (int z = i + 1; z < 8; z++) {
                        if ('A' <= pos->board[z][j] && pos->board[z][j] <= 'Z')break;
                        if ('a' <= pos->board[z][j] && pos->board[z][j] <= 'z') { moves.pb(daj_ruch(i, j, z, j, z, j, 'X')); break; }
                        moves.pb(daj_ruch(i, j, z, j, -1, -1, 'X'));
                    }
                    //lewo
                    for (int z = j - 1; z >= 0; z--) {
                        if ('A' <= pos->board[i][z] && pos->board[i][z] <= 'Z')break;
                        if ('a' <= pos->board[i][z] && pos->board[i][z] <= 'z') { moves.pb(daj_ruch(i, j, i, z, i, z, 'X')); break; }
                        moves.pb(daj_ruch(i, j, i, z, -1, -1, 'X'));
                    }
                    //prawo
                    for (int z = j + 1; z < 8; z++) {
                        if ('A' <= pos->board[i][z] && pos->board[i][z] <= 'Z')break;
                        if ('a' <= pos->board[i][z] && pos->board[i][z] <= 'z') { moves.pb(daj_ruch(i, j, i, z, i, z, 'X')); break; }
                        moves.pb(daj_ruch(i, j, i, z, -1, -1, 'X'));
                    }
                    //lewo gora
                    for (int z = 1; i - z >= 0 && j - z >= 0; z++) {
                        if ('A' <= pos->board[i - z][j - z] && pos->board[i - z][j - z] <= 'Z')break;
                        if ('a' <= pos->board[i - z][j - z] && pos->board[i - z][j - z] <= 'z') { moves.pb(daj_ruch(i, j, i - z, j - z, i - z, j - z, 'X')); break; }
                        moves.pb(daj_ruch(i, j, i - z, j - z, -1, -1, 'X'));
                    }
                    //prawo dol
                    for (int z = 1; i + z < 8 && j + z < 8; z++) {
                        if ('A' <= pos->board[i + z][j + z] && pos->board[i + z][j + z] <= 'Z')break;
                        if ('a' <= pos->board[i + z][j + z] && pos->board[i + z][j + z] <= 'z') { moves.pb(daj_ruch(i, j, i + z, j + z, i + z, j + z, 'X')); break; }
                        moves.pb(daj_ruch(i, j, i + z, j + z, -1, -1, 'X'));
                    }
                    //prawo gora
                    for (int z = 1; i - z >= 0 && j + z < 8; z++) {
                        if ('A' <= pos->board[i - z][j + z] && pos->board[i - z][j + z] <= 'Z')break;
                        if ('a' <= pos->board[i - z][j + z] && pos->board[i - z][j + z] <= 'z') { moves.pb(daj_ruch(i, j, i - z, j + z, i - z, j + z, 'X')); break; }
                        moves.pb(daj_ruch(i, j, i - z, j + z, -1, -1, 'X'));

                    }
                    //lewo dol
                    for (int z = 1; i + z < 8 && j - z >= 0; z++) {
                        if ('A' <= pos->board[i + z][j - z] && pos->board[i + z][j - z] <= 'Z')break;
                        if ('a' <= pos->board[i + z][j - z] && pos->board[i + z][j - z] <= 'z') { moves.pb(daj_ruch(i, j, i + z, j - z, i + z, j - z, 'X')); break; }
                        moves.pb(daj_ruch(i, j, i + z, j - z, -1, -1, 'X'));

                    }
                }
                if (pos->board[i][j] == 'R') {
                    //gora
                    for (int z = i - 1; z >= 0; z--) {
                        if ('A' <= pos->board[z][j] && pos->board[z][j] <= 'Z')break;
                        if ('a' <= pos->board[z][j] && pos->board[z][j] <= 'z') { moves.pb(daj_ruch(i, j, z, j, z, j, 'X')); break; }
                        moves.pb(daj_ruch(i, j, z, j, -1, -1, 'X'));
                    }
                    //dol
                    for (int z = i + 1; z < 8; z++) {
                        if ('A' <= pos->board[z][j] && pos->board[z][j] <= 'Z')break;
                        if ('a' <= pos->board[z][j] && pos->board[z][j] <= 'z') { moves.pb(daj_ruch(i, j, z, j, z, j, 'X')); break; }
                        moves.pb(daj_ruch(i, j, z, j, -1, -1, 'X'));
                    }
                    //lewo
                    for (int z = j - 1; z >= 0; z--) {
                        if ('A' <= pos->board[i][z] && pos->board[i][z] <= 'Z')break;
                        if ('a' <= pos->board[i][z] && pos->board[i][z] <= 'z') { moves.pb(daj_ruch(i, j, i, z, i, z, 'X')); break; }
                        moves.pb(daj_ruch(i, j, i, z, -1, -1, 'X'));
                    }
                    //prawo
                    for (int z = j + 1; z < 8; z++) {
                        if ('A' <= pos->board[i][z] && pos->board[i][z] <= 'Z')break;
                        if ('a' <= pos->board[i][z] && pos->board[i][z] <= 'z') { moves.pb(daj_ruch(i, j, i, z, i, z, 'X')); break; }
                        moves.pb(daj_ruch(i, j, i, z, -1, -1, 'X'));
                    }
                }
                if (pos->board[i][j] == 'B') {
                    //lewo gora
                    for (int z = 1; i - z >= 0 && j - z >= 0; z++) {
                        if ('A' <= pos->board[i - z][j - z] && pos->board[i - z][j - z] <= 'Z')break;
                        if ('a' <= pos->board[i - z][j - z] && pos->board[i - z][j - z] <= 'z') { moves.pb(daj_ruch(i, j, i - z, j - z, i - z, j - z, 'X')); break; }
                        moves.pb(daj_ruch(i, j, i - z, j - z, -1, -1, 'X'));
                    }
                    //prawo dol
                    for (int z = 1; i + z < 8 && j + z < 8; z++) {
                        if ('A' <= pos->board[i + z][j + z] && pos->board[i + z][j + z] <= 'Z')break;
                        if ('a' <= pos->board[i + z][j + z] && pos->board[i + z][j + z] <= 'z') { moves.pb(daj_ruch(i, j, i + z, j + z, i + z, j + z, 'X')); break; }
                        moves.pb(daj_ruch(i, j, i + z, j + z, -1, -1, 'X'));
                    }
                    //prawo gora
                    for (int z = 1; i - z >= 0 && j + z < 8; z++) {
                        if ('A' <= pos->board[i - z][j + z] && pos->board[i - z][j + z] <= 'Z')break;
                        if ('a' <= pos->board[i - z][j + z] && pos->board[i - z][j + z] <= 'z') { moves.pb(daj_ruch(i, j, i - z, j + z, i - z, j + z, 'X')); break; }
                        moves.pb(daj_ruch(i, j, i - z, j + z, -1, -1, 'X'));

                    }
                    //lewo dol
                    for (int z = 1; i + z < 8 && j - z >= 0; z++) {
                        if ('A' <= pos->board[i + z][j - z] && pos->board[i + z][j - z] <= 'Z')break;
                        if ('a' <= pos->board[i + z][j - z] && pos->board[i + z][j - z] <= 'z') { moves.pb(daj_ruch(i, j, i + z, j - z, i + z, j - z, 'X')); break; }
                        moves.pb(daj_ruch(i, j, i + z, j - z, -1, -1, 'X'));

                    }
                }
                if (pos->board[i][j] == 'N') {
                    for (int z = 0; z < 8; z++) {
                        int akt_x = i + x_kon[z], akt_y = j + y_kon[z];
                        if (!w_planszy(akt_x, akt_y))continue;
                        char attacked = pos->board[akt_x][akt_y];
                        if (attacked == ' ')moves.pb(daj_ruch(i, j, akt_x, akt_y, -1, -1, 'X'));
                        if ('a' <= attacked && attacked <= 'z')moves.pb(daj_ruch(i, j, akt_x, akt_y, akt_x, akt_y, 'X'));
                    }
                }
                if (pos->board[i][j] == 'P') {
                    //promocje
                    if (i == 1) {
                        if (pos->board[i - 1][j] == ' ') {
                            moves.pb(daj_ruch(i, j, i - 1, j, -1, -1, 'H'));
                            moves.pb(daj_ruch(i, j, i - 1, j, -1, -1, 'R'));
                            moves.pb(daj_ruch(i, j, i - 1, j, -1, -1, 'N'));
                            moves.pb(daj_ruch(i, j, i - 1, j, -1, -1, 'B'));
                        }
                        if (j > 0 && 'a' <= pos->board[i - 1][j - 1] && pos->board[i - 1][j - 1] <= 'z') {
                            moves.pb(daj_ruch(i, j, i - 1, j - 1, i - 1, j - 1, 'H'));
                            moves.pb(daj_ruch(i, j, i - 1, j - 1, i - 1, j - 1, 'R'));
                            moves.pb(daj_ruch(i, j, i - 1, j - 1, i - 1, j - 1, 'N'));
                            moves.pb(daj_ruch(i, j, i - 1, j - 1, i - 1, j - 1, 'B'));
                        }
                        if (j < 7 && 'a' <= pos->board[i - 1][j + 1] && pos->board[i - 1][j + 1] <= 'z') {
                            moves.pb(daj_ruch(i, j, i - 1, j + 1, i - 1, j + 1, 'H'));
                            moves.pb(daj_ruch(i, j, i - 1, j + 1, i - 1, j + 1, 'R'));
                            moves.pb(daj_ruch(i, j, i - 1, j + 1, i - 1, j + 1, 'N'));
                            moves.pb(daj_ruch(i, j, i - 1, j + 1, i - 1, j + 1, 'B'));
                        }
                        continue;
                    }
                    //dodatkowy ruch o dwa pola
                    if (i == 6 && pos->board[i - 1][j] == ' ' && pos->board[i - 2][j] == ' ')moves.pb(daj_ruch(i, j, i - 2, j, -1, -1, 'X'));
                    //ruch zwykly
                    if (pos->board[i - 1][j] == ' ')moves.pb(daj_ruch(i, j, i - 1, j, -1, -1, 'X'));
                    //bicie zwykle
                    if (j > 0 && 'a' <= pos->board[i - 1][j - 1] && pos->board[i - 1][j - 1] <= 'z')moves.pb(daj_ruch(i, j, i - 1, j - 1, i - 1, j - 1, 'X'));
                    if (j < 7 && 'a' <= pos->board[i - 1][j + 1] && pos->board[i - 1][j + 1] <= 'z')moves.pb(daj_ruch(i, j, i - 1, j + 1, i - 1, j + 1, 'X'));
                    //en passant
                    if (i == 3 && abs(j - (pos->col_enpas - '0')) == 1)moves.pb(daj_ruch(i, j, i - 1, pos->col_enpas, i, pos->col_enpas, 'X'));
                }
            }
        }
    }
    else {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (pos->board[i][j] == 'k') {
                    for (int z = 0; z < 8; z++) {
                        int akt_x = i + x_krol[z], akt_y = j + y_krol[z];
                        if (!w_planszy(akt_x, akt_y))continue;
                        char attacked = pos->board[akt_x][akt_y];
                        if (attacked == ' ')moves.pb(daj_ruch(i, j, akt_x, akt_y, -1, -1, 'X'));
                        if ('A' <= attacked && attacked <= 'Z')moves.pb(daj_ruch(i, j, akt_x, akt_y, akt_x, akt_y, 'X'));
                    }
                    if (pos->poss_K && pos->board[0][5] == ' ' && pos->board[0][6] == ' ') {
                        if (position_checked(0, 4, 'b', pos) == 0 && position_checked(0, 5, 'b', pos) == 0 && position_checked(0, 6, 'b', pos) == 0)
                            moves.pb("O-O");
                    }
                    if (pos->poss_Q && pos->board[0][1] == ' ' && pos->board[0][2] == ' ' && pos->board[0][3] == ' ') {
                        if (position_checked(0, 4, 'b', pos) == 0 && position_checked(0, 5, 'b', pos) == 0 && position_checked(0, 6, 'b', pos) == 0)
                            moves.pb("O-O-O");
                    }
                }
                if (pos->board[i][j] == 'q') {
                    //gora
                    for (int z = i - 1; z >= 0; z--) {
                        if ('a' <= pos->board[z][j] && pos->board[z][j] <= 'z')break;
                        if ('A' <= pos->board[z][j] && pos->board[z][j] <= 'Z') { moves.pb(daj_ruch(i, j, z, j, z, j, 'X')); break; }
                        moves.pb(daj_ruch(i, j, z, j, -1, -1, 'X'));
                    }
                    //dol
                    for (int z = i + 1; z < 8; z++) {
                        if ('a' <= pos->board[z][j] && pos->board[z][j] <= 'z')break;
                        if ('A' <= pos->board[z][j] && pos->board[z][j] <= 'Z') { moves.pb(daj_ruch(i, j, z, j, z, j, 'X')); break; }
                        moves.pb(daj_ruch(i, j, z, j, -1, -1, 'X'));
                    }
                    //lewo
                    for (int z = j - 1; z >= 0; z--) {
                        if ('z' <= pos->board[i][z] && pos->board[i][z] <= 'z')break;
                        if ('A' <= pos->board[i][z] && pos->board[i][z] <= 'Z') { moves.pb(daj_ruch(i, j, i, z, i, z, 'X')); break; }
                        moves.pb(daj_ruch(i, j, i, z, -1, -1, 'X'));
                    }
                    //prawo
                    for (int z = j + 1; z < 8; z++) {
                        if ('a' <= pos->board[i][z] && pos->board[i][z] <= 'z')break;
                        if ('A' <= pos->board[i][z] && pos->board[i][z] <= 'Z') { moves.pb(daj_ruch(i, j, i, z, i, z, 'X')); break; }
                        moves.pb(daj_ruch(i, j, i, z, -1, -1, 'X'));
                    }
                    //lewo gora
                    for (int z = 1; i - z >= 0 && j - z >= 0; z++) {
                        if ('a' <= pos->board[i - z][j - z] && pos->board[i - z][j - z] <= 'z')break;
                        if ('A' <= pos->board[i - z][j - z] && pos->board[i - z][j - z] <= 'Z') { moves.pb(daj_ruch(i, j, i - z, j - z, i - z, j - z, 'X')); break; }
                        moves.pb(daj_ruch(i, j, i - z, j - z, -1, -1, 'X'));
                    }
                    //prawo dol
                    for (int z = 1; i + z < 8 && j + z < 8; z++) {
                        if ('a' <= pos->board[i + z][j + z] && pos->board[i + z][j + z] <= 'z')break;
                        if ('A' <= pos->board[i + z][j + z] && pos->board[i + z][j + z] <= 'Z') { moves.pb(daj_ruch(i, j, i + z, j + z, i + z, j + z, 'X')); break; }
                        moves.pb(daj_ruch(i, j, i + z, j + z, -1, -1, 'X'));
                    }
                    //prawo gora
                    for (int z = 1; i - z >= 0 && j + z < 8; z++) {
                        if ('a' <= pos->board[i - z][j + z] && pos->board[i - z][j + z] <= 'z')break;
                        if ('A' <= pos->board[i - z][j + z] && pos->board[i - z][j + z] <= 'Z') { moves.pb(daj_ruch(i, j, i - z, j + z, i - z, j + z, 'X')); break; }
                        moves.pb(daj_ruch(i, j, i - z, j + z, -1, -1, 'X'));

                    }
                    //lewo dol
                    for (int z = 1; i + z < 8 && j - z >= 0; z++) {
                        if ('a' <= pos->board[i + z][j - z] && pos->board[i + z][j - z] <= 'z')break;
                        if ('A' <= pos->board[i + z][j - z] && pos->board[i + z][j - z] <= 'Z') { moves.pb(daj_ruch(i, j, i + z, j - z, i + z, j - z, 'X')); break; }
                        moves.pb(daj_ruch(i, j, i + z, j - z, -1, -1, 'X'));

                    }
                }
                if (pos->board[i][j] == 'r') {
                    //gora
                    for (int z = i - 1; z >= 0; z--) {
                        if ('a' <= pos->board[z][j] && pos->board[z][j] <= 'z')break;
                        if ('A' <= pos->board[z][j] && pos->board[z][j] <= 'Z') { moves.pb(daj_ruch(i, j, z, j, z, j, 'X')); break; }
                        moves.pb(daj_ruch(i, j, z, j, -1, -1, 'X'));
                    }
                    //dol
                    for (int z = i + 1; z < 8; z++) {
                        if ('a' <= pos->board[z][j] && pos->board[z][j] <= 'z')break;
                        if ('A' <= pos->board[z][j] && pos->board[z][j] <= 'Z') { moves.pb(daj_ruch(i, j, z, j, z, j, 'X')); break; }
                        moves.pb(daj_ruch(i, j, z, j, -1, -1, 'X'));
                    }
                    //lewo
                    for (int z = j - 1; z >= 0; z--) {
                        if ('a' <= pos->board[i][z] && pos->board[i][z] <= 'z')break;
                        if ('A' <= pos->board[i][z] && pos->board[i][z] <= 'Z') { moves.pb(daj_ruch(i, j, i, z, i, z, 'X')); break; }
                        moves.pb(daj_ruch(i, j, i, z, -1, -1, 'X'));
                    }
                    //prawo
                    for (int z = j + 1; z < 8; z++) {
                        if ('a' <= pos->board[i][z] && pos->board[i][z] <= 'z')break;
                        if ('A' <= pos->board[i][z] && pos->board[i][z] <= 'Z') { moves.pb(daj_ruch(i, j, i, z, i, z, 'X')); break; }
                        moves.pb(daj_ruch(i, j, i, z, -1, -1, 'X'));
                    }
                }
                if (pos->board[i][j] == 'b') {
                    //lewo gora
                    for (int z = 1; i - z >= 0 && j - z >= 0; z++) {
                        if ('a' <= pos->board[i - z][j - z] && pos->board[i - z][j - z] <= 'z')break;
                        if ('A' <= pos->board[i - z][j - z] && pos->board[i - z][j - z] <= 'Z') { moves.pb(daj_ruch(i, j, i - z, j - z, i - z, j - z, 'X')); break; }
                        moves.pb(daj_ruch(i, j, i - z, j - z, -1, -1, 'X'));
                    }
                    //prawo dol
                    for (int z = 1; i + z < 8 && j + z < 8; z++) {
                        if ('a' <= pos->board[i + z][j + z] && pos->board[i + z][j + z] <= 'z')break;
                        if ('A' <= pos->board[i + z][j + z] && pos->board[i + z][j + z] <= 'Z') { moves.pb(daj_ruch(i, j, i + z, j + z, i + z, j + z, 'X')); break; }
                        moves.pb(daj_ruch(i, j, i + z, j + z, -1, -1, 'X'));
                    }
                    //prawo gora
                    for (int z = 1; i - z >= 0 && j + z < 8; z++) {
                        if ('a' <= pos->board[i - z][j + z] && pos->board[i - z][j + z] <= 'z')break;
                        if ('A' <= pos->board[i - z][j + z] && pos->board[i - z][j + z] <= 'Z') { moves.pb(daj_ruch(i, j, i - z, j + z, i - z, j + z, 'X')); break; }
                        moves.pb(daj_ruch(i, j, i - z, j + z, -1, -1, 'X'));

                    }
                    //lewo dol
                    for (int z = 1; i + z < 8 && j - z >= 0; z++) {
                        if ('a' <= pos->board[i + z][j - z] && pos->board[i + z][j - z] <= 'z')break;
                        if ('A' <= pos->board[i + z][j - z] && pos->board[i + z][j - z] <= 'Z') { moves.pb(daj_ruch(i, j, i + z, j - z, i + z, j - z, 'X')); break; }
                        moves.pb(daj_ruch(i, j, i + z, j - z, -1, -1, 'X'));

                    }
                }
                if (pos->board[i][j] == 'n') {
                    for (int z = 0; z < 8; z++) {
                        int akt_x = i + x_kon[z], akt_y = j + y_kon[z];
                        if (!w_planszy(akt_x, akt_y))continue;
                        char attacked = pos->board[akt_x][akt_y];
                        if (attacked == ' ')moves.pb(daj_ruch(i, j, akt_x, akt_y, -1, -1, 'X'));
                        if ('A' <= attacked && attacked <= 'Z')moves.pb(daj_ruch(i, j, akt_x, akt_y, akt_x, akt_y, 'X'));
                    }
                }
                if (pos->board[i][j] == 'p') {
                    //promocje
                    if (i == 6) {
                        if (pos->board[i - 1][j] == ' ') {
                            moves.pb(daj_ruch(i, j, 7, j, -1, -1, 'h'));
                            moves.pb(daj_ruch(i, j, 7, j, -1, -1, 'r'));
                            moves.pb(daj_ruch(i, j, 7, j, -1, -1, 'n'));
                            moves.pb(daj_ruch(i, j, 7, j, -1, -1, 'b'));
                        }
                        if (j > 0 && 'A' <= pos->board[i + 1][j - 1] && pos->board[i + 1][j - 1] <= 'Z') {
                            moves.pb(daj_ruch(i, j, 7, j - 1, 7, j - 1, 'h'));
                            moves.pb(daj_ruch(i, j, 7, j - 1, 7, j - 1, 'r'));
                            moves.pb(daj_ruch(i, j, 7, j - 1, 7, j - 1, 'n'));
                            moves.pb(daj_ruch(i, j, 7, j - 1, 7, j - 1, 'b'));
                        }
                        if (j < 7 && 'A' <= pos->board[i + 1][j + 1] && pos->board[i + 1][j + 1] <= 'Z') {
                            moves.pb(daj_ruch(i, j, 7, j + 1, 7, j + 1, 'h'));
                            moves.pb(daj_ruch(i, j, 7, j + 1, 7, j + 1, 'r'));
                            moves.pb(daj_ruch(i, j, 7, j + 1, 7, j + 1, 'n'));
                            moves.pb(daj_ruch(i, j, 7, j + 1, 7, j + 1, 'b'));
                        }
                        continue;
                    }
                    //dodatkowy ruch o dwa pola
                    if (i == 1 && pos->board[i + 1][j] == ' ' && pos->board[i + 2][j] == ' ')moves.pb(daj_ruch(i, j, i + 2, j, -1, -1, 'X'));
                    //ruch zwykly
                    if (pos->board[i + 1][j] == ' ')moves.pb(daj_ruch(i, j, i + 1, j, -1, -1, 'X'));
                    //bicie zwykle
                    if (j > 0 && 'A' <= pos->board[i + 1][j - 1] && pos->board[i + 1][j - 1] <= 'Z')moves.pb(daj_ruch(i, j, i + 1, j - 1, i + 1, j - 1, 'X'));
                    if (j < 7 && 'A' <= pos->board[i + 1][j + 1] && pos->board[i + 1][j + 1] <= 'Z')moves.pb(daj_ruch(i, j, i + 1, j + 1, i + 1, j + 1, 'X'));
                    //en passant
                    if (i == 4 && abs(j - (pos->col_enpas - '0')) == 1)moves.pb(daj_ruch(i, j, i + 1, pos->col_enpas, i, pos->col_enpas, 'X'));
                }
            }
        }
    }
    vector<string> legal_moves = {};
    for (auto i : moves) {
        if (i[0] == 'O')continue;
        if (czy_szach(color, pos, i) == 0)legal_moves.pb(i);
    }
    return legal_moves;
}


int main(){    
    
    position pos;    
    string basic_fen;
    getline(cin, basic_fen);  
    //basic_fen = beginnig_fen; 
    int val; 
    pos = position_from_fen(basic_fen);  
    vector<string> moves = possible_moves(&pos, pos.mover);     
    // cout << sz(moves) << "\n"; 
    // for(auto x : moves)     
    //     cout << x << "\n";   
    vector<string> uci_moves; 
    for(auto x : moves){ 
        uci_moves.pb(uci_from_our_fromat(x, &pos)); 
    } 
    sort(all(uci_moves));   
    cout << sz(uci_moves) << "\n";
    for(auto x : uci_moves) 
        cout <<  x << "\n"; 
}
