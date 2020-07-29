#!/bin/bash

if [ ! -f "${1}" ] || [ ! -f "${2}" ]; then
	printf "Arguments must be files.\n"
	exit 1
fi

if [ $# -ne 2 ]; then
	printf "Invalid usage. Valid is bash ./ex27.sh <csvfile> <csvfile>.\n"
	exit 2
fi

sorted=$(mktemp)
cat "${1}" | sort -n  > "${sorted}"


while read line; do
	containts="$(echo "${line}" | cut -d ',' -f2,3,4)"
	newfound="$(cat "${sorted}" | egrep "^[0-9],${containts}$" | head -1)"

	if [ ! "$(cat "${2}" | fgrep "${newfound}")" ]; then
		echo "${newfound}" >> "${2}"
	fi
	
done <<< "$(cat "${1}")"
