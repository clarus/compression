default:
	gcc -Wall -std=c99 -g *.c -o entropy -lm

test: default
	ruby test.rb