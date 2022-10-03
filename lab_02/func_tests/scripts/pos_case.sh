#!/bin/bash

in=$1
out=$2
app=./app.exe
result=./out.txt
comp=./func_tests/scripts/comparator.sh
log_val=./valgrind_info/$(basename $1)

[[ $3 == "0" ]] && args="" || args=$(cat "$3")
[[ $USE_VALGRIND == 1 ]] && vgc="valgrind --log-file=${log_val}" || vgc=""

if $vgc "$app" $args <"$in" >"$result" && "$comp" "$out" "$result"
then
    exit 0
else
    exit 1
fi