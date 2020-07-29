#!/bin/bash
if [ $# -ge 3 ]; then
	printf "Invalid number of arguments, valid is 1 or 2.\n"
	exit 1
fi

dir=$(date | tr "[ :]" "-")

if [ $# -eq 2 ]; then
	if [[ "${2}" =~ (/)$ ]]; then
		
		dir=${2::-1}
	else
		dir="${2}"
	fi
else
	mkdir"${dir}"
fi

find "${1}" -type f -cmin -45 | xargs -I{} cp {} "${dir}"

read -p "Arhive new directory?(y/n): " ans

if [[ "${ans}" =~ [yY] ]]; then
	tar -zcvf "${dir}".tar.gz "${dir}"
fi

echo "${dir}"
