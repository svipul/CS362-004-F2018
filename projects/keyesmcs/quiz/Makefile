CFLAGS = -Wall -lm -std=c99

testme.exe: testme.c
	gcc -o testme.exe testme.c -g $(CFLAGS)

all: testme.exe
	./testme.exe

clean:
	rm *.exe
