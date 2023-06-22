

b:
	betty *.c

factors:
	make b
	gcc factors.c -o factors -L~/gmp-6.2.1/.libs -lgmp -static

rsa:
	make b
	gcc rsa.c -o rsa -L~/gmp-6.2.1/.libs -lgmp -static

