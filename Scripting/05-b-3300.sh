#!/bin/bash

if [ $# -ne 3 ]; then
	printf "Invalid number of arguments, valid is 3.\n"
	exit 1
fi
if [ ! -r $1 ] || [ ! -r $2 ] || [ ! -r $3 ]; then
	printf "Arguments must be readable files.\n"
	exit 2
fi

echo $(paste "${1}" "${2}") > "${3}" 
