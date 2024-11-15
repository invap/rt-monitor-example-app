.PHONY : clean buggy-debug buggy-exec patched-debug patched-exec

clean:
	rm -rf main *.o *.dSYM

buggy: clean
	make -C ../c-reporter-api/ lib
	gcc buggy\ app/main.c buggy\ app/functions.c data-display/ex_display.c data-source/ex_adc.c -L../c-reporter-api/lib/ -lstopwatch -L../c-reporter-api/lib/ -lc-reporter-api -o main

patched: clean
	make -C ../c-reporter-api lib
	gcc patched\ app/main.c patched\ app/functions.c data-display/ex_display.c data-source/ex_adc.c -L../c-reporter-api/lib/ -lstopwatch -L../c-reporter-api/lib/ -lc-reporter-api -o main

buggy-self-logging: clean
	make -C ../c-reporter-api/ lib
	gcc buggy\ app\ self-logging/main.c buggy\ app\ self-logging/functions.c data-display/ex_display.c data-source\ self-logging/ex_adc.c -L../c-reporter-api/lib/ -lstopwatch -L../c-reporter-api/lib/ -lc-reporter-api -o main

patched-self-logging: clean
	make -C ../c-reporter-api/ lib
	gcc patched\ app\ self-logging/main.c patched\ app\ self-logging/functions.c data-display/ex_display.c data-source\ self-logging/ex_adc.c -L../c-reporter-api/lib/ -lstopwatch -L../c-reporter-api/lib/ -lc-reporter-api -o main

