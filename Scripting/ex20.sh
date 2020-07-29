#!/bin/bash

if [ $(id -u) -ne 0 ]; then
	printf "Must be root.\n"
	exit 1
fi

src="${1}"
dst="${2}"
str="${3}"

if [ $(find "${dst}" -mindepth 1 2>/dev/null | wc -l) -ne 0 ]; then
	printf "Destination must be an empty directory.\n"
	exit 2
fi

find "${src}" -type f -name "*${str}*" | xargs -I{} cp {} "${dst}" 
