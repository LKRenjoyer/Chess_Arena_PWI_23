#include "funkcje.h"
#include "tabelki.h"

void porusz(string ruch, pozycja *poz) {
    //zmiana ruchu
    if(poz->czyj_ruch == 'b') {
        poz->liczba_ruchow++;
        poz->czyj_ruch = 'w';
    }
    else {
        poz->czyj_ruch = 'b';
    }
    //zmiana roszad
    if(ruch[0] == 'e') {
        if(ruch[1] == '1') {
            poz->czy_Q = 0;
            poz->czy_K = 0;
        }
        else if(ruch[1] == '8') {
            poz->czy_k = 0;
            poz->czy_q = 0;
        }
    }
    if(ruch[0] == 'a') {
        if(ruch[1] == '1') {
            poz->czy_Q = 0;
        }
        else if(ruch[1] == '8') {
            poz->czy_q = 0;
        }
    }
    if(ruch[0] == 'h') {
        if(ruch[1] == '1') {
            poz->czy_K = 0;
        }
        else if(ruch[1] == '8') {
            poz->czy_k = 0;
        }
    }
    //zmiana bicia w przelocie
    poz->czy_bicie_w_przelocie = 0;
    poz->wiersz_bwp = ' ';
    poz->kolumna_bwp = ' ';
    if(ruch[1] == '2' && ruch[3] == '4' && poz->plansza[(ruch[1] - '1')][(ruch[0] - 'a')] == 'P') {
        poz->czy_bicie_w_przelocie = 1;
        poz->wiersz_bwp = '3';
        poz->kolumna_bwp = ruch[0];
    }
    else if(ruch[1] == '7' && ruch[3] == '5' && poz->plansza[(ruch[1] - '1')][(ruch[0] - 'a')] == 'p') {
        poz->czy_bicie_w_przelocie = 1;
        poz->wiersz_bwp = '6';
        poz->kolumna_bwp = ruch[0];
    }
    //licz polowki ruchow
    if(poz->plansza[(ruch[1] - '1')][(ruch[0] - 'a')] == 'P' || poz->plansza[(ruch[1] - '1')][(ruch[0] - 'a')] == 'p') {
        //ruch pionem + (bicie w przelocie)
        poz->liczba_polowek_ruchow = 0;
    }
    else if(poz->plansza[(ruch[3] - '1')][(ruch[2]) - 'a'] != ' ') {
        //pozostałe bicia
        poz->liczba_polowek_ruchow = 0;
    }
    else {
        poz->liczba_polowek_ruchow++;
        if(poz->liczba_polowek_ruchow == 100) {
            //uwaga remis
            //uwaga remis
            //uwaga remis
            //uwaga remis
            //uwaga remis
            //trzeba uważać na regułe 50 ruchow 
        }
    }
    if(ruch.size() == 5) {
        //uwaga na promocje figur 
        poz->plansza[(ruch[1] - '1')][(ruch[0] - 'a')] = ' ';
        if(ruch[3] == '1')
            poz->plansza[(ruch[3] - '1')][(ruch[2] - 'a')] = ruch[4];
        else 
            poz->plansza[(ruch[3] - '1')][(ruch[2] - 'a')] = ruch[4];
    }
    else if(ruch[0] == 'e' && ruch[1] == '1' && (ruch[2] == 'g' || ruch[2] == 'c') && poz->plansza[(ruch[1] - '1')][(ruch[0] - 'a')] == 'K') {
        //uwaga na roszady bialego
        if(ruch[2] == 'c') {
            poz->plansza[0][0] = ' ';
            poz->plansza[0][2] = 'K';
            poz->plansza[0][3] = 'R';
            poz->plansza[0][4] = ' ';
        }
        else {
            poz->plansza[0][7] = ' ';
            poz->plansza[0][6] = 'K';
            poz->plansza[0][5] = 'R';
            poz->plansza[0][4] = ' ';
        }
    }
    else if(ruch[0] == 'e' && ruch[1] == '8' && (ruch[2] == 'g' || ruch[2] == 'c') && poz->plansza[(ruch[1] - '1')][(ruch[0] - 'a')] == 'k') {
        //uwaga na roszady czarnego
        if(ruch[2] == 'c') {
            poz->plansza[7][0] = ' ';
            poz->plansza[7][2] = 'k';
            poz->plansza[7][3] = 'r';
            poz->plansza[7][4] = ' ';
        }
        else {
            poz->plansza[7][7] = ' ';
            poz->plansza[7][6] = 'k';
            poz->plansza[7][5] = 'r';
            poz->plansza[7][4] = ' ';
        }
    }
    else if(poz->plansza[(ruch[1] - '1')][(ruch[0] - 'a')] == 'P' && ruch[0] != ruch[2] && abs(ruch[1] - ruch[3]) == 2){
        //uwaga na bicia w przelocie bialych
        poz->plansza[(ruch[1] - '1')][(ruch[0] - 'a')] = ' ';
        poz->plansza[(ruch[3] - '1')][(ruch[2] - 'a')] = 'P';
        poz->plansza[(ruch[3] - '1') - 1][(ruch[2] - 'a')] = ' ';
    }
    else if(poz->plansza[(ruch[1] - '1')][(ruch[0] - 'a')] == 'p' && ruch[0] != ruch[2] && abs(ruch[1] - ruch[3]) == 2){
        //uwaga na bicia w przelocie czarnych
        poz->plansza[(ruch[1] - '1')][(ruch[0] - 'a')] = ' ';
        poz->plansza[(ruch[3] - '1')][(ruch[2] - 'a')] = 'p';
        poz->plansza[(ruch[3] - '1') + 1][(ruch[2] - 'a')] = ' ';
    }
    else {
        //porusz figure
        //cout << "poruszam figure\n";
        poz->plansza[(ruch[3] - '1')][(ruch[2] - 'a')] = poz->plansza[(ruch[1] - '1')][(ruch[0] - 'a')];
        poz->plansza[(ruch[1] - '1')][(ruch[0] - 'a')] = ' ';
    }
}

