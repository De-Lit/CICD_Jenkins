#-------------------------------------------------------
#    Узнаем какая ОС, Присваиваем значение флагов
#-------------------------------------------------------

OS = $(shell uname)
ifeq ("$(OS)", "Linux")
    LEAKS_RUN = valgrind ./my_grep
else
    LEAKS_RUN = leaks -atExit -- ./my_grep
endif

FLAGS = -Wall -Wextra -Werror -std=c11

#-------------------------------------------------------
#    Переменная для компилятора
#-------------------------------------------------------

CC = gcc

#-------------------------------------------------------
#    Переменная которая указывает на наш Makefile
#-------------------------------------------------------

THIS_FILE := $(lastword $(MAKEFILE_LIST))

#-------------------------------------------------------
#    Цели
#-------------------------------------------------------

all: my_grep

my_grep: my_grep.c my_grep.h
	$(CC) my_grep.c $(FLAGS) -o my_grep

test: my_grep
	bash t_grep.sh

clean:
	rm -rf my_grep *.o

leaks: my_grep
	$(LEAKS_RUN) $(PARAMS)
	@$(MAKE) -f $(THIS_FILE) clean

make_google_style:
	cp ../../../materials/linters/.clang-format .clang-format
	clang-format -i -verbose *my*.c *my*.h
	rm .clang-format

clang:
	cp ../../../materials/linters/.clang-format .clang-format
	clang-format -n -verbose *my*.c *my*.h
	rm .clang-format
