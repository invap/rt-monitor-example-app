.PHONY : clean buggy-debug buggy-exec patched-debug patched-exec

clean:
	rm -rf main *.o *.dSYM

buggy-debug: clean
	make -C ../c-reporter-api debug
	make -C ../timer debug
	gcc -g buggy\ app/main.c buggy\ app/functions.c data-display/ex_display.c data-source/ex_adc.c ../timer/bin/timer.o ../c-reporter-api/bin/c-reporter-api.o -o main

buggy-exec: clean
	make -C ../c-reporter-api/ lib
	make -C ../timer/ lib
	gcc buggy\ app/main.c buggy\ app/functions.c data-display/ex_display.c data-source/ex_adc.c -L../timer/lib/ -ltimer -L../c-reporter-api/lib/ -lc-reporter-api -o main

patched-debug: clean
	make -C ../c-reporter-api debug
	make -C ../timer debug
	gcc -g patched\ app/main.c patched\ app/functions.c data-display/ex_display.c data-source/ex_adc.c ../timer/bin/timer.o ../c-reporter-api/bin/c-reporter-api.o -o main

patched-exec: clean
	make -C ../c-reporter-api lib
	make -C ../timer lib
	gcc patched\ app/main.c patched\ app/functions.c data-display/ex_display.c data-source/ex_adc.c -L../timer/lib/ -ltimer -L../c-reporter-api/lib/ -lc-reporter-api -o main
