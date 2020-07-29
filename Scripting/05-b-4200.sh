#!/bin/bash

if [ ! -r "${1}" ]; then
	printf "Argument must be a readable file.\n"
	exit 1
fi

if [ $# -ne 1 ]; then
	printf "Invalid number of arguments, valid is 1.\n"
	exit 2
fi

parantheses=$(cat "${1}" | sed "s/[^{}]//g" | tr -d "\n"  | sed "s/}{//g")

echo "$(expr length "${parantheses}" / 2)"


