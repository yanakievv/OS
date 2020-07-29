#!/bin/bash

if [ ! -d ${1} ]; then
	printf "First argument must be a directory.\n"
	exit 1
fi

files=($(find "${1}" -maxdepth 1 -type f -printf "%f\n"))
sizes=($(find "${1}" -maxdepth 1 -type f | xargs -I{} stat {} | grep "Size" | cut -f1 | cut -d':' -f2))

drs=($(find "${1}" -maxdepth 1 -mindepth 1 -type d -printf "%f\n"))
entries=($(find "${1}" -maxdepth 1 -mindepth 1 -type d | xargs -I{} find {} -maxdepth 1 -mindepth 1 | wc -l))


i=0
length="${#files[@]}"

while [ ${i} -lt ${length} ]; do
	printf "${files[${i}]} (${sizes[${i}]} bytes)\n"
	i=$(expr "${i}" + 1)
done

i=0
length="${#drs[@]}"

while [ ${i} -lt ${length} ]; do
	if [ -z "${entries[${i}]}" ]; then
		entries[${i}]=0
	fi
	printf "${drs[${i}]} (${entries[${i}]} entires)\n"
	i=$(expr "${i}" + 1)
done
