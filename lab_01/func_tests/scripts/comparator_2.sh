#!/bin/bash

expression="[-]?[0-9]+*"

one=$(grep -E "$expression" "$1")
two=$(grep -E "$expression" "$2")

[ "$one" == "$two" ] && exit 0 || exit 1