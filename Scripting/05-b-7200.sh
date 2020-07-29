#!/bin/bash

for i in $@; do
	if [ -f "${i}" ] && [ -r "${i}" ]; then
		printf "${i} is a readable file.\n"
	fi

	if [ -d "${i}" ]; then
		files=$(find "${i}" -mindepth 1 -maxdepth 1 -type f | wc -l)
		echo "${files}"
		find "${i}" -mindepth 1 -type f -size "-${files}c"
	fi
done

