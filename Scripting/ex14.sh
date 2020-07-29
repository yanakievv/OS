#!/bin/bash

if [ $# -ne 1 ]; then
	printf "Invalid number of arguments. Usage $0 <number>.\n"
	exit 1
fi

if [[ !  "${1}" =~ ^[+-]?[0-9]+$ ]]; then
	printf "Invalid argument.\n"
	exit 2
fi

f=$(mktemp)

ps -e -o rss,pid,user | grep -v "root" > $f

while read rss pid user; do
	echo "\n ${rss} \n"
	if [ "${rss}" -gt "${1}" ]; then
		echo "${pid}, ${user}"
	fi
done < $f

