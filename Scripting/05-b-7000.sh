#!/bin/bash
read -p "Enter string to search lines for: " str

for i in $@; do
	if [ ! -r "${i}" ]; then
		printf "Argument ${i} is not a readable file !"
		continue
	fi

	printf "$(grep "${str}" "${i}" | wc -l)\n"

done

