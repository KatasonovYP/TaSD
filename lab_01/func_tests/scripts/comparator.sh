#!/bin/bash

if [[ $# -ne 2 ]]; 
then
    exit 1
fi

one=$(grep -Po "[+-]?[0-9]*[.]?[0-9]+" "$1")
two=$(grep -Po "[+-]?[0-9]*[.]?[0-9]+" "$2")

if [[ "$one" == "$two" ]]; 
then
    exit 0
else
    exit 1
fi
