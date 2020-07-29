#!/bin/bash

if [ ! -d "${1}" ] || [ $# -ne 1 ]; then
	printf "Incorrect usage, valid is <dir>.\n"
	exit 1
fi

tars=$(mktemp)

find "${1}" | egrep 


