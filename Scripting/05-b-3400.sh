#!/bin/bash

if [ $# -ne 2 ]; then
	printf "Invalid number of arguments, valid is 2.\n"
	exit 10
fi

if [ -z "${1}" ] || [ ! -r "${2}" ]; then
	printf "Arguments must be a string and a readable file.\n"
	exit 11
fi

grep -o "${1}" "${2}" | wc -l

echo "$?"