bool czy_pole_jest_szachowane(int y, int x, char kolor, pozycja *poz) {//sprawdza czy pole jest szachowane przez figury koloru "kolor"
    vector <pair <int,int> > ruchy_skoczka = {{1, 2}, {1, -2}, {-1, 2}, {-1, -2}, {2, -1}, {2, 1}, {-2, -1}, {-2, 1}};
    vector <pair <int,int> > ruchy_krola = {{1, 1}, {1, 0}, {1, -1}, {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {0, -1}};
    if(kolor == 'w') {
        //czy pion szachuje
        if(y - 1 >= 0 && x - 1 >= 0) {
            if(poz->plansza[y - 1][x - 1] == 'P') {
                return 1;
            }
        }
        if(y - 1 >= 0 && x + 1 <= 7) {
            if(poz->plansza[y - 1][x + 1] == 'P') {
                return 1;
            }
        }
        for(int i = 0; i < 8; i++) {
            //czy skoczek szachuje
            if(y + ruchy_skoczka[i].st >= 0 && y + ruchy_skoczka[i].st <= 7 && x + ruchy_skoczka[i].nd >= 0 && x + ruchy_skoczka[i].nd <= 7) {
                if(poz->plansza[y + ruchy_skoczka[i].st][x + ruchy_skoczka[i].nd] == 'N') {
                    return 1;
                }    
            }
            //czy krol szachuje
            if(y + ruchy_krola[i].st >= 0 && y + ruchy_krola[i].st <= 7 && x + ruchy_krola[i].nd >= 0 && x + ruchy_krola[i].nd <= 7) {
                if(poz->plansza[y + ruchy_krola[i].st][x + ruchy_krola[i].nd] == 'K') {
                    return 1;
                }    
            }
        }
        //czy kolumny i wiersze
        int pom = 1;
        while(y + pom <= 7) {
            if(poz->plansza[y + pom][x] != ' ') {
                if(poz->plansza[y + pom][x] == 'Q' || poz->plansza[y + pom][x] == 'R') {
                    return 1;
                }
                else {
                    break;
                }
            }
            pom++;
        }
        pom = 1;
        while(y - pom >= 0) {
            if(poz->plansza[y - pom][x] != ' ') {
                if(poz->plansza[y - pom][x] == 'Q' || poz->plansza[y - pom][x] == 'R') {
                    return 1;
                }
                else {
                    break;
                }
            }
            pom++;
        }
        pom = 1;
        while(x + pom <= 7) {
            if(poz->plansza[y][x + pom] != ' ') {
                if(poz->plansza[y][x + pom] == 'Q' || poz->plansza[y][x + pom] == 'R') {
                    return 1;
                }
                else {
                    break;
                }
            }
            pom++;
        }
        pom = 1;
        while(x - pom >= 0) {
            if(poz->plansza[y][x - pom] != ' ') {
                if(poz->plansza[y][x - pom] == 'Q' || poz->plansza[y][x - pom] == 'R') {
                    return 1;
                }
                else {
                    break;
                }
            }
            pom++;
        } 
        //czy przekatne
        pom = 1;
        while(y + pom <= 7 && x + pom <= 7) {
            if(poz->plansza[y + pom][x + pom] != ' ') {
                if(poz->plansza[y + pom][x + pom] == 'Q' || poz->plansza[y + pom][x + pom] == 'B') {
                    return 1;
                }
                else {
                    break;
                }
            }
            pom++;
        }
        pom = 1;
        while(y + pom <= 7 && x - pom >= 0) {
            if(poz->plansza[y + pom][x - pom] != ' ') {
                if(poz->plansza[y + pom][x - pom] == 'Q' || poz->plansza[y + pom][x - pom] == 'B') {
                    return 1;
                }
                else {
                    break;
                }
            }
            pom++;
        }
        pom = 1;
        while(y - pom >= 0 && x + pom <= 7) {
            if(poz->plansza[y - pom][x + pom] != ' ') {
                if(poz->plansza[y - pom][x + pom] == 'Q' || poz->plansza[y - pom][x + pom] == 'B') {
                    return 1;
                }
                else {
                    break;
                }
            }
            pom++;
        }
        pom = 1;
        while(y - pom >= 0 && x - pom >= 0) {
            if(poz->plansza[y - pom][x - pom] != ' ') {
                if(poz->plansza[y - pom][x - pom] == 'Q' || poz->plansza[y - pom][x - pom] == 'B') {
                    return 1;
                }
                else {
                    break;
                }
            }
            pom++;
        }
    }
    else {
        //czy pion szachuje
        if(y + 1 <= 7 && x - 1 >= 0) {
            if(poz->plansza[y + 1][x - 1] == 'p') {
                return 1;
            }
        }
        if(y + 1 <= 7 && x + 1 <= 7) {
            if(poz->plansza[y + 1][x + 1] == 'p') {
                return 1;
            }
        }
        for(int i = 0; i < 8; i++) {
            //czy skoczek szachuje
            if(y + ruchy_skoczka[i].st >= 0 && y + ruchy_skoczka[i].st <= 7 && x + ruchy_skoczka[i].nd >= 0 && x + ruchy_skoczka[i].nd <= 7) {
                if(poz->plansza[y + ruchy_skoczka[i].st][x + ruchy_skoczka[i].nd] == 'n') {
                    return 1;
                }    
            }
            //czy krol szachuje
            if(y + ruchy_krola[i].st >= 0 && y + ruchy_krola[i].st <= 7 && x + ruchy_krola[i].nd >= 0 && x + ruchy_krola[i].nd <= 7) {
                if(poz->plansza[y + ruchy_krola[i].st][x + ruchy_krola[i].nd] == 'k') {
                    return 1;
                }    
            }
        }
        //czy kolumny i wiersze
        int pom = 1;
        while(y + pom <= 7) {
            if(poz->plansza[y + pom][x] != ' ') {
                if(poz->plansza[y + pom][x] == 'q' || poz->plansza[y + pom][x] == 'r') {
                    return 1;
                }
                else {
                    break;
                }
            }
            pom++;
        }
        pom = 1;
        while(y - pom >= 0) {
            if(poz->plansza[y - pom][x] != ' ') {
                if(poz->plansza[y - pom][x] == 'q' || poz->plansza[y - pom][x] == 'r') {
                    return 1;
                }
                else {
                    break;
                }
            }
            pom++;
        }
        pom = 1;
        while(x + pom <= 7) {
            if(poz->plansza[y][x + pom] != ' ') {
                if(poz->plansza[y][x + pom] == 'q' || poz->plansza[y][x + pom] == 'r') {
                    return 1;
                }
                else {
                    break;
                }
            }
            pom++;
        }
        pom = 1;
        while(x - pom >= 0) {
            if(poz->plansza[y][x - pom] != ' ') {
                if(poz->plansza[y][x - pom] == 'q' || poz->plansza[y][x - pom] == 'r') {
                    return 1;
                }
                else {
                    break;
                }
            }
            pom++;
        } 
        //czy przekatne
        pom = 1;
        while(y + pom <= 7 && x + pom <= 7) {
            if(poz->plansza[y + pom][x + pom] != ' ') {
                if(poz->plansza[y + pom][x + pom] == 'q' || poz->plansza[y + pom][x + pom] == 'b') {
                    return 1;
                }
                else {
                    break;
                }
            }
            pom++;
        }
        pom = 1;
        while(y + pom <= 7 && x - pom >= 0) {
            if(poz->plansza[y + pom][x - pom] != ' ') {
                if(poz->plansza[y + pom][x - pom] == 'q' || poz->plansza[y + pom][x - pom] == 'b') {
                    return 1;
                }
                else {
                    break;
                }
            }
            pom++;
        }
        pom = 1;
        while(y - pom >= 0 && x + pom <= 7) {
            if(poz->plansza[y - pom][x + pom] != ' ') {
                if(poz->plansza[y - pom][x + pom] == 'q' || poz->plansza[y - pom][x + pom] == 'b') {
                    return 1;
                }
                else {
                    break;
                }
            }
            pom++;
        }
        pom = 1;
        while(y - pom >= 0 && x - pom >= 0) {
            if(poz->plansza[y - pom][x - pom] != ' ') {
                if(poz->plansza[y - pom][x - pom] == 'q' || poz->plansza[y - pom][x - pom] == 'b') {
                    return 1;
                }
                else {
                    break;
                }
            }
            pom++;
        }
    }
    return 0;
}

void wizualizacja(pozycja *poz) {
    cout << '\n';
    
    for(int i = 7; i >= 0; i--) {
        cout << ANSI_COLOR_GREEN << i + 1 << ANSI_COLOR_RESET;
        cout << '|';
        for(int ii = 0; ii < 8; ii++) {
            if(poz->plansza[i][ii] >= 'a' && poz->plansza[i][ii] <= 'z')
                cout << ANSI_COLOR_RED << poz->plansza[i][ii] << ANSI_COLOR_RESET << '|';
            else if(poz->plansza[i][ii] >= 'A' && poz->plansza[i][ii] <= 'Z')
                cout << poz->plansza[i][ii] << '|';
            else
                cout << " |";
        }
        cout << '\n';
    }
    cout << ANSI_COLOR_GREEN << "  A B C D E F G H\n" << ANSI_COLOR_RESET;
   
    cout << '\n';
    cout << "czyj ruch: " << poz->czyj_ruch << '\n';
    cout << "możliwe roszady: " << (poz->czy_K ? "K" : "") << (poz->czy_Q ? "Q" : "") << (poz->czy_k ? "k" : "") << (poz->czy_q ? "q" : "") << '\n';
    cout << "czy mozliwe bicie w przelocie: " << (poz->czy_bicie_w_przelocie ? "TAK " : "NIE ") << (poz->czy_bicie_w_przelocie ? poz->kolumna_bwp : ' ') << (poz->czy_bicie_w_przelocie ? poz->wiersz_bwp : ' ') << '\n';
    cout << "liczba_polowek_ruchow: " << poz->liczba_polowek_ruchow << '\n';
    cout << "liczba_ruchow: " << poz->liczba_ruchow << '\n'; 
    cout << "ewaluacja: " << fixed << setprecision(5) << ewaluacja_pozycji(poz) << '\n';
}

void fen_to_chessboard(string fen, pozycja *poz) {
    for(int i = 0; i <= 7; i++) {
        for(int ii = 0; ii <= 7; ii++) {
            poz->plansza[i][ii] = ' ';
        }
    }
    int x = 0;
    for(int i = 7; i >= 0; i--) {
        for(int ii = 0; ii <= 20; ii++) {
            if(fen[x] == '/' || fen[x] == ' ') {
                x++;
                break;
            }
            else if(fen[x] >= '1' && fen[x] <= '9') {
                ii += (fen[x] - '0') - 1;
                x++;
            }
            else {
                poz->plansza[i][ii] = fen[x];
                x++;
            }
        }
    }
    poz->czyj_ruch = fen[x];
    x += 2;
    while(fen[x] != ' ') {
        if(fen[x] == 'K') {
            poz->czy_K = 1;
        }
        else if(fen[x] == 'Q') {
            poz->czy_Q = 1;
        }
        else if(fen[x] == 'k') {
            poz->czy_k = 1;
        }
        else if(fen[x] == 'q'){
            poz->czy_q = 1;
        }
        x++;
    }
    x++;
    if(fen[x] == '-') {
        x += 2;
    }
    else {
        poz->czy_bicie_w_przelocie = 1;
        poz->kolumna_bwp = fen[x];
        x++;
        poz->wiersz_bwp = fen[x];
        x += 2;
    }
    string pom = "";
    while(fen[x] != ' ') {
        pom += fen[x];
        x++;
    }
    poz->liczba_polowek_ruchow = stoi(pom);
    x++;
    pom = "";
    while(x < (int)fen.size()) {
        pom += fen[x];
        x++;
    }
    poz->liczba_ruchow = stoi(pom);
}

long double ewaluacja_pozycji(pozycja *poz) {
    int liczfigury[256] = {};
    int pionyb[8] = {}, pionyc[8] = {};
    for(int i = 0; i <= 7; i++) {
        for(int ii = 0; ii <= 7; ii++) {
            liczfigury[poz->plansza[i][ii]]++;
        }
    }
    long double wart = 
    (long double)200 * (liczfigury['K'] - liczfigury['k']) +
    (long double)9 * (liczfigury['Q'] - liczfigury['q']) +
    (long double)5 * (liczfigury['R'] - liczfigury['r']) +
    (long double)3 * (liczfigury['B'] - liczfigury['b']) +
    (long double)3 * (liczfigury['N'] - liczfigury['n']) +
    (long double)1 * (liczfigury['P'] - liczfigury['p']);
    bool czy_endgame_b = 0;
    bool czy_endgame_c = 0;
    if(liczfigury['Q'] * 9 + liczfigury['R'] * 5 + liczfigury['B'] * 3 + liczfigury['N'] * 3 <= 15)
        czy_endgame_b = 1;
    if(liczfigury['q'] * 9 + liczfigury['r'] * 5 + liczfigury['b'] * 3 + liczfigury['n'] * 3 <= 15)
        czy_endgame_c = 1;
    pair <int, int> bk, ck; // pozycja bialego i czarnego krola
    for(int i = 0; i < 8; i++) {
        for(int ii = 0; ii < 8; ii++) {
            if(poz->plansza[i][ii] == 'K') {
                bk = {i, ii};
                if(!czy_endgame_b) {
                    wart += krol_b_pocz[i][ii] / 100;
                }
                else {
                    wart += krol_b_kon[i][ii] / 100;
                }
            }
            else if(poz->plansza[i][ii] == 'Q') {
                wart += hetmany_b[i][ii] / 100;
            }
            else if(poz->plansza[i][ii] == 'R') {
                wart += wieze_b[i][ii] / 100;
            }
            else if(poz->plansza[i][ii] == 'B') {
                wart += gonce_b[i][ii] / 100;
            }
            else if(poz->plansza[i][ii] == 'N') {
                wart += skoczki_b[i][ii] / 100;
            }
            else if(poz->plansza[i][ii] == 'P') {
                //zblokowane 
                if(poz->plansza[i + 1][ii] != ' ') {
                    wart -= 0.25;
                }
                if(!czy_endgame_b) {
                    wart += piony_b_pon[i][ii] / 100;
                }
                else {
                    wart += piony_b_kon[i][ii] / 100;
                }
                pionyb[ii]++;
            }
            else if(poz->plansza[i][ii] == 'k') {
                ck = {i, ii};
                if(!czy_endgame_c) {
                    wart -= krol_c_pocz[i][ii] / 100;
                }
                else {
                    wart -= krol_c_kon[i][ii] / 100;
                }
            }
            else if(poz->plansza[i][ii] == 'q') {
                wart -= hetmany_c[i][ii] / 100;
            }
            else if(poz->plansza[i][ii] == 'r') {
                wart -= wieze_c[i][ii] / 100;
            }
            else if(poz->plansza[i][ii] == 'b') {
                wart -= gonce_c[i][ii] / 100;
            }
            else if(poz->plansza[i][ii] == 'n') {
                wart -= skoczki_c[i][ii] / 100;
            }
            else if(poz->plansza[i][ii] == 'p') {
                //zblokowane 
                if(poz->plansza[i - 1][ii] != ' ') {
                    wart += 0.25;
                }
                if(!czy_endgame_c) {
                    wart -= piony_c_pon[i][ii] / 100;
                }
                else {
                    wart -= piony_c_kon[i][ii] / 100;
                }
                pionyc[ii]++;
            }
        }
    }
    //zdublowane piony
    for(int i = 0; i < 8; i++) {
        wart -= (long double)max(0, pionyb[i] - 1) * 0,25;
        wart += (long double)max(0, pionyc[i] - 1) * 0,25;
    }
    //izolowane piony
    for(int i = 1; i < 7; i++) {
        if(pionyb[i] > 0 && pionyb[i - 1] == 0 && pionyb[i + 1] == 0) {
            wart -= 0.25;
        }
        if(pionyc[i] > 0 && pionyc[i - 1] == 0 && pionyc[i + 1] == 0) {
            wart += 0.25;
        }
    }
    //bezpieczenstwo krola bialego
    for(int i = max(0, bk.st - 2); i <= min(7, bk.st + 2); i++) {
        for(int ii = max(0, bk.nd - 2); ii <= min(7, bk.nd + 2); ii++) {
            if(poz->plansza[i][ii] == 'q') {
                wart -= 1.8;
            }
            else if(poz->plansza[i][ii] == 'w') {
                wart -= 1;
            }
            else if(poz->plansza[i][ii] == 'b' || poz->plansza[i][ii] == 'n') {
                wart -= 0.6; 
            }
            else if(poz->plansza[i][ii] == 'p') {
                wart -= 0.2;
            }
        }
    }
    //bezpieczenstwo krola czarnrgo
    for(int i = max(0, ck.st - 2); i <= min(7, ck.st + 2); i++) {
        for(int ii = max(0, ck.nd - 2); ii <= min(7, ck.nd + 2); ii++) {
            if(poz->plansza[i][ii] == 'Q') {
                wart += 1.8;
            }
            else if(poz->plansza[i][ii] == 'W') {
                wart += 1;
            }
            else if(poz->plansza[i][ii] == 'B' || poz->plansza[i][ii] == 'N') {
                wart += 0.6; 
            }
            else if(poz->plansza[i][ii] == 'P') {
                wart += 0.2;
            }
        }
    }

    //dodać sprawdzanie czy pat i czy mat 

    return -wart;
}

bool czy_w_planszy(int i,int j)
{
    if (i>=0&&i<=7&&j>=0&&j<=7)
    {
        return 1;
    }
    return 0;
}

string pole(int a,int b,int c,int d)
{
    string wynik;
    wynik.push_back(b+'a');
    wynik.push_back(a+'1');
    wynik.push_back(d+'a');
    wynik.push_back(c+'1');
    return wynik;
}

vector <int> pole_w_liczby(char bwp1,char bwp2)
{
    vector <int> wynik;
    wynik.push_back(bwp2-'1');
    wynik.push_back(bwp1-'a');
    return wynik;
}

vector <string> mozliwe_ruchy(pozycja *poz)
{
    vector <string> cos;
    pozycja poz2=*poz;
    pair <int,int> white_king;
    pair <int,int> black_king;
    for (int i=0;i<8;i++)
    {
        for (int j=0;j<8;j++)
        {
            if (poz->plansza[i][j]=='k')
            {
                black_king=make_pair(i,j);
            }
            if (poz->plansza[i][j]=='K')
            {
                white_king=make_pair(i,j);
            }
        }
    }
    if (poz->czyj_ruch=='b')
    {
        for (int i=0;i<8;i++)
        {
            for (int j=0;j<8;j++)
            {
                //ruch króla;
                if (poz->plansza[i][j]=='k')
                {
                    if (czy_w_planszy(i-1,j-1)==1&&(poz->plansza[i-1][j-1]>'z'||poz->plansza[i-1][j-1]<'a'))
                    {
                        poz2=*poz;
                        string slowo=pole(i,j,i-1,j-1);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(i-1,j-1,'w',&poz2)==0)
                        {
                            cos.push_back(slowo);
                        }
                    }
                    if (czy_w_planszy(i+1,j-1)==1&&(poz->plansza[i+1][j-1]>'z'||poz->plansza[i+1][j-1]<'a'))
                    {
                        poz2=*poz;
                        string slowo=pole(i,j,i+1,j-1);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(i+1,j-1,'w',&poz2)==0)
                        {
                            cos.push_back(slowo);
                        }
                    }
                    if (czy_w_planszy(i-1,j+1)==1&&(poz->plansza[i-1][j+1]>'z'||poz->plansza[i-1][j+1]<'a'))
                    {
                        poz2=*poz;
                        string slowo=pole(i,j,i-1,j+1);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(i-1,j+1,'w',&poz2)==0)
                        {
                            cos.push_back(slowo);
                        }
                    }
                    if (czy_w_planszy(i+1,j+1)==1&&(poz->plansza[i+1][j+1]>'z'||poz->plansza[i+1][j+1]<'a'))
                    {
                        poz2=*poz;
                        string slowo=pole(i,j,i+1,j+1);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(i+1,j+1,'w',&poz2)==0)
                        {
                            cos.push_back(slowo);
                        }
                    }
                    if (czy_w_planszy(i-1,j)==1&&(poz->plansza[i-1][j]>'z'||poz->plansza[i-1][j]<'a'))
                    {
                        poz2=*poz;
                        string slowo=pole(i,j,i-1,j);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(i-1,j,'w',&poz2)==0)
                        {
                            cos.push_back(slowo);
                        }
                    }
                    if (czy_w_planszy(i,j-1)==1&&(poz->plansza[i][j-1]>'z'||poz->plansza[i][j-1]<'a'))
                    {
                        poz2=*poz;
                        string slowo=pole(i,j,i,j-1);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(i,j-1,'w',&poz2)==0)
                        {
                            cos.push_back(slowo);
                        }
                    }
                    if (czy_w_planszy(i+1,j)==1&&(poz->plansza[i+1][j]>'z'||poz->plansza[i+1][j]<'a'))
                    {
                        poz2=*poz;
                        string slowo=pole(i,j,i+1,j);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(i+1,j,'w',&poz2)==0)
                        {
                            cos.push_back(slowo);
                        }
                    }
                    if (czy_w_planszy(i,j+1)==1&&(poz->plansza[i][j+1]>'z'||poz->plansza[i][j+1]<'a'))
                    {
                        poz2=*poz;
                        string slowo=pole(i,j,i,j+1);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(i,j+1,'w',&poz2)==0)
                        {
                            cos.push_back(slowo);
                        }
                    }
                    if (poz->czy_k==1)//roszada krótka;
                    {
                        if (czy_pole_jest_szachowane(i,j,'w',poz)==0)
                        {
                            if (poz->plansza[7][5]==' '&&poz->plansza[7][6]==' '&&czy_pole_jest_szachowane(7,5,'w',poz)==0&&czy_pole_jest_szachowane(7,6,'w',poz)==0)
                            {
                                string slowo=pole(i,j,7,6);
                                cos.push_back(slowo);
                            }
                        }
                    }
                    if (poz->czy_q==1)//roszada d³uga;
                    {
                        if (czy_pole_jest_szachowane(i,j,'w',poz)==0)
                        {
                            if (poz->plansza[7][2]==' '&&poz->plansza[7][1]==' '&&poz->plansza[7][3]==' '&&czy_pole_jest_szachowane(7,2,'w',poz)==0&&czy_pole_jest_szachowane(7,3,'w',poz)==0)
                            {
                                string slowo=pole(i,j,7,1);
                                cos.push_back(slowo);
                            }
                        }
                    }
                }
                //ruch królowej;
                if (poz->plansza[i][j]=='q')
                {
                    int pom=1;
                    //sprawdzanie prawej czêci wiersza;
                    while(czy_w_planszy(i,j+pom)==1&&(poz->plansza[i][j+pom]>'z'||poz->plansza[i][j+pom]<'a'))
                    {
                        if (poz->plansza[i][j+pom]!=' ')
                        {
                            poz2=*poz;
                            string slowo=pole(i,j,i,j+pom);
                            porusz(slowo,&poz2);
                            if (czy_pole_jest_szachowane(black_king.st,black_king.nd,'w',&poz2)==0)
                            {
                                cos.push_back(slowo);
                            }
                            break;
                        }
                        poz2=*poz;
                        string slowo=pole(i,j,i,j+pom);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(black_king.st,black_king.nd,'w',&poz2)==0)
                        {
                            cos.push_back(slowo);
                        }
                        pom++;
                    }
                    pom=-1;
                    //sprawdzanie lewej czêci wiersza;
                    while(czy_w_planszy(i,j+pom)==1&&(poz->plansza[i][j+pom]>'z'||poz->plansza[i][j+pom]<'a'))
                    {
                        if (poz->plansza[i][j+pom]!=' ')
                        {
                            poz2=*poz;
                            string slowo=pole(i,j,i,j+pom);
                            porusz(slowo,&poz2);
                            if (czy_pole_jest_szachowane(black_king.st,black_king.nd,'w',&poz2)==0)
                            {
                                cos.push_back(slowo);
                            }
                            break;
                        }
                        poz2=*poz;
                        string slowo=pole(i,j,i,j+pom);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(black_king.st,black_king.nd,'w',&poz2)==0)
                        {
                            cos.push_back(slowo);
                        }
                        pom--;
                    }
                    pom=1;
                    //sprawdzanie dolnej czêci kolumny;
                    while(czy_w_planszy(i+pom,j)==1&&(poz->plansza[i+pom][j]>'z'||poz->plansza[i+pom][j]<'a'))
                    {
                        if (poz->plansza[i+pom][j]!=' ')
                        {
                            poz2=*poz;
                            string slowo=pole(i,j,i+pom,j);
                            porusz(slowo,&poz2);
                            if (czy_pole_jest_szachowane(black_king.st,black_king.nd,'w',&poz2)==0)
                            {
                                cos.push_back(slowo);
                            }
                            break;
                        }
                        poz2=*poz;
                        string slowo=pole(i,j,i+pom,j);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(black_king.st,black_king.nd,'w',&poz2)==0)
                        {
                            cos.push_back(slowo);
                        }
                        pom++;
                    }
                    pom=-1;
                    //sprawdzanie górnej czêci kolumny;
                    while(czy_w_planszy(i+pom,j)==1&&(poz->plansza[i+pom][j]>'z'||poz->plansza[i+pom][j]<'a'))
                    {
                        if (poz->plansza[i+pom][j]!=' ')
                        {
                            poz2=*poz;
                            string slowo=pole(i,j,i+pom,j);
                            porusz(slowo,&poz2);
                            if (czy_pole_jest_szachowane(black_king.st,black_king.nd,'w',&poz2)==0)
                            {
                                cos.push_back(slowo);
                            }
                            break;
                        }
                        poz2=*poz;
                        string slowo=pole(i,j,i+pom,j);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(black_king.st,black_king.nd,'w',&poz2)==0)
                        {
                            cos.push_back(slowo);
                        }
                        pom--;
                    }
                    pom=-1;
                    //sprawdzanie lewej górnej przek¹tnej;
                    while(czy_w_planszy(i+pom,j+pom)==1&&(poz->plansza[i+pom][j+pom]>'z'||poz->plansza[i+pom][j+pom]<'a'))
                    {
                        if (poz->plansza[i+pom][j+pom]!=' ')
                        {
                            poz2=*poz;
                            string slowo=pole(i,j,i+pom,j+pom);
                            porusz(slowo,&poz2);
                            if (czy_pole_jest_szachowane(black_king.st,black_king.nd,'w',&poz2)==0)
                            {
                                cos.push_back(slowo);
                            }
                            break;
                        }
                        poz2=*poz;
                        string slowo=pole(i,j,i+pom,j+pom);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(black_king.st,black_king.nd,'w',&poz2)==0)
                        {
                            cos.push_back(slowo);
                        }
                        pom--;
                    }
                    pom=1;
                    //sprawdzanie prawej dolnej przek¹tnej;
                    while(czy_w_planszy(i+pom,j+pom)==1&&(poz->plansza[i+pom][j+pom]>'z'||poz->plansza[i+pom][j+pom]<'a'))
                    {
                        if (poz->plansza[i+pom][j+pom]!=' ')
                        {
                            poz2=*poz;
                            string slowo=pole(i,j,i+pom,j+pom);
                            porusz(slowo,&poz2);
                            if (czy_pole_jest_szachowane(black_king.st,black_king.nd,'w',&poz2)==0)
                            {
                                cos.push_back(slowo);
                            }
                            break;
                        }
                        poz2=*poz;
                        string slowo=pole(i,j,i+pom,j+pom);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(black_king.st,black_king.nd,'w',&poz2)==0)
                        {
                            cos.push_back(slowo);
                        }
                        pom++;
                    }
                    pom=1;
                    //sprawdzanie lewej dolnej przek¹tnej;
                    while(czy_w_planszy(i+pom,j-pom)==1&&(poz->plansza[i+pom][j-pom]>'z'||poz->plansza[i+pom][j-pom]<'a'))
                    {
                        if (poz->plansza[i+pom][j-pom]!=' ')
                        {
                            poz2=*poz;
                            string slowo=pole(i,j,i+pom,j-pom);
                            porusz(slowo,&poz2);
                            if (czy_pole_jest_szachowane(black_king.st,black_king.nd,'w',&poz2)==0)
                            {
                                cos.push_back(slowo);
                            }
                            break;
                        }
                        poz2=*poz;
                        string slowo=pole(i,j,i+pom,j-pom);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(black_king.st,black_king.nd,'w',&poz2)==0)
                        {
                            cos.push_back(slowo);
                        }
                        pom++;
                    }
                    pom=1;
                    //sprawdzanie prawej górnej przek¹tnej;
                    while(czy_w_planszy(i-pom,j+pom)==1&&(poz->plansza[i-pom][j+pom]>'z'||poz->plansza[i-pom][j+pom]<'a'))
                    {
                        if (poz->plansza[i-pom][j+pom]!=' ')
                        {
                            poz2=*poz;
                            string slowo=pole(i,j,i-pom,j+pom);
                            porusz(slowo,&poz2);
                            if (czy_pole_jest_szachowane(black_king.st,black_king.nd,'w',&poz2)==0)
                            {
                                cos.push_back(slowo);
                            }
                            break;
                        }
                        poz2=*poz;
                        string slowo=pole(i,j,i-pom,j+pom);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(black_king.st,black_king.nd,'w',&poz2)==0)
                        {
                            cos.push_back(slowo);
                        }
                        pom++;
                    }
                }
                //ruch wie¿y
                if (poz->plansza[i][j]=='r')
                {
                    int pom=1;
                    //sprawdzanie prawej czêci wiersza;
                    while(czy_w_planszy(i,j+pom)==1&&(poz->plansza[i][j+pom]>'z'||poz->plansza[i][j+pom]<'a'))
                    {
                        if (poz->plansza[i][j+pom]!=' ')
                        {
                            poz2=*poz;
                            string slowo=pole(i,j,i,j+pom);
                            porusz(slowo,&poz2);
                            if (czy_pole_jest_szachowane(black_king.st,black_king.nd,'w',&poz2)==0)
                            {
                                cos.push_back(slowo);
                            }
                            break;
                        }
                        poz2=*poz;
                        string slowo=pole(i,j,i,j+pom);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(black_king.st,black_king.nd,'w',&poz2)==0)
                        {
                            cos.push_back(slowo);
                        }
                        pom++;
                    }
                    pom=-1;
                    //sprawdzanie lewej czêci wiersza;
                    while(czy_w_planszy(i,j+pom)==1&&(poz->plansza[i][j+pom]>'z'||poz->plansza[i][j+pom]<'a'))
                    {
                        if (poz->plansza[i][j+pom]!=' ')
                        {
                            poz2=*poz;
                            string slowo=pole(i,j,i,j+pom);
                            porusz(slowo,&poz2);
                            if (czy_pole_jest_szachowane(black_king.st,black_king.nd,'w',&poz2)==0)
                            {
                                cos.push_back(slowo);
                            }
                            break;
                        }
                        poz2=*poz;
                        string slowo=pole(i,j,i,j+pom);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(black_king.st,black_king.nd,'w',&poz2)==0)
                        {
                            cos.push_back(slowo);
                        }
                        pom--;
                    }
                    pom=1;
                    //sprawdzanie dolnej czêci kolumny;
                    while(czy_w_planszy(i+pom,j)==1&&(poz->plansza[i+pom][j]>'z'||poz->plansza[i+pom][j]<'a'))
                    {
                        if (poz->plansza[i+pom][j]!=' ')
                        {
                            poz2=*poz;
                            string slowo=pole(i,j,i+pom,j);
                            porusz(slowo,&poz2);
                            if (czy_pole_jest_szachowane(black_king.st,black_king.nd,'w',&poz2)==0)
                            {
                                cos.push_back(slowo);
                            }
                            break;
                        }
                        poz2=*poz;
                        string slowo=pole(i,j,i+pom,j);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(black_king.st,black_king.nd,'w',&poz2)==0)
                        {
                            cos.push_back(slowo);
                        }
                        pom++;
                    }
                    pom=-1;
                    //sprawdzanie górnej czêci kolumny;
                    while(czy_w_planszy(i+pom,j)==1&&(poz->plansza[i+pom][j]>'z'||poz->plansza[i+pom][j]<'a'))
                    {
                        if (poz->plansza[i+pom][j]!=' ')
                        {
                            poz2=*poz;
                            string slowo=pole(i,j,i+pom,j);
                            porusz(slowo,&poz2);
                            if (czy_pole_jest_szachowane(black_king.st,black_king.nd,'w',&poz2)==0)
                            {
                                cos.push_back(slowo);
                            }
                            break;
                        }
                        poz2=*poz;
                        string slowo=pole(i,j,i+pom,j);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(black_king.st,black_king.nd,'w',&poz2)==0)
                        {
                            cos.push_back(slowo);
                        }
                        pom--;
                    }
                }
                //ruch laufra
                if (poz->plansza[i][j]=='b')
                {
                    int pom=-1;
                    //sprawdzanie lewej górnej przek¹tnej;
                    while(czy_w_planszy(i+pom,j+pom)==1&&(poz->plansza[i+pom][j+pom]>'z'||poz->plansza[i+pom][j+pom]<'a'))
                    {
                        if (poz->plansza[i+pom][j+pom]!=' ')
                        {
                            poz2=*poz;
                            string slowo=pole(i,j,i+pom,j+pom);
                            porusz(slowo,&poz2);
                            if (czy_pole_jest_szachowane(black_king.st,black_king.nd,'w',&poz2)==0)
                            {
                                cos.push_back(slowo);
                            }
                            break;
                        }
                        poz2=*poz;
                        string slowo=pole(i,j,i+pom,j+pom);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(black_king.st,black_king.nd,'w',&poz2)==0)
                        {
                            cos.push_back(slowo);
                        }
                        pom--;
                    }
                    pom=1;
                    //sprawdzanie prawej dolnej przek¹tnej;
                    while(czy_w_planszy(i+pom,j+pom)==1&&(poz->plansza[i+pom][j+pom]>'z'||poz->plansza[i+pom][j+pom]<'a'))
                    {
                        if (poz->plansza[i+pom][j+pom]!=' ')
                        {
                            poz2=*poz;
                            string slowo=pole(i,j,i+pom,j+pom);
                            porusz(slowo,&poz2);
                            if (czy_pole_jest_szachowane(black_king.st,black_king.nd,'w',&poz2)==0)
                            {
                                cos.push_back(slowo);
                            }
                            break;
                        }
                        poz2=*poz;
                        string slowo=pole(i,j,i+pom,j+pom);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(black_king.st,black_king.nd,'w',&poz2)==0)
                        {
                            cos.push_back(slowo);
                        }
                        pom++;
                    }
                    pom=1;
                    //sprawdzanie lewej dolnej przek¹tnej;
                    while(czy_w_planszy(i+pom,j-pom)==1&&(poz->plansza[i+pom][j-pom]>'z'||poz->plansza[i+pom][j-pom]<'a'))
                    {
                        if (poz->plansza[i+pom][j-pom]!=' ')
                        {
                            poz2=*poz;
                            string slowo=pole(i,j,i+pom,j-pom);
                            porusz(slowo,&poz2);
                            if (czy_pole_jest_szachowane(black_king.st,black_king.nd,'w',&poz2)==0)
                            {
                                cos.push_back(slowo);
                            }
                            break;
                        }
                        poz2=*poz;
                        string slowo=pole(i,j,i+pom,j-pom);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(black_king.st,black_king.nd,'w',&poz2)==0)
                        {
                            cos.push_back(slowo);
                        }
                        pom++;
                    }
                    pom=1;
                    //sprawdzanie prawej górnej przek¹tnej;
                    while(czy_w_planszy(i-pom,j+pom)==1&&(poz->plansza[i-pom][j+pom]>'z'||poz->plansza[i-pom][j+pom]<'a'))
                    {
                        if (poz->plansza[i-pom][j+pom]!=' ')
                        {
                            poz2=*poz;
                            string slowo=pole(i,j,i-pom,j+pom);
                            porusz(slowo,&poz2);
                            if (czy_pole_jest_szachowane(black_king.st,black_king.nd,'w',&poz2)==0)
                            {
                                cos.push_back(slowo);
                            }
                            break;
                        }
                        poz2=*poz;
                        string slowo=pole(i,j,i-pom,j+pom);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(black_king.st,black_king.nd,'w',&poz2)==0)
                        {
                            cos.push_back(slowo);
                        }
                        pom++;
                    }
                }
                //ruch skoczka
                if (poz->plansza[i][j]=='n')
                {
                    if (czy_w_planszy(i-2,j-1)==1&&(poz->plansza[i-2][j-1]>'z'||poz->plansza[i-2][j-1]<'a'))
                    {
                        poz2=*poz;
                        string slowo=pole(i,j,i-2,j-1);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(black_king.st,black_king.nd,'w',&poz2)==0)
                        {
                            cos.push_back(slowo);
                            //cout<<"1\n";
                        }
                    }
                    if (czy_w_planszy(i-1,j-2)==1&&(poz->plansza[i-1][j-2]>'z'||poz->plansza[i-1][j-2]<'a'))
                    {
                        poz2=*poz;
                        string slowo=pole(i,j,i-1,j-2);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(black_king.st,black_king.nd,'w',&poz2)==0)
                        {
                            cos.push_back(slowo);
                            //cout<<"2\n";
                        }
                    }
                    if (czy_w_planszy(i-2,j+1)==1&&(poz->plansza[i-2][j+1]>'z'||poz->plansza[i-2][j+1]<'a'))
                    {
                        poz2=*poz;
                        string slowo=pole(i,j,i-2,j+1);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(black_king.st,black_king.nd,'w',&poz2)==0)
                        {
                            cos.push_back(slowo);
                            //cout<<"3\n";
                        }
                    }
                    if (czy_w_planszy(i-1,j+2)==1&&(poz->plansza[i-1][j+2]>'z'||poz->plansza[i-1][j+2]<'a'))
                    {
                        poz2=*poz;
                        string slowo=pole(i,j,i-1,j+2);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(black_king.st,black_king.nd,'w',&poz2)==0)
                        {
                            cos.push_back(slowo);
                            //cout<<"4\n";
                        }
                    }
                    if (czy_w_planszy(i+2,j+1)==1&&(poz->plansza[i+2][j+1]>'z'||poz->plansza[i+2][j+1]<'a'))
                    {
                        poz2=*poz;
                        string slowo=pole(i,j,i+2,j+1);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(black_king.st,black_king.nd,'w',&poz2)==0)
                        {
                            cos.push_back(slowo);
                            //cout<<"5\n";
                        }
                    }
                    if (czy_w_planszy(i+1,j+2)==1&&(poz->plansza[i+1][j+2]>'z'||poz->plansza[i+1][j+2]<'a'))
                    {
                        poz2=*poz;
                        string slowo=pole(i,j,i+1,j+2);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(black_king.st,black_king.nd,'w',&poz2)==0)
                        {
                            cos.push_back(slowo);
                            //cout<<"6\n";
                        }
                    }
                    if (czy_w_planszy(i+2,j-1)==1&&(poz->plansza[i+2][j-1]>'z'||poz->plansza[i+2][j-1]<'a'))
                    {
                        poz2=*poz;
                        string slowo=pole(i,j,i+2,j-1);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(black_king.st,black_king.nd,'w',&poz2)==0)
                        {
                            cos.push_back(slowo);
                            //cout<<"7\n";
                        }
                    }
                    if (czy_w_planszy(i+1,j-2)==1&&(poz->plansza[i+1][j-2]>'z'||poz->plansza[i+1][j-2]<'a'))
                    {
                        poz2=*poz;
                        string slowo=pole(i,j,i+1,j-2);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(black_king.st,black_king.nd,'w',&poz2)==0)
                        {
                            cos.push_back(slowo);
                            //cout<<"8\n";
                        }
                    }
                }
                if (poz->plansza[i][j]=='p')
                {
                    if (i>1)
                    {
                        if (czy_w_planszy(i-1,j)==1&&poz->plansza[i-1][j]==' ')
                        {
                            poz2=*poz;
                            string slowo=pole(i,j,i-1,j);
                            porusz(slowo,&poz2);
                            if (czy_pole_jest_szachowane(black_king.st,black_king.nd,'w',&poz2)==0)
                            {
                                cos.push_back(slowo);
                            }
                        }
                        if (i==6&&czy_w_planszy(i-2,j)==1&&czy_w_planszy(i-1,j)==1&&poz->plansza[i-2][j]==' '&&poz->plansza[i-1][j]==' ')
                        {
                            poz2=*poz;
                            string slowo=pole(i,j,i-2,j);
                            porusz(slowo,&poz2);
                            if (czy_pole_jest_szachowane(black_king.st,black_king.nd,'w',&poz2)==0)
                            {
                                cos.push_back(slowo);
                            }
                        }
                        if (czy_w_planszy(i-1,j+1)==1&&poz->plansza[i-1][j+1]>='A'&&poz->plansza[i-1][j+1]<='Z')
                        {
                            poz2=*poz;
                            string slowo=pole(i,j,i-1,j+1);
                            porusz(slowo,&poz2);
                            if (czy_pole_jest_szachowane(black_king.st,black_king.nd,'w',&poz2)==0)
                            {
                                cos.push_back(slowo);
                            }
                        }
                        if (czy_w_planszy(i-1,j-1)==1&&poz->plansza[i-1][j-1]>='A'&&poz->plansza[i-1][j-1]<='Z')
                        {
                            poz2=*poz;
                            string slowo=pole(i,j,i-1,j-1);
                            porusz(slowo,&poz2);
                            if (czy_pole_jest_szachowane(black_king.st,black_king.nd,'w',&poz2)==0)
                            {
                                cos.push_back(slowo);
                            }
                        }
                    }
                    if (i==1)//promocje;
                    {
                        if (czy_w_planszy(i-1,j)==1&&poz->plansza[i-1][j]==' ')
                        {
                            string slowo=pole(i,j,i-1,j);
                            slowo+="q";
                            poz2=*poz;
                            porusz(slowo,&poz2);
                            if (czy_pole_jest_szachowane(black_king.st,black_king.nd,'w',&poz2)==0)
                            {
                                cos.push_back(slowo);
                                slowo.pop_back();
                                slowo+="r";
                                cos.push_back(slowo);
                                slowo.pop_back();
                                slowo+="b";
                                cos.push_back(slowo);
                                slowo.pop_back();
                                slowo+="n";
                                cos.push_back(slowo);
                                slowo.pop_back();
                            }
                        }
                        if (czy_w_planszy(i-1,j+1)==1&&poz->plansza[i-1][j+1]>='A'&&poz->plansza[i-1][j+1]<='Z')
                        {
                            string slowo=pole(i,j,i-1,j+1);
                            slowo+="q";
                            poz2=*poz;
                            porusz(slowo,&poz2);
                            if (czy_pole_jest_szachowane(black_king.st,black_king.nd,'w',&poz2)==0)
                            {
                                cos.push_back(slowo);
                                slowo.pop_back();
                                slowo+="r";
                                cos.push_back(slowo);
                                slowo.pop_back();
                                slowo+="b";
                                cos.push_back(slowo);
                                slowo.pop_back();
                                slowo+="n";
                                cos.push_back(slowo);
                                slowo.pop_back();
                            }
                        }
                        if (czy_w_planszy(i-1,j-1)==1&&poz->plansza[i-1][j-1]>='A'&&poz->plansza[i-1][j-1]<='Z')
                        {
                            string slowo=pole(i,j,i-1,j-1);
                            slowo+="q";
                            poz2=*poz;
                            porusz(slowo,&poz2);
                            if (czy_pole_jest_szachowane(black_king.st,black_king.nd,'w',&poz2)==0)
                            {
                                cos.push_back(slowo);
                                slowo.pop_back();
                                slowo+="r";
                                cos.push_back(slowo);
                                slowo.pop_back();
                                slowo+="b";
                                cos.push_back(slowo);
                                slowo.pop_back();
                                slowo+="n";
                                cos.push_back(slowo);
                                slowo.pop_back();
                            }
                        }
                    }
                    if (poz->czy_bicie_w_przelocie==1)//bwp;
                    {
                        if (i==pole_w_liczby(poz->kolumna_bwp,poz->wiersz_bwp)[0]+1&&j==pole_w_liczby(poz->kolumna_bwp,poz->wiersz_bwp)[1]-1)
                        {
                            string slowo=pole(i,j,i-1,j+1);
                            poz2=*poz;
                            porusz(slowo,&poz2);
                            if (czy_pole_jest_szachowane(black_king.st,black_king.nd,'w',&poz2)==0)
                            {
                                cos.push_back(slowo);
                            }
                        }
                        if (i==pole_w_liczby(poz->kolumna_bwp,poz->wiersz_bwp)[0]+1&&j==pole_w_liczby(poz->kolumna_bwp,poz->wiersz_bwp)[1]+1)
                        {
                            string slowo=pole(i,j,i-1,j-1);
                            poz2=*poz;
                            porusz(slowo,&poz2);
                            if (czy_pole_jest_szachowane(black_king.st,black_king.nd,'w',&poz2)==0)
                            {
                                cos.push_back(slowo);
                            }
                        }
                    }
                }
            }
        }
    }
    if (poz->czyj_ruch=='w')
    {
        //cout<<"debug\n";
        for (int i=0;i<8;i++)
        {
            for (int j=0;j<8;j++)
            {
                //ruch króla;
                if (poz->plansza[i][j]=='K')
                {
                    if (czy_w_planszy(i-1,j-1)==1&&(poz->plansza[i-1][j-1]>'Z'||poz->plansza[i-1][j-1]<'A'))
                    {
                        poz2=*poz;
                        string slowo=pole(i,j,i-1,j-1);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(i-1,j-1,'b',&poz2)==0)
                        {
                            cos.push_back(slowo);
                        }
                    }
                    if (czy_w_planszy(i+1,j-1)==1&&(poz->plansza[i+1][j-1]>'Z'||poz->plansza[i+1][j-1]<'A'))
                    {
                        poz2=*poz;
                        string slowo=pole(i,j,i+1,j-1);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(i+1,j-1,'b',&poz2)==0)
                        {
                            cos.push_back(slowo);
                        }
                    }
                    if (czy_w_planszy(i-1,j+1)==1&&(poz->plansza[i-1][j+1]>'Z'||poz->plansza[i-1][j+1]<'A'))
                    {
                        poz2=*poz;
                        string slowo=pole(i,j,i-1,j+1);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(i-1,j+1,'b',&poz2)==0)
                        {
                            cos.push_back(slowo);
                        }
                    }
                    if (czy_w_planszy(i+1,j+1)==1&&(poz->plansza[i+1][j+1]>'Z'||poz->plansza[i+1][j+1]<'A'))
                    {
                        poz2=*poz;
                        string slowo=pole(i,j,i+1,j+1);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(i+1,j+1,'b',&poz2)==0)
                        {
                            cos.push_back(slowo);
                        }
                    }
                    if (czy_w_planszy(i-1,j)==1&&(poz->plansza[i-1][j]>'Z'||poz->plansza[i-1][j]<'A'))
                    {
                        poz2=*poz;
                        string slowo=pole(i,j,i-1,j);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(i-1,j,'b',&poz2)==0)
                        {
                            cos.push_back(slowo);
                        }
                    }
                    if (czy_w_planszy(i,j-1)==1&&(poz->plansza[i][j-1]>'Z'||poz->plansza[i][j-1]<'A'))
                    {
                        poz2=*poz;
                        string slowo=pole(i,j,i,j-1);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(i,j-1,'b',&poz2)==0)
                        {
                            cos.push_back(slowo);
                        }
                    }
                    if (czy_w_planszy(i+1,j)==1&&(poz->plansza[i+1][j]>'Z'||poz->plansza[i+1][j]<'A'))
                    {
                        poz2=*poz;
                        string slowo=pole(i,j,i+1,j);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(i+1,j,'b',&poz2)==0)
                        {
                            cos.push_back(slowo);
                        }
                    }
                    if (czy_w_planszy(i,j+1)==1&&(poz->plansza[i][j+1]>'Z'||poz->plansza[i][j+1]<'A'))
                    {
                        poz2=*poz;
                        string slowo=pole(i,j,i,j+1);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(i,j+1,'b',&poz2)==0)
                        {
                            cos.push_back(slowo);
                        }
                    }
                    if (poz->czy_K==1)//roszada krótka;
                    {
                        if (czy_pole_jest_szachowane(i,j,'b',poz)==0)
                        {
                            if (poz->plansza[0][5]==' '&&poz->plansza[0][6]==' '&&czy_pole_jest_szachowane(0,5,'b',poz)==0&&czy_pole_jest_szachowane(0,6,'b',poz)==0)
                            {
                                string slowo=pole(i,j,0,6);
                                cos.push_back(slowo);
                            }
                        }
                    }
                    if (poz->czy_Q==1)//roszada d³uga;
                    {
                        if (czy_pole_jest_szachowane(i,j,'b',poz)==0)
                        {
                            if (poz->plansza[0][2]==' '&&poz->plansza[0][1]==' '&&poz->plansza[0][3]==' '&&czy_pole_jest_szachowane(0,2,'b',poz)==0&&czy_pole_jest_szachowane(0,3,'b',poz)==0)
                            {
                                string slowo=pole(i,j,0,1);
                                cos.push_back(slowo);
                            }
                        }
                    }
                }
                //ruch królowej;
                if (poz->plansza[i][j]=='Q')
                {
                    int pom=1;
                    //sprawdzanie prawej czêci wiersza;
                    while(czy_w_planszy(i,j+pom)==1&&(poz->plansza[i][j+pom]>'Z'||poz->plansza[i][j+pom]<'A'))
                    {
                        if (poz->plansza[i][j+pom]!=' ')
                        {
                            poz2=*poz;
                            string slowo=pole(i,j,i,j+pom);
                            porusz(slowo,&poz2);
                            if (czy_pole_jest_szachowane(white_king.st,white_king.nd,'b',&poz2)==0)
                            {
                                cos.push_back(slowo);
                            }
                            break;
                        }
                        poz2=*poz;
                        string slowo=pole(i,j,i,j+pom);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(white_king.st,white_king.nd,'b',&poz2)==0)
                        {
                            cos.push_back(slowo);
                        }
                        pom++;
                    }
                    pom=-1;
                    //sprawdzanie lewej czêci wiersza;
                    while(czy_w_planszy(i,j+pom)==1&&(poz->plansza[i][j+pom]>'Z'||poz->plansza[i][j+pom]<'A'))
                    {
                        if (poz->plansza[i][j+pom]!=' ')
                        {
                            poz2=*poz;
                            string slowo=pole(i,j,i,j+pom);
                            porusz(slowo,&poz2);
                            if (czy_pole_jest_szachowane(white_king.st,white_king.nd,'b',&poz2)==0)
                            {
                                cos.push_back(slowo);
                            }
                            break;
                        }
                        poz2=*poz;
                        string slowo=pole(i,j,i,j+pom);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(white_king.st,white_king.nd,'b',&poz2)==0)
                        {
                            cos.push_back(slowo);
                        }
                        pom--;
                    }
                    pom=1;
                    //sprawdzanie dolnej czêci kolumny;
                    while(czy_w_planszy(i+pom,j)==1&&(poz->plansza[i+pom][j]>'Z'||poz->plansza[i+pom][j]<'A'))
                    {
                        if (poz->plansza[i+pom][j]!=' ')
                        {
                            poz2=*poz;
                            string slowo=pole(i,j,i+pom,j);
                            porusz(slowo,&poz2);
                            if (czy_pole_jest_szachowane(white_king.st,white_king.nd,'b',&poz2)==0)
                            {
                                cos.push_back(slowo);
                            }
                            break;
                        }
                        poz2=*poz;
                        string slowo=pole(i,j,i+pom,j);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(white_king.st,white_king.nd,'b',&poz2)==0)
                        {
                            cos.push_back(slowo);
                        }
                        pom++;
                    }
                    pom=-1;
                    //sprawdzanie górnej czêci kolumny;
                    while(czy_w_planszy(i+pom,j)==1&&(poz->plansza[i+pom][j]>'Z'||poz->plansza[i+pom][j]<'A'))
                    {
                        if (poz->plansza[i+pom][j]!=' ')
                        {
                            poz2=*poz;
                            string slowo=pole(i,j,i+pom,j);
                            porusz(slowo,&poz2);
                            if (czy_pole_jest_szachowane(white_king.st,white_king.nd,'b',&poz2)==0)
                            {
                                cos.push_back(slowo);
                            }
                            break;
                        }
                        poz2=*poz;
                        string slowo=pole(i,j,i+pom,j);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(white_king.st,white_king.nd,'b',&poz2)==0)
                        {
                            cos.push_back(slowo);
                        }
                        pom--;
                    }
                    pom=-1;
                    //sprawdzanie lewej górnej przek¹tnej;
                    while(czy_w_planszy(i+pom,j+pom)==1&&(poz->plansza[i+pom][j+pom]>'Z'||poz->plansza[i+pom][j+pom]<'A'))
                    {
                        if (poz->plansza[i+pom][j+pom]!=' ')
                        {
                            poz2=*poz;
                            string slowo=pole(i,j,i+pom,j+pom);
                            porusz(slowo,&poz2);
                            if (czy_pole_jest_szachowane(white_king.st,white_king.nd,'b',&poz2)==0)
                            {
                                cos.push_back(slowo);
                            }
                            break;
                        }
                        poz2=*poz;
                        string slowo=pole(i,j,i+pom,j+pom);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(white_king.st,white_king.nd,'b',&poz2)==0)
                        {
                            cos.push_back(slowo);
                        }
                        pom--;
                    }
                    pom=1;
                    //sprawdzanie prawej dolnej przek¹tnej;
                    while(czy_w_planszy(i+pom,j+pom)==1&&(poz->plansza[i+pom][j+pom]>'Z'||poz->plansza[i+pom][j+pom]<'A'))
                    {
                        if (poz->plansza[i+pom][j+pom]!=' ')
                        {
                            poz2=*poz;
                            string slowo=pole(i,j,i+pom,j+pom);
                            porusz(slowo,&poz2);
                            if (czy_pole_jest_szachowane(white_king.st,white_king.nd,'b',&poz2)==0)
                            {
                                cos.push_back(slowo);
                            }
                            break;
                        }
                        poz2=*poz;
                        string slowo=pole(i,j,i+pom,j+pom);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(white_king.st,white_king.nd,'b',&poz2)==0)
                        {
                            cos.push_back(slowo);
                        }
                        pom++;
                    }
                    pom=1;
                    //sprawdzanie lewej dolnej przek¹tnej;
                    while(czy_w_planszy(i+pom,j-pom)==1&&(poz->plansza[i+pom][j-pom]>'Z'||poz->plansza[i+pom][j-pom]<'A'))
                    {
                        if (poz->plansza[i+pom][j-pom]!=' ')
                        {
                            poz2=*poz;
                            string slowo=pole(i,j,i+pom,j-pom);
                            porusz(slowo,&poz2);
                            if (czy_pole_jest_szachowane(white_king.st,white_king.nd,'b',&poz2)==0)
                            {
                                cos.push_back(slowo);
                            }
                            break;
                        }
                        poz2=*poz;
                        string slowo=pole(i,j,i+pom,j-pom);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(white_king.st,white_king.nd,'b',&poz2)==0)
                        {
                            cos.push_back(slowo);
                        }
                        pom++;
                    }
                    pom=1;
                    //sprawdzanie prawej górnej przek¹tnej;
                    while(czy_w_planszy(i-pom,j+pom)==1&&(poz->plansza[i-pom][j+pom]>'Z'||poz->plansza[i-pom][j+pom]<'A'))
                    {
                        if (poz->plansza[i-pom][j+pom]!=' ')
                        {
                            poz2=*poz;
                            string slowo=pole(i,j,i-pom,j+pom);
                            porusz(slowo,&poz2);
                            if (czy_pole_jest_szachowane(white_king.st,white_king.nd,'b',&poz2)==0)
                            {
                                cos.push_back(slowo);
                            }
                            break;
                        }
                        poz2=*poz;
                        string slowo=pole(i,j,i-pom,j+pom);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(white_king.st,white_king.nd,'b',&poz2)==0)
                        {
                            cos.push_back(slowo);
                        }
                        pom++;
                    }
                }
                //ruch wie¿y
                if (poz->plansza[i][j]=='R')
                {
                    int pom=1;
                    //sprawdzanie prawej czêci wiersza;
                    while(czy_w_planszy(i,j+pom)==1&&(poz->plansza[i][j+pom]>'Z'||poz->plansza[i][j+pom]<'A'))
                    {
                        if (poz->plansza[i][j+pom]!=' ')
                        {
                            poz2=*poz;
                            string slowo=pole(i,j,i,j+pom);
                            porusz(slowo,&poz2);
                            if (czy_pole_jest_szachowane(white_king.st,white_king.nd,'b',&poz2)==0)
                            {
                                cos.push_back(slowo);
                            }
                            break;
                        }
                        poz2=*poz;
                        string slowo=pole(i,j,i,j+pom);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(white_king.st,white_king.nd,'b',&poz2)==0)
                        {
                            cos.push_back(slowo);
                        }
                        pom++;
                    }
                    pom=-1;
                    //sprawdzanie lewej czêci wiersza;
                    while(czy_w_planszy(i,j+pom)==1&&(poz->plansza[i][j+pom]>'Z'||poz->plansza[i][j+pom]<'A'))
                    {
                        if (poz->plansza[i][j+pom]!=' ')
                        {
                            poz2=*poz;
                            string slowo=pole(i,j,i,j+pom);
                            porusz(slowo,&poz2);
                            if (czy_pole_jest_szachowane(white_king.st,white_king.nd,'b',&poz2)==0)
                            {
                                cos.push_back(slowo);
                            }
                            break;
                        }
                        poz2=*poz;
                        string slowo=pole(i,j,i,j+pom);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(white_king.st,white_king.nd,'b',&poz2)==0)
                        {
                            cos.push_back(slowo);
                        }
                        pom--;
                    }
                    pom=1;
                    //sprawdzanie dolnej czêci kolumny;
                    while(czy_w_planszy(i+pom,j)==1&&(poz->plansza[i+pom][j]>'Z'||poz->plansza[i+pom][j]<'A'))
                    {
                        if (poz->plansza[i+pom][j]!=' ')
                        {
                            poz2=*poz;
                            string slowo=pole(i,j,i+pom,j);
                            porusz(slowo,&poz2);
                            if (czy_pole_jest_szachowane(white_king.st,white_king.nd,'b',&poz2)==0)
                            {
                                cos.push_back(slowo);
                            }
                            break;
                        }
                        poz2=*poz;
                        string slowo=pole(i,j,i+pom,j);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(white_king.st,white_king.nd,'b',&poz2)==0)
                        {
                            cos.push_back(slowo);
                        }
                        pom++;
                    }
                    pom=-1;
                    //sprawdzanie górnej czêci kolumny;
                    while(czy_w_planszy(i+pom,j)==1&&(poz->plansza[i+pom][j]>'Z'||poz->plansza[i+pom][j]<'A'))
                    {
                        if (poz->plansza[i+pom][j]!=' ')
                        {
                            poz2=*poz;
                            string slowo=pole(i,j,i+pom,j);
                            porusz(slowo,&poz2);
                            if (czy_pole_jest_szachowane(white_king.st,white_king.nd,'b',&poz2)==0)
                            {
                                cos.push_back(slowo);
                            }
                            break;
                        }
                        poz2=*poz;
                        string slowo=pole(i,j,i+pom,j);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(white_king.st,white_king.nd,'b',&poz2)==0)
                        {
                            cos.push_back(slowo);
                        }
                        pom--;
                    }
                }
                //ruch laufra
                if (poz->plansza[i][j]=='B')
                {
                    int pom=-1;
                    //sprawdzanie lewej górnej przek¹tnej;
                    while(czy_w_planszy(i+pom,j+pom)==1&&(poz->plansza[i+pom][j+pom]>'Z'||poz->plansza[i+pom][j+pom]<'A'))
                    {
                        if (poz->plansza[i+pom][j+pom]!=' ')
                        {
                            poz2=*poz;
                            string slowo=pole(i,j,i+pom,j+pom);
                            porusz(slowo,&poz2);
                            if (czy_pole_jest_szachowane(white_king.st,white_king.nd,'b',&poz2)==0)
                            {
                                cos.push_back(slowo);
                            }
                            break;
                        }
                        poz2=*poz;
                        string slowo=pole(i,j,i+pom,j+pom);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(white_king.st,white_king.nd,'b',&poz2)==0)
                        {
                            cos.push_back(slowo);
                        }
                        pom--;
                    }
                    pom=1;
                    //sprawdzanie prawej dolnej przek¹tnej;
                    while(czy_w_planszy(i+pom,j+pom)==1&&(poz->plansza[i+pom][j+pom]>'Z'||poz->plansza[i+pom][j+pom]<'A'))
                    {
                        if (poz->plansza[i+pom][j+pom]!=' ')
                        {
                            poz2=*poz;
                            string slowo=pole(i,j,i+pom,j+pom);
                            porusz(slowo,&poz2);
                            if (czy_pole_jest_szachowane(white_king.st,white_king.nd,'b',&poz2)==0)
                            {
                                cos.push_back(slowo);
                            }
                            break;
                        }
                        poz2=*poz;
                        string slowo=pole(i,j,i+pom,j+pom);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(white_king.st,white_king.nd,'b',&poz2)==0)
                        {
                            cos.push_back(slowo);
                        }
                        pom++;
                    }
                    pom=1;
                    //sprawdzanie lewej dolnej przek¹tnej;
                    while(czy_w_planszy(i+pom,j-pom)==1&&(poz->plansza[i+pom][j-pom]>'Z'||poz->plansza[i+pom][j-pom]<'A'))
                    {
                        if (poz->plansza[i+pom][j-pom]!=' ')
                        {
                            poz2=*poz;
                            string slowo=pole(i,j,i+pom,j-pom);
                            porusz(slowo,&poz2);
                            if (czy_pole_jest_szachowane(white_king.st,white_king.nd,'b',&poz2)==0)
                            {
                                cos.push_back(slowo);
                            }
                            break;
                        }
                        poz2=*poz;
                        string slowo=pole(i,j,i+pom,j-pom);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(white_king.st,white_king.nd,'b',&poz2)==0)
                        {
                            cos.push_back(slowo);
                        }
                        pom++;
                    }
                    pom=1;
                    //sprawdzanie prawej górnej przek¹tnej;
                    while(czy_w_planszy(i-pom,j+pom)==1&&(poz->plansza[i-pom][j+pom]>'Z'||poz->plansza[i-pom][j+pom]<'A'))
                    {
                        if (poz->plansza[i-pom][j+pom]!=' ')
                        {
                            poz2=*poz;
                            string slowo=pole(i,j,i-pom,j+pom);
                            porusz(slowo,&poz2);
                            if (czy_pole_jest_szachowane(white_king.st,white_king.nd,'b',&poz2)==0)
                            {
                                cos.push_back(slowo);
                            }
                            break;
                        }
                        poz2=*poz;
                        string slowo=pole(i,j,i-pom,j+pom);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(white_king.st,white_king.nd,'b',&poz2)==0)
                        {
                            cos.push_back(slowo);
                        }
                        pom++;
                    }
                }
                //ruch skoczka
                if (poz->plansza[i][j]=='N')
                {
                    if (czy_w_planszy(i-2,j-1)==1&&(poz->plansza[i-2][j-1]>'Z'||poz->plansza[i-2][j-1]<'A'))
                    {
                        poz2=*poz;
                        string slowo=pole(i,j,i-2,j-1);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(white_king.st,white_king.nd,'b',&poz2)==0)
                        {
                            cos.push_back(slowo);
                        }
                    }
                    if (czy_w_planszy(i-1,j-2)==1&&(poz->plansza[i-1][j-2]>'Z'||poz->plansza[i-1][j-2]<'A'))
                    {
                        poz2=*poz;
                        string slowo=pole(i,j,i-1,j-2);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(white_king.st,white_king.nd,'b',&poz2)==0)
                        {
                            cos.push_back(slowo);
                        }
                    }
                    if (czy_w_planszy(i-2,j+1)==1&&(poz->plansza[i-2][j+1]>'Z'||poz->plansza[i-2][j+1]<'A'))
                    {
                        poz2=*poz;
                        string slowo=pole(i,j,i-2,j+1);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(white_king.st,white_king.nd,'b',&poz2)==0)
                        {
                            cos.push_back(slowo);
                        }
                    }
                    if (czy_w_planszy(i-1,j+2)==1&&(poz->plansza[i-1][j+2]>'Z'||poz->plansza[i-1][j+2]<'A'))
                    {
                        poz2=*poz;
                        string slowo=pole(i,j,i-1,j+2);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(white_king.st,white_king.nd,'b',&poz2)==0)
                        {
                            cos.push_back(slowo);
                        }
                    }
                    if (czy_w_planszy(i+2,j+1)==1&&(poz->plansza[i+2][j+1]>'Z'||poz->plansza[i+2][j+1]<'A'))
                    {
                        poz2=*poz;
                        string slowo=pole(i,j,i+2,j+1);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(white_king.st,white_king.nd,'b',&poz2)==0)
                        {
                            cos.push_back(slowo);
                        }
                    }
                    if (czy_w_planszy(i+1,j+2)==1&&(poz->plansza[i+1][j+2]>'Z'||poz->plansza[i+1][j+2]<'A'))
                    {
                        poz2=*poz;
                        string slowo=pole(i,j,i+1,j+2);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(white_king.st,white_king.nd,'b',&poz2)==0)
                        {
                            cos.push_back(slowo);
                        }
                    }
                    if (czy_w_planszy(i+2,j-1)==1&&(poz->plansza[i+2][j-1]>'Z'||poz->plansza[i+2][j-1]<'A'))
                    {
                        poz2=*poz;
                        string slowo=pole(i,j,i+2,j-1);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(white_king.st,white_king.nd,'b',&poz2)==0)
                        {
                            cos.push_back(slowo);
                        }
                    }
                    if (czy_w_planszy(i+1,j-2)==1&&(poz->plansza[i+1][j-2]>'Z'||poz->plansza[i+1][j-2]<'A'))
                    {
                        poz2=*poz;
                        string slowo=pole(i,j,i+1,j-2);
                        porusz(slowo,&poz2);
                        if (czy_pole_jest_szachowane(white_king.st,white_king.nd,'b',&poz2)==0)
                        {
                            cos.push_back(slowo);
                        }
                    }
                }
                if (poz->plansza[i][j]=='P')
                {
                    if (i<6)
                    {
                        if (czy_w_planszy(i+1,j)==1&&poz->plansza[i+1][j]==' ')
                        {
                            poz2=*poz;
                            string slowo=pole(i,j,i+1,j);
                            porusz(slowo,&poz2);
                            //cout<<"rozpatruje pionka\n";
                            //wizualizacja(&poz2);
                            //cout<<"\n";
                            if (czy_pole_jest_szachowane(white_king.st,white_king.nd,'b',&poz2)==0)
                            {
                                //cout<<"nie wyszlo\n";
                                cos.push_back(slowo);
                                //cout<<slowo<<"\n";
                                //licznik++;
                            }
                        }
                        if (i==1&&czy_w_planszy(i+2,j)==1&&czy_w_planszy(i+1,j)==1&&poz->plansza[i+2][j]==' '&&poz->plansza[i+1][j]==' ')
                        {
                            poz2=*poz;
                            string slowo=pole(i,j,i+2,j);
                            porusz(slowo,&poz2);
                            if (czy_pole_jest_szachowane(white_king.st,white_king.nd,'b',&poz2)==0)
                            {
                                cos.push_back(slowo);
                                //cout<<slowo<<"\n";
                                //licznik++;
                            }
                        }
                        if (czy_w_planszy(i+1,j+1)==1&&poz->plansza[i+1][j+1]>='a'&&poz->plansza[i+1][j+1]<='z')
                        {
                            poz2=*poz;
                            string slowo=pole(i,j,i+1,j+1);
                            porusz(slowo,&poz2);
                            if (czy_pole_jest_szachowane(white_king.st,white_king.nd,'b',&poz2)==0)
                            {
                                cos.push_back(slowo);
                                //cout<<slowo<<"\n";
                                //licznik++;
                            }
                        }
                        if (czy_w_planszy(i+1,j-1)==1&&poz->plansza[i+1][j-1]>='a'&&poz->plansza[i+1][j-1]<='z')
                        {
                            poz2=*poz;
                            string slowo=pole(i,j,i+1,j-1);
                            porusz(slowo,&poz2);
                            if (czy_pole_jest_szachowane(white_king.st,white_king.nd,'b',&poz2)==0)
                            {
                                cos.push_back(slowo);
                                //cout<<slowo<<"\n";
                                //licznik++;
                            }
                        }
                    }
                    if (i==6)//promocje;
                    {
                        //cout<<"promocje\n";
                        if (czy_w_planszy(i+1,j)==1&&poz->plansza[i+1][j]==' ')
                        {
                            string slowo=pole(i,j,i+1,j);
                            slowo+="Q";
                            poz2=*poz;
                            porusz(slowo,&poz2);
                            if (czy_pole_jest_szachowane(white_king.st,white_king.nd,'b',&poz2)==0)
                            {
                                //cout<<"opcja1\n";
                                cos.push_back(slowo);
                                //cout<<slowo<<"\n";
                                //licznik++;
                                slowo.pop_back();
                                slowo+="R";
                                cos.push_back(slowo);
                                //cout<<slowo<<"\n";
                                //licznik++;
                                slowo.pop_back();
                                slowo+="B";
                                cos.push_back(slowo);
                                //cout<<slowo<<"\n";
                                //licznik++;
                                slowo.pop_back();
                                slowo+="N";
                                cos.push_back(slowo);
                                //cout<<slowo<<"\n";
                                //licznik++;
                                slowo.pop_back();
                            }
                        }
                        if (czy_w_planszy(i+1,j+1)==1&&poz->plansza[i+1][j+1]>='a'&&poz->plansza[i+1][j+1]<='z')
                        {
                            string slowo=pole(i,j,i+1,j+1);
                            slowo+="Q";
                            poz2=*poz;
                            porusz(slowo,&poz2);
                            if (czy_pole_jest_szachowane(white_king.st,white_king.nd,'b',&poz2)==0)
                            {
                                //cout<<"opcja2\n";
                                cos.push_back(slowo);
                                //cout<<slowo<<"\n";
                                //licznik++;
                                slowo.pop_back();
                                slowo+="R";
                                cos.push_back(slowo);
                                //cout<<slowo<<"\n";
                                //licznik++;
                                slowo.pop_back();
                                slowo+="B";
                                cos.push_back(slowo);
                                //cout<<slowo<<"\n";
                                //licznik++;
                                slowo.pop_back();
                                slowo+="N";
                                cos.push_back(slowo);
                                //cout<<slowo<<"\n";
                                //licznik++;
                                slowo.pop_back();
                            }
                        }
                        if (czy_w_planszy(i+1,j-1)==1&&poz->plansza[i+1][j-1]>='a'&&poz->plansza[i+1][j-1]<='z')
                        {
                            string slowo=pole(i,j,i+1,j-1);
                            slowo+="Q";
                            poz2=*poz;
                            porusz(slowo,&poz2);
                            if (czy_pole_jest_szachowane(white_king.st,white_king.nd,'b',&poz2)==0)
                            {
                                //cout<<"opcja3\n";
                                cos.push_back(slowo);
                                //cout<<slowo<<"\n";
                                //licznik++;
                                slowo.pop_back();
                                slowo+="R";
                                cos.push_back(slowo);
                                //cout<<slowo<<"\n";
                                //licznik++;
                                slowo.pop_back();
                                slowo+="B";
                                cos.push_back(slowo);
                                //cout<<slowo<<"\n";
                                //licznik++;
                                slowo.pop_back();
                                slowo+="N";
                                cos.push_back(slowo);
                                //cout<<slowo<<"\n";
                                //licznik++;
                                slowo.pop_back();
                            }
                        }
                    }
                    if ((poz->czy_bicie_w_przelocie)==1)//bwp;
                    {
                        //cout<<"\n"<<pole_w_liczby(poz->kolumna_bwp,poz->wiersz_bwp)[0]<<" "<<pole_w_liczby(poz->kolumna_bwp,poz->wiersz_bwp)[1]<<"\n";
                        if (i==pole_w_liczby(poz->kolumna_bwp,poz->wiersz_bwp)[0]-1&&j==pole_w_liczby(poz->kolumna_bwp,poz->wiersz_bwp)[1]-1)
                        {
                            string slowo=pole(i,j,i+1,j+1);
                            poz2=*poz;
                            porusz(slowo,&poz2);
                            if (czy_pole_jest_szachowane(white_king.st,white_king.nd,'b',&poz2)==0)
                            {
                                cos.push_back(slowo);
                                //cout<<slowo<<"\n";
                                //licznik++;
                            }
                        }
                        if (i==pole_w_liczby(poz->kolumna_bwp,poz->wiersz_bwp)[0]-1&&j==pole_w_liczby(poz->kolumna_bwp,poz->wiersz_bwp)[1]+1)
                        {
                            string slowo=pole(i,j,i+1,j-1);
                            poz2=*poz;
                            porusz(slowo,&poz2);
                            if (czy_pole_jest_szachowane(white_king.st,white_king.nd,'b',&poz2)==0)
                            {
                                cos.push_back(slowo);
                                //cout<<slowo<<"\n";
                                //licznik++;
                            }
                        }
                    }
                }
            }
        }
    }
    return cos;
}

