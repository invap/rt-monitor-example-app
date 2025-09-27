.PHONY : clean buggy-debug buggy-exec patched-debug patched-exec

clean:
	rm -rf main *.o *.dSYM

buggy: clean
	make -C ../c-reporter-api/ lib
	gcc buggy\ app/main.c buggy\ app/functions.c data-display/ex_display.c data-source/ex_adc.c -L../c-reporter-api/lib/ -lstopwatch -L../c-reporter-api/lib/ -lc-reporter-api -o main

buggy-no-clocks: clean
	make -C ../c-reporter-api/ lib
	gcc buggy\ app\ no-clocks/main.c buggy\ app\ no-clocks/functions.c data-display/ex_display.c data-source/ex_adc.c -L../c-reporter-api/lib/ -lstopwatch -L../c-reporter-api/lib/ -lc-reporter-api -o main

patched: clean
	make -C ../c-reporter-api lib
	gcc patched\ app/main.c patched\ app/functions.c data-display/ex_display.c data-source/ex_adc.c -L../c-reporter-api/lib/ -lstopwatch -L../c-reporter-api/lib/ -lc-reporter-api -o main

patched-no-clocks: clean
	make -C ../c-reporter-api lib
	gcc patched\ app\ no-clocks/main.c patched\ app\ no-clocks/functions.c data-display/ex_display.c data-source/ex_adc.c -L../c-reporter-api/lib/ -lstopwatch -L../c-reporter-api/lib/ -lc-reporter-api -o main
