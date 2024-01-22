unordered_map <long long, long double> unmp;
unordered_map <long long, long double> unmp2;

long double piony_c_pon[8][8] = {
{ 0,   0,   0,   0,   0,   0,   0,   0},
{50,  50,  50,  50,  50,  50,  50,  50},
{10,  10,  20,  30,  30,  20,  10,  10},
{ 5,   5,  10,  25,  25,  10,   5,   5},
{ 0,   0,   0,  20,  20,   0,   0,   0},
{ 5,  10, -10,  10,  10, -10,  10,   5},
{ 5,  10,  10, -40, -40,  10,  10,   5},
{ 0,   0,   0,   0,   0,   0,   0,   0}
};

long double piony_b_pon[8][8] = {
{ 0,   0,   0,   0,   0,   0,   0,   0},
{ 5,  10,  10, -40, -40,  10,  10,   5},
{ 5,  10, -10,  10,  10, -10,  10,   5},
{ 0,   0,   0,  20,  20,   0,   0,   0},
{ 5,   5,  10,  25,  25,  10,   5,   5},
{10,  10,  20,  30,  30,  20,  10,  10},
{50,  50,  50,  50,  50,  50,  50,  50},
{ 0,   0,   0,   0,   0,   0,   0,   0}
};

long double piony_c_kon[8][8] = {
{ 0,   0,   0,   0,   0,   0,   0,   0},
{80,  80,  80,  80,  80,  80,  80,  80},
{50,  50,  50,  50,  50,  50,  50,  50},
{30,  30,  30,  30,  30,  30,  30,  30},
{20,  20,  20,  20,  20,  20,  20,  20},
{10,  10,  10,  10,  10,  10,  10,  10},
{10,  10,  10,  10,  10,  10,  10,  10},
{ 0,   0,   0,   0,   0,   0,   0,   0}		
};

long double piony_b_kon[8][8] = {
{ 0,   0,   0,   0,   0,   0,   0,   0},
{10,  10,  10,  10,  10,  10,  10,  10},
{10,  10,  10,  10,  10,  10,  10,  10},
{20,  20,  20,  20,  20,  20,  20,  20},
{30,  30,  30,  30,  30,  30,  30,  30},
{50,  50,  50,  50,  50,  50,  50,  50},
{80,  80,  80,  80,  80,  80,  80,  80},
{ 0,   0,   0,   0,   0,   0,   0,   0}		
};

long double wieze_c[8][8] = {
{ 0,  0,  0,  0,  0,  0,  0,  0},
{ 5, 10, 10, 10, 10, 10, 10,  5},
{-5,  0,  0,  0,  0,  0,  0, -5},
{-5,  0,  0,  0,  0,  0,  0, -5},
{-5,  0,  0,  0,  0,  0,  0, -5},
{-5,  0,  0,  0,  0,  0,  0, -5},
{-5,  0,  0,  0,  0,  0,  0, -5},
{ 0,  0,  25, 0,  25,  0,  0,  0}
};

long double wieze_b[8][8] = {
{ 0,  0, 25,  0,  25,  0,  0,  0},
{-5,  0,  0,  0,  0,  0,  0, -5},
{-5,  0,  0,  0,  0,  0,  0, -5},
{-5,  0,  0,  0,  0,  0,  0, -5},
{-5,  0,  0,  0,  0,  0,  0, -5},
{-5,  0,  0,  0,  0,  0,  0, -5},
{ 5, 10, 10, 10, 10, 10, 10,  5},
{ 0,  0,  0,  0,  0,  0,  0,  0}
};

long double skoczki_c[8][8] = {
{-50,-40,-30,-30,-30,-30,-40,-50},
{-40,-20,  0,  0,  0,  0,-20,-40},
{-30,  0, 10, 15, 15, 10,  0,-30},
{-30,  5, 15, 20, 20, 15,  5,-30},
{-30,  0, 15, 20, 20, 15,  0,-30},
{-30,  5, 10, 15, 15, 10,  5,-30},
{-40,-20,  0,  5,  5,  0,-20,-40},
{-50,-50,-30,-30,-30,-30,-50,-50}
};

long double skoczki_b[8][8] = {
{-50,-50,-30,-30,-30,-30,-50,-50},
{-40,-20,  0,  5,  5,  0,-20,-40},
{-30,  5, 10, 15, 15, 10,  5,-30},
{-30,  0, 15, 20, 20, 15,  0,-30},
{-30,  5, 15, 20, 20, 15,  5,-30},
{-30,  0, 10, 15, 15, 10,  0,-30},
{-40,-20,  0,  0,  0,  0,-20,-40},
{-50,-40,-30,-30,-30,-30,-40,-50}
};

