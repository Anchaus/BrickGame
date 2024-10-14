CC=gcc
CFLAGS=-std=c11
CFLAGS_REPORT=-fprofile-arcs -ftest-coverage

OS=$(shell uname)
ifeq ($(OS), Darwin)
CFLAGS_TEST=-lcheck
open=open
else
CFLAGS_TEST=-lpthread -lcheck -lsubunit -lm
endif

TETRIS_DIR=brick_game/tetris/
SOURSE_DIR=brick_game/tetris/src/
BUILD_DIR=../build/
DVI_DIR=gui/cli/
TEST_DIR=brick_game/tetris/tests/

LIB_SOURSES=fsm.c
DVI_SOURSES=cli.c
TEST_SOURSES=fsm_tests.c

LIB_OBJ=$(patsubst %.c,%.o,$(LIB_SOURSES))
DVI_OBJ=$(patsubst %.c,%.o,$(DVI_SOURSES))
TEST_OBJ=$(patsubst %.c,%.o,$(TEST_SOURSES))
GCOV_OBJ=$(patsubst %.c,gcov_%.o,$(LIB_SOURSES))

all: gcov_report install

install: dist
	if [ ! -d "$(shell echo ~)/.tetris" ]; then mkdir ~/.tetris/; fi
	touch ~/.tetris/highscore.txt
	echo 0 > ~/.tetris/highscore.txt
	
uninstall: clean
	rm -rf ~/.tetris/

clean:
	rm -rf $(BUILD_DIR)* $(TETRIS_DIR)gcov-report

dvi: 
	$(CC) $(CFLAGS) -c $(patsubst %,$(DVI_DIR)%,$(DVI_SOURSES)) -o $(BUILD_DIR)dvi.o

dist: $(LIB_OBJ) dvi
	$(CC) $(CFLAGS) $(patsubst %,$(BUILD_DIR)%,$(LIB_OBJ)) $(BUILD_DIR)dvi.o $(SOURSE_DIR)tetris.c -o $(BUILD_DIR)tetris -lncurses

test: $(LIB_OBJ) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(patsubst %,$(BUILD_DIR)%,$(LIB_OBJ)) $(patsubst %,$(BUILD_DIR)%,$(TEST_OBJ)) $(TEST_DIR)unit_test.c -o $(BUILD_DIR)unit_test $(CFLAGS_TEST)
	./$(BUILD_DIR)unit_test

gcov_report: $(GCOV_OBJ) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(CFLAGS_REPORT) $(patsubst %,$(BUILD_DIR)%,$(GCOV_OBJ)) $(patsubst %,$(BUILD_DIR)%,$(TEST_OBJ)) $(TEST_DIR)unit_test.c -o $(BUILD_DIR)gcov_unit_test $(CFLAGS_TEST)
	./$(BUILD_DIR)gcov_unit_test
	mkdir -p $(TETRIS_DIR)gcov-report
	gcovr -r ./$(TETRIS_DIR) -e $(TEST_DIR) --html --html-details -o $(TETRIS_DIR)gcov-report/index.html

leak_check: $(LIB_OBJ) $(TEST_OBJ)
	$(CC) $(CFLAGS) -DLEAK_CHECK $(patsubst %,$(BUILD_DIR)%,$(LIB_OBJ)) $(patsubst %,$(BUILD_DIR)%,$(TEST_OBJ)) $(TEST_DIR)unit_test.c -o $(TETRIS_DIR)unit_test $(CFLAGS_TEST)
	valgrind --tool=memcheck --leak-check=yes ./$(TETRIS_DIR)unit_test

$(LIB_OBJ): %.o : $(SOURSE_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $(BUILD_DIR)$@ 

$(TEST_OBJ): %.o : $(TEST_DIR)%.c
	$(CC) $(CFLAGS_TEST) -c $< -o $(BUILD_DIR)$@ $(CFLAGS_TEST)

$(GCOV_OBJ): gcov_%.o : $(SOURSE_DIR)%.c
	$(CC) $(CFLAGS) $(CFLAGS_REPORT) -c $< -o $(BUILD_DIR)$@