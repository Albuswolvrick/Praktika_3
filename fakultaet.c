#include "rechner.h"

/* Berechnet n! iterativ; n = Zahl >= 0.
 * Rueckgabe: n!, bei n < 0 der Wert -1.
 *
 * Aufgabe 3.1 - Wertebereich: Bei 32-Bit-int ist 12! = 479001600 noch
 * korrekt (INT_MAX = 2147483647), ab n = 13 tritt ein Ueberlauf auf
 * (13! = 6227020800 > INT_MAX) und das Ergebnis ist falsch.
 * Experimentell bestaetigt (siehe Ausgabe in main, Menuepunkt 8).
 * Hinweis: Signed-Overflow ist in C formal undefiniertes Verhalten. */
int fakultaet(int n) {
    if (n < 0) {
        return -1;
    }
    int ergebnis = 1;
    for (int i = 2; i <= n; i++) {
        ergebnis *= i;
    }
    return ergebnis;
}//hv
