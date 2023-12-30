Koncept jest taki żeby napisać tutaj program, który będzie potrafił konfrotnować ze sobą dwa boty, ma to działać na początku jakoś głupio w stylu 100ms na ruch po prostu, i boty walczą ze sobą na jakichś 200 pozycjach(różnych, szacowanych na okołorówne). Opiszę jeszcze jak powinna działać dokładnie komunikacja z "programem prowadzącym pojedynek". Ale koncept jest taki że boty grają na każdej planszy dwie partie, po pierwszej zamieniają się kolorami bierek.  
Pozycje byly oceniane przez 300 ms pracy stockfisha jakiego nowego.


Więc programem do konfrontacji dwóch botów jest fight.py, póki co działa to dla plików pythonowych o takich właśnie nazwach, ale ławto to można zmienić, odpowiednio zmieniając napisy w takich dwóch liniach: 
	botA = run_bot(["python3", "botA.py"])
    	botB = run_bot(["python3", "botB.py"])
Komunikacja z botami w pełni odbywa się przez ich standardowe wejścia. 
początek procedury komunikacyjnej wygląda tak: 
K: isready? 
B: ready
K: color: ["white" / "black"] 
B: ["white" / "black"]
K: FEN: [jakiś fen] 
B: understood 
następnie jeśli jest tura bota to powinien on wypisać swój ruch w formacie uci, jeśli nie to powinien czekać aż sprawdzaczka wypisze na jego weście ruch oponenta. Jeśli sprawdzaczka wypisze ruch "a1a1" to jest to znak dla bota że partia się zakończyła i powinien zakończyć pracę. 
 
