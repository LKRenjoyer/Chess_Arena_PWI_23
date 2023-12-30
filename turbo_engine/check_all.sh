for((i = 0; i < 100000; ++i)) do
    ./gen > moj_fen
    python3 simple_position.py > moj_fen 
    python3 legal_moves.py < moj_fen > proper_moves  
    ./wzo  < moj_fen > out
    diff -w proper_moves out || break; 
    echo "test $i OK" 
done