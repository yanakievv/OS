#!/bin/bash

if [ $(who | grep -o "${1}") ]; then
	printf "No such user.\n"
	exit 1
fi

if [ $# -ne 1 ]; then
	printf "Invalid number of arguments, valid is 1.\n"
	exit 2
fi

while read i; do
	rss=$(echo $i | awk -F ' ' '{print $1}')
	vsz=$(echo $i | awk -F ' ' '{print $2}')
	sort -rn <<<$(echo "scale=2; "${rss}"/"${vsz}" " | bc 2>/dev/null )
done <<<$(ps -e -o rss,vsz)
