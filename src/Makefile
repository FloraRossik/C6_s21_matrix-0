NAME = s21_matrix
CC = gcc -Wall -Werror -Wextra -std=c11
GCOVFLAGS = -fprofile-arcs -ftest-coverage
SOURSES = s21_matrix.c
OBJECT = s21_matrix.o
UNIT_TEST = testest.c
TEST = test

OS := $(shell uname -s)

ifeq ($(OS), Darwin)
 CC += -D OS_MAC
 TEST_FLAGS =-lcheck
endif
ifeq ($(OS), Linux)
 CC += -D OS_LINUX
 TEST_FLAGS =-lcheck -lsubunit -lm -lrt -pthread
endif

all: clean s21_matrix.a test

$(NAME): $(OBJECT)
	$(CC) $(OBJECT) -o $(NAME)

s21_matrix.a: s21_matrix.o
	$(CC) -c $(SOURSES)
	@ar rcs s21_matrix.a $(OBJECT)

test: testest.c s21_matrix.a
	$(CC) $< s21_matrix.a $(TEST_FLAGS) -o test
	./test

gcov_report: s21_matrix.a
	@gcc $(GCOVFLAGS) testest.c $(SOURSES) $(TEST_FLAGS) -o GcovReport
	@./GcovReport
	@lcov -t "GcovReport" -o GcovReport.info -c -d .
	@genhtml -o report GcovReport.info
	@open ./report/index-sort-f.html
	@rm -rf ./*.gcno ./*.gcda ./GcovReport.*  

clean:
	@rm -rf ./*.o ./*.a ./a.out ./GcovReport ./*.gcno ./*.gcda ./report ./*.info ./decimal_o ./*.dSYM ./test ./CPPLINT*

rebuild:
	$(MAKE) clean
	$(MAKE) all
 
 valgrind:
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --tool=memcheck --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt ./test