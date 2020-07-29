#!/bin/bash

if [ $# -ne 1 ]; then
	printf "Invalid number of arguments, valid is 1.\n"
	exit 2
elif [[ "${1}" =~ ^[a-zA-Z0-9]+$ ]]; then
	exit 0
else
	exit 1
fi
