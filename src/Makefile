CC=g++
CFLAGS=-Wall -Werror -Wextra -lstdc++ -std=c++17
GTEST=-lgtest -lgtest_main
TFLAGS=$(CFLAGS) $(GTEST)
FSAN=-fsanitize=address
COVER=-fprofile-arcs -ftest-coverage
TESTFILE=./test/main_test.cc
MAINTESTFILES=$(wildcard ./test/s21_*.cc)
BONUSTESTFILES=$(wildcard ./test_bonus/s21_*.cc)
PROJECTFILES=./lib/*.h
PROJECTNAME=s21_containers
BONUSPARTNAME=s21_containersplus
BONUSPARTFILES=./lib_bonus/*.h
GCOVFLAG=
CPPFLAGS=--enable=all --suppress=missingIncludeSystem --inconclusive --check-config $(PROJECTFILES) $(TESTFILES)

ifeq ($(shell uname -s), Linux)
	LEAKS=valgrind --tool=memcheck --leak-check=yes
	TFLAGS+= -lpthread -lrt -lsubunit
else 
	LEAKS=leaks -atExit --
	GCOVFLAG+=--ignore-errors mismatch
endif

#----------------------------------------------------------------------

all: clean clang_format $(PROJECTNAME).h test_main leaks_main clean test_bonus leaks_bonus gcov_report

test: clean
	$(CC) $(CFLAGS) $(TESTFILE) $(MAINTESTFILES) $(BONUSTESTFILES) -o test_full $(GTEST)
	- ./test_full

leaks: test 
	- $(LEAKS) ./test_full

test_main: clean
	$(CC) $(CFLAGS) $(TESTFILE) $(MAINTESTFILES) -o test_full_main $(GTEST)
	- ./test_full_main
	
leaks_main: test_main 
	- $(LEAKS) ./test_full_main

test_bonus: clean
	$(CC) $(CFLAGS) $(TESTFILE) $(BONUSTESTFILES) -o test_full_bonus $(GTEST)
	- ./test_full_bonus
	
leaks_bonus: test_bonus 
	- $(LEAKS) ./test_full_bonus

coverage: clean
	$(CC) $(CFLAGS) $(COVER) $(TESTFILE) $(MAINTESTFILES) $(BONUSTESTFILES) -o test_full $(GTEST)
	./test_full

$(PROJECTNAME).h: clean
	$(CC) $(CFLAGS) -c $(PROJECTNAME).h -o $(PROJECTNAME).o
	ar rcs $(PROJECTNAME).a $(PROJECTNAME).o
	ranlib $(PROJECTNAME).a
	rm -rf *.o
	
$(BONUSPARTNAME).h: clean
	$(CC) $(CFLAGS) -c $(BONUSPARTNAME).h -o $(BONUSPARTNAME).o
	ar rcs $(BONUSPARTNAME).a $(BONUSPARTNAME).o
	ranlib $(BONUSPARTNAME).a
	rm -rf *.o
	
clean:
	rm -rf test_full test_full_bonus test_full_main
	rm -rf ./.vscode
	rm -rf *.a *.o *.out
	rm -rf *.info *.gcda *.gcno *.gcov *.gch *.dSYM
	rm -rf lib/*.gch lib_bonus/*.gch
	rm -rf coverage gcov_report report

clang_format:
	cp ../materials/linters/.clang-format ../.clang-format
	clang-format -n $(PROJECTNAME).h
	clang-format -n $(PROJECTFILES)
	clang-format -n $(TESTFILE)
	clang-format -n $(BONUSPARTNAME).h
	clang-format -n $(MAINTESTFILES)
	clang-format -n $(BONUSPARTFILES)
	clang-format -n $(BONUSTESTFILES)
	rm -rf ../.clang-format
	cppcheck $(CPPFLAGS)

clang_format_apply:
	cp ../materials/linters/.clang-format ../.clang-format
	clang-format -i $(PROJECTNAME).h
	clang-format -i $(PROJECTFILES)
	clang-format -i $(TESTFILE)
	clang-format -i $(BONUSPARTNAME).h
	clang-format -i $(BONUSPARTFILES)
	clang-format -i $(MAINTESTFILES)
	clang-format -i $(BONUSTESTFILES)
	rm -rf ../.clang-format
	
gcov_report: coverage
	geninfo $(GCOVFLAG) . -b . -o ./coverage.info --no-external 
	genhtml coverage.info -o ./coverage
	open coverage/index.html
	

manual_test:
	rm -rf extras/test
	$(CC) $(CFLAGS) extras/ammoshri_ramblings.cc -o extras/test $(GTEST)
	./extras/test
	rm -rf extras/test

manual_test_leaks: 
	rm -rf extras/test
	$(CC) $(CFLAGS) extras/ammoshri_ramblings.cc -o extras/test $(GTEST)
	$(LEAKS) ./extras/test
	rm -rf extras/test
