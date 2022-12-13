/**********************************************************************
 *  M�nsterigenk�nning readme.txt
 **********************************************************************/

/**********************************************************************
 *  Empirisk    Fyll i tabellen nedan med riktiga k�rtider i sekunder
 *  analys      n�r det k�nns vettigt att v�nta p� hela ber�kningen.
 *              Ge uppskattningar av k�rtiden i �vriga fall.
 *
 **********************************************************************/
    
      N           brute           sortering
 -------------------------------------------
    150           0,024s
    200           0,107s
    300           0,204s
    400           0,495s
    800           3,853s
   1600          30,255s
   3200         242,040s, upp.
   6400        1936,320s, upp.
  12800       15490,560s, upp.


/**********************************************************************
 *  Teoretisk   Ge ordo-uttryck f�r v�rstafallstiden f�r programmen som
 *  analys      en funktion av N. Ge en kort motivering.
 *
 **********************************************************************/

Brute:
Genomsnittstiden blir O(n^3), vilket man kan se n�r man j�mf�r de givna
k�rtiderna. Uppskattningarna har ocks� gjorts till h�nsyn av en
tidskomplexitet p� O(n^3).
N�r man d�remot kollar p� v�rstafallstiden blir det O(n^4).
Tidskomplexiten f�r den fj�rde n�stlade for-loopen �r O(n), d� den �r
beroende av de andra looparna som ocks� �r O(n).
O(n^4) beror p� att alla loopar �r beroende p� N, s� antalet iterationer
v�xer linj�rt med N.

Sortering:
