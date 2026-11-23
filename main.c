#include <stdio.h>
#include <time.h>
#include "rechner.h"

/* Entfernt die restlichen Zeichen der Eingabezeile (z. B. nach Fehleingabe). */
static void puffer_leeren(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* nichts tun */
    }
}

/* Liest eine Kommazahl. Gibt 1 bei Erfolg zurueck, 0 bei Eingabeende (EOF). */
static int lies_double(const char *text, double *wert)
{
    int r;
    for (;;) {
        printf("%s", text);
        r = scanf("%lf", wert);
        if (r == EOF) {
            return 0;
        }
        puffer_leeren();
        if (r == 1) {
            return 1;
        }
        printf("Ungueltige Eingabe, bitte eine Zahl eingeben.\n");
    }
}

/* Liest eine ganze Zahl. Gibt 1 bei Erfolg zurueck, 0 bei Eingabeende (EOF). */
static int lies_int(const char *text, int *wert)
{
    int r;
    for (;;) {
        printf("%s", text);
        r = scanf("%d", wert);
        if (r == EOF) {
            return 0;
        }
        puffer_leeren();
        if (r == 1) {
            return 1;
        }
        printf("Ungueltige Eingabe, bitte eine ganze Zahl eingeben.\n");
    }
}

static void zeige_menue(void)
{
    printf("\n===== Rechner =====\n");
    printf("1  Addition\n");
    printf("2  Subtraktion\n");
    printf("3  Multiplikation\n");
    printf("4  Division\n");
    printf("5  Fakultaet\n");
    printf("6  Fibonacci-Tabelle n = 0..15 (Aufgabe 2)\n");
    printf("7  Fakultaet-Ueberlauf-Test (Aufgabe 3)\n");
    printf("8  Laufzeitvergleich fibonacci(40) (Aufgabe 4)\n");
    printf("0  Beenden\n");
}

/* Menuepunkte 1 bis 4: zwei Operanden einlesen und Ergebnis ausgeben. */
static void grundrechenart(int wahl)
{
    double a, b, ergebnis;
    int fehler = 0;

    if (!lies_double("Erster Operand:  ", &a)) return;
    if (!lies_double("Zweiter Operand: ", &b)) return;

    switch (wahl) {
    case 1:
        ergebnis = addiere(a, b);
        printf("Ergebnis: %g + %g = %g\n", a, b, ergebnis);
        break;
    case 2:
        ergebnis = subtrahiere(a, b);
        printf("Ergebnis: %g - %g = %g\n", a, b, ergebnis);
        break;
    case 3:
        ergebnis = multipliziere(a, b);
        printf("Ergebnis: %g * %g = %g\n", a, b, ergebnis);
        break;
    case 4:
        ergebnis = dividiere(a, b, &fehler);
        if (fehler) {
            printf("Fehler: Division durch 0\n");
        } else {
            printf("Ergebnis: %g / %g = %g\n", a, b, ergebnis);
        }
        break;
    }
}

/* Menuepunkt 5: Fakultaet iterativ und rekursiv. */
static void fakultaet_menue(void)
{
    int n;

    if (!lies_int("n: ", &n)) return;
    if (n < 0) {
        printf("Fehler: Fakultaet nur fuer n >= 0 definiert\n");
        return;
    }
    printf("iterativ: %d! = %d\n", n, fakultaet(n));
    printf("rekursiv: %d! = %d\n", n, fakultaet_rekursiv(n));
    if (n >= 13) {
        printf("Hinweis: ab n = 13 ist das Ergebnis wegen int-Ueberlauf falsch.\n");
    }
}

