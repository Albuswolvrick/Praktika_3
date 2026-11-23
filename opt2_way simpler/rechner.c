#include "rechner.h"

/* Addiert a und b; Rueckgabe: Summe a + b. */
double addiere(double a, double b) {
    return a + b;
}

/* Subtrahiert b von a; Rueckgabe: Differenz a - b. */
double subtrahiere(double a, double b) {
    return a - b;
}

/* Multipliziert a und b; Rueckgabe: Produkt a * b. */
double multipliziere(double a, double b) {
    return a * b;
}

/* Dividiert a durch b; fehler (Ausgabeparameter, darf nicht NULL sein)
 * wird auf 1 gesetzt bei b == 0, sonst auf 0.
 * Rueckgabe: a / b, bei Division durch 0 der Wert 0.0. */
double dividiere(double a, double b, int *fehler) {
    if (b == 0.0) {
        *fehler = 1;
        return 0.0;
    }
    *fehler = 0;
    return a / b;
}

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
}

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
