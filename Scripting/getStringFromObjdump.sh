#!/bin/bash

if [ $# -ne 1 ]; then
        printf "Invalid number of arguments.\n"
        printf "Usage: ./getStringFromObjdump.sh [executable] \n"
        printf "Command objdump is ran with flag -d.\n"
        printf "See OBJDUMP(1) for more info.\n"
        exit 1
fi

var=$(objdump -d $1 | grep -A10000 '<.text>' | tail +2 | cut -f2 | tr -d "\n" | tr -d " ")
ctr=0
hasNull=0

for ((i = 0; i < "${#var}"; i+=2)); do
        printf "%s\\\x${var:$i:2}"

        if [ "${var:$i:2}" == "00" ]; then
                hasNull=$((hasNull+1))
        fi

        ctr=$((ctr+1))
done

printf "\nNumber of instructions: ${ctr}\n"
printf "Null Bytes: ${hasNull}\n"

exit 0
