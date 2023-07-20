CC=gcc
CCF=-Wall -Werror -Wextra
CFLAGS_GCOV= --coverage

OS = $(shell uname)
ifeq ($(OS), Darwin)
	APPNAME=calc.app/Contents/MacOS/calc
	APP_SRC_DIR=calc/calc.app
	DEBUG_BUILD_DIR=build-calc-Desktop_x86_darwin_generic_mach_o_64bit-Debug
	OS_OPEN=open -a "Google Chrome"
	CFLAGS_TEST= -lcheck -lm 
	LEAK_CHECK = leaks -q --atExit -- 
else
	APPNAME=calc
	APP_SRC_DIR=calc/calc
	DEBUG_BUILD_DIR=build-calc-Desktop-Debug
	OS_OPEN=xdg-open
	CFLAGS_TEST= -lcheck -lm -lpthread -lrt -lsubunit
	LEAK_CHECK = valgrind --tool=memcheck --leak-check=yes --quiet --log-file=./tests/logs/leaks_log.txt ./smartcalc_test
endif

#Dir
CDIR=functions/
HDIR=headers/
TMP_DIR=../tmp/
BUILD_DIR=../build/

#Files
CFILE=$(CDIR)*.c
HFILE=$(HDIR)*.h
SOURCES_TEST = ./tests/test.c
OUTFILE_TEST = $(BUILD_DIR)smartcalc_test

APPFILE=$(BUILD_DIR)$(APPNAME)

#Path
CLANGFILE=$(CFILE) $(HFILE)

all: clean install run

clang: clang-format clang-check

run:
	./$(APPFILE)

dvi:

dist:
	rm -rf Archive_SmartCalc_C1/
	mkdir Archive_SmartCalc_C1/
	mkdir Archive_SmartCalc_C1/src
	mv ./$(APPFILE) Archive_SmartCalc_C1/src/
	tar cvzf Archive_SmartCalc_C1.tgz Archive_SmartCalc_C1/
	rm -rf Archive_SmartCalc_C1/

install: uninstall clean
	mkdir build
	cd calc && qmake && make && make clean && rm Makefile && cd ../ && mv $(APP_SRC_DIR) $(BUILD_DIR)

uninstall:
	rm -rf $(BUILD_DIR)Contents

test: clean 
	$(CC) $(CFLAGS) $(CFILE) $(SOURCES_TEST) $(CFLAGS_TEST) -o $(OUTFILE_TEST)
	./$(OUTFILE_TEST)


leaks: test
	$(LEAK_CHECK) ./$(OUTFILE_TEST)

gcov_report: clean
	$(CC) $(CFLAGS_GCOV) $(CFILE) $(SOURCES_TEST) -o $(TMP_DIR)sc_test $(CFLAGS_TEST)
	./$(TMP_DIR)sc_test
	lcov -t "sc_test" -o $(TMP_DIR)test.info -c -d .
	genhtml -o $(TMP_DIR)report $(TMP_DIR)test.info
	rm -rf *.{a,o,dSYM,out} *.gcda *.gcno

open:
	$(OS_OPEN) $(TMP_DIR)report/index.html

clang: clang-format clang-check

clang-check: 
	cp ../materials/linters/.clang-format .
	clang-format -n -style=Google $(CLANGFILE)
	rm -f .clang-format

clang-format: 
	cp ../materials/linters/.clang-format .
	clang-format -i -style=Google $(CLANGFILE)
	rm -f .clang-format

clean:
	rm -rf *.{a,o,dSYM,out}
	rm -rf gcov_report
	rm -rf $(TMP_DIR)report
	rm -rf CPPLINT.cfg
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf $(TMP_DIR)*.info
	rm -rf Archive_SmartCalc_C1
	rm -rf *tgz
	rm -f $(BUILD_DIR)smartcalc_test
	rm -f $(TMP_DIR)sc_test
	#cd $(DEBUG_BUILD_DIR)/ && make clean && cd ..

save: clean
	git add . && git commit -m "auto save" && git push origin develop