void los1(int a,int b,int tab[12][64])
{
    mt19937_64 gen(getpid());
    for (int i=0;i<12;i++)
    {
    	for (int j=0;j<64;j++)
    	{
    	    tab[i][j]=gen()%(b-a+1)+a;
    	}
    }
}

void los2(int a,int b,int tab[13])
{
    mt19937_64 gen(getpid());
    for (int i=0;i<13;i++)
    {
        tab[i]=gen()%(b-a+1)+a;
    }
}

//kolejnosc figur w Zobrist1 tabelce
// k,h,r,b,n,p,K,H,R,B,N,P
//kolejnosc zdarzen w Zobrist2 tabelce
// czyj_ruch (jak białych to xor a jak czarnych to unxor), roszady: czy_K, czy_Q, czy_k, czy_q, bwp: dla białych a3,b3,...,h3, dla czarnych a6,b6,...,h6;

int Zobrist_hash_start(pozycja *poz,int *tab1,int *tab2)
{
    int wynik=0;
    for (int i=0;i<8;i++)
    {
    	for (int j=0;j<8;j++)
    	{
    	    if (poz->plansza[i][j]=='k')
    	    {
    	    	wynik^=tab1[i*8+j];
    	    }
    	    else if (poz->plansza[i][j]=='h')
    	    {
    	    	wynik^=tab1[1*64+i*8+j];
    	    }
    	    else if (poz->plansza[i][j]=='r')
    	    {
    	    	wynik^=tab1[2*64+i*8+j];
    	    }
    	    else if (poz->plansza[i][j]=='b')
    	    {
    	    	wynik^=tab1[3*64+i*8+j];
    	    }
    	    else if (poz->plansza[i][j]=='n')
    	    {
    	    	wynik^=tab1[4*64+i*8+j];
    	    }
    	    else if (poz->plansza[i][j]=='p')
    	    {
    	    	wynik^=tab1[5*64+i*8+j];
    	    }
    	    else if (poz->plansza[i][j]=='K')
    	    {
    	    	wynik^=tab1[6*64+i*8+j];
    	    }
    	    else if (poz->plansza[i][j]=='H')
    	    {
    	    	wynik^=tab1[7*64+i*8+j];
    	    }
    	    else if (poz->plansza[i][j]=='R')
    	    {
    	    	wynik^=tab1[8*64+i*8+j];
    	    }
    	    else if (poz->plansza[i][j]=='B')
    	    {
    	    	wynik^=tab1[9*64+i*8+j];
    	    }
    	    else if (poz->plansza[i][j]=='N')
    	    {
    	    	wynik^=tab1[10*64+i*8+j];
    	    }
    	    else if (poz->plansza[i][j]=='P')
    	    {
    	    	wynik^=tab1[11*64+i*8+j];
    	    }
    	}
    }
    if (poz->czyj_ruch=='w')
    {
    	wynik^=tab2[0];
    }
    if (poz->czy_K==1)
    {
    	wynik^=tab2[1];
    }
    if (poz->czy_Q==1)
    {
    	wynik^=tab2[2];
    }
    if (poz->czy_k==1)
    {
    	wynik^=tab2[3];
    }
    if (poz->czy_q==1)
    {
    	wynik^=tab2[4];
    }
    if (poz->czy_bicie_w_przelocie==1)
    {
    	if (poz->kolumna_bwp=='a')
    	{
    	    wynik^=tab2[5];
    	}
    	else if (poz->kolumna_bwp=='b')
    	{
    	    wynik^=tab2[6];
    	}
    	else if (poz->kolumna_bwp=='c')
    	{
    	    wynik^=tab2[7];
    	}
    	else if (poz->kolumna_bwp=='d')
    	{
    	    wynik^=tab2[8];
    	}
    	else if (poz->kolumna_bwp=='e')
    	{
    	    wynik^=tab2[9];
    	}
    	else if (poz->kolumna_bwp=='f')
    	{
    	    wynik^=tab2[10];
    	}
    	else if (poz->kolumna_bwp=='g')
    	{
    	    wynik^=tab2[11];
    	}
    	else if (poz->kolumna_bwp=='h')
    	{
    	    wynik^=tab2[12];
    	}
    }
    return wynik;
}

