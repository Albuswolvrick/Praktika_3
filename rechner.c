#include <stddef.h>   /* fuer NULL */
#include "rechner.h"

/* addiere: a, b = Operanden; gibt a + b zurueck. */
double addiere(double a, double b)
{
    return a + b;
}

/* subtrahiere: a, b = Operanden; gibt a - b zurueck. */
double subtrahiere(double a, double b)
{
    return a - b;
}

/* multipliziere: a, b = Operanden; gibt a * b zurueck. */
double multipliziere(double a, double b)
{
    return a * b;
}

/* dividiere: a = Dividend, b = Divisor, fehler = Ausgabeparameter
   (0 = ok, 1 = Division durch 0); gibt a / b zurueck, bei Fehler 0.0. */
double dividiere(double a, double b, int *fehler)
{
    if (b == 0.0) {
        if (fehler != NULL) {
            *fehler = 1;
        }
        return 0.0;
    }
    if (fehler != NULL) {
        *fehler = 0;
    }
    return a / b;
}

/* fakultaet: n = Eingabe (n >= 0); gibt n! iterativ zurueck, -1 bei n < 0.
 *
 * Aufgabe 3 - Ueberlauf (experimentell ermittelt mit Menuepunkt 7):
 *   12! = 479001600   -> passt in int (INT_MAX = 2147483647)
 *   13! = 6227020800  -> zu gross fuer int
 *   Das Programm liefert fuer 13 den falschen Wert 1932053504.
 *   Ab n = 13 ist das Ergebnis also falsch (Ueberlauf).
 */
int fakultaet(int n)
{
    int ergebnis = 1;
    int i;

    if (n < 0) {
        return -1;
    }
    for (i = 2; i <= n; i++) {
        ergebnis = ergebnis * i;
    }
    return ergebnis;
}

/* fakultaet_rekursiv: n = Eingabe (n >= 0); gibt n! rekursiv zurueck, -1 bei n < 0. */
int fakultaet_rekursiv(int n)
{
    if (n < 0) {
        return -1;
    }
    if (n <= 1) {
        return 1;                           /* Abbruchbedingung */
    }
    return n * fakultaet_rekursiv(n - 1);   /* rekursiver Aufruf */
}

/* fakultaet_genau: n = Eingabe (n >= 0); gibt n! als double zurueck
   (exakt bis 22!), dient als Vergleichswert fuer den Ueberlauf-Test. */
double fakultaet_genau(int n)
{
    double ergebnis = 1.0;
    int i;

    if (n < 0) {
        return -1.0;
    }
    for (i = 2; i <= n; i++) {
        ergebnis = ergebnis * i;
    }
    return ergebnis;
}

/* fibonacci_rekursiv: n = Index (n >= 0); gibt die n-te Fibonacci-Zahl
   rekursiv zurueck, -1 bei n < 0. */
int fibonacci_rekursiv(int n)
{
    if (n < 0) {
        return -1;
    }
    if (n <= 1) {
        return n;                           /* fib(0) = 0, fib(1) = 1 */
    }
    return fibonacci_rekursiv(n - 1) + fibonacci_rekursiv(n - 2);
}

/* fibonacci_iterativ: n = Index (n >= 0); gibt die n-te Fibonacci-Zahl
   mit einer Schleife zurueck, -1 bei n < 0. */
int fibonacci_iterativ(int n)
{
    int vorletzte = 0;   /* fib(i-2) */
    int letzte = 1;      /* fib(i-1) */
    int aktuell;
    int i;

    if (n < 0) {
        return -1;
    }
    if (n <= 1) {
        return n;
    }
    for (i = 2; i <= n; i++) {
        aktuell = vorletzte + letzte;
        vorletzte = letzte;
        letzte = aktuell;
    }
    return letzte;
}
