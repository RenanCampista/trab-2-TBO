all:
#	gcc -Wall -Wextra -Werror -g -pg -o trab2 *.c -lm
	gcc -Wall -Wextra -Werror -o trab2 src/client/main.c src/libs/src/*.c
clean:
	rm trab2
run:
	./trab2 input/N10_S3_C3_M3.txt output/N10_S3_C3_M3-output.txt
	./trab2 input/N100_S20_C30_M5.txt output/N100_S20_C30_M5-output.txt
	./trab2 input/N1000_S50_C300_M10.txt output/N1000_S50_C300_M10-output.txt
	./trab2 input/N10000_S50_C300_M10.txt output/N10000_S50_C300_M10-output.txt
valgrind:
	valgrind --track-origins=yes --leak-check=full ./trab2 input/N10000_S50_C300_M10.txt output/N10000_S50_C300_M10-output.txt
gprof:
	./trab2 input/N10000_S50_C300_M10.txt output/N10000_S50_C300_M10-output.txt
	gprof trab2 gmon.out > analysis.txt
diff:
	diff output/N10_S3_C3_M3-output.txt solution/N10_S3_C3_M3-solution.txt
	diff output/N100_S20_C30_M5-output.txt solution/N100_S20_C30_M5-solution.txt
	diff output/N1000_S50_C300_M10-output.txt solution/N1000_S50_C300_M10-solution.txt
	diff output/N10000_S50_C300_M10-output.txt solution/N10000_S50_C300_M10-solution.txt
