.PHONY : clean buggy-debug buggy-exec patched-debug patched-exec

clean:
	make -C ../c-reporter-api/ clean
	rm -rf main *.o *.dSYM

buggy:
	make -C ../c-reporter-api/ lib
	gcc buggy\ app/main.c buggy\ app/functions.c data-display/ex_display.c data-source/ex_adc.c -L../c-reporter-api/lib/ -lstopwatch -L../c-reporter-api/lib/ -lc-reporter-api -lm -o main

buggy-no-clocks:
	make -C ../c-reporter-api/ lib
	gcc buggy\ app\ no-clocks/main.c buggy\ app\ no-clocks/functions.c data-display/ex_display.c data-source/ex_adc.c -L../c-reporter-api/lib/ -lstopwatch -L../c-reporter-api/lib/ -lc-reporter-api -lm -o main

patched:
	make -C ../c-reporter-api/ lib
	gcc patched\ app/main.c patched\ app/functions.c data-display/ex_display.c data-source/ex_adc.c -L../c-reporter-api/lib/ -lstopwatch -L../c-reporter-api/lib/ -lc-reporter-api -lm -o main

patched-no-clocks:
	make -C ../c-reporter-api/ lib
	gcc patched\ app\ no-clocks/main.c patched\ app\ no-clocks/functions.c data-display/ex_display.c data-source/ex_adc.c -L../c-reporter-api/lib/ -lstopwatch -L../c-reporter-api/lib/ -lc-reporter-api -lm -o main
