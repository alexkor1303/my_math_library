FLAGS = -Wall -Werror -Wextra

all: s21_math.a test gcov_report

s21_math: s21_math.o

s21_math.o: s21_math.c
	gcc $(FLAGS) -c s21_math.c

s21_math.a:
	gcc $(FLAGS) -c s21_*.c
	ar r s21_math.a *.o 
	rm *.o

test: s21_math.a
	gcc $(FLAGS) test.c s21_math.a -lcheck -lm -lpthread --coverage -o test
	./test

testme: s21_math.a
	gcc $(FLAGS) test.c s21_math.a -I/Users/sashaboss/.brew/Cellar/check/0.15.2/include -L/Users/sashaboss/.brew/Cellar/check/0.15.2/lib -lcheck -lm -lpthread --coverage   -o test
	./test

gcov_report:
	lcov -t "test_info" -o test.info -c -d .
	genhtml -o report test.info
	open ./report/index.html

clean:
	rm -rf report *.o *.a *.gcno *.gcda  *.info test

rebuild: clean s21_math.a
