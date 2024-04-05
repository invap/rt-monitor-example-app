clean:
	rm -rf main *.o main.dSYM

debug-buggy:
	gcc -g -c ../c-reporter-api/src/c-reporter-api.c -o c-reporter-api.o
	gcc -g -c ../c-reporter-api/src/timer.c -o timer.o
	gcc -g buggy\ app/main.c buggy\ app/functions.c data-display/ex_display.c data-source/ex_adc.c timer.o c-reporter-api.o -o main

main-buggy:
	gcc -c ../c-reporter-api/src/c-reporter-api.c -o c-reporter-api.o
	gcc -c ../c-reporter-api/src/timer.c -o timer.o
	gcc buggy\ app/main.c buggy\ app/functions.c data-display/ex_display.c data-source/ex_adc.c timer.o c-reporter-api.o -o main

debug-patched:
	gcc -g -c ../c-reporter-api/src/c-reporter-api.c -o c-reporter-api.o
	gcc -g -c ../c-reporter-api/src/timer.c -o timer.o
	gcc -g patched\ app/main.c patched\ app/functions.c data-display/ex_display.c data-source/ex_adc.c timer.o c-reporter-api.o -o main

main-patched:
	gcc -c ../c-reporter-api/src/c-reporter-api.c -o c-reporter-api.o
	gcc -c ../c-reporter-api/src/timer.c -o timer.o
	gcc patched\ app/main.c patched\ app/functions.c data-display/ex_display.c data-source/ex_adc.c timer.o c-reporter-api.o -o main
