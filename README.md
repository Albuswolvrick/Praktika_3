# Praktikum 3 – A Calculator Module in C
 
A small C project that teaches you how real C programs are organised:
**multiple files, header files, functions, pointers, recursion, integer overflow and measuring run time.**
 
The comments in the code are in German (the assignment is German). This README is in English and explains everything step by step.
 
---
 
## 1. What does the program do?
 
When you start it, you see a menu:
 
```
===== Rechner =====
1 - Addition
2 - Subtraktion
3 - Multiplikation
4 - Division
5 - Fakultaet (iterativ und rekursiv)
6 - Fibonacci-Vergleich n = 0..15
7 - Laufzeitvergleich Fibonacci(40)
8 - Fakultaet-Ueberlauf (n = 0..15)
0 - Beenden
```
 
You type a number, the program does the job, shows the result and shows the menu again until you enter `0`.
 
---
 
## 2. Project structure
 
```
praktikum3/
├── CMakeLists.txt          build instructions for CLion
├── rechner.h               the "table of contents": declares all functions
├── main.c                  menu, input and output (NO calculation logic)
├── addition.c              addiere()
├── subtraktion.c           subtrahiere()
├── multiplikation.c        multipliziere()
├── division.c              dividiere()
├── fakultaet.c             fakultaet()            (loop version)
├── fakultaet_rekursiv.c    fakultaet_rekursiv()   (recursive version)
├── fibonacci_rekursiv.c    fibonacci_rekursiv()
└── fibonacci_iterativ.c    fibonacci_iterativ()
```
 
**Design rule:** `main.c` only talks to the user. All calculations live in the other files. This is called *separation of concerns* – you can change or test a calculation without touching the menu.
 
---
 
## 3. Key concepts (read this first!)
 
### 3.1 Why split a program into several files?
 
- Small files are easier to read and find things in.
- Several people can work on different files.
- Only changed files need to be recompiled.
- You can reuse a file (e.g. `division.c`) in other projects.
### 3.2 Declaration vs. definition
 
| | Looks like | Where | Purpose |
|---|---|---|---|
| **Declaration** (prototype) | `double addiere(double a, double b);` | `rechner.h` | Tells the compiler: "this function exists, here is how to call it" |
| **Definition** | `double addiere(double a, double b) { return a + b; }` | `addition.c` | The actual code |
 
`main.c` includes `rechner.h`, so the compiler knows `addiere` exists, even though the code is in another file. The *linker* later connects the call to the real code.
 
### 3.3 The include guard
 
```c
#ifndef RECHNER_H
#define RECHNER_H
...
#endif
```
 
If a header is included twice (e.g. through two other headers), the compiler would see every declaration twice and may complain. The guard makes sure the content is only used **once**: the first time, `RECHNER_H` is not defined, so the content is used and `RECHNER_H` gets defined. Next time it *is* defined, so everything is skipped.
 
### 3.4 `#include "..."` vs. `#include <...>`
 
- `#include <stdio.h>` → standard library header (searched in system folders)
- `#include "rechner.h"` → your own header (searched in your project first)
### 3.5 How a C program is built
 
```
addition.c ──┐
division.c ──┤  compiler   ┌ addition.o ┐
main.c ──────┤ ─────────►  │ division.o │  linker   ┌──────────────┐
...          ┘ (one .o per │ main.o     │ ───────►  │ praktikum3   │
               .c file)    └ ...        ┘           │ (executable) │
                                                     └──────────────┘
```
 
1. The **compiler** turns each `.c` file into an object file (`.o`).
2. The **linker** joins all object files into one program.
Typical error messages tell you which step failed:
- `error: ...` with a file and line number → **compiler** problem (syntax, missing declaration)
- `undefined reference to 'xyz'` → **linker** problem (a function is declared but its `.c` file is missing from the build)
---
 
## 4. Walkthrough of the code
 
### 4.1 Basic calculations (`addition.c`, `subtraktion.c`, `multiplikation.c`)
 
```c
double addiere(double a, double b) {
    return a + b;
}
```
 
- `double` = number with decimals (e.g. `3.14`)
- The function receives two values (**parameters**), calculates and `return`s the result.
### 4.2 Division and the error parameter (`division.c`)
 
```c
double dividiere(double a, double b, int *fehler) {
    if (b == 0.0) {
        *fehler = 1;
        return 0.0;
    }
    *fehler = 0;
    return a / b;
}
```
 
**Problem:** A function can only `return` one value. But we need two: the result *and* "did it work?".
 
**Solution:** an **output parameter** using a **pointer**.
 
- `int *fehler` means: "I don't get an int, I get the *address* of an int."
- `*fehler = 1;` means: "go to that address and write 1 there."
How `main.c` uses it:
 
```c
int fehler;                           // a variable in main
double erg = dividiere(a, b, &fehler); // &fehler = "address of fehler"
if (fehler) {
    printf("Fehler: Division durch 0\n");
}
```
 
