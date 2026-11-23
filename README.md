# Praktikum 3 – Rechenmodul in C

A small calculator in C, split into a module.
This file explains every part for beginners.

---

## 1. Files in this project

| File         | What it does                                          |
|--------------|-------------------------------------------------------|
| `rechner.h`  | Header. Lists the functions (only names and types).   |
| `rechner.c`  | Implementation. The real code of every function.      |
| `main.c`     | Menu. Reads input, calls functions, prints results.   |
| `Makefile`   | Build instructions for `make`.                        |
| `.gitignore` | Tells Git to ignore compiled files.                   |

---

## 2. How to compile and run

You need the compiler `gcc`.

### Option A: with make

```bash
make
./rechner
```

Clean up compiled files:

```bash
make clean
```

### Option B: by hand

```bash
gcc -Wall -Wextra -std=c11 -o rechner main.c rechner.c
./rechner
```

On Windows (MinGW) the program is called `rechner.exe`.
Start it with `rechner.exe`.

### What the flags mean

- `-Wall -Wextra` – show warnings. Warnings often point to bugs.
- `-std=c11` – use the C11 standard.
- `-o rechner` – name of the output program.
- `-O0` (in the Makefile) – no optimization. Keeps the time measurement honest.

Important: give **both** `.c` files to gcc.
If you forget `rechner.c`, you get the error `undefined reference to 'addiere'`.

---

## 3. What is a module?

A module splits a program into parts.

- The **header** (`.h`) says *what* exists.
- The **source file** (`.c`) says *how* it works.
- Other files use the module with `#include "rechner.h"`.

Think of it like a restaurant:

- The **menu card** is the header. You see the dishes.
- The **kitchen** is the `.c` file. There the food is made.
- The **guest** is `main.c`. The guest orders but does not cook.

That is why `main.c` has **no calculation logic**. It only orders (calls functions) and shows the result.

---

## 4. The header file `rechner.h`

### Prototypes

```c
double addiere(double a, double b);
```

This is a **prototype** (declaration).
It tells the compiler:

- the name: `addiere`
- the parameters: two `double` values
- the return type: `double`

There is no `{ ... }` body here. The body is in `rechner.c`.

### Include guard

```c
#ifndef RECHNER_H
#define RECHNER_H
...
#endif
```

This stops the header from being included twice.

Step by step:

1. `#ifndef RECHNER_H` – "if RECHNER_H is not defined yet ..."
2. `#define RECHNER_H` – "... define it now ..."
3. the content is read
4. `#endif` – end

The second time, `RECHNER_H` already exists. So the content is skipped.
Without the guard you can get "redefinition" errors.

### `#include "..."` vs `#include <...>`

- `"rechner.h"` – your own file, searched in the project folder.
- `<stdio.h>` – system library file.

---

## 5. Aufgabe 1 – the calculator

### The simple functions

```c
double addiere(double a, double b)
{
    return a + b;
}
```

`subtrahiere` and `multipliziere` work the same way.

### Division by zero with an output parameter

```c
double dividiere(double a, double b, int *fehler)
```

A function can only `return` one value.
But here we want two things back:

1. the result
2. the information "was there an error?"

Solution: a **pointer** parameter `int *fehler`.

In `main.c`:

```c
int fehler = 0;
ergebnis = dividiere(a, b, &fehler);
```

- `&fehler` means "the address of the variable `fehler`".
- The function gets this address.
- Inside the function, `*fehler = 1;` writes directly into the variable in `main`.

Picture it like this: you give the function your house address.
The function can now put a letter in your mailbox.

After the call, `main` checks:

```c
if (fehler) {
    printf("Fehler: Division durch 0\n");
}
```

So the program does not crash. It prints a clean error message.

The function also checks `if (fehler != NULL)`.
This protects against someone passing no address at all.

---

## 6. The menu in `main.c`

The menu runs in an endless loop `for (;;)`.
It stops when the user enters `0`.

```
1  Addition
2  Subtraktion
3  Multiplikation
4  Division
5  Fakultaet
6  Fibonacci-Tabelle n = 0..15 (Aufgabe 2)
7  Fakultaet-Ueberlauf-Test (Aufgabe 3)
8  Laufzeitvergleich fibonacci(40) (Aufgabe 4)
0  Beenden
```

A `switch` picks the right action.

### Safe input

`scanf` returns how many values it read.

- `1` – success
- `0` – wrong input (for example letters)
- `EOF` – input ended

If the input is wrong, the rest of the line is removed with `puffer_leeren()`.
Otherwise the bad letters stay in the input and cause an endless loop.

The functions are `static`. This means: only visible inside `main.c`.
They are helpers, not part of the module.

---

## 7. Aufgabe 2 – recursion vs. iteration

### Two ways to repeat work

- **Iteration** – a loop (`for`, `while`).
- **Recursion** – a function calls itself.

