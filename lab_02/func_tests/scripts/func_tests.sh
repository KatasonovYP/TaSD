#!/bin/bash

GREEN="\033[32m"
RED="\033[31m"
BLUE="\033[34m"
END="\033[0m"

pos_cnt=$(find func_tests/data/ -name "pos*in*" | wc -l)
neg_cnt=$(find func_tests/data/ -name "neg*in*" | wc -l)
pos_failed=0
neg_failed=0

USE_VALGRIND=0
SHOW_ERROR=0
while [ -n "$1" ]
do
    case "$1" in
        -v) export USE_VALGRIND=1 ;;
        -e) SHOW_ERROR=1 ;;
        *) echo "$1 is not an option";;
    esac
    shift
done


for ((i=1; i <= pos_cnt; ++i))
do
    [[ $i -lt 10 ]] && number="0$i" || number="$i"
    
    test_in="func_tests/data/pos_${number}_in.txt"
    test_out="func_tests/data/pos_${number}_out.txt"
    test_args="func_tests/data/pos_${number}_args.txt"
    result="./out.txt"
    if ! [[ -f $test_args ]]
    then
        test_args=""
    fi

    if func_tests/scripts/pos_case.sh $test_in $test_out $test_args
    then
        echo -e "POS TEST $number ${GREEN}PASS${END}"
    else
        echo -e "POS TEST $number ${RED}FAIL${END}"
        pos_failed=$(( pos_failed + 1 ))
        if [[ $SHOW_ERROR == 1 ]]
        then
            echo -e "${BLUE}----------${END}"
            echo -e "${BLUE}INPUT:${END}"
            cat $test_in
            echo -e "${BLUE}NEED:${END}"
            cat $test_out
            echo -e "${BLUE}GOT:${END}"
            cat $result
            echo -e "${BLUE}----------${END}"
        fi
    fi
done
echo

for ((i=1; i <= neg_cnt; ++i))
do
    [[ $i -lt 10 ]] && number="0$i" || number="$i"
    
    test_in="func_tests/data/neg_${number}_in.txt"
    test_out="func_tests/data/neg_${number}_out.txt"
    test_args="func_tests/data/neg_${number}_args.txt"
    if ! [[ -f $test_args ]]
    then
        test_args=""
    fi

    if func_tests/scripts/neg_case.sh $test_in $test_args
    then
        echo -e "NEG TEST $number ${GREEN}PASS${END}"
    else
        echo -e "NEG TEST $number ${RED}FAIL${END}"
        neg_failed=$(( neg_failed + 1 ))
        if [[ $SHOW_ERROR == 1 ]]
        then
            echo -e "${BLUE}----------${END}"
            echo -e "${BLUE}INPUT:${END}"
            cat $test_in
            echo -e "${BLUE}NEED:${END}"
            cat $test_out
            echo -e "${BLUE}GOT:${END}"
            cat $result
            echo -e "${BLUE}----------${END}"
        fi
    fi
done

# Удаление ненужных логов valgrind
for file in $(ls valgrind_info)
do
    path="valgrind_info/${file}"
    if grep -Fq 'no leaks are possible' ${path}  && grep -Fq 'ERROR SUMMARY: 0 errors' ${path}
    then
        find ./valgrind_info -type f -name "${file}" -delete
    fi
done

unset USE_VALGRIND

echo -e "Positive tests: correct $(( pos_cnt - pos_failed )) of ${pos_cnt};"
echo -e "Negative tests: correct $(( neg_cnt - neg_failed )) of ${neg_cnt};"

exit $(( neg_failed + pos_failed ))
