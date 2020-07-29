#!/bin/bash
if [ $# -ne 2 ]; then
	printf "Invalid number of arguments, valid is 2.\n"
	exit 1
fi

if [ ! -d "${1}" ] || [[ ! "${2}" =~ ^[0-9]+$ ]]; then
	printf "First argument must be a directory and second an integer.\n"
	exit 2
fi

find "${1}" -mindepth 1 -maxdepth 1 -type f -size -"${2}c"
