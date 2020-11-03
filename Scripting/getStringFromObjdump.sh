#!/bin/bash

if [ $# -ne 1 ]; then
	printf "Invalid number of arguments.\n"
	printf "Usage: ./getStringFromObjdump.sh [executable] \n"
	printf "Command objdump is ran with flag -d.\n"
	printf "See OBJDUMP(1) for more info.\n"
	exit 1
fi

var=$(objdump -d $1 | grep -A10000 '<.text>' | tail +2 | cut -f2 | tr -d "\n" | tr -d " ")

for ((i = 0; i < "${#var}"; i+=2)); do
	printf "%s\\\x${var:$i:2}"
done

exit 0

