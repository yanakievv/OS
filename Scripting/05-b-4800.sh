#!/bin/bash
if [ ! -r "${1}" ] || [ ! -d "${2}" ]; then
	printf "Arguments must be a file and a directory.\n"
	exit 1
fi

if [ $# -ne 2 ]; then
	printf "Invalid number of arguments.\n"
	exit 2
fi

find "${2}" | xargs -I{} diff -rsq --from-file {} "${1}" | grep 'identical'
exit 0
