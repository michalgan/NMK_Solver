Uogólniona wersja silnika gry Kółko i Krzyżyk czyli rodzina gier NMK (https://en.wikipedia.org/wiki/M,n,k-game) pobiera 3 parametry N, M i K gdzie (N x M) to rozmiar planszy a (K) to liczba nieprzerwanie sąsiadujących ze sobą pól w ciągłej pionowej, poziomej bądź ukośnej linii które są warunkiem wygrania.
Należy zaimplementować deterministyczny generator posunięć, który dodaje pion gracza (np. Kółko bądź Krzyżyk, albo biały bądź czarny pionek) zaczynając od górnego lewego rogu, kontynuując w rzędach a następnie w kolumnach. Na potrzeby naszego zadania posunięcia pierwszego gracza będziemy oznaczać jedynkami a drugiego dwójkami, niezajęte pola będą oznaczone zerami. Zatem w podstawowej grze Kółko i krzyżyk (NMK 3,3,3) wygenerowane możliwe posunięcia dla pustej planszy to (kolejność jest ważna):

100 010 001 000 000 000 000 000 000
000 000 000 100 010 001 000 000 000
000 000 000 000 000 000 100 010 001

Silnik gry pozwala na:
1. generowanie wszystkich możliwych posunięć,
2. Ocenę gry w postaci odpowiedźi na pytanie - czy gra się zakończyła i czy gracz wygrał/zremisował/przegrał?

Przykładowo wszystkie możliwe stany poniższego (aktywnym graczem jest 1):
102
012
000

to:

112 102 102 102 102
012 112 012 012 012
000 000 100 010 001

Tylko ostatni z nich jest posunięciem wygrywającym dla gracza 1 i w ulepszonej wersji silnika tylko on powinien zostać wygenerowany.

W drugiej części zadania należy zaimplementować algorytm rozwiązujący pewien, niekoniecznie początkowy, stan gry NMK. Można zastosować algorytm Minmax albo Negamax z pewnymi usprawnieniami. Zauważmy, że r przypadku tej rodziny gier, rozwiązanie zawsze będzie deterministyczne ponieważ gra jest 2-osobowa, bez elementów losowych i pozbawiona ukrytej informacji. Zatem będziemy zawsze wiedzieli czy taka rozgrywka (jeśli obydwaj gracze grają optymalnie) zakończy się wygraną, przegraną czy remisem każdego z graczy.

Pierwszym usprawnieniem algorytmu Minmax jest zakończenie poszykiwań min w przypadku otrzymiania wartości -1 albo max w przypadku uzyskania wartości 1 ponieważ tych wyników nie da się już poprawić.

Drugie usprawnienie wynika z faktu, że możliwe jest stworzenie sytuacji w której gracz ma sytuację wygrywającą w następnym posunięciu, no chyba, że przeciwnik stworzył taka sytuację wcześniej. Chodzi o ciągi długości (K-1) którr na końcach posiadają możliwośc dołożenia swojego piona. Jesli jest taki jeden to przeciwnik może sie jeszcze obronić. Jesli są dwa lub więcej to jeśli przeciwnik wcześniej nie stworzył zagrożenia jest juz na przegranej pozycji.

Rozważmy poniższy przykład dla gry (4,4,3):

0000
0110
0200
0002

Ruch należy do gracza 1 i widać, że 2 nie może sie już obronić, jeśli postawi swojego piona po lewej stronie:

0000
2110
0200
0002

to przeciwnik dostawi po prawej:

0000
2111
0200
0002

jeśli postawi go po prawej:

0000
0112
0200
0002

to przeciwnik po lewej:

0000
2110
0200
0002

Zatem wykrycie takiej sytuacji można oznaczyć jako zagrożenie ze strony jednego z graczy i w przypadku kiedy w przyszłości natrafimy na tak oznaczony stan gry (zawierający takie zagrożenie) a przeciwnik gracza, który stworzył takie zagrożenie nie wygrał we właśnie analizowanym ruchu to mamy pewność, że już nie wygra.

Program powinien obsługiwać 3 komendy:

1. GEN_ALL_POS_MOV N M K ActivePlayer - wygenerowanie wszystkich możliwych posunięć wraz z ich liczbą,

Przykłady:

Wejście:

GEN_ALL_POS_MOV 3 3 3 2
1 0 0
0 0 0
0 0 0

Wyjście:

8
1 2 0
0 0 0
0 0 0

1 0 2
0 0 0
0 0 0

1 0 0
2 0 0
0 0 0

1 0 0
0 2 0
0 0 0

1 0 0
0 0 2
0 0 0

1 0 0
0 0 0
2 0 0

1 0 0
0 0 0
0 2 0

1 0 0
0 0 0
0 0 2

Wejście:

GEN_ALL_POS_MOV 3 3 3 1
1 2 0
0 0 0
0 0 0

Wyjście:

7
1 2 1
0 0 0
0 0 0

1 2 0
1 0 0
0 0 0

1 2 0
0 1 0
0 0 0

1 2 0
0 0 1
0 0 0

1 2 0
0 0 0
1 0 0

1 2 0
0 0 0
0 1 0

1 2 0
0 0 0
0 0 1

2. GEN_ALL_POS_MOV_CUT_IF_GAME_OVER N M K ActivePlayer - wygenerowanie wszystkich możliwych posunięć wraz z ich liczbą, a w przypadku kiedy jedno z nich jest wygrywające albo kończące to wygenerowanie tylko pierwszego z nich

Wejście:

GEN_ALL_POS_MOV_CUT_IF_GAME_OVER 3 3 3 1

0 2 1
2 2 1
0 1 0

Wyjście:

1
0 2 1
2 2 1
0 1 1

Wejście:

GEN_ALL_POS_MOV_CUT_IF_GAME_OVER 3 3 3 1

1 2 1
2 2 1
0 1 2

Wyjście:

1
1 2 1
2 2 1
1 1 2

3 SOLVE_GAME_STATE N M K ActivePlayer - rozwiązanie gry, oraz podania jednej z trzech możliwych odpowiedzi: FIRST_PLAYER_WINS, SECOND_PLAYER_WINS, BOTH_PLAYERS_TIE.

Przykłady:

Wejście:

SOLVE_GAME_STATE 3 3 3 2
1 0 0
0 0 0
0 0 0

Wyjście:

BOTH_PLAYERS_TIE

Wejście:

SOLVE_GAME_STATE 3 3 3 1
1 2 0
0 0 0
0 0 0

Wyjście:

FIRST_PLAYER_WINS
