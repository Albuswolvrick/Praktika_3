#include <stdio.h>
#include <time.h>
#include "rechner.h"

static void menue_anzeigen(void) {
    printf("\n===== Rechner =====\n");
    printf("1 - Addition\n");
    printf("2 - Subtraktion\n");
    printf("3 - Multiplikation\n");
    printf("4 - Division\n");
    printf("5 - Fakultaet (iterativ und rekursiv)\n");
    printf("6 - Fibonacci-Vergleich n = 0..15\n");
    printf("7 - Laufzeitvergleich Fibonacci(40)\n");
    printf("8 - Fakultaet-Ueberlauf (n = 0..15)\n");
    printf("0 - Beenden\n");
    printf("Auswahl: ");
}

static int lese_zahlen(double *a, double *b) {
    printf("Erster Operand: ");
    if (scanf("%lf", a) != 1) return 0;
    printf("Zweiter Operand: ");
    if (scanf("%lf", b) != 1) return 0;
    return 1;
}

static void fibonacci_vergleich(void) {
    int alle_gleich = 1;
    printf("\n n | rekursiv | iterativ | gleich?\n");
    printf("---+----------+----------+--------\n");
    for (int n = 0; n <= 15; n++) {
        int r = fibonacci_rekursiv(n);
        int i = fibonacci_iterativ(n);
        if (r != i) alle_gleich = 0;
        printf("%2d | %8d | %8d | %s\n", n, r, i, r == i ? "ja" : "NEIN");
    }
    printf(alle_gleich ? "Alle Werte stimmen ueberein.\n"
                       : "ACHTUNG: Abweichungen gefunden!\n");
}

static void laufzeitvergleich(void) {
    clock_t t0 = clock();
    int r = fibonacci_rekursiv(40);
    clock_t t1 = clock();
    int i = fibonacci_iterativ(40);
    clock_t t2 = clock();

    printf("\nfibonacci_rekursiv(40) = %d, Zeit: %.4f s\n",
           r, (double)(t1 - t0) / CLOCKS_PER_SEC);
    printf("fibonacci_iterativ(40) = %d, Zeit: %.6f s\n",
           i, (double)(t2 - t1) / CLOCKS_PER_SEC);

    /* Aufgabe 4 - Erklaerung:
     * Die rekursive Variante berechnet dieselben Teilprobleme immer wieder
     * (fib(38) wird z.B. in fib(40) und fib(39) separat berechnet). Der
     * Aufrufbaum waechst exponentiell (ca. 1,6^n Aufrufe, fuer n = 40 rund
     * 330 Millionen). Die iterative Variante berechnet jeden Wert genau
     * einmal und braucht nur n Schleifendurchlaeufe (linear), daher ist
     * sie um viele Groessenordnungen schneller. */
}

static void fakultaet_ueberlauf(void) {
    int erste_abweichung = -1;
    printf("\n n | fakultaet (int) | korrekt (long long)\n");
    printf("---+-----------------+--------------------\n");
    long long korrekt = 1;
    for (int n = 0; n <= 15; n++) {
        if (n > 1) korrekt *= n;
        int f = fakultaet(n);
        int ok = ((long long)f == korrekt);
        if (!ok && erste_abweichung < 0) erste_abweichung = n;
        printf("%2d | %15d | %19lld %s\n", n, f, korrekt, ok ? "" : "<-- Ueberlauf");
    }
    printf("Erstes falsches Ergebnis bei n = %d\n", erste_abweichung);
}

int main(void) {
    int wahl;

    do {
        menue_anzeigen();
        if (scanf("%d", &wahl) != 1) {
            printf("Ungueltige Eingabe.\n");
            break;
        }

        switch (wahl) {
            case 1: case 2: case 3: case 4: {
                double a, b;
                if (!lese_zahlen(&a, &b)) {
                    printf("Ungueltige Eingabe.\n");
                    return 1;
                }
                if (wahl == 1) {
                    printf("Ergebnis: %g\n", addiere(a, b));
                } else if (wahl == 2) {
                    printf("Ergebnis: %g\n", subtrahiere(a, b));
                } else if (wahl == 3) {
                    printf("Ergebnis: %g\n", multipliziere(a, b));
                } else {
                    int fehler;
                    double erg = dividiere(a, b, &fehler);
                    if (fehler) {
                        printf("Fehler: Division durch 0\n");
                    } else {
                        printf("Ergebnis: %g\n", erg);
                    }
                }
                break;
            }
            case 5: {
                int n;
                printf("n: ");
                if (scanf("%d", &n) != 1) {
                    printf("Ungueltige Eingabe.\n");
                    return 1;
                }
                if (n < 0) {
                    printf("Fehler: n muss >= 0 sein\n");
                } else {
                    printf("%d! iterativ  = %d\n", n, fakultaet(n));
                    printf("%d! rekursiv  = %d\n", n, fakultaet_rekursiv(n));
                }
                break;
            }
            case 6: fibonacci_vergleich(); break;
            case 7: laufzeitvergleich(); break;
            case 8: fakultaet_ueberlauf(); break;
            case 0: printf("Auf Wiedersehen!\n"); break;
            default: printf("Unbekannte Auswahl.\n");
        }
    } while (wahl != 0);

    return 0;
}