`&` gets the address, `*` follows the address. The function changes `main`'s variable directly. That is why the program prints an error message instead of crashing.
 
> **Why check for 0?** Dividing two `double`s by zero doesn't crash in C (you get `inf`), but for an integer division it would. Checking explicitly is good habit and the assignment requires it.
 
### 4.3 Factorial: loop vs. recursion
 
n! = 1 · 2 · 3 · … · n (for example 5! = 120, and 0! = 1)
 
**Iterative** (`fakultaet.c`) – a loop:
 
```c
int ergebnis = 1;
for (int i = 2; i <= n; i++) {
    ergebnis *= i;
}
return ergebnis;
```
 
**Recursive** (`fakultaet_rekursiv.c`) – the function calls itself:
 
```c
if (n <= 1) return 1;                  // base case: stops the recursion
return n * fakultaet_rekursiv(n - 1);  // recursive case: smaller problem
```
 
Every recursive function needs
1. a **base case** (where it stops), and
2. a **recursive case** that moves *towards* the base case.
Forget the base case and the function calls itself forever until the program crashes (*stack overflow*).
 
Trace of `fakultaet_rekursiv(4)`:
 
```
4 * fakultaet_rekursiv(3)
    3 * fakultaet_rekursiv(2)
        2 * fakultaet_rekursiv(1)
            1                    <- base case
        2 * 1 = 2
    3 * 2 = 6
4 * 6 = 24
```
 
### 4.4 Fibonacci: loop vs. recursion
 
The sequence: `0, 1, 1, 2, 3, 5, 8, 13, 21, ...` – each number is the sum of the two before it.
 
**Recursive** (`fibonacci_rekursiv.c`) – looks just like the math definition:
 
```c
if (n < 2) return n;
return fibonacci_rekursiv(n - 1) + fibonacci_rekursiv(n - 2);
```
 
**Iterative** (`fibonacci_iterativ.c`) – keeps only the last two numbers:
 
```c
int a = 0, b = 1;
for (int i = 0; i < n; i++) {
    int t = a + b;
    a = b;
    b = t;
}
return a;
```
 
### 4.5 Why is the recursive Fibonacci so slow?
 
Look at which calls are made for `fibonacci_rekursiv(5)`:
 
```
                     fib(5)
                   /        \
              fib(4)         fib(3)
             /     \         /    \
         fib(3)   fib(2)  fib(2)  fib(1)
         /   \    /   \    /   \
     fib(2) fib(1) ...    ...
```
 
`fib(3)` is computed **twice**, `fib(2)` **three times**. For `n = 5` the function is called 15 times, but only 6 different values (0 to 5) exist. This gets dramatically worse as `n` grows – the number of calls roughly multiplies by 1.6 for every step:
 
| n | calls (recursive) | loop steps (iterative) |
|---|---|---|
| 5 | 15 | 5 |
| 20 | about 22,000 | 20 |
| 30 | about 2.7 million | 30 |
| 40 | about 331 million | 40 |
 
This is called **exponential** growth. The iterative version needs **linear** time: it computes each value exactly once.
 
On the machine I tested this on:
 
```
fibonacci_rekursiv(40) = 102334155, Zeit: 0.92 s
fibonacci_iterativ(40) = 102334155, Zeit: 0.000002 s
```
 
Same result, but the loop is hundreds of thousands of times faster. (Your numbers will differ.)
 
> **Lesson:** Recursion is elegant, but don't use it blindly. Always ask: "Do I compute the same thing many times?" (The fix, called *memoization* or *dynamic programming*, is a nice follow-up topic.)
 
### 4.6 Integer overflow (`fakultaet.c`, menu item 8)
 
An `int` is usually 32 bits and can store at most `2,147,483,647` (`INT_MAX`).
 
| n | n! | fits in int? |
|---|---|---|
| 12 | 479,001,600 | yes |
| 13 | 6,227,020,800 | **no** – larger than INT_MAX |
 
So `fakultaet(13)` returns a **wrong number** (we got `1932053504`) – and C doesn't warn you! The program continues happily with garbage.
 
Menu item 8 detects this by computing the same factorial with `long long` (64 bits) and comparing.
 
> **Important:** For *signed* integers, overflow is **undefined behaviour** in C. On most computers the number "wraps around", but the language does not promise this. Never rely on it. Choose a data type that is large enough, or check before you multiply.
 
Ideas to fix it: use `long long` (works up to 20!), `unsigned long long` (up to 20!), or return an error code when `n > 12`.
 
### 4.7 Measuring run time (`main.c`)
 
```c
#include <time.h>
 
clock_t start = clock();
int r = fibonacci_rekursiv(40);
clock_t ende = clock();
double sekunden = (double)(ende - start) / CLOCKS_PER_SEC;
```
 
- `clock()` returns the CPU time used so far, in "ticks".
- `CLOCKS_PER_SEC` converts ticks to seconds.
- The `(double)` cast avoids integer division, which would throw away the decimals.
### 4.8 The menu loop (`main.c`)
 
