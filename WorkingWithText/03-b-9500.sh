#!/bin/bash

if [ $# -ne 1 ]; then
	printf "Invalid number of arguments, valid is 1.\n"
	exit 1
fi

grep -A 1 "${1}" <<<$( who | cat) | tail -1 | cut -d' ' -f1 | write