/* Aufgabe 2: Fibonacci beider Varianten nebeneinander, mit Pruefung. */
static void fibonacci_tabelle(void)
{
    int n;
    int rek, it;
    int alle_gleich = 1;

    printf("\n%4s %12s %12s %8s\n", "n", "rekursiv", "iterativ", "gleich?");
    for (n = 0; n <= 15; n++) {
        rek = fibonacci_rekursiv(n);
        it = fibonacci_iterativ(n);
        printf("%4d %12d %12d %8s\n", n, rek, it, (rek == it) ? "ja" : "NEIN");
        if (rek != it) {
            alle_gleich = 0;
        }
    }
    if (alle_gleich) {
        printf("Alle Werte stimmen ueberein.\n");
    } else {
        printf("Es gibt Abweichungen!\n");
    }

    /* Zusaetzlich: Fakultaet iterativ vs. rekursiv vergleichen */
    alle_gleich = 1;
    for (n = 0; n <= 12; n++) {
        if (fakultaet(n) != fakultaet_rekursiv(n)) {
            alle_gleich = 0;
        }
    }
    printf("Fakultaet iterativ und rekursiv (n = 0..12): %s\n",
           alle_gleich ? "stimmen ueberein" : "weichen ab");
}

/* Aufgabe 3: Ab welchem n ist fakultaet (int) falsch? */
static void ueberlauf_test(void)
{
    int n;
    int erster_fehler = -1;

    printf("\n%4s %15s %22s %10s\n", "n", "fakultaet(int)", "richtiger Wert", "Status");
    for (n = 0; n <= 20; n++) {
        int wert_int = fakultaet(n);
        double wert_genau = fakultaet_genau(n);
        int ok = ((double)wert_int == wert_genau);

        printf("%4d %15d %22.0f %10s\n", n, wert_int, wert_genau, ok ? "ok" : "FALSCH");
        if (!ok && erster_fehler == -1) {
            erster_fehler = n;
        }
    }
    printf("Erstes falsches Ergebnis bei n = %d\n", erster_fehler);
}

/* Aufgabe 4: Laufzeitvergleich.
 *
 * Erklaerung des Unterschieds:
 *   fibonacci_rekursiv(40) ruft sich selbst zweimal auf: fib(39) und fib(38).
 *   fib(39) ruft wieder fib(38) und fib(37) auf usw. Dieselben Teilprobleme
 *   (z. B. fib(38), fib(37), ...) werden also sehr oft neu berechnet.
 *   Fuer n = 40 sind das ueber 331 Millionen Funktionsaufrufe.
 *   Die Anzahl der Aufrufe waechst exponentiell (ungefaehr 1.6 hoch n).
 *
 *   fibonacci_iterativ(40) braucht nur 39 Schleifendurchlaeufe, weil jedes
 *   Teilergebnis genau einmal berechnet und in einer Variable gemerkt wird.
 *   Der Aufwand waechst nur linear mit n.
 *
 *   Deshalb dauert die rekursive Version deutlich laenger (je nach Rechner
 *   etwa 0.3 bis 2 Sekunden), die iterative ist praktisch sofort fertig.
 */
static void laufzeitvergleich(void)
{
    clock_t start, ende;
    int ergebnis_rek, ergebnis_it;
    double zeit_rek, zeit_it;

    printf("Berechne fibonacci_rekursiv(40), bitte warten ...\n");

    start = clock();
    ergebnis_rek = fibonacci_rekursiv(40);
    ende = clock();
    zeit_rek = (double)(ende - start) / CLOCKS_PER_SEC;

    start = clock();
    ergebnis_it = fibonacci_iterativ(40);
    ende = clock();
    zeit_it = (double)(ende - start) / CLOCKS_PER_SEC;

    printf("rekursiv: fib(40) = %d   Zeit: %.6f s\n", ergebnis_rek, zeit_rek);
    printf("iterativ: fib(40) = %d   Zeit: %.6f s\n", ergebnis_it, zeit_it);
}

int main(void)
{
    int wahl;

    for (;;) {
        zeige_menue();
        if (!lies_int("Auswahl: ", &wahl)) {
            break;                      /* Eingabeende */
        }

        switch (wahl) {
        case 0:
            printf("Programm beendet.\n");
            return 0;
        case 1:
        case 2:
        case 3:
        case 4:
            grundrechenart(wahl);
            break;
        case 5:
            fakultaet_menue();
            break;
        case 6:
            fibonacci_tabelle();
            break;
        case 7:
            ueberlauf_test();
            break;
        case 8:
            laufzeitvergleich();
            break;
        default:
            printf("Ungueltige Auswahl.\n");
            break;
        }
    }
    return 0;
}
