#!/bin/bash

friends_messages=$(mktemp)

while read friend; do
	messages="$(find "${1}" -mindepth 3 -maxdepth 3 -type f | egrep "${friend}" | xargs -I{} wc -l {} | awk -v "ctr=0" '{ctr+=$1} END {print ctr}')"

	echo "${friend} ${messages}" >> "${friends_messages}"

done < <(find "${1}" -mindepth 3 -maxdepth 3 -type f -printf "%f\n" | sort | uniq)

cat "${friends_messages}" | sort -n -t' ' -k2
