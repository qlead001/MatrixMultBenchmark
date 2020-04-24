CC = gcc

all: bench1000 bench1500 bench2000 bench2500

bench%:
	${CC} -o benchmark$* main.c benchmark.c -O3 -D SIZE=$*

clean:
	rm benchmark[0-9]* benchmark
