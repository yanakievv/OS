#!/bin/bash
if [ $# -lt 1 ]; then
	printf "Invalid number of arguments! Valid is 1.\n"
	exit 1
fi

delimiter=" "

if [ $# -eq 2 ]; then
	delimiter="${2}"
elif [ $# -ne 1 ]; then
	printf "Invalid number of arguments! Valid is 1.\n"
	exit 1
fi

if ! [[ "${1}" =~ ^[0-9\-][0-9]+$ ]]; then
	printf "First argument is not an integer!\n"
	exit 2
fi

length=$(expr length "${1}")

nums=($(grep -o [0-9] <<< "${1}"))

i=0

if [[ "${1}" =~ ^- ]]; then
	printf "-"
fi

while [ "${i}" -lt "${length}" ]; do
	if [ $(( i%3 )) -eq 0 ] && [ "${i}" -ne 0 ]; then
		printf " "
	fi
	printf "${nums[${i}]}"
	i=$(( i+1 ))
done
