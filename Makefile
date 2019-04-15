CC=gcc
CFLAGS=-std=c99 -Wall -I include -pedantic -g

all: clean program test

obj/Dictionary.o: src/Dictionary.c
	$(CC) $(CFLAGS) -c $< -o $@

obj/WordChecker.o: src/WordChecker.c
	$(CC) $(CFLAGS) -c $< -o $@

obj/BoardGenerator.o: src/BoardGenerator.c
	$(CC) $(CFLAGS) -c $< -o $@

obj/Scoreboard.o: src/Scoreboard.c
	$(CC) $(CFLAGS) -c $< -o $@

obj/Boggle.o: src/Boggle.c
	$(CC) $(CFLAGS) -c $< -o $@

bin/program: obj/Dictionary.o obj/WordChecker.o obj/BoardGenerator.o obj/Scoreboard.o obj/Boggle.o
	$(CC) -o $@ $^

program: clean bin/program

#runprogram: clean program
#	./bin/program

#obj/test.o: src/testBoggle.c
#	$(CC) $(CFLAGS) -c $< -o $@

#bin/test: obj/Dictionary.o obj/WordChecker.o obj/BoardGenerator.o obj/Scoreboard.o obj/test.o
#	$(CC) -o $@ $^

#test: clean bin/test

#runtest: clean test
#	./bin/test

clean:
	rm -f obj/Dictionary.o obj/Boggle.o obj/WordChecker.o obj/BoardGenerator.o obj/Scoreboard.o bin/program #bin/test