int Zobrist_hash_ruch(string ruch,pozycja *poz,int hash,int *tab1,int *tab2)
{
    int wynik=hash;
    int x1=pole_w_liczby(ruch[0],ruch[1])[0];
    int y1=pole_w_liczby(ruch[0],ruch[1])[1];
    int x2=pole_w_liczby(ruch[2],ruch[3])[0];
    int y2=pole_w_liczby(ruch[2],ruch[3])[1];
    int x3;
    int y3;
    wynik^=tab2[0];
    if (poz->czy_bicie_w_przelocie==1)
    {
        x3=pole_w_liczby(poz->kolumna_bwp,poz->wiersz_bwp)[0];
        y3=pole_w_liczby(poz->kolumna_bwp,poz->wiersz_bwp)[1];
        if (x2!=x3||y2!=y3||(poz->plansza[x1][y1]!='P'&&poz->plansza[x1][y1]!='p'))
        {
            wynik^=tab2[5+y3];
        }
    }
    if (ruch.size()==4)
    {
    	if (poz->czyj_ruch=='w')
    	{
    	    if (poz->plansza[x2][y2]!=' ')
    	    {
    	    	if (poz->plansza[x2][y2]=='k')
      	        {
    	            wynik^=tab1[x2*8+y2];
    	        }
    	        else if (poz->plansza[x2][y2]=='h')
    	        {
    	    	    wynik^=tab1[1*64+x2*8+y2];
    	        }
    	        else if (poz->plansza[x2][y2]=='r')
    	        {
    	    	    wynik^=tab1[2*64+x2*8+y2];
    	        }
    	        else if (poz->plansza[x2][y2]=='b')
    	        {
    	    	    wynik^=tab1[3*64+x2*8+y2];
    	        }
    	        else if (poz->plansza[x2][y2]=='n')
    	        {
    	    	    wynik^=tab1[4*64+x2*8+y2];
    	        }
    	        else if (poz->plansza[x2][y2]=='p')
    	        {
    	    	    wynik^=tab1[5*64+x2*8+y2];
    	        }
    	    }
    	    if (poz->plansza[x1][y1]=='K')
    	    {
    	    	wynik^=tab1[6*64+x1*8+y1];
    	    	wynik^=tab1[6*64+x2*8+y2];
    	    	if (y2-y1==2)
    	    	{
    	    	    wynik^=tab2[1];
    	    	    wynik^=tab1[8*64+7];
    	    	    wynik^=tab1[8*64+5];
    	    	}
    	    	if (y1-y2==3)
    	    	{
    	    	    wynik^=tab2[2];
    	    	    wynik^=tab1[8*64];
    	    	    wynik^=tab1[8*64+2];
    	    	}
    	    	if (poz->czy_K==1)
    	    	{
    	    	    if (y2-y1!=2&&y1-y2!=3)
    	    	    {
    	    	        wynik^=tab2[1];
    	    	    }
    	    	}
    	    	if (poz->czy_Q==1)
    	    	{
    	    	    if (y2-y1!=2&&y1-y2!=3)
    	    	    {
    	    	    	wynik^=tab2[2];
    	    	    }
    	    	}
    	    }
    	    else if (poz->plansza[x1][y1]=='H')
    	    {
    	    	wynik^=tab1[7*64+x1*8+y1];
    	    	wynik^=tab1[7*64+x2*8+y2];
    	    }
    	    else if (poz->plansza[x1][y1]=='R')
    	    {
    	    	wynik^=tab1[8*64+x1*8+y1];
    	    	wynik^=tab1[8*64+x2*8+y2];
    	    	if (poz->czy_K==1&&x1==0&&y1==7)
    	    	{
    	    	    wynik^=tab2[1];
    	    	}
    	    	if (poz->czy_Q==1&&x1==0&&y1==0)
    	    	{
    	       	    wynik^=tab2[2];
    	    	}
    	    }
    	    else if (poz->plansza[x1][y1]=='B')
    	    {
    	    	wynik^=tab1[9*64+x1*8+y1];
    	    	wynik^=tab1[9*64+x2*8+y2];
    	    }
    	    else if (poz->plansza[x1][y1]=='N')
    	    {
    	    	wynik^=tab1[10*64+x1*8+y1];
    	    	wynik^=tab1[10*64+x2*8+y2];
    	    }
    	    else if (poz->plansza[x1][y1]=='P')
    	    {
    	    	wynik^=tab1[11*64+x1*8+y1];
    	    	wynik^=tab1[11*64+x2*8+y2];
    	    	if (x2==x1+2)
    	    	{
    	    	    wynik^=tab2[5+y1];
    	    	}
    	    	if (poz->czy_bicie_w_przelocie==1)
    	    	{
    	    	    if (x2==x3&&y2==y3)
    	    	    {
    	    	    	wynik^=tab1[5*64+(x3-1)*8+y3];
    	    	    	wynik^=tab2[5+y3];
    	    	    }
    	    	}
    	    }
    	}
    	if (poz->czyj_ruch=='b')
    	{
    	    if (poz->plansza[x2][y2]!=' ')
    	    {
    	    	if (poz->plansza[x2][y2]=='K')
      	        {
    	            wynik^=tab1[6*64+x2*8+y2];
    	        }
    	        else if (poz->plansza[x2][y2]=='H')
    	        {
    	    	    wynik^=tab1[7*64+x2*8+y2];
    	        }
    	        else if (poz->plansza[x2][y2]=='R')
    	        {
    	    	    wynik^=tab1[8*64+x2*8+y2];
    	        }
    	        else if (poz->plansza[x2][y2]=='B')
    	        {
    	    	    wynik^=tab1[9*64+x2*8+y2];
    	        }
    	        else if (poz->plansza[x2][y2]=='N')
    	        {
    	    	    wynik^=tab1[10*64+x2*8+y2];
    	        }
    	        else if (poz->plansza[x2][y2]=='P')
    	        {
    	    	    wynik^=tab1[11*64+x2*8+y2];
    	        }
    	    }
    	    if (poz->plansza[x1][y1]=='k')
    	    {
    	    	wynik^=tab1[x1*8+y1];
    	    	wynik^=tab1[x2*8+y2];
    	    	if (y2-y1==2)
    	    	{
    	    	    wynik^=tab2[3];
    	    	    wynik^=tab1[2*64+7*8+7];
    	    	    wynik^=tab1[2*64+7*8+5];
    	    	}
    	    	if (y1-y2==3)
    	    	{
    	    	    wynik^=tab2[4];
    	    	    wynik^=tab1[2*64+7*8];
    	    	    wynik^=tab1[2*64+7*8+2];
    	    	}
    	    	if (poz->czy_k==1)
    	    	{
    	    	    if (y2-y1!=2&&y1-y2!=3)
    	    	    {
    	    	        wynik^=tab2[3];
    	    	    }
    	    	}
    	    	if (poz->czy_q==1)
    	    	{
    	    	    if (y2-y1!=2&&y1-y2!=3)
    	    	    {
    	    	    	wynik^=tab2[4];
    	    	    }
    	    	}
    	    }
    	    else if (poz->plansza[x1][y1]=='h')
    	    {
    	    	wynik^=tab1[1*64+x1*8+y1];
    	    	wynik^=tab1[1*64+x2*8+y2];
    	    }
    	    else if (poz->plansza[x1][y1]=='r')
    	    {
    	    	wynik^=tab1[2*64+x1*8+y1];
    	    	wynik^=tab1[2*64+x2*8+y2];
    	    	if (poz->czy_k==1&&x1==7&&y1==7)
    	    	{
    	    	    wynik^=tab2[3];
    	    	}
    	    	if (poz->czy_q==1&&x1==7&&y1==0)
    	    	{
    	       	    wynik^=tab2[4];
    	    	}
    	    }
    	    else if (poz->plansza[x1][y1]=='b')
    	    {
    	    	wynik^=tab1[3*64+x1*8+y1];
    	    	wynik^=tab1[3*64+x2*8+y2];
    	    }
    	    else if (poz->plansza[x1][y1]=='n')
    	    {
    	    	wynik^=tab1[4*64+x1*8+y1];
    	    	wynik^=tab1[4*64+x2*8+y2];
    	    }
    	    else if (poz->plansza[x1][y1]=='p')
    	    {
    	    	wynik^=tab1[5*64+x1*8+y1];
    	    	wynik^=tab1[5*64+x2*8+y2];
    	    	if (x2==x1-2)
    	    	{
    	    	    wynik^=tab2[5+y1];
    	    	}
    	    	if (poz->czy_bicie_w_przelocie==1)
    	    	{
    	    	    if (x2==x3&&y2==y3)
    	    	    {
    	    	    	wynik^=tab1[5*64+(x3+1)*8+y3];
    	    	    	wynik^=tab2[5+y3];
    	    	    }
    	    	}
    	    }
    	}
    }
    if (ruch.size()==5)
    {
    	if (poz->czyj_ruch=='w')
    	{
    	    if (poz->plansza[x2][y2]!=' ')
    	    {
    	    	if (poz->plansza[x2][y2]=='k')
      	        {
    	            wynik^=tab1[x2*8+y2];
    	        }
    	        else if (poz->plansza[x2][y2]=='h')
    	        {
    	    	    wynik^=tab1[1*64+x2*8+y2];
    	        }
    	        else if (poz->plansza[x2][y2]=='r')
    	        {
    	    	    wynik^=tab1[2*64+x2*8+y2];
    	    	    if (poz->czy_k==1&&x2==7&&y2==7)
    	    	    {
    	    	    	wynik^=tab2[3];
    	    	    }
    	    	    if (poz->czy_q==1&&x2==7&&y2==0)
    	    	    {
    	    	    	wynik^=tab2[4];
    	    	    }
    	        }
    	        else if (poz->plansza[x2][y2]=='b')
    	        {
    	    	    wynik^=tab1[3*64+x2*8+y2];
    	        }
    	        else if (poz->plansza[x2][y2]=='n')
    	        {
    	    	    wynik^=tab1[4*64+x2*8+y2];
    	        }
    	        else if (poz->plansza[x2][y2]=='p')
    	        {
    	    	    wynik^=tab1[5*64+x2*8+y2];
    	        }
    	    }
    	    wynik^=tab1[11*64+x1*8+y1];
    	    if (ruch[4]=='Q')
    	    {
    	        wynik^=tab1[7*64+x2*8+y2];
    	    }
    	    else if (ruch[4]=='R')
    	    {
    	        wynik^=tab1[8*64+x2*8+y2];
    	    }
    	    else if (ruch[4]=='B')
    	    {
    	        wynik^=tab1[9*64+x2*8+y2];
    	    }
    	    else if (ruch[4]=='N')
    	    {
    	        wynik^=tab1[10*64+x2*8+y2];
    	    }
    	}
    	if (poz->czyj_ruch=='b')
    	{
    	    if (poz->plansza[x2][y2]!=' ')
    	    {
    	    	if (poz->plansza[x2][y2]=='K')
      	        {
    	            wynik^=tab1[6*64+x2*8+y2];
    	        }
    	        else if (poz->plansza[x2][y2]=='H')
    	        {
    	    	    wynik^=tab1[7*64+x2*8+y2];
    	        }
    	        else if (poz->plansza[x2][y2]=='R')
    	        {
    	    	    wynik^=tab1[8*64+x2*8+y2];
    	    	    if (poz->czy_K==1&&x2==0&&y2==7)
    	    	    {
    	    	    	wynik^=tab2[1];
    	    	    }
    	    	    if (poz->czy_Q==1&&x2==0&&y2==0)
    	    	    {
    	    	    	wynik^=tab2[2];
    	    	    }
    	        }
    	        else if (poz->plansza[x2][y2]=='B')
    	        {
    	    	    wynik^=tab1[9*64+x2*8+y2];
    	        }
    	        else if (poz->plansza[x2][y2]=='N')
    	        {
    	    	    wynik^=tab1[10*64+x2*8+y2];
    	        }
    	        else if (poz->plansza[x2][y2]=='P')
    	        {
    	    	    wynik^=tab1[11*64+x2*8+y2];
    	        }
    	    }
    	    wynik^=tab1[5*64+x1*8+y1];
    	    if (ruch[4]=='q')
    	    {
    	        wynik^=tab1[1*64+x2*8+y2];
    	    }
    	    else if (ruch[4]=='r')
    	    {
    	        wynik^=tab1[2*64+x2*8+y2];
    	    }
    	    else if (ruch[4]=='b')
    	    {
    	        wynik^=tab1[3*64+x2*8+y2];
    	    }
    	    else if (ruch[4]=='n')
    	    {
    	        wynik^=tab1[4*64+x2*8+y2];
    	    }
    	}
    }
    return wynik;
}

