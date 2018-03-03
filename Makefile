build: livrare

livrare: debug.c
	gcc -Wall debug.c -o livrare -std=c99

clean:
	rm -rf livrare
