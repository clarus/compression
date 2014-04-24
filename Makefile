default:
	gcc -Wall -std=c99 -g *.c -o etoile -lm

test: default
	ruby test.rb