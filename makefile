.PHONY : clean dirs lib buggy-debug buggy-exec patched-debug patched-exec

clean:
	make -C ../c-reporter-api/ clean
	rm -rf main *.o *.dSYM

dirs:
	mkdir -p lib bin

lib: dirs
	make -C ../c-reporter-api/ lib

buggy: lib
	gcc buggy\ app/main.c buggy\ app/functions.c data-display/ex_display.c data-source/ex_adc.c -L../c-reporter-api/lib/ -lstopwatch -L../c-reporter-api/lib/ -lc-reporter-api -lm -o main

buggy-no-clocks: lib
	gcc buggy\ app\ no-clocks/main.c buggy\ app\ no-clocks/functions.c data-display/ex_display.c data-source/ex_adc.c -L../c-reporter-api/lib/ -lstopwatch -L../c-reporter-api/lib/ -lc-reporter-api -lm -o main

patched: lib
	gcc patched\ app/main.c patched\ app/functions.c data-display/ex_display.c data-source/ex_adc.c -L../c-reporter-api/lib/ -lstopwatch -L../c-reporter-api/lib/ -lc-reporter-api -lm -o main

patched-no-clocks: lib
	gcc patched\ app\ no-clocks/main.c patched\ app\ no-clocks/functions.c data-display/ex_display.c data-source/ex_adc.c -L../c-reporter-api/lib/ -lstopwatch -L../c-reporter-api/lib/ -lc-reporter-api -lm -o main
