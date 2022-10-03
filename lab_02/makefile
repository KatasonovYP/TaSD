CFLAGS = -std=c99 -Wall -Werror -Wpedantic -Wextra 
CFLAGS += -Wfloat-equal -Wfloat-conversion -Wvla -fdiagnostics-color=always
CFLAGS += -I "inc"

# CHECK_FLAGS = -lcheck_pic -lm -lsubunit
CHECK_FLAGS := $(shell pkg-config --cflags --libs check)
CC = gcc

SRCS = io.c
OBJS = $(SRCS:%.c=out/%.o)

T_SRCS = check_io.c
T_OBJS = $(T_SRCS:%.c=out/%.o)

SHELL = bash

# Сборка исполняемых файлов
app.exe : $(OBJS) out/main.o
	$(CC) $^ -o $@ -lm

unit_tests.exe: $(T_OBJS) $(OBJS) out/check_main.o
	$(CC) $^ -o $@ $(CHECK_FLAGS)
# -pthread -lrt

# Генерация объектных файлов
out/%.o : src/%.c out/%.d
	$(CC) $< -c -o $@ $(CFLAGS)

out/%.o : unit_tests/%.c out/%.d
	$(CC) $< -c -o $@ $(CFLAGS)

# Генерация файлов зависимостей
out/%.d : inc/%.h src/%.c
	echo -n "out/" > $@
	$(CC) -MM $< >> $@

out/%.d : inc/%.h unit_tests/%.c
	echo -n "out/" > $@
	$(CC) -MM $< >> $@

C_DEPS = $(SRCS:%.c=out/%.d)
T_DEPS = $(T_SRCS:%.c=out/%.d)

$(C_DEPS) :
$(T_DEPS) :

include $(wildcard $(C_DEPS))
include $(wildcard $(T_DEPS))

.PHONY : clean release debug

clean :
	find . -type f -name '*.o' -delete
	find . -type f -name '*.d' -delete
	find . -type f -name '*.exe' -delete
	find ./valgrind_info -type f -name '*.txt' -delete

release: CFLAGS += -O2
release: app.exe

debug: CFLAGS += -g3
debug: app.exe

unit: CFLAGS += -g3
unit: unit_tests.exe
unit: run_unit

clean_valgrind_info:
	find ./valgrind_info -type f -name '*.txt' -delete
	

func: build_func_tests clean_valgrind_info debug app.exe run_func

run_func:
	./func_tests/scripts/func_tests.sh -e -v

run_unit:
	valgrind --log-file=valgrind_info.txt --leak-check=full --track-origins=yes ./unit_tests.exe

build_func_tests:
	python3 func_tests/scripts/make_tests.py
