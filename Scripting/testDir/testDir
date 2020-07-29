#!/bin/bash
if [ $# -ne 2 ]; then
	echo "Invalid number of arguments! "
	exit 1
fi

if [ ! -r "${1}" ]; then
	echo "First argument not a file! "
	exit 2
fi

write $(cat "${1}" | grep "${2}" | cut -d ' ' -f2)
