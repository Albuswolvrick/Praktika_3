#include "rechner.h"

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