bool czy_pat(pozycja *poz,int licznik1,int licznik2,int hash1,int hash2,int *tab1,int *tab2)
{
    if (poz->liczba_polowek_ruchow==100)
    {
        return 1;
    }
    if (poz->czyj_ruch=='w'&&Zobrist_hash_start(poz,tab1,tab2)==hash1)
    {
    	licznik1++;
    	if (licznik1==3)
    	{
    	    return 1;
    	}
    }
    else if (poz->czyj_ruch=='w')
    {
        licznik1=1;
        hash1=Zobrist_hash_start(poz,tab1,tab2);
    }
    if (poz->czyj_ruch=='b'&&Zobrist_hash_start(poz,tab1,tab2)==hash2)
    {
    	licznik2++;
    	if (licznik2==3)
    	{
    	    return 1;
    	}
    }
    else if (poz->czyj_ruch=='b')
    {
        licznik2=1;
        hash2=Zobrist_hash_start(poz,tab1,tab2);
    }
    int x1,x2,y1,y2;
    for (int i=0;i<8;i++)
    {
    	for (int j=0;j<8;j++)
    	{
    	    if (poz->plansza[i][j]=='k')
    	    {
    	    	x2=i;
    	    	y2=j;
    	    }
    	    if (poz->plansza[i][j]=='k')
    	    {
    	    	x1=i;
    	    	y1=j;
    	    }
    	}
    }
    if (poz->czyj_ruch=='w'&&czy_pole_jest_szachowane(x1,y1,'b',poz)==0)
    {
    	if(mozliwe_ruchy(poz).size()==0)
    	{
    	    return 1;
    	}
    }
    if (poz->czyj_ruch=='b'&&czy_pole_jest_szachowane(x2,y2,'w',poz)==0)
    {
    	if(mozliwe_ruchy(poz).size()==0)
    	{
    	    return 1;
    	}
    }
    return 0;
}

