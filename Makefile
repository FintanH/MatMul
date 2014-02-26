all:
	gcc a.c -O3 -fopenmp -std=c99
debug:
	gcc a.c -fopenmp -std=c99 -g
