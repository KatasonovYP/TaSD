#!/bin/bash

in=$1
app=./app.exe
result=./out.txt
log_val=./valgrind_info/$(basename $1)

[[ $2 == "" ]] && args="" || args=$(cat "$2")
[[ $USE_VALGRIND == 1 ]] && vgc="valgrind --log-file=${log_val}" || vgc=""

$vgc "$app" $args <"$in" >"$result" && exit 1 || exit 0