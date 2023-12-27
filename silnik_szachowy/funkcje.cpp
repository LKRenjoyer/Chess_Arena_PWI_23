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
    else if(poz->plansza[(ruch[1] - '1')][(ruch[0] - 'a')] == 'P' && ruch[0] != ruch[2]){
        //uwaga na bicia w przelocie bialych
        poz->plansza[(ruch[1] - '1')][(ruch[0] - 'a')] = ' ';
        poz->plansza[(ruch[3] - '1')][(ruch[2] - 'a')] = 'P';
        poz->plansza[(ruch[3] - '1') - 1][(ruch[2] - 'a')] = ' ';
    }
    else if(poz->plansza[(ruch[1] - '1')][(ruch[0] - 'a')] == 'p' && ruch[0] != ruch[2]){
        //uwaga na bicia w przelocie czarnych
        poz->plansza[(ruch[1] - '1')][(ruch[0] - 'a')] = ' ';
        poz->plansza[(ruch[3] - '1')][(ruch[2] - 'a')] = 'p';
        poz->plansza[(ruch[3] - '1') + 1][(ruch[2] - 'a')] = ' ';
    }
    else {
        //porusz figure
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
    cout << '*';
    for(int i = 0; i < 16; i++) {
        cout << '-';
    }
    cout << '*' << '\n';
    for(int i = 7; i >= 0; i--) {
        cout << '|';
        for(int ii = 0; ii < 8; ii++) {
            cout << poz->plansza[i][ii] << ' ';
        }
        cout << '|';
        cout << '\n';
    }
    cout << '*';
    for(int i = 0; i < 16; i++) {
        cout << '-';
    }
    cout << '*' << '\n';
    cout << '\n';
    cout << "czyj ruch: " << poz->czyj_ruch << '\n';
    cout << "możliwe roszady: " << (poz->czy_K ? "K" : "") << (poz->czy_Q ? "Q" : "") << (poz->czy_k ? "k" : "") << (poz->czy_q ? "q" : "") << '\n';
    cout << "czy mozliwe bicie w przelocie: " << (poz->czy_bicie_w_przelocie ? "TAK " : "NIE ") << (poz->czy_bicie_w_przelocie ? poz->kolumna_bwp : ' ') << (poz->czy_bicie_w_przelocie ? poz->wiersz_bwp : ' ') << '\n';
    cout << "liczba_polowek_ruchow: " << poz->liczba_polowek_ruchow << '\n';
    cout << "liczba_ruchow: " << poz->liczba_ruchow << '\n'; 
    cout << "ewaluacja: " << ewaluacja_pozycji(poz) << '\n';
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
        poz->wiersz_bwp = fen[x];
        x++;
        poz->kolumna_bwp = fen[x];
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
            liczfigury[poz->plansza[i][ii]];
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
    if(liczfigury['Q'] * 3 + liczfigury['R'] * 3 + liczfigury['B'] * 3 + liczfigury['N'] * 3 <= 15)
        czy_endgame_b = 1;
    if(liczfigury['q'] * 3 + liczfigury['r'] * 3 + liczfigury['b'] * 3 + liczfigury['n'] * 3 <= 15)
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
                    wart -= 0.2;
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
                    wart += 0.2;
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
        wart -= (long double)max(0, pionyb[i] - 1) * 0,5;
        wart += (long double)max(0, pionyc[i] - 1) * 0,5;
    }
    //izolowane piony
    for(int i = 1; i < 7; i++) {
        if(pionyb[i] > 0 && pionyb[i - 1] == 0 && pionyb[i + 1] == 0) {
            wart -= 0.5;
        }
        if(pionyc[i] > 0 && pionyc[i - 1] == 0 && pionyc[i + 1] == 0) {
            wart += 0.5;
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

    //czy figury sa pod biciem przez słabsze / nie są bronione 
    //jeśli atakujemy więcej razy niż bronimy to dla nas fajnie jeśli suma się zgadza 

    //dodać sprawdzanie czy pat i czy mat 
    return wart;
}
