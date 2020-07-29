#!/bin/bash

if [ $# -ne 1 ] || [ ! -d "${}" ]; then
	printf "Incorrect usage, valid is bash ex13.sh <dirname>\n"
	exit 1
fi

find "${1}" -type l | grep 'broken' | cut -d ':' -f1
