#!/bin/bash

if [ $# -ne 1 ]; then
	printf "Invalid number of arguments, valid is 1.\n"
fi

if [ ! -d ${1} ]; then
	printf "Argument must be a directory.\n"
fi


files=($(find "${1}" -type f -printf "%f\n" | sort -n))

i=0

length="${#files[@]}"

while [ ${i} -lt ${length} ]; do
	find "${1}" ! -name "${files[${i}]}" -type f | xargs -I{} diff -rsq --from-file {} "${1}/${files[${i}]}" | grep 'identical' | cut -d ' ' -f2 | xargs -I{} rm {}
	i=$(expr ${i} + 1)
done
