#!/bin/bash


value1=$(cat "${1}" | grep "${2}" | cut -d'=' -f2)
value2=$(cat "${1}" | grep "${3}" | cut -d'=' -f2)

newval=""

for term in ${value2}; do
	if fgrep -qv "${term}" <(echo "${value1}"); then
		newval+="${term} "
	fi
done

sed  "s/${3}=${value2}/${3}=${newval}/" "${1}"
