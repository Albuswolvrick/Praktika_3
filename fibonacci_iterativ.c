#include "rechner.h"

/* Berechnet die n-te Fibonacci-Zahl iterativ (F0 = 0, F1 = 1);
 * n = Index >= 0. Rueckgabe: F(n), bei n < 0 der Wert -1.
 * Laufzeit linear (n Schleifendurchlaeufe). */
int fibonacci_iterativ(int n) {
    if (n < 0) {
        return -1;
    }
    int a = 0, b = 1;
    for (int i = 0; i < n; i++) {
        int t = a + b;
        a = b;
        b = t;
    }
    return a;
}
//sdäobufj