#ifndef RECHNER_H
#define RECHNER_H

/* Aufgabe 1: Grundrechenarten */
double addiere(double a, double b);
double subtrahiere(double a, double b);
double multipliziere(double a, double b);
double dividiere(double a, double b, int *fehler); /* *fehler = 1 bei Division durch 0 */
int fakultaet(int n);

/* Aufgabe 2: Rekursion vs. Iteration */
int fakultaet_rekursiv(int n);
int fibonacci_rekursiv(int n);
int fibonacci_iterativ(int n);

/* Aufgabe 3: Referenzwert zum Erkennen des Ueberlaufs */
double fakultaet_genau(int n);

#endif