Every recursion needs a **base case** (Abbruchbedingung).
Without it, the function calls itself forever and the program crashes (stack overflow).

### Factorial (Fakultaet)

Math: `5! = 5 * 4 * 3 * 2 * 1 = 120`, and `0! = 1`.

Iterative (loop):

```c
int ergebnis = 1;
for (i = 2; i <= n; i++) {
    ergebnis = ergebnis * i;
}
```

Recursive:

```c
if (n <= 1) return 1;              /* base case */
return n * fakultaet_rekursiv(n - 1);
```

How `fakultaet_rekursiv(4)` runs:

```
4 * fak(3)
    3 * fak(2)
        2 * fak(1)
            1          <- base case
        2 * 1 = 2
    3 * 2 = 6
4 * 6 = 24
```

### Fibonacci

Rule: every number is the sum of the two before.

```
0, 1, 1, 2, 3, 5, 8, 13, 21, ...
fib(0) = 0
fib(1) = 1
fib(n) = fib(n-1) + fib(n-2)
```

Recursive version: a direct copy of the math rule.

Iterative version: remember only the last two numbers.

```c
aktuell   = vorletzte + letzte;
vorletzte = letzte;
letzte    = aktuell;
```

Menu point 6 prints both versions side by side for n = 0 to 15.
The column `gleich?` shows `ja` if both are equal.

---

## 8. Aufgabe 3 – value range and overflow

### What is overflow?

An `int` has limited space (usually 32 bits).
The largest value is `INT_MAX = 2147483647` (about 2.1 billion).

If a result is bigger, it does not fit.
The number "wraps around" and becomes wrong, sometimes even negative.

Compare it to a car odometer at 999999. One more km and it shows 000000.

### Result of the experiment

Menu point 7 compares `fakultaet(n)` with an exact value (`double`):

```
  12       479001600              479001600         ok
  13      1932053504             6227020800     FALSCH
```

- `12! = 479001600` – fits into `int`
- `13! = 6227020800` – too big, the program shows `1932053504`

**From n = 13 the result is wrong.**
This is also written as a comment in `rechner.c`.

Note: in C, overflow of a signed `int` is "undefined behavior".
This means the C standard does not say what happens.
On normal PCs you see the wrap-around shown above.

How to fix it if needed: use a bigger type like `long long` (correct up to 20!).

### Comments on each function

Every function in `rechner.c` has a short comment:
what it does, what the parameters mean, what it returns.

---

## 9. Aufgabe 4 – runtime comparison

### How time is measured

```c
#include <time.h>

clock_t start = clock();
ergebnis = fibonacci_rekursiv(40);
clock_t ende = clock();

double sekunden = (double)(ende - start) / CLOCKS_PER_SEC;
```

- `clock()` gives the used processor time in "ticks".
- `CLOCKS_PER_SEC` says how many ticks are one second.
- The cast `(double)` is needed, otherwise integer division cuts off the decimals.

### Example result

```
rekursiv: fib(40) = 102334155   Zeit: 0.886435 s
iterativ: fib(40) = 102334155   Zeit: 0.000000 s
```

Your times can be different. It depends on your computer.

### Why is recursion so slow here?

Look at the call tree for `fib(5)`:

```
                 fib(5)
              /          \
         fib(4)          fib(3)
        /     \          /    \
    fib(3)  fib(2)   fib(2)  fib(1)
    /   \
fib(2) fib(1)
```

`fib(3)` is calculated **twice**. `fib(2)` is calculated **three times**.
The same sub-problems are calculated again and again
(mehrfach berechnete Teilprobleme).

For `fib(40)` that is more than **331 million** function calls.
The work grows **exponentially** (about 1.6 times more for each +1 in n).

The iterative version calculates each value **only once**.
For `fib(40)` it needs only 39 loop steps.
The work grows **linearly** with n.

| Version    | Calls / steps for n = 40 | Growth      |
|------------|--------------------------|-------------|
| rekursiv   | about 331 000 000        | exponential |
| iterativ   | 39                       | linear      |

---

## 10. Push to GitHub

```bash
git init
git add .
git commit -m "Praktikum 3: Rechenmodul"
git branch -M main
git remote add origin https://github.com/<your-name>/<repo-name>.git
git push -u origin main
```

The `.gitignore` keeps compiled files (`rechner`, `*.o`, `*.exe`) out of the repo.

---

## 11. Common errors

| Error message                         | Reason and fix                                    |
|---------------------------------------|---------------------------------------------------|
| `undefined reference to 'addiere'`    | `rechner.c` not compiled. Add it to the gcc line. |
| `rechner.h: No such file or directory`| Header not in the same folder.                    |
| `implicit declaration of function`    | `#include "rechner.h"` is missing.                |
| Program hangs after wrong input       | Input buffer not cleared (see `puffer_leeren`).   |
