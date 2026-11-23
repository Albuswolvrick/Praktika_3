CC     = gcc
CFLAGS = -Wall -Wextra -std=c11 -O0

rechner: main.o rechner.o
	$(CC) $(CFLAGS) -o rechner main.o rechner.o

main.o: main.c rechner.h
	$(CC) $(CFLAGS) -c main.c

rechner.o: rechner.c rechner.h
	$(CC) $(CFLAGS) -c rechner.c

clean:
	rm -f *.o rechner rechner.exe
