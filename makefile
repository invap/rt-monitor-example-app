clean:
	rm -rf main *.o main.dSYM

debug:
	gcc -g -c ../c-reporter-api/src/c-reporter-api.c -o c-reporter-api.o
	gcc -g main.c functions.c data-display/ex_display.c data-source/ex_adc.c c-reporter-api.o -o main

main:
	gcc -c ../c-reporter-api/src/c-reporter-api.c -o c-reporter-api.o
	gcc main.c functions.c data-display/ex_display.c data-source/ex_adc.c c-reporter-api.o -o main
