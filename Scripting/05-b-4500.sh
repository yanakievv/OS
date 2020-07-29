#!/bin/bash
if [ $# -ne 1 ]; then
	printf "Invalid number of arguments, valid is 1\n"
	exit 1
fi
while true;
do
	for u in $(who | grep "${1}" | uniq)
	do
		if [ "${1}" = "${u}" ]; then
			printf "User is currently logged in.\n"
			exit 0
		fi
	sleep 60
	done

	printf "No such user logged in at the moment.\n"

done
exit 2
