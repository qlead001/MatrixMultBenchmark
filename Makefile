CC = gcc

all:
	${CC} -o benchmark main.c benchmark.c -D SIZE=1000

clean:
	rm benchmark
