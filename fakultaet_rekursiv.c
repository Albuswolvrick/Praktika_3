#include "rechner.h"

/* Berechnet n! rekursiv; n = Zahl >= 0.
 * Rueckgabe: n!, bei n < 0 der Wert -1. Gleicher Ueberlauf ab n = 13. */
int fakultaet_rekursiv(int n) {
    if (n < 0) {
        return -1;
    }
    if (n <= 1) {
        return 1;
    }
    return n * fakultaet_rekursiv(n - 1);
}
//ldsjkfn