```c
do {
    menue_anzeigen();
    scanf("%d", &wahl);
    switch (wahl) {
        case 1: ...
        case 0: ...
        default: ...
    }
} while (wahl != 0);
```
 
- `do { ... } while (...)` runs the body **at least once**, then repeats while the condition is true.
- `scanf("%d", &wahl)` reads an integer. Note the `&` – `scanf` needs the *address* of the variable (same idea as with `fehler`).
- `scanf` returns how many values it read. We check `!= 1` to catch invalid input like letters.
- `switch` picks the code to run for each menu number. Every `case` ends with `break;`, otherwise execution "falls through" into the next case.
- Functions marked `static` (like `menue_anzeigen`) are private to `main.c`.
---
 
## 5. How to build and run
 
### In CLion
 
1. **File → Open** and choose the `praktikum3` folder (the one with `CMakeLists.txt`).
2. Wait until CLion finishes loading the CMake project.
3. Press the green ▶ **Run** button (or `Shift+F10`).
4. The program runs in the **Run** window at the bottom. Click into it before typing.
If you add a new `.c` file: add its name to `add_executable(...)` in `CMakeLists.txt`, then **Tools → CMake → Reload CMake Project**.
 
**Debugger tip:** click in the grey margin next to a line to set a *breakpoint*, then press the bug icon 🐞. Step through `fibonacci_rekursiv(5)` with *Step Into* (`F7`) and watch the call stack grow. This is the best way to understand recursion.
 
### On the command line (optional)
 
```bash
gcc -Wall -Wextra -std=c11 -o praktikum3 *.c
./praktikum3          # Linux / macOS
praktikum3.exe        # Windows
```
 
`-Wall -Wextra` turns on helpful warnings. Treat warnings as errors you haven't fixed yet.
 
---
 
## 6. Common beginner mistakes (and how to spot them)
 
| Symptom | Likely cause |
|---|---|
| `undefined reference to 'addiere'` | `addition.c` is not listed in `CMakeLists.txt` (reload CMake after editing) |
| `implicit declaration of function` | Missing `#include "rechner.h"`, or no prototype in the header |
| `redefinition of ...` | Header has no include guard, or a function is defined in two files |
| Program prints strange huge/negative numbers | Integer overflow (see 4.6) |
| Program crashes with a huge recursion | Missing or wrong base case |
| `scanf` loops forever on letter input | Invalid input stays in the buffer; always check the return value |
| `0.1 + 0.2` doesn't print exactly `0.3` | Normal for `double` – computers store decimals in binary, which is only approximate |
 
---
 
## 7. Exercises (to learn more)
 
**Easy**
1. Add a function `modulo(int a, int b)` – create `modulo.c`, declare it in `rechner.h`, add it to `CMakeLists.txt` and the menu.
2. Make the Fibonacci table in menu item 6 go up to n = 20.
3. Print `n!` for n = 0..20 using `long long` – at which `n` does *that* overflow?
**Medium**
4. Write `potenz(double basis, int exponent)` once iteratively and once recursively.
5. Write `ggt(int a, int b)` (greatest common divisor) with the Euclidean algorithm – recursive and iterative.
6. Change `fakultaet` so that it returns `-1` when `n > 12` instead of an overflowing value. Update the comments.
 
**Challenge**
7. Write `fibonacci_memo(int n)` that stores already computed values in an array so that the recursive version becomes fast. Compare the time for `n = 40`.
8. Add a test file `tests.c` with a `main` that checks every function with `assert(...)` (from `<assert.h>`).
 
---
 
## 8. Glossary
 
| Term | Meaning |
|---|---|
| **Prototype** | Declaration of a function without its body |
| **Header file** (`.h`) | File with declarations, included by other files |
| **Include guard** | `#ifndef/#define/#endif` that prevents double inclusion |
| **Compiler** | Translates `.c` files into object files |
| **Linker** | Combines object files into one executable |
| **Pointer** | A variable that stores a memory address |
| **Output parameter** | A pointer parameter the function uses to give back an extra value |
| **Recursion** | A function that calls itself |
| **Base case** | The condition that ends a recursion |
| **Iteration** | Repeating with a loop (`for`, `while`) |
| **Overflow** | A result is too big for its data type |
| **Undefined behaviour** | Code for which C makes no promise about what happens |
 
---
 
## 9. Publishing on GitHub
 
Add a file called `.gitignore` next to this README so build files don't end up in your repository:
 
```
cmake-build-*/
.idea/
*.o
*.exe
```
 
Then, for example:
 
```bash
git init
git add .
git commit -m "Praktikum 3: Rechenmodul"
git branch -M main
git remote add origin https://github.com/<your-name>/<repo-name>.git
git push -u origin main
```
 
Good luck and have fun experimenting! Change things, break them, and read the error messages – that is how you learn C.
 
<