long double gonce_c[8][8] = {
{-20,-10,-10,-10,-10,-10,-10,-20},
{-10,  0,  0,  0,  0,  0,  0,-10},
{-10,  0,  5, 10, 10,  5,  0,-10},
{-10,  5,  5, 10, 10,  5,  5,-10},
{-10,  0, 10, 10, 10, 10,  0,-10},
{-10, 10, 10, 10, 10, 10, 10,-10},
{-10, 10,  0,  0,  0,  0, 10,-10},
{-20,-10,-30,-10,-10,-30,-10,-20}
};

long double gonce_b[8][8] = {
{-20,-10,-30,-10,-10,-30,-10,-20},
{-10, 10,  0,  0,  0,  0, 10,-10},
{-10, 10, 10, 10, 10, 10, 10,-10},
{-10,  0, 10, 10, 10, 10,  0,-10},
{-10,  5,  5, 10, 10,  5,  5,-10},
{-10,  0,  5, 10, 10,  5,  0,-10},
{-10,  0,  0,  0,  0,  0,  0,-10},
{-20,-10,-10,-10,-10,-10,-10,-20}
};

long double hetmany_c[8][8] {
{-20,-10,-10, -5, -5,-10,-10,-20},
{-10,  0,  0,  0,  0,  0,  0,-10},
{-10,  0,  5,  5,  5,  5,  0,-10},
{-5,   0,  5,  5,  5,  5,  0, -5},
{0,    0,  5,  5,  5,  5,  0, -5},
{-10,  5,  5,  5,  5,  5,  0,-10},
{-10,  0,  5,  0,  0,  0,  0,-10},
{-20,-10,-10, -5, -5,-10,-10,-20}
};

long double hetmany_b[8][8] {
{-20,-10,-10, -5, -5,-10,-10,-20},
{-10,  0,  5,  0,  0,  0,  0,-10},
{-10,  5,  5,  5,  5,  5,  0,-10},
{0,    0,  5,  5,  5,  5,  0, -5},
{-5,   0,  5,  5,  5,  5,  0, -5},
{-10,  0,  5,  5,  5,  5,  0,-10},
{-10,  0,  0,  0,  0,  0,  0,-10},
{-20,-10,-10, -5, -5,-10,-10,-20}
};

long double krol_c_pocz[8][8] = {
{-80, -70, -70, -70, -70, -70, -70, -80}, 
{-60, -60, -60, -60, -60, -60, -60, -60}, 
{-40, -50, -50, -60, -60, -50, -50, -40}, 
{-30, -40, -40, -50, -50, -40, -40, -30}, 
{-20, -30, -30, -40, -40, -30, -30, -20}, 
{-10, -20, -20, -20, -20, -20, -20, -10}, 
{ 20,  20,  -5,  -5,  -5,  -5,  20,  20}, 
{ 20,  40,  -20,   0, -20,  40,  30,  20}
};

long double krol_b_pocz[8][8] = {
{ 20,  40,  -20,   0, -20,  40,  30,  20},
{ 20,  20,  -5,  -5,  -5,  -5,  20,  20}, 
{-10, -20, -20, -20, -20, -20, -20, -10}, 
{-20, -30, -30, -40, -40, -30, -30, -20}, 
{-30, -40, -40, -50, -50, -40, -40, -30}, 
{-40, -50, -50, -60, -60, -50, -50, -40}, 
{-60, -60, -60, -60, -60, -60, -60, -60}, 
{-80, -70, -70, -70, -70, -70, -70, -80} 
};

long double krol_c_kon[8][8] = {
{-20, -10, -10, -10, -10, -10, -10, -20},
{ -5,   0,   5,   5,   5,   5,   0,  -5}, 
{-10, -5,   20,  30,  30,  20,  -5, -10},
{-15, -10,  35,  45,  45,  35, -10, -15},
{-20, -15,  30,  40,  40,  30, -15, -20},
{-25, -20,  20,  25,  25,  20, -20, -25},
{-30, -25,   0,   0,   0,   0, -25, -30},
{-50, -30, -30, -30, -30, -30, -30, -50}
};

long double krol_b_kon[8][8] = {
{-50, -30, -30, -30, -30, -30, -30, -50},
{-30, -25,   0,   0,   0,   0, -25, -30},
{-25, -20,  20,  25,  25,  20, -20, -25},
{-20, -15,  30,  40,  40,  30, -15, -20},
{-15, -10,  35,  45,  45,  35, -10, -15},
{-10, -5,   20,  30,  30,  20,  -5, -10},
{ -5,   0,   5,   5,   5,   5,   0,  -5}, 
{-20, -10, -10, -10, -10, -10, -10, -20}
};

//tabelki z https://github.com/SebLague/Chess-Coding-Adventure/blob/Chess-V2-UCI/Chess-Coding-Adventure/src/Core/Evaluation/PieceSquareTable.cs