bool czy_mat(pozycja *poz)
{
    int x1,x2,y1,y2;
    for (int i=0;i<8;i++)
    {
    	for (int j=0;j<8;j++)
    	{
    	    if (poz->plansza[i][j]=='k')
    	    {
    	    	x2=i;
    	    	y2=j;
    	    }
    	    if (poz->plansza[i][j]=='k')
    	    {
    	    	x1=i;
    	    	y1=j;
    	    }
    	}
    }
    if (poz->czyj_ruch=='w'&&czy_pole_jest_szachowane(x1,y1,'b',poz)==1)
    {
    	if(mozliwe_ruchy(poz).size()==0)
    	{
    	    return 1;
    	}
    }
    if (poz->czyj_ruch=='b'&&czy_pole_jest_szachowane(x2,y2,'w',poz)==1)
    {
    	if(mozliwe_ruchy(poz).size()==0)
    	{
    	    return 1;
    	}
    }
    return 0;
}

//alphabeta(stan_pocz, gl_docelowa, −10000, 10000, 1);

long double alpha_beta(pozycja stan, int glebokosc, long double alpha, long double beta, bool czy_maksymalizujemy_na_ruchu) {
    //cout << glebokosc << endl;
    if(glebokosc == 0) {//lub pat/mat dodać!!!
        //jak mat czy pat to koniec

        //wpp
        return ewaluacja_pozycji(&stan);
        //sprawdzamy czy jak zejdziemy glebiej to zmieni sie ewaluacja o min 1.81 !!!
        /*
        long double akt_wart = ewaluacja_pozycji(&stan);
        vector <string> ruchy = mozliwe_ruchy(&stan);
        if(czy_maksymalizujemy_na_ruchu) {
            for(int i = 0; i < ruchy.size(); i++) {
                pozycja stan_2 = stan;
                porusz(ruchy[i], &stan_2);
                long double nowa_wart = ewaluacja_pozycji(&stan_2);
                if(nowa_wart - akt_wart >= 4.81) {
                    akt_wart = alpha_beta(stan_2, 0, alpha, beta, 0);
                }
            }
        }
        else {
            for(int i = 0; i < ruchy.size(); i++) {
                pozycja stan_2 = stan;
                porusz(ruchy[i], &stan_2);
                long double nowa_wart = ewaluacja_pozycji(&stan_2);
                if(nowa_wart - akt_wart <= -4.81) {
                    akt_wart = alpha_beta(stan_2, 0, alpha, beta, 1);
                }
            }
        }
        return akt_wart;
        */
    }
    long double wart;
    vector <string> ruchy = mozliwe_ruchy(&stan);
    if(czy_maksymalizujemy_na_ruchu) {
        wart = -10000;
        for(int i = 0; i < ruchy.size(); i++) {
            pozycja stan_2 = stan;
            porusz(ruchy[i], &stan_2);
            long double wart2 = alpha_beta(stan_2, glebokosc - 1, alpha, beta, 0);
            if(wart2 > wart) {
                wart = wart2;
                if(glebokosc == glebokoscstartowa) {
                    najlepszy_ruch = ruchy[i];
                }
            }
            if(wart >= beta)
                break;
            alpha = max(alpha, wart);
        }
    }
    else {
        wart = 10000;
        for(int i = 0; i < ruchy.size(); i++) {
            pozycja stan_2 = stan;
            porusz(ruchy[i], &stan_2);
            long double wart2 = alpha_beta(stan_2, glebokosc - 1, alpha, beta, 1);
            if(wart2 < wart) {
                wart = wart2;
                if(glebokosc == glebokoscstartowa) {
                    najlepszy_ruch = ruchy[i];
                }
            }
            wart = min(wart, alpha_beta(stan_2, glebokosc - 1, alpha, beta, 1));
            if(wart <= alpha)
                break;
            beta = min(beta, wart);
        }
    }
    return wart;
}