#-------------------------------------------------------
#    Узнаем какая ОС, Присваиваем значение флагов
#-------------------------------------------------------

OS = $(shell uname)
ifeq ("$(OS)", "Linux")
    LEAKS_RUN = valgrind ./my_cat
else
    LEAKS_RUN = leaks -atExit -- ./my_cat
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

all: my_cat

my_cat: my_cat.c my_cat.h
	$(CC) my_cat.c $(FLAGS) -o my_cat

test: my_cat
	bash t_cat.sh

clean:
	rm -rf my_cat *.o

leaks: my_cat
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
