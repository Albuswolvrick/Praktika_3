#include "rechner.h"

/* Berechnet die n-te Fibonacci-Zahl rekursiv (F0 = 0, F1 = 1);
 * n = Index >= 0. Rueckgabe: F(n), bei n < 0 der Wert -1.
 * Laufzeit exponentiell, da Teilprobleme mehrfach berechnet werden. */
int fibonacci_rekursiv(int n) {
    if (n < 0) {
        return -1;
    }
    if (n < 2) {
        return n;
    }
    return fibonacci_rekursiv(n - 1) + fibonacci_rekursiv(n - 2);
}
