#!/bin/bash

all_modified=$(mktemp)
usr_home=$(mktemp)
cat /etc/passwd | cut -d':' -f 1,6 | tr ':' ' ' > "${usr_home}"
modMax=0
fileMax=0

while read user home; do

	file=$(find "${home}" -type f ! -name ".*" -printf "%T@ %f\n" 2>/dev/null | sort -n -t' ' -k1 | tail -1)
	echo "${file}" >> "${all_modified}"

done < "${usr_home}"

cat "${all_modified}" | sort -t' ' -k1 | tail -1
