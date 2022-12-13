/**********************************************************************
 *  Mönsterigenkänning readme.txt
 **********************************************************************/

/**********************************************************************
 *  Empirisk    Fyll i tabellen nedan med riktiga körtider i sekunder
 *  analys      när det känns vettigt att vänta på hela beräkningen.
 *              Ge uppskattningar av körtiden i övriga fall.
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
 *  Teoretisk   Ge ordo-uttryck för värstafallstiden för programmen som
 *  analys      en funktion av N. Ge en kort motivering.
 *
 **********************************************************************/

Brute:
Genomsnittstiden blir O(n^3), vilket man kan se när man jämför de givna
körtiderna. Uppskattningarna har också gjorts till hänsyn av en
tidskomplexitet på O(n^3).
När man däremot kollar på värstafallstiden blir det O(n^4).
Tidskomplexiten för den fjärde nästlade for-loopen är O(n), då den är
beroende av de andra looparna som också är O(n).
O(n^4) beror på att alla loopar är beroende på N, så antalet iterationer
växer linjärt med N.

Sortering:
