CFLAGS = -Wall -Wextra -Werror

all:
	gcc $(CFLAGS) -o trab2 src/client/main.c src/libs/src/*.c
clean:
	rm -f trab2
debug:
	gcc $(CFLAGS) -DDEBUG_MODE -o trab2 src/client/main.c src/libs/src/*.c
run:
	./trab2 input/N10_S3_C3_M3.txt output/N10_S3_C3_M3-output.txt
	./trab2 input/N100_S20_C30_M5.txt output/N100_S20_C30_M5-output.txt
	./trab2 input/N1000_S50_C300_M10.txt output/N1000_S50_C300_M10-output.txt
	./trab2 input/N10000_S50_C300_M10.txt output/N10000_S50_C300_M10-output.txt
valgrind:
	valgrind --track-origins=yes --leak-check=full ./trab2 input/N10000_S50_C300_M10.txt output/N10000_S50_C300_M10-output